#include "em_private.h"

/* $Id: crpnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crpnam(int op,const char *p)
{
	/*	CON or ROM with argument PNAM(p)
	*/
	PS(op);
	PNAM(p);
	CEND();
	NL();
}
