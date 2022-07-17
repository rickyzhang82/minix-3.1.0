/* $Header: /cvsup/minix/src/commands/aal/wr_int2.c,v 1.1.1.1 2005/04/21 14:53:58 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "object.h"

wr_int2(fd, i)
{
	char buf[2];

	put2(i, buf);
	wr_bytes(fd, buf, 2L);
}
