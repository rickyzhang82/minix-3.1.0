#include "em_private.h"

/* $Id: bhicon.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */

void
CC_bhicon(int op,arith n,const char *s,arith sz,int i)
{
	/*	BSS or HOL with size n, initial value an ICON (s, sz),
		and flag i
	*/
	PS(op);
	CST(n);
	COMMA();
	WCON(sp_icon, s, sz);
	COMMA();
	CST((arith) i);
	NL();
}
