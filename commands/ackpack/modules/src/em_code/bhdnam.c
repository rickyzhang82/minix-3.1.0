#include "em_private.h"

/* $Id: bhdnam.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */

void
CC_bhdnam(int op,arith n,const char *s,arith off,int i)
{
	/*	BSS or HOL with size n, initial value a dnam(s, off),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	NOFF(s, off);
	COMMA();
	CST((arith) i);
	NL();
}
