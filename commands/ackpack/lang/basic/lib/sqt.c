/*
 * (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* $Id: sqt.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

#include "internal.h"

#define __NO_DEFS
#include <math.h>

#define NITER	5

double _fef(double,int*);

double
ldexp(double fl,int exp)
{
	int sign = 1;
	int currexp;

	if (fl<0) {
		fl = -fl;
		sign = -1;
	}
	fl = _fef(fl,&currexp);
	exp += currexp;
	if (exp > 0) {
		while (exp>30) {
			fl *= (double) (1L << 30);
			exp -= 30;
		}
		fl *= (double) (1L << exp);
	}
	else	{
		while (exp<-30) {
			fl /= (double) (1L << 30);
			exp += 30;
		}
		fl /= (double) (1L << -exp);
	}
	return sign * fl;
}

double
_sqt(double x)
{
	int exponent;
	double val;

	if (x <= 0) {
		if (x < 0) error(3);
		return 0;
	}

	val = _fef(x, &exponent);
	if (exponent & 1) {
		exponent--;
		val *= 2;
	}
	val = ldexp(val + 1.0, exponent/2 - 1);
	/* was: val = (val + 1.0)/2.0; val = ldexp(val, exponent/2); */
	for (exponent = NITER - 1; exponent >= 0; exponent--) {
		val = (val + x / val) / 2.0;
	}
	return val;
}
