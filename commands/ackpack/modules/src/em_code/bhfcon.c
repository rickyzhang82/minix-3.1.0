#include "em_private.h"

/* $Id: bhfcon.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */

void
CC_bhfcon(int op,arith n,const char *s,arith sz,int i)
{
	/*	BSS or HOL with size n, initial value an FCON (s, sz),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	WCON(sp_fcon, s, sz);
	COMMA();
	CST((arith) i);
	NL();
}
