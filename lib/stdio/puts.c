/*
 * puts.c - print a string onto the standard output stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/puts.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>

int
puts(register const char *s)
{
	register FILE *file = stdout;
	register int i = 0;

	while (*s) {
		if (putc(*s++, file) == EOF) return EOF;
		else i++;
	}
	if (putc('\n', file) == EOF) return EOF;
	return i + 1;
}
