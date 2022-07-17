#include "em_private.h"

/* $Id: crxcon.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_crxcon(int op,int spec,const char *v,arith s)
{
	/*	CON or ROM with argument ICON(v,z)
	*/
	PS(op);
	WCON(spec, v, s);
	CEND();
	NL();
}
