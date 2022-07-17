#include <stdio.h>
#include <stdlib.h>
#include "internal.h"

/* $Id: random.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

#if !defined(EM_WSIZE)
#define EM_WSIZE _EM_WSIZE
#endif

void
_setrand(int i)
{
	srand(i);
}

void
_randomi(void)
{
	int i;
	_setchan(-1);
	printf("Random number seed (-32768 to 32767) ? ");
	_readint(&i);
	_setrand(i);
}

double
_rnd(double d)
{
	double f; f= (int) rand();
	return(f/
#if EM_WSIZE == 4
		2147483647.0
#else
		32767.0
#endif
	);
}
