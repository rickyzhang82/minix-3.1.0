/*
 * remove.c - remove a file
 */
/* $Header: /cvsup/minix/src/lib/stdio/remove.c,v 1.1.1.1 2005/04/21 14:56:36 beng Exp $ */

#include	<stdio.h>

int _unlink(const char *path);

int
remove(const char *filename) {
	return _unlink(filename);
}
