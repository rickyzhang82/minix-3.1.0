/* $Id: rd_int2.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

int
rd_int2(FILE *fd)
{
	char buf[2];

	rd_bytes(fd, buf, 2L);
	return get2(buf);
}
