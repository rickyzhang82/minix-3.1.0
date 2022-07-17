/* $Header: /cvsup/minix/src/lib/ansi/atexit.c,v 1.1.1.1 2005/04/21 14:56:04 beng Exp $ */

#include	<stdlib.h>

#define	NEXITS	32

extern void (*__functab[NEXITS])(void);
extern int __funccnt;

int
atexit(void (*func)(void))
{
	if (__funccnt >= NEXITS)
		return 1;
	__functab[__funccnt++] = func;
	return 0;
}
