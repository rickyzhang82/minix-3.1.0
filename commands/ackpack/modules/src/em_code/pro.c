#include "em_private.h"

/* $Id: pro.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_pro(const char *pnam,arith l)
{
	/*	PRO pseudo with procedure name pnam and # of locals l
	*/
	PS(ps_pro);
	PNAM(pnam);
	COMMA();
	CST(l);
	NL();
}
