#include "em_private.h"

/* $Id: op.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_op(int opcode)
{
	/*	Instruction that never has an argument
		Argument types: -
	*/
	OP(opcode);
	NL();
}
