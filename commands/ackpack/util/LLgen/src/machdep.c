/* Copyright (c) 1991 by the Vrije Universiteit, Amsterdam, the Netherlands.
 * For full copyright and restrictions on use see the file COPYING in the top
 * level of the LLgen tree.
 */

/*
 *  L L G E N
 *
 *  An Extended LL(1) Parser Generator
 *
 *  Author : Ceriel J.H. Jacobs
 */

/*
 * machdep.c
 * Machine dependant things
 */

#ifndef _WIN32
# include <unistd.h>
#endif
#include "system.h"
#include "types.h"
#include "prototypes.h"

# ifndef NORCSID
static const_string rcsid5 = "$Id: machdep.c,v 1.3 2005/09/01 12:13:29 beng Exp $";
# endif

/* In this file the following routines are defined: */
#if 0
extern void	UNLINK(const_string);
extern void	RENAME(const_string,const_string);
extern string	libpath(const_string);
#endif

void
UNLINK(const_string x)
{
	unlink(x);
}

void
RENAME(const_string x,const_string y)
{
	/* Must move the file "x" to the file "y" */

	unlink( y );
#if defined( _WIN32 ) && !defined( __CYGWIN__ )
	if( 0 != rename( x, y ) )
		fatal( 1, "Cannot rename to %s", y );
#else
	if( 0 != link( x, y ) )
		fatal( 1, "Cannot rename to %s", y );
	unlink( x );
#endif
}

/* Have problems defining a string define in POMAKE */
#ifdef __POCC__
# undef LIBDIR
# define LIBDIR "ignored"
#endif

/* Allow compilation... an explicit warning would be nice... */
#ifndef LIBDIR
# define LIBDIR "undefined"
#endif

/* to make it easier to patch ... */
static char _libdir[256] = LIBDIR;
char * libdir = _libdir;

string
libpath(const_string s)
{
	/* Must deliver a full pathname to the library file "s" */

	register string p;
	register int length;

	length = strlen(libdir) + strlen(s) + 2;
	p = (string) alloc((unsigned) length);
	strcpy(p,libdir);
	strcat(p,"/");
	strcat(p,s);
	return p;
}
