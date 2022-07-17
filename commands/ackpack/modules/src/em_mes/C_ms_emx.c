/* $Id: C_ms_emx.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <em.h>
#include <em_mes.h>

void
C_ms_emx(arith wsiz,arith psiz)
{
	C_mes_begin(ms_emx);
	C_cst(wsiz);
	C_cst(psiz);
	C_mes_end();
}
