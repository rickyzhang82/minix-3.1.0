#include "em_private.h"

/* $Id: bhpnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_bhpnam(int op,arith n,const char *p,int i)
{
	/*	BSS or HOL with size n, initial value a PNAM(p),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	PNAM(p);
	COMMA();
	CST((arith) i);
	NL();
}
