#include "em_private.h"

/* $Id: dnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_dnam(const char *str,arith val)
{
	COMMA();
	NOFF(str, val);
}
