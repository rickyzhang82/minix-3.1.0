/*
 * gets.c - read a line from a stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/gets.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

char *
gets(char *s)
{
	register FILE *stream = stdin;
	register int ch;
	register char *ptr;

	ptr = s;
	while ((ch = getc(stream)) != EOF && ch != '\n')
		*ptr++ = ch;

	if (ch == EOF) {
		if (feof(stream)) {
			if (ptr == s) return NULL;
		} else return NULL;
	}

	*ptr = '\0';
	return s;
}
