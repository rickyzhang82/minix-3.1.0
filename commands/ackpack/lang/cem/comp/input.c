/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: input.c,v 1.1 2005/09/01 12:13:19 beng Exp $ */

#include "prototypes.h"
#include "inputtype.h"
#include "file_info.h"
#include "input.h"
#include <ack_string.h>

#define INP_PUSHBACK	3
#define INP_TYPE	struct file_info
#define INP_VAR		finfo
struct file_info	finfo;
#include "nopp.h"
#include <inp_pkg.body>
#include <alloc.h>

#include        "dbsymtab.h"
#include	"lint.h"
#ifndef NOPP
#ifdef DBSYMTAB
#include <stb.h>
#include <em.h>
extern int      IncludeLevel;
extern char	options[];
#endif

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
		return "";

	if( fn < e )
	{
		char * p = Salloc(fn,e-fn+1);
		p[e-fn] = '\0';
		return p;
	}
	return ".";
}

int	InputLevel;
extern int		nestlevel;
#endif /* NOPP */

int	NoUnstack;

int
AtEoIT(void)
{
#ifndef NOPP
	InputLevel--;
	unstackrepl();
#endif /* NOPP */
	return 0;
}

extern char *source;

int
AtEoIF(void)
{
#ifndef NOPP
	if (nestlevel != nestlow) lexwarning("missing #endif");
	else
#endif /* NOPP */
	if (NoUnstack) lexerror("unexpected EOF");
#ifndef NOPP
	nestlevel = nestlow;
#ifdef DBSYMTAB
	if (options['g'] && IncludeLevel > 0) {
		C_ms_stb_cst(FileName, N_EINCL, 0, (arith) 0);
	}
	IncludeLevel--;
#endif
	if (WorkingDir[0] != '\0') free(WorkingDir);
#endif /* NOPP */
#ifndef LINT
	/* Ideally free the current file name; the only problem is
	 * that the name could be referenced by many different structures,
	 * including:
	 *	ahead.tok_file
	 *	dot.tok_file
	 *	finfo.fil_name		== FileName
	 * So freeing this string can cause the error messages to become
	 * garbled. It is lesser evil to accept a memory leak than it is
	 * to dereference freed memory...
	 *
	 * The difficulty is knowing when all references to the filename
	 * have been released.
	 */
#ifdef XXX_DONT_ACCEPT_A_MEMORY_LEAK
	if (FileName != source) free(FileName);
#endif
#endif
	return 0;
}
