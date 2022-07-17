/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: bits.h,v 1.1 2005/09/01 12:13:20 beng Exp $ */
#include "dobits.h"
#ifdef DOBITS
#define bit0	0x01
#define bit1	0x02
#define bit2	0x04
#define bit3	0x08
#define bit4	0x10
#define bit5	0x20
#define bit6	0x40
#define bit7	0x80

extern char bits[];
#endif
