/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: regvar.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#define ANY_REGVAR	0x1
#define SL_REGVAR	0x2
#define DL_REGVAR	0x4

extern int rvused;
extern int nregvar[4];
extern int rvsize[4];
extern int rvnumbers[4][MAXREGVAR];
