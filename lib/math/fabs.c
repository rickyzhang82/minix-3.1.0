/*
 * (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */
/* $Header: /cvsup/minix/src/lib/math/fabs.c,v 1.1.1.1 2005/04/21 14:56:26 beng Exp $ */

double
fabs(double x)
{
	return  x < 0 ? -x : x;
}
