#include "em_private.h"

/* $Id: bhilb.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */

void
CC_bhilb(int op,arith n,label l,int i)
{
	/*	BSS or HOL with size n, initial value a ILB(l),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	ILB(l);
	COMMA();
	CST((arith) i);
	NL();
}
