#include "em_private.h"

/* $Id: crdlb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crdlb(int op,label v,arith off)
{
	/*	CON or ROM with argument DLB(v, off)
	*/
	PS(op);
	DOFF(v, off);
	CEND();
	NL();
}
