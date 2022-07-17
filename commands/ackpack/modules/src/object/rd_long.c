/* $Id: rd_long.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

long
rd_long(FILE *fd)
{
	char buf[4];

	rd_bytes(fd, buf, 4L);
	return get4(buf);
}
