/* $Id: sgn.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

int
_sgn(double v)
{
	if( v>0) return(1);
	if( v<0) return(-1);
	return(0);
}

int
_forsgn(double v)
{
	if (v >= 0) return 1;
	return -1;
}
