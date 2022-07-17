#include <stdlib.h>
#include "internal.h"

/* $Id: hlt.c,v 1.1 2005/09/01 12:13:17 beng Exp $ */

void
_hlt(int nr)
{
	exit(nr);
}

void
_goto_err(void)
{
	error(3);
}
