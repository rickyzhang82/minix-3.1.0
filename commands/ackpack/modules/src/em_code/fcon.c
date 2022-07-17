#include "em_private.h"

/* $Id: fcon.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_fcon(const char *val,arith siz)
{
	COMMA();
	WCON(sp_fcon, val, siz);
}
