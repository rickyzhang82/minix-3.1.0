/* $Id: No_Mem.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include	<system.h>
#include	"alloc.h"

void
No_Mem(void)
{
	sys_write(stderr, "Out of memory\n", 14);
	exit( 1 );
}
