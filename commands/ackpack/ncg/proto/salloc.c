#ifndef NORCSID
static char rcsid[] = "$Id: salloc.c,v 1.1 2005/09/01 12:13:28 beng Exp $";
#endif

#include "prototypes.h"
#include "extern.h"

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */

/*
 * Package for string allocation and garbage collection.
 * Call salloc(size) to get room for string.
 * Every now and then call garbage_collect() from toplevel.
 */

#define MAXSTAB         1500
#define THRESHOLD       200

static char *stab[MAXSTAB];
int nstab=0;

string
myalloc(int size)
{
	register string p;

	p = (string) malloc((unsigned)size);
	if (p==0)
		fatal("Out of memory");
	return(p);
}

void
myfree(string p)
{
	free(p);
}

void
popstr(int nnstab)
{
	register i;

	for (i=nnstab;i<nstab;i++)
	{
		myfree(stab[i]);
		stab[i]=0;
	}
	nstab = nnstab;
}

/* Address of each string is stored in nstab */
char *
salloc(int size)
{
	register char *p;

	if (nstab==MAXSTAB)
		fatal("String table overflow");
	p = myalloc(size+1);    /* extra room for terminating zero */
	stab[nstab++] = p;
	return(p);
}

/* Order nstab by element address; since each element is allocated
 * by malloc() all addresses are distinct.
 */
static
int
compar(const void * p1,const void * p2)
{
	assert(*(const char**)p1 != *(const char**)p2);
	if (*(const char**)p1 < *(const char**)p2)
		return(-1);
	return(1);
}

/* Search for string in table, and if found, mark as used.
 *
 * Assumes all addresses are distinct, and ordered.
 */
static
void
chkstr(string str,char used[])
{
	int low,middle,high;

	low=0; high=nstab-1;
	while (high>low) {
		middle= (low+high)>>1;
		if (str==stab[middle]) {
			used[middle]=1;
			return;
		}
		if (str<stab[middle])
			high = middle-1;
		else
			low = middle+1;
	}
	if (low==high) {
		if (str==stab[low]) {
			used[low]=1;
		}
		return;
	}
}

void
garbage_collect(void)
{
	register i;
	struct emline *emlp;
	token_p tp;
	tkdef_p tdp;
	struct reginfo *rp;
	register char **fillp,**scanp;
	char used[MAXSTAB];     /* could be bitarray */

	if (nstab<THRESHOLD)
		return;
	qsort(stab,nstab,sizeof(char *),compar);
	for (i=0;i<nstab;i++)
		used[i]= FALSE;
	for(emlp=emlines;emlp<emlines+nemlines;emlp++)
		chkstr(emlp->em_soper,used);
	for (tp= fakestack;tp<&fakestack[stackheight];tp++) {
		if (tp->t_token== -1)
			continue;
		tdp = &tokens[tp->t_token];
		for (i=0;i<TOKENSIZE;i++)
			if (tdp->t_type[i] == EV_ADDR)
				chkstr(tp->t_att[i].aa.ea_str,used);
	}
	for (rp= machregs+1; rp<machregs+NREGS; rp++) {
		tp = &rp->r_contents;
		assert(tp->t_token != -1);
		tdp= &tokens[tp->t_token];
		for (i=0;i<TOKENSIZE;i++)
			if (tdp->t_type[i] == EV_ADDR)
				chkstr(tp->t_att[i].aa.ea_str,used);
	}
	for (i=0;i<nstab;i++)
		if (!used[i]) {
			myfree(stab[i]);
			stab[i]=0;
		}
	fillp=stab;
	for (scanp=stab;scanp<stab+nstab;scanp++)
		if (*scanp != 0)
			*fillp++ = *scanp;
	nstab = fillp-stab;
}

