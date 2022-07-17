#include <stdio.h>
#include <stdlib.h>
#include "internal.h"

/* $Id: stop.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

void
_stop(void)
{
	extern int _erlsym;

	_setline();
	printf("Break in %d\n", _erlsym);
	exit(0);
}
