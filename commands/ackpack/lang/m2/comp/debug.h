/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* D E B U G G I N G   M A C R O */

/* $Id: debug.h,v 1.1 2005/09/01 12:13:21 beng Exp $ */

#include "debugcst.h"

#ifdef DEBUG
#define DO_DEBUG(x, y)	((x) && (y))
#define STATIC
#else
#define DO_DEBUG(x, y)
#define STATIC static
#endif
