/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* D E F I N I T I O N   M O D U L E S */

/* $Id: defmodule.c,v 1.1 2005/09/01 12:13:21 beng Exp $ */

#include	"debug.h"

#include	<assert.h>
#include	<em_arith.h>
#include	<em_label.h>
#include	<alloc.h>
#include	<ack_string.h>

#include	"prototypes.h"
#include	"input.h"
#include	"Lpars.h"
#include	"f_info.h"
#include	"main.h"
#include	"misc.h"

#ifdef DEBUG
long	sys_filesize();
#endif

t_idf *DefId;

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

STATIC
int
GetFile(const char *name)
{
	/*	Try to find a file with basename "name" and extension ".def",
		in the directories mentioned in "DEFPATH".
	*/
	char buf[15];

	strncpy(buf, name, 10);
	buf[10] = '\0';			/* maximum length */
	strcat(buf, ".def");
	DEFPATH[0] = WorkingDir;
	if (! InsertFile(buf, DEFPATH, &(FileName))) {
		error("could not find a DEFINITION MODULE for \"%s\"", name);
		return 0;
	}
	WorkingDir = getwdir(FileName);
	LineNumber = 1;
	DO_DEBUG(options['F'], debug("File %s : %ld characters", FileName, sys_filesize(FileName)));
	return 1;
}

t_def *
GetDefinitionModule(t_idf *id,int incr)
{
	/*	Return a pointer to the "def" structure of the definition
		module indicated by "id".
		We may have to read the definition module itself.
		Also increment level by "incr".
	*/
	register t_def *df;
	static int level;
	t_scopelist *vis;
	const char *fn = FileName;
	int ln = LineNumber;
	t_scope *newsc;

	level += incr;
	df = lookup(id, GlobalScope, D_IMPORTED, 0);
	if (!df) {
		/* Read definition module. Make an exception for SYSTEM.
		*/
		extern int ForeignFlag;

		ForeignFlag = 0;
		DefId = id;
		open_scope(CLOSEDSCOPE);
		newsc = CurrentScope;
		vis = CurrVis;
		newsc->sc_defmodule = incr;
		if (!strcmp(id->id_text, "SYSTEM")) {
			do_SYSTEM();
			df = lookup(id, GlobalScope, D_IMPORTED, 0);
		}
		else {
			if (!is_anon_idf(id) && GetFile(id->id_text)) {

				const char *f = FileName;
				DefModule();
				df = lookup(id, GlobalScope, D_IMPORTED, 0);
				if (level == 1 &&
				    (df && !(df->df_flags & D_FOREIGN))) {
					/* The module is directly imported by
					   the currently defined module, and
					   is not foreign, so we have to
					   remember its name because we have 
					   to call its initialization routine
					*/
					static t_node *nd_end;
					register t_node *n;
					extern t_node *Modules;

					n = dot2leaf(Def);
					n->nd_def = newsc->sc_definedby;
					if (nd_end) nd_end->nd_NEXT = n;
					else Modules = n;
					nd_end = n;
				}
				free(f);
			}
			else {
				df = lookup(id, GlobalScope, D_IMPORTED, 0);
				newsc->sc_name = id->id_text;
			}
		}
		close_scope(SC_CHKFORW);
		if (! df) {
			df = MkDef(id, GlobalScope, D_ERROR);
			df->mod_vis = vis;
			newsc->sc_definedby = df;
		}
	}
	else if (df->df_flags & D_BUSY) {
		error("definition module \"%s\" depends on itself",
			id->id_text);
	}
	else if (df == Defined && level == 1) {
		error("cannot import from current module \"%s\"", id->id_text);
		df->df_kind = D_ERROR;
	}
	FileName = fn;
	LineNumber = ln;
	assert(df);
	level -= incr;
	return df;
}
