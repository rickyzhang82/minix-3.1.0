/* $Id: Malloc.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	M E M O R Y  A L L O C A T I O N  R O U T I N E S	*/

/*	The memory allocation routines offered in this file are:

	char *Malloc(n)		: allocate n bytes
*/

#include <stdlib.h>
#include	"alloc.h"

void *
Malloc(unsigned int sz)
{
	register void *res = malloc(sz);
	
	if (sz && res == 0) No_Mem();
	return res;
}
