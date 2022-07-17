/*
 * fputs - print a string
 */
/* $Header: /cvsup/minix/src/lib/stdio/fputs.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

int
fputs(register const char *s, register FILE *stream)
{
	register int i = 0;

	while (*s) 
		if (putc(*s++, stream) == EOF) return EOF;
		else i++;

	return i;
}
