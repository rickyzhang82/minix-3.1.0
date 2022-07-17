/*
 * vprintf - formatted output without ellipsis to the standard output stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/vprintf.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>
#include	<stdarg.h>
#include	"loc_incl.h"

int
vprintf(const char *format, va_list arg)
{
	return _doprnt(format, arg, stdout);
}
