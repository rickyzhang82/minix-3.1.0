#include "em_private.h"

/* $Id: opilb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_opilb(int opcode,label ilb)
{
	/*	Instruction with instruction label argument
		Argument types: b
	*/
	OP(opcode);
	CILB(ilb);
	NL();
}
