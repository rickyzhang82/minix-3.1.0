#include "em_private.h"

/* $Id: crcst.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crcst(int op,arith v)
{
	/*	CON or ROM with argument CST(v)
	*/
	PS(op);
	CST(v);
	CEND();
	NL();
}
