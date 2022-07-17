#include "em_private.h"

/* $Id: exc.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_exc(arith c1,arith c2)
{
	PS(ps_exc);
	CST(c1);
	COMMA();
	CST(c2);
	NL();
}
