/*
 * (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* $Id: log.c,v 1.1 2005/09/01 12:13:17 beng Exp $ */

#define __NO_DEFS
/* XXX Assumes Pascal compiler sources */
#define __NO_DEFS
#include <pc_math.h>

double
_log(double x)
{
	/*	Algorithm and coefficients from:
			"Software manual for the elementary functions"
			by W.J. Cody and W. Waite, Prentice-Hall, 1980
	*/
	static double a[] = {
		-0.64124943423745581147e2,
		 0.16383943563021534222e2,
		-0.78956112887491257267e0
	};
	static double b[] = {
		-0.76949932108494879777e3,
		 0.31203222091924532844e3,
		-0.35667977739034646171e2,
		 1.0
	};

	extern double _fef();
	double	znum, zden, z, w;
	int	exponent;

	if (x <= 0) {
		error(3);
		return -HUGE;
	}

	x = _fef(x, &exponent);
	if (x > M_1_SQRT2) {
		znum = (x - 0.5) - 0.5;
		zden = x * 0.5 + 0.5;
	}
	else {
		znum = x - 0.5;
		zden = znum * 0.5 + 0.5;
		exponent--;
	}
	z = znum/zden; w = z * z;
	x = z + z * w * (POLYNOM2(w,a)/POLYNOM3(w,b));
	z = exponent;
	x += z * (-2.121944400546905827679e-4);
	return x + z * 0.693359375;
}
