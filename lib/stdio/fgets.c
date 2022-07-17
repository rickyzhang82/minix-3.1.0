/*
 * fgets.c - get a string from a file
 */
/* $Header: /cvsup/minix/src/lib/stdio/fgets.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

char *
fgets(char *s, register int n, register FILE *stream)
{
	register int ch;
	register char *ptr;

	ptr = s;
	while (--n > 0 && (ch = getc(stream)) != EOF) {
		*ptr++ = ch;
		if ( ch == '\n')
			break;
	}
	if (ch == EOF) {
		if (feof(stream)) {
			if (ptr == s) return NULL;
		} else return NULL;
	}
	*ptr = '\0';
	return s;
}
