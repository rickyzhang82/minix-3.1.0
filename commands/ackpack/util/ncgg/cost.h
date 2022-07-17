/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: cost.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#define _COST_

typedef struct cost {
	int ct_space;
	int ct_time;
} cost_t,*cost_p;
