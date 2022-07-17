/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* RCS: $Id: system.h,v 1.3 2005/09/01 12:13:27 beng Exp $ */
#ifndef __SYSTEM_INCLUDED__
#define __SYSTEM_INCLUDED__

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/* flags previously used for sys_open(): now used by archiver */
#define OP_READ		01
#define OP_WRITE	02
#define OP_APPEND	04

/* flags for sys_seek() */
#ifndef SEEK_SET
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
#endif

/* macros for sys_stat() and file modes */
#define _ACK_IS_TYPE(m,f)	(((m) & 0xf000) == (m))

#define ACK_ISDIR(m)	_ACK_IS_TYPE((m),0x4000)	/* Directory */
#define ACK_ISCHR(m)	_ACK_IS_TYPE((m),0x2000)	/* Char. device */
#define ACK_ISBLK(m)	_ACK_IS_TYPE((m),0x6000)	/* Block device */
#define ACK_ISREG(m)	_ACK_IS_TYPE((m),0x8000)	/* Regular file */

#define ACK_ISUID	0x0800		/* Set user ID on exec */
#define ACK_ISGID	0x0400		/* Set group ID on exec */
#define ACK_ISVTX	0x0200		/* Stick bit (save swapped text) */
#define ACK_IREAD	0x0100		/* Read by owner */
#define ACK_IWRITE	0x0080		/* Write by owner */
#define ACK_IEXEC	0x0040		/* Exec by owner */

int sys_read(FILE *, char *, size_t, size_t *);
int sys_write(FILE *, const char *, size_t);
int sys_seek(FILE *, long, int, long *);
long sys_time(void);

/* maximum number of open files */
#define SYS_NOPEN	20

/* return value for sys_break */
#define ILL_BREAK	((char *)0)

/* system's idea of block */
#ifdef BUFSIZ
#define ACK_BUFSIZ	BUFSIZ
#else
#define ACK_BUFSIZ	1024
#endif
#endif /* __SYSTEM_INCLUDED__ */
