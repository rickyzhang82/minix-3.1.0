/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: time.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */

#include "system.h"

long time(long *);

long
sys_time(void)
{
	return time((long *) 0);
}
