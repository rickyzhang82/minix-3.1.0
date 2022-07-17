/* $Id: Realloc.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	M E M O R Y  A L L O C A T I O N  R O U T I N E S	*/

/*	The memory allocation routines offered in this file are:

	char *Realloc(ptr, n)	: reallocate buffer to n bytes
*/

#include <stdlib.h>
#include	"alloc.h"

void *
Realloc(void *ptr,unsigned int sz)
{
	register void *mptr;

	if (!ptr) mptr = malloc(sz);
	else mptr = realloc(ptr, sz);
	if (sz && mptr == 0) No_Mem();
	return mptr;
}
