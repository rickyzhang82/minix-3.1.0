/*
 * fscanf.c - read formatted input from stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/fscanf.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>
#include	<stdarg.h>
#include	"loc_incl.h"

int
fscanf(FILE *stream, const char *format, ...)
{
	va_list ap;
	int retval;

	va_start(ap, format);

	retval = _doscan(stream, format, ap);

	va_end(ap);

	return retval;
}
