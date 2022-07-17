/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef lint
static char rcsid[] = "$Id: write.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <arch.h>
#include <out.h>
#include <ranlib.h>
#include <object.h>
#include <stdio.h>
#include "const.h"
#include "assert.h"
#include "memory.h"
#include "prototypes.h"

extern struct outhead	outhead;
extern struct outsect	outsect[];
extern int		flagword;
extern bool		incore;
extern unsigned short	NGlobals;
extern long		NGChars;

void
wr_fatal(void)
{
	fatal("write error");
}

static long		off_char;

/*
 * Open the output file according to the chosen strategy.
 * Write away the header and section table: they will not change anymore.
 */
void
begin_write(void)
{
	register struct outhead *hd = &outhead;

	assert(! incore);
	wr_ohead(hd);
	wr_sect(outsect, hd->oh_nsect);
	off_char = OFF_CHAR(*hd);
}

static
struct outname *
sectname(int sectindex)
{
	static struct outname	namebuf;

	namebuf.on_foff = (long)0;	/* No string name. */
	namebuf.on_type = (S_MIN + sectindex) | S_SCT;
	namebuf.on_desc = 0;
	namebuf.on_valu = outsect[sectindex].os_base;

	return &namebuf;
}

/*
 * Write out the symbol table and the section names.
 */
void
end_write(void)
{
	register struct outname	*name;
	register int		sectindex;

	assert(!incore);
	assert(!(flagword & SFLAG));
	name = (struct outname *)address(ALLOGLOB, (ind_t)0);
	namecpy(name, NGlobals, off_char);
	wr_name(name, NGlobals);
	wr_string(malloc_base+mems[ALLOGCHR].mem_offset+1, NGChars);
	off_char += NGChars;

	for (sectindex = 0; sectindex < outhead.oh_nsect; sectindex++)
		wrt_name(sectname(sectindex), 1);
}
	
void
wrt_emit(char *emit,int sectindex,long cnt)
{

	wr_outsect(sectindex);
	wr_emit(emit, cnt);
}

void
wrt_nulls(int sectindex,long cnt)
{
	static char nullbuf[BUFSIZ];

	wr_outsect(sectindex);
	while (cnt) {
		register int n = cnt >= BUFSIZ ? BUFSIZ : cnt;
		wr_emit(nullbuf, (long)n);
		cnt -= n;
	}
}

void
wrt_name(struct outname *name,int writename)
{
	assert(!incore);
	assert(!(flagword & SFLAG));
	if (name->on_mptr != (char *)0) {
		register long	len = strlen(name->on_mptr) + 1;

		wr_string(name->on_mptr, len);
		name->on_foff = off_char;
		off_char += len;
	} else {
		name->on_foff = (long)0;
	}
	if (writename) wr_name(name, 1);
}
