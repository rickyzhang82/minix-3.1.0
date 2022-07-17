#include <stdio.h>
#include <stdlib.h>

/* $Id: asrt.c,v 1.1 2005/09/01 12:13:17 beng Exp $ */

void
asrt(int b)
{
	if(!b){
		printf("ASSERTION ERROR\n");
		abort();
	}
}
