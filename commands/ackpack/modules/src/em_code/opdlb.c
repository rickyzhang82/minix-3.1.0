#include "em_private.h"

/* $Id: opdlb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_opdlb(int opcode,label dlb,arith offset)
{
	/*	Instruction that as a numeric datalabel + offset as argument
		Argument types: g
	*/
	OP(opcode);
	DOFF(dlb, offset);
	NL();
}
