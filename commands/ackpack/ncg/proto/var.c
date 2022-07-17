#ifndef NORCSID
static char rcsid[] = "$Id: var.c,v 1.1 2005/09/01 12:13:28 beng Exp $";
#endif

#include "param.h"
#include "tables.h"
#include "types.h"
#include <cgg_cg.h>
#include "data.h"
#include "result.h"

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */

int stackheight = 0;
token_t fakestack[MAXFSTACK];
int nallreg = 0;
int allreg[MAXALLREG];
token_p curtoken = (token_p) 0;
result_t dollar[LONGESTPATTERN];
int nemlines =0;
struct emline emlines[MAXEMLINES];
struct emline *emp=emlines;
struct emline *saveemp;
int tokpatlen;
rl_p curreglist;
