#include "em_private.h"

/* $Id: crdnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crdnam(int op,const char *s,arith off)
{
	/*	CON or ROM with argument DNAM(s, off)
	*/
	PS(op);
	NOFF(s, off);
	CEND();
	NL();
}
