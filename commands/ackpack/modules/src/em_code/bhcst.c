#include "em_private.h"

/* $Id: bhcst.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */

void
CC_bhcst(int op,arith n,arith w,int i)
{
	/*	BSS or HOL with size n, initial value a cst w, and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	CST(w);
	COMMA();
	CST((arith) i);
	NL();
}
