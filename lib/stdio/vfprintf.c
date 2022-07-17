/*
 * vfprintf - formatted output without ellipsis
 */
/* $Header: /cvsup/minix/src/lib/stdio/vfprintf.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>
#include	<stdarg.h>
#include	"loc_incl.h"

int
vfprintf(FILE *stream, const char *format, va_list arg)
{
	return _doprnt (format, arg, stream);
}
