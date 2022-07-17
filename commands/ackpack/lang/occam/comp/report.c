/* $Id: report.c,v 1.1 2005/09/01 12:13:23 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern int err, lineno;
extern char *curr_file;

/*VARARGS1*/
void
report(const char * fmt, ... )
{
	va_list va;
	fprintf(stderr, "%s (%d) F: ", curr_file, lineno);
	va_start( va, fmt );
	vfprintf(stderr, fmt, va);
	va_end( va );
	fprintf(stderr,"\n");
	err=1;
}

/*VARARGS1*/
void
warning(const char * fmt, ... )
{
	va_list va;
	fprintf(stderr, "%s (%d) E: ", curr_file, lineno);
	va_start( va, fmt );
	vfprintf(stderr, fmt, va);
	va_end( va );
	fprintf(stderr,"\n");
}

/*VARARGS1*/
void
fatal(const char * fmt, ... )
{
	va_list va;
	fprintf(stderr, "%s (%d) X: ", curr_file, lineno);
	va_start( va, fmt );
	vfprintf(stderr, fmt, va);
	va_end( va );
	fprintf(stderr,"\n");
	exit(1);
}
