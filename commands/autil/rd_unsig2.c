/* $Id: rd_unsig2.c,v 1.1 2005/06/23 09:50:54 philip Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

unsigned int
rd_unsigned2(fd)
{
	char buf[2];

	rd_bytes(fd, buf, 2L);
	return uget2(buf);
}
