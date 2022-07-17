/*
 * fputc.c - print an unsigned character
 */
/* $Header: /cvsup/minix/src/lib/stdio/fputc.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

int
fputc(int c, FILE *stream)
{
	return putc(c, stream);
}
