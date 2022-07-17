/*
 * fprintf - write output on a stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/fprintf.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>
#include	<stdarg.h>
#include	"loc_incl.h"

int
fprintf(FILE *stream, const char *format, ...)
{
	va_list ap;
	int retval;
	
	va_start(ap, format);

	retval = _doprnt (format, ap, stream);

	va_end(ap);

	return retval;
}
