#include "em_private.h"

/* $Id: end.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_end(arith l)
{
	/*	END pseudo of procedure with l locals
	*/
	PS(ps_end);
	CST(l);
	NL();
}
