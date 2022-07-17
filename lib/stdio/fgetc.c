/*
 * fgetc - get an unsigned character and return it as an int
 */
/* $Header: /cvsup/minix/src/lib/stdio/fgetc.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

int
fgetc(FILE *stream)
{
	return getc(stream);
}
