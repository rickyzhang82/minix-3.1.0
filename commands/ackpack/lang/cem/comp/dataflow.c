/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: dataflow.c,v 1.1 2005/09/01 12:13:19 beng Exp $ */
/*	DATAFLOW ANALYSIS ON C PROGRAMS	*/

/*	Compile the C compiler with flag DATAFLOW.
	Use the compiler option --d.
*/

#include	"dataflow.h"	/* UF */
#include	<stdio.h>

#ifdef	DATAFLOW
const char *CurrentFunction = 0;
int NumberOfCalls;

void
DfaStartFunction(const char *nm)
{
	CurrentFunction = nm;
	NumberOfCalls = 0;
}

void
DfaEndFunction(void)
{
	if (NumberOfCalls == 0)
		printf("DFA: %s: --none--\n", CurrentFunction);
}

void
DfaCallFunction(const char *s)
{
	printf("DFA: %s: %s\n", CurrentFunction, s);
	++NumberOfCalls;
}
#endif	/* DATAFLOW */
