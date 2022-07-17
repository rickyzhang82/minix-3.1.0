#include "em_private.h"

/* $Id: psdnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_psdnam(int op,const char *dnam)
{
	/*	Pseudo with data label
	*/
	PS(op);
	DNAM(dnam);
	NL();
}
