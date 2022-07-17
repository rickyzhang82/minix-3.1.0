/* $Id: rd_unsig2.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

unsigned int
rd_unsigned2(FILE *fd)
{
	char buf[2];

	rd_bytes(fd, buf, 2L);
	return uget2(buf);
}
