/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: read.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */

#include "system.h"

int
sys_read(FILE *fp,char *bufptr,size_t bufsiz,size_t *pnbytes)
{
	int got;
	if( 0 == fp )
		return 0;
	got = fread( bufptr, 1, bufsiz, fp );
	if( 0 == got && ferror( fp ) )
		return 0;

	*pnbytes = (size_t)got;
	return 1;
}
