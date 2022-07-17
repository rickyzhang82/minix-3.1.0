/* 
 * putw - write an word on a stream
 */
/* $Header: /cvsup/minix/src/lib/other/putw.c,v 1.1.1.1 2005/04/21 14:56:27 beng Exp $ */

#include	<stdio.h>

_PROTOTYPE(int putw, (int w, FILE *stream ));

int
putw(w, stream)
int w;
register FILE *stream;
{
	register int cnt = sizeof(int);
	register char *p = (char *) &w;

	while (cnt--) {
		putc(*p++, stream);
	}
	if (ferror(stream)) return EOF;
	return w;
}
