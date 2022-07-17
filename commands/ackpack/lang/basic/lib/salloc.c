/* $Id: salloc.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

#include <stdlib.h>
#include "internal.h"

char *
salloc(unsigned int length)
{
	char *c, *s;
	c= malloc(length);
	if( !c ) error(5);
	for(s=c;s<c+length;s++) *s = 0;
	return(c);
}

void
sfree(char *c)
{
	if( !c ) return;
	free(c);
}
