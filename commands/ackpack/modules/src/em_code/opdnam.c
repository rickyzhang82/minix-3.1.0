#include "em_private.h"

/* $Id: opdnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_opdnam(int opcode,const char *dnam,arith offset)
{
	/*	Instruction that has a datalabel + offset as argument
		Argument types: g
	*/
	OP(opcode);
	NOFF(dnam, offset);
	NL();
}
