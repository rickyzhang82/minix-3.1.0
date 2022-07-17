#include "em_private.h"

/* $Id: bhucon.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_bhucon(int op,arith n,const char *s,arith sz,int i)
{
	/*	BSS or HOL with size n, initial value an UCON (s, sz),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	WCON(sp_ucon, s, sz);
	COMMA();
	CST((arith) i);
	NL();
}
