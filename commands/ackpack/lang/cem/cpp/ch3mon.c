/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: ch3mon.c,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* EVALUATION OF MONADIC OPERATORS */

#include	"Lpars.h"
#include	"arith.h"

/*ARGSUSED2*/
void
ch3mon(int oper,arith *pval,int *puns)
{
	switch (oper)	{
	case '~':
		*pval = ~(*pval);
		break;
	case '-':
		*pval = -(*pval);
		break;
	case '!':
		*pval = !(*pval);
		break;
	}
}
