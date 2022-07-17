/* $Id: failed.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <system.h>

void
C_failed(void)
{
	sys_write(stderr,"read, write, or open failed\n",28);
	exit( 1 );
}
