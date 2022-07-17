/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: optim.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#undef DIAGOPT /* if defined diagnostics are produced */
#ifdef DIAGOPT
#define OPTIM(x) optim(x)
#define O_UNREACH 1001
#define O_BRALAB  1002
#define O_LINLNI  1003
#define O_LINGONE 1004
#else
#define OPTIM(x)	/* NOTHING */
#endif
