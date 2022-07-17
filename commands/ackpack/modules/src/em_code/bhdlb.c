#include "em_private.h"

/* $Id: bhdlb.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */

void
CC_bhdlb(int op,arith n,label s,arith off,int i)
{
	/*	BSS or HOL with size n, initial value a dlb(s, off),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	DOFF(s, off);
	COMMA();
	CST((arith) i);
	NL();
}
