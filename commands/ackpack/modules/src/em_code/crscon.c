#include "em_private.h"

/* $Id: crscon.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crscon(int op,const char *v,arith s)
{
	/*	CON or ROM with argument SCON(v,z)
	*/
	PS(op);
	SCON(v, s);
	CEND();
	NL();
}
