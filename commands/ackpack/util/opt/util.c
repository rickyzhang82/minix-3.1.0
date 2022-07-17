#ifndef NORCSID
static char rcsid[] = "$Id: util.c,v 1.3 2005/09/01 12:13:35 beng Exp $";
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "param.h"
#include "types.h"
#include "tes.h"
#include "assert.h"
#include "lookup.h"
#include "proinf.h"
#include "optim.h"
#include "ext.h"

#ifdef _WIN32
# include <io.h>
#endif

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */


/* VARARGS1 */
void
error(char * fmt,...)
{
	va_list va;
	fprintf(stderr,"%s: error on line %u",progname,linecount);
	if (prodepth != 0)
		fprintf(stderr,"(%.*s)",IDL,curpro.symbol->s_name);
	fprintf(stderr,": ");
	va_start(va,fmt);
	vfprintf(stderr,fmt,va);
	va_end(va);
	fprintf(stderr,"\n");
#ifndef NDEBUG
	abort();
#endif
	exit(-1);
}

#ifndef NDEBUG
void
badassertion(char * file,unsigned int line)
{
	fprintf(stderr,"assertion failed file %s, line %u\n",file,line);
	error("assertion");
}
#endif

#ifdef DIAGOPT
void
optim(int n)
{
	fprintf(stderr,"Made optimization %d",n);
	if (prodepth)
		fprintf(stderr," (%.*s)",IDL,curpro.symbol->s_name);
	fprintf(stderr,"\n");
}
#endif
