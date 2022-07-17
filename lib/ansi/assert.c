/*
 * assert.c - diagnostics
 */
/* $Header: /cvsup/minix/src/lib/ansi/assert.c,v 1.1.1.1 2005/04/21 14:56:04 beng Exp $ */

#include	<assert.h>
#include	<stdio.h>
#include	<stdlib.h>

void __bad_assertion(const char *mess) {

	fputs(mess, stderr);
	abort();
}
