#ifndef NORCSID
static char rcsid[] = "$Id: equiv.c,v 1.1 2005/09/01 12:13:27 beng Exp $";
#endif

#include "prototypes.h"
#include "equiv.h"
#include "extern.h"

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */

int rar[MAXCREG];
rl_p *lar;
int maxindex;
int regclass[NREGS];
struct perm *perms;

static
void
permute(int index)
{
	register struct perm *pp;
	register rl_p rlp;
	register i,j;

	if (index == maxindex) {
		for (pp=perms; pp != 0; pp=pp->p_next) {
			for (i=0; i<maxindex; i++)
				if (regclass[rar[i]] != regclass[pp->p_rar[i]])
					goto diff;
			for (i=0; i<maxindex; i++) {
				int rari = rar[i], p_rari = pp->p_rar[i];
				for (j=0; j<i; j++)
					if (clash(rari,rar[j]) !=
					    clash(p_rari,pp->p_rar[j]))
						goto diff;
			}
			return;
		    diff: ;
		}
		pp = (struct perm *) myalloc(sizeof ( *pp ));
		pp->p_next = perms;
		for (i=0; i<maxindex; i++)
			pp->p_rar[i] = rar[i];
		perms = pp;
	} else {
		rlp=lar[index];
		for (i=rlp->rl_n; i>0; i--) {
			rar[index] = rlp->rl_list[rlp->rl_n-i];
			permute(index+1);
		}
	}
}


struct perm *
tuples(rl_p *regls,int nregneeded)
{
	int class=0;
	register i,j;
	register struct reginfo *rp;

	/*
	 * First compute equivalence classes of registers.
	 */

	for (i=NREGS, rp = &machregs[NREGS-1];--i>=0;rp--) {
		regclass[i] = class++;
		if (getrefcount(i, FALSE) == 0) {
			for (j=NREGS;--j>i;) {
				if (eqregclass(i,j) &&
				    eqtoken(&rp->r_contents,
					    &machregs[j].r_contents)) {
					regclass[i] = regclass[j];
					break;
				}
			}
		}
	}

	/*
	 * Now create tuples through a recursive function
	 */

	maxindex = nregneeded;
	lar = regls;
	perms = 0;
	permute(0);
	return(perms);
}
