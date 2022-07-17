/* $Id: internerr.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <system.h>

void
C_internal_error(void)
{
	sys_write(stderr,"internal error\n",15);
	exit( 1 );
}
