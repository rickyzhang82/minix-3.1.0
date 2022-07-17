/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: input.c,v 1.1 2005/09/01 12:13:20 beng Exp $ */

#include "prototypes.h"
#include "input.h"

#define INP_PUSHBACK	3
#define INP_TYPE	struct file_info
#define INP_VAR		finfo
struct file_info	finfo;
#include <inp_pkg.body>
#include <alloc.h>
#include "ack_string.h"

const char *
getwdir(const char *fn)
{
	const char * e;

	/* Find end of string */
	for( e = fn ; *e ; ++e )
		;
	/* Remove all trailing /'s */
	while( fn <= e && e[-1] == '/' )
		--e;

	/* Now scan back to the last / in the path */
	while( fn <= e && *e != '/' )
		--e;

	/* Absolute path? (or empty string) */
	if( e == fn || '\0' == fn[0] )
		return Salloc( "", 1 );

	if( fn < e )
	{
		char * p = Salloc(fn,e-fn+1);
		p[e-fn] = '\0';
		return p;
	}
	return Salloc( ".", 2 );
}

int	NoUnstack;
int	InputLevel;

int
AtEoIT(void)
{
	InputLevel--;
	/* if (NoUnstack) warning("unexpected EOF"); ??? */
	unstackrepl();
	return 0;
}

int
AtEoIF(void)
{
	extern int nestlevel;
	extern int nestcount;
	extern int svnestlevel[];

	if (nestlevel > svnestlevel[nestcount]) warning("missing #endif");
	else if (NoUnstack) warning("unexpected EOF");
	nestlevel = svnestlevel[nestcount--];
	return 0;
}
