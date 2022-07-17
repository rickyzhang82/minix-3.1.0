/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef lint
static char rcsid[] = "$Id: error.c,v 1.3 2005/09/01 12:13:33 beng Exp $";
#endif

#include <stdio.h>
#include <out.h>
#include <system.h>
#include "const.h"
#include <stdarg.h>
#ifndef _WIN32
# include <unistd.h>
#endif

static short	nerrors = 0;

extern char	*progname, *archname, *modulname; 
extern char	*outputname;
extern int	exitstatus;


static
void
diag(char *tail,char * format,va_list ap)
{
	fprintf(stderr, "%s: ", progname);
	if (archname && modulname)
		fprintf(stderr, "%s(%.14s): ", archname, modulname);
	else if (archname)
		fprintf(stderr, "%s: ", archname);
	else if (modulname)
		fprintf(stderr, "%s: ", modulname);

	vfprintf(stderr, format, ap );

	if (tail) fprintf(stderr, " (%s)\n", tail);
	else putc('\n', stderr);
}

void
stop(void)
{
	if (nerrors) {
		unlink(outputname);
		exit(nerrors);
	}

	exit(exitstatus);
}

/* VARARGS1 */
void
fatal(char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	nerrors++;
	diag("fatal", format, ap);
	va_end(ap);
	stop();
}

/* VARARGS1 */
void
warning(char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	diag("warning", format, ap);
	va_end(ap);
}

/* VARARGS1 */
void
error(char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	nerrors++;
	diag("error", format, ap);
	va_end(ap);
}

/* VARARGS1 */
int
do_verbose(char *format, ...)
{
	va_list ap;
	va_start(ap,format);
	diag((char *) 0, format, ap);
	va_end(ap);
	return 0;
}

