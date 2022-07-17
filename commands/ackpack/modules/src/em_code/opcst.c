#include "em_private.h"

/* $Id: opcst.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

void
CC_opcst(int opcode,arith cst)
{
	/*	Instruction with a constant argument
		Argument types: c, d, l, g, f, n, s, z, o, w, r
	*/
	OP(opcode);
	CST(cst);
	NL();
}
