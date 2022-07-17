#include "em_private.h"

/* $Id: endarg.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_endnarg(void)
{
	/*	END pseudo of procedure with unknown # of locals
	*/
	PS(ps_end);
	CCEND();
	NL();
}
