/*
 * scanf.c - read formatted input from the standard input stream
 */
/* $Header: /cvsup/minix/src/lib/stdio/scanf.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>
#include	<stdarg.h>
#include	"loc_incl.h"

int
scanf(const char *format, ...)
{
	va_list ap;
	int retval;

	va_start(ap, format);

	retval = _doscan(stdin, format, ap);

	va_end(ap);

	return retval;
}


