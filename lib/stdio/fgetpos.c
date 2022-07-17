/*
 * fgetpos.c - get the position in the file
 */
/* $Header: /cvsup/minix/src/lib/stdio/fgetpos.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

int
fgetpos(FILE *stream, fpos_t *pos)
{
	*pos = ftell(stream);
	if (*pos == -1) return -1;
	return 0;
}
