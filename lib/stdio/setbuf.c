/*
 * setbuf.c - control buffering of a stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/setbuf.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>
#include	"loc_incl.h"

void
setbuf(register FILE *stream, char *buf)
{
	(void) setvbuf(stream, buf, (buf ? _IOFBF : _IONBF), (size_t) BUFSIZ);
}
