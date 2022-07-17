/*-
 * Copyright (c) 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)rec_close.c	8.9 (Berkeley) 11/18/94";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/uio.h>
#ifdef RECNO_USE_MMAP
#include <sys/mman.h>
#endif

#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#include <db.h>
#include "recno.h"

/*
 * __REC_CLOSE -- Close a recno tree.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__rec_close(dbp)
	DB *dbp;
{
	BTREE *t;
	int status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	if (__rec_sync(dbp, 0) == RET_ERROR)
		return (RET_ERROR);

	/* Committed to closing. */
	status = RET_SUCCESS;
#ifdef	RECNO_USE_MMAP
	if (F_ISSET(t, R_MEMMAPPED) && munmap(t->bt_smap, t->bt_msize))
		status = RET_ERROR;
#endif

	if (!F_ISSET(t, R_INMEM))
		if (F_ISSET(t, R_CLOSEFP)) {
			if (fclose(t->bt_rfp))
				status = RET_ERROR;
		} else
			if (close(t->bt_rfd))
				status = RET_ERROR;

	if (__bt_close(dbp) == RET_ERROR)
		status = RET_ERROR;

	return (status);
}

#if _MINIX
static ssize_t writev(int fildes, const struct iovec *iov, int iovcnt)
{
	int i, r;
	char *p;
	ssize_t l, sum;

	/* We should buffer */
	sum= 0;
	for (i= 0; i<iovcnt; i++)
	{
		p= iov[i].iov_base;
		l= iov[i].iov_len;
		while (l > 0)
		{
			r= write(fildes, p, l);
			if (r <= 0)
			{
				assert(sum == 0);
				return r;
			}
			p += r;
			l -= r;
			sum += r;
		}
	}
	return sum;
}

#define panic(str) { fprintf(stderr, "vi panic: %s\n", (str)); abort(); }

int treetrunc(BTREE *bt, off_t off)
{
	char *fn = NULL, *t;
	char copybuf[4096];
	int tmpfd, ok = 1;
	off_t rem, chunk;

	if(!(fn = strdup(bt->bt_savename)) ||
	     fn[0] != '/' || !(t = strrchr(fn, '/'))) {
		if(fn) free(fn);
		return (RET_ERROR);
	}

	/* Prepare template for mkstemp(). */
	t++;
	while(*t) *t++ = 'X';

	if((tmpfd = mkstemp(fn)) < 0) {
		free(fn);
		return (RET_ERROR);
	}

	if(lseek(bt->bt_rfd, 0, SEEK_SET) == -1)
		return (RET_ERROR);

	for(rem = off; rem > 0; rem -= chunk) {
		chunk = rem;
		if(chunk > sizeof(copybuf))
			chunk = sizeof(copybuf);
		if(read(bt->bt_rfd, copybuf, chunk) != chunk ||
		   write(tmpfd, copybuf, chunk) != chunk) {
			ok = 0;
			break;
		}
	}

	close(tmpfd);

	if(ok) {
		if(close(bt->bt_rfd) < 0)
			panic("close failed in ftruncate clone");
		if(unlink(bt->bt_savename) < 0)
			panic("unlink failed in ftruncate clone");
		if(rename(fn, bt->bt_savename) < 0)
			panic("rename failed in ftruncate clone");
		if((bt->bt_rfd = open(bt->bt_savename, bt->bt_saveflags, bt->bt_savemode)) < 0)
			panic("re-open failed in ftruncate clone");
	}

	if(lseek(bt->bt_rfd, (off_t)off, SEEK_SET) < 0)
		panic("lseek failed in ftruncate clone");

	free(fn);

	if(!ok) return (RET_ERROR);

	return (RET_SUCCESS);
}
#endif

/*
 * __REC_SYNC -- sync the recno tree to disk.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
 */
int
__rec_sync(dbp, flags)
	const DB *dbp;
	u_int flags;
{
	struct iovec iov[2];
	BTREE *t;
	DBT data, key;
	off_t off;
	recno_t scursor, trec;
	int status;

	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	if (flags == R_RECNOSYNC)
		return (__bt_sync(dbp, 0));

	if (F_ISSET(t, R_RDONLY | R_INMEM) || !F_ISSET(t, R_MODIFIED))
		return (RET_SUCCESS);

	/* Read any remaining records into the tree. */
	if (!F_ISSET(t, R_EOF) && t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
		return (RET_ERROR);

	/* Rewind the file descriptor. */
	if (lseek(t->bt_rfd, (off_t)0, SEEK_SET) != 0)
		return (RET_ERROR);

	/* Save the cursor. */
	scursor = t->bt_cursor.rcursor;

	key.size = sizeof(recno_t);
	key.data = &trec;

	if (F_ISSET(t, R_FIXLEN)) {
		/*
		 * We assume that fixed length records are all fixed length.
		 * Any that aren't are either EINVAL'd or corrected by the
		 * record put code.
		 */
		status = (dbp->seq)(dbp, &key, &data, R_FIRST);
		while (status == RET_SUCCESS) {
			if (write(t->bt_rfd, data.data, data.size) != data.size)
				return (RET_ERROR);
			status = (dbp->seq)(dbp, &key, &data, R_NEXT);
		}
	} else {
		iov[1].iov_base = &t->bt_bval;
		iov[1].iov_len = 1;

		status = (dbp->seq)(dbp, &key, &data, R_FIRST);
		while (status == RET_SUCCESS) {
			iov[0].iov_base = data.data;
			iov[0].iov_len = data.size;
			if (writev(t->bt_rfd, iov, 2) != data.size + 1)
				return (RET_ERROR);
			status = (dbp->seq)(dbp, &key, &data, R_NEXT);
		}
	}

	/* Restore the cursor. */
	t->bt_cursor.rcursor = scursor;

	if (status == RET_ERROR)
		return (RET_ERROR);
	if ((off = lseek(t->bt_rfd, (off_t)0, SEEK_CUR)) == -1)
		return (RET_ERROR);
#if _MINIX
	if (treetrunc(t, off) != RET_SUCCESS) {
		return (RET_ERROR);
	}
#else
	if (ftruncate(t->bt_rfd, off))
		return (RET_ERROR);
#endif
	F_CLR(t, R_MODIFIED);
	return (RET_SUCCESS);
}


