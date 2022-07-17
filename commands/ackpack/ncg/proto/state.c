#ifndef NORCSID
static char rcsid[] = "$Id: state.c,v 1.1 2005/09/01 12:13:28 beng Exp $";
#endif

#include "prototypes.h"
#include "extern.h"

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */

extern int nstab;	/* salloc.c */

void
savestatus(state_p sp)
{
	sp->st_sh = stackheight;
	memmove(sp->st_fs,fakestack,stackheight*sizeof(token_t));
	sp->st_na = nallreg;
	memmove(sp->st_ar,allreg,nallreg*sizeof(int));
	sp->st_ct = curtoken;
	memmove(sp->st_do,dollar,LONGESTPATTERN*sizeof(result_t));
	memmove(sp->st_mr,machregs,NREGS*sizeof(struct reginfo));
	sp->st_ne = nemlines;
	memmove(sp->st_el,emlines,nemlines*sizeof(struct emline));
	sp->st_em = emp;
	sp->st_se = saveemp;
	sp->st_tl = tokpatlen;
	sp->st_ns = nstab;
}

void
restorestatus(state_p sp)
{
	stackheight = sp->st_sh;
	memmove(fakestack,sp->st_fs,stackheight*sizeof(token_t));
	nallreg = sp->st_na;
	memmove(allreg,sp->st_ar,nallreg*sizeof(int));
	curtoken = sp->st_ct;
	memmove(dollar,sp->st_do,LONGESTPATTERN*sizeof(result_t));
	memmove(machregs,sp->st_mr,NREGS*sizeof(struct reginfo));
	nemlines = sp->st_ne;
	memmove(emlines,sp->st_el,nemlines*sizeof(struct emline));
	emp = sp->st_em;
	saveemp = sp->st_se;
	tokpatlen = sp->st_tl;
	popstr(sp->st_ns);
}

