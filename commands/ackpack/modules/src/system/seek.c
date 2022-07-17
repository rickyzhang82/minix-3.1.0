/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: seek.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */

#include "system.h"

int
sys_seek(FILE *fp,long off,int whence,long *poff)
{
	if (! fp) return 0;
	if( fseek( fp, off, whence ) )
		return 0;
	*poff = ftell( fp );
	return 1;
}
