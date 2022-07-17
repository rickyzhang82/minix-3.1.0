#include "em_private.h"

/* $Id: crilb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crilb(int op,label l)
{
	/*	CON or ROM with argument ILB(l)
	*/
	PS(op);
	ILB(l);
	CEND();
	NL();
}
