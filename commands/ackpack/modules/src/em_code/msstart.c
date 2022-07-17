#include "em_private.h"

/* $Id: msstart.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_msstart(int cst)
{
	/*	start of message
	*/
	PS(ps_mes);
	CST((arith)cst);
}
