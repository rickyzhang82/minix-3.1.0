/* $Id: ocm_parco.h,v 1.1 2005/09/01 12:13:17 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	parco.h - Define names for simulation routines
 *
 *      This file is to be included by users of the higher-level routines
 *
 */

#ifndef ptrdiff	/* This type must be able to hold a pointer difference */
#if EM_WSIZE <EM_PSIZE
#define ptrdiff long
#else
#define ptrdiff int	/* Define as long int if necessary */
#endif
#endif

#define nil	0
void * alloc(unsigned int size);

typedef ptrdiff wordsize, identification;

int pc_fork(identification id);
void pc_begin(void *s_brk,identification id);
void resumenext(void);
void parend(void);
void resume(identification id);
void coend(void);

#define nullid	((int *) 0 - (int *) 0)
	/* I.e. a 0 of type "pointer difference" */

#define parbegin(sbrk)		pc_begin(sbrk, nullid)
#define parfork()		pc_fork(nullid)
#define cobegin(sbrk, id)	pc_begin(sbrk, id)
#define cofork(id)		pc_fork(id)

extern int deadlock;
