/* $Id: chan_strct.c,v 1.1 2005/09/01 12:13:23 beng Exp $ */
/*	chan_struct.c - channel routines for more structured objects */
#include "ocm_chan.h"

void
cbyte_in(char *b,chan *c)
{
	long v;
	chan_in(&v, c);
	*b= (char) v;
}

void
c_wa_in(long *a,unsigned int z,chan *c)
{
	do
		chan_in(a++, c);
	while (--z!=0);
}

void
c_ba_in(char *a,unsigned int z,chan *c)
{
	do {
		long v;
		chan_in(&v, c);
		*a++ = (char) v;
	} while (--z!=0);
}

void
c_wa_out(long *a,unsigned int z,chan *c)
{
	do
		chan_out(*a++, c);
	while (--z!=0);
}

void
c_ba_out(char *a,unsigned int z,chan *c)
{
	do
		chan_out((long) (*a++ &0377), c);
	while (--z!=0);
}
