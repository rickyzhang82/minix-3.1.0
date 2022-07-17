#include "em_private.h"

/* $Id: pspnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_pspnam(int op,const char *pnam)
{
	/*	Pseudo with procedure name
	*/
	PS(op);
	PNAM(pnam);
	NL();
}
