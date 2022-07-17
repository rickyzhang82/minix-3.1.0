/*
 * printf - write on the standard output stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/printf.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>
#include	<stdarg.h>
#include	"loc_incl.h"

int
printf(const char *format, ...)
{
	va_list ap;
	int retval;

	va_start(ap, format);

	retval = _doprnt(format, ap, stdout);

	va_end(ap);

	return retval;
}
