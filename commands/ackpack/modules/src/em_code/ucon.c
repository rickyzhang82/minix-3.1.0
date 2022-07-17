#include "em_private.h"

/* $Id: ucon.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_ucon(const char *val,arith siz)
{
	COMMA();
	WCON(sp_ucon, val, siz);
}
