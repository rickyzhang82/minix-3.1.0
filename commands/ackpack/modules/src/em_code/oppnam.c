#include "em_private.h"

/* $Id: oppnam.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_oppnam(int opcode,const char *pnam)
{
	/*	Instruction that has a procedure name as argument
		Argument types: p
	*/
	OP(opcode);
	PNAM(pnam);
	NL();
}
