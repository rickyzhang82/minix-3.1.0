/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: write.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */

#include "system.h"

int
sys_write(FILE *fp,const char *bufptr,size_t nbytes)
{
	if (! fp) return 0;
	return 1 == fwrite( bufptr, nbytes, 1, fp );
}
