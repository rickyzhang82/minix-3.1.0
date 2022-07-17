#include "em_private.h"

/* $Id: scon.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_scon(const char *str,arith siz)
{
	COMMA();
	SCON(str, siz);
}
