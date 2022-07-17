/*
 * rewind.c - set the file position indicator of a stream to the start
 */
/* $Header: /cvsup/minix/src/lib/stdio/rewind.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>
#include	"loc_incl.h"

void
rewind(FILE *stream)
{
	(void) fseek(stream, 0L, SEEK_SET);
	clearerr(stream);
}
