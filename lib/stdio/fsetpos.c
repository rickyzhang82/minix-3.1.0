/*
 * fsetpos.c - set the position in the file
 */
/* $Header: /cvsup/minix/src/lib/stdio/fsetpos.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

int
fsetpos(FILE *stream, fpos_t *pos)
{
	return fseek(stream, *pos, SEEK_SET);
}
