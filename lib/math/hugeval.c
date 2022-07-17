/*
 * (c) copyright 1990 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Eck
 */
/* $Header: /cvsup/minix/src/lib/math/hugeval.c,v 1.1.1.1 2005/04/21 14:56:26 beng Exp $ */
#include	<math.h>

double
__huge_val(void)
{
	return 1.0e+1000;	/* This will generate a warning */
}
