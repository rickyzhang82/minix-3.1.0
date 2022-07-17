#include "bc_string.h"
#include "internal.h"

/* $Id: asc.c,v 1.1 2005/09/01 12:13:17 beng Exp $ */

int
_asc(String *str)
{
	if(str==0 || str->strval==0)
		error(3);
	return( *str->strval);
}
