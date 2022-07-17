/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/commands/aal/write.c,v 1.1.1.1 2005/04/21 14:53:58 beng Exp $ */

#include <system.h>

int
sys_write(fp, bufptr, nbytes)
	File *fp;
	char *bufptr;
	int nbytes;
{
	if (! fp) return 0;
	return write(fp->o_fd, bufptr, nbytes) == nbytes;
}
