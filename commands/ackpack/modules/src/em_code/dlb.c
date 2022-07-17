#include "em_private.h"

/* $Id: dlb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_dlb(label l,arith val)
{
	COMMA();
	DOFF(l, val);
}
