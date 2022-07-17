#include "em_private.h"

/* $Id: opnarg.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_opnarg(int opcode)
{
	/*	Instruction with optional argument, but now without one
		Argument types: w
	*/
	OP(opcode);
	CCEND();
	NL();
}
