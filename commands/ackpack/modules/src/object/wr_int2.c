/* $Id: wr_int2.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

void
wr_int2(FILE *fd,int i)
{
	char buf[2];

	put2(i, buf);
	wr_bytes(fd, buf, 2L);
}
