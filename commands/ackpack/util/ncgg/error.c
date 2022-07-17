/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef NORCSID
static char rcsid[]= "$Id: error.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "extern.h"

int nerrors=0;

void
yyerror(char *s)
{
	error("Parser gives %s",s);
}

void
goodbye(void)
{
	error("This was fatal, goodbye!");
#ifndef NDEBUG
	abort();
#endif
}

static
void
verror(char * s, va_list args)
{
	extern int lineno;
	extern char *filename;

	fprintf(stderr,"\"%s\", line %d:",filename,lineno);
	vfprintf(stderr,s,args);
	fprintf(stderr,"\n");
	nerrors++;
}

/*VARARGS1*/
void
fatal(char * s,...)
{
	va_list args;

	va_start(args,s);
	verror(s,args);
	va_end(args);
	errorexit();
	goodbye();
	exit(-1);
}

/*VARARGS1*/
void
error(char *s,...)
{
	va_list args;

	va_start(args,s);
	verror(s,args);
	va_end(args);
}

#ifndef NDEBUG
void
badassertion(char *string,char *file,int line)
{
	fprintf(stderr,"\"%s\", line %d: Assertion failed \"%s\"\n",
		file,line,string);
	goodbye();
}
#endif

int
tabovf(char *string)
{
	fatal("%s overflow",string);
	return 0;
}
