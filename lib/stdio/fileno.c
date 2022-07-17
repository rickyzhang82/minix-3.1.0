/*
 * fileno .c - map a stream to a file descriptor
 */
/* $Header: /cvsup/minix/src/lib/stdio/fileno.c,v 1.1.1.1 2005/04/21 14:56:35 beng Exp $ */

#include	<stdio.h>

int
(fileno)(FILE *stream)
{
	return stream->_fd;
}
