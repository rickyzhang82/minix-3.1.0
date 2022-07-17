#include "em_private.h"

/* $Id: psdlb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_psdlb(int op,label dlb)
{
	/*	Pseudo with numeric datalabel
	*/
	PS(op);
	DLB(dlb);
	NL();
}
