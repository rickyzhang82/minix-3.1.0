#include "em_private.h"

/* $Id: pronarg.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_pronarg(const char *pnam)
{
	/*	PRO pseudo with procedure name pnam and unknown # of locals
	*/
	PS(ps_pro);
	PNAM(pnam);
	COMMA();
	CCEND();
	NL();
}
