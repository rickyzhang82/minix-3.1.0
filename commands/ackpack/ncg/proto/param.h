/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: param.h,v 1.1 2005/09/01 12:13:28 beng Exp $ */

#define BMASK 0377
#define BSHIFT 8

#define TRUE    1
#define FALSE   0

#define MAXINT 32767
#define INFINITY (MAXINT+100)

#define MAXROM 3

#define op_lab  (sp_lmnem+1)

/*
 * Tunable constants
 */

#define MAXEMLINES 20
#define MAXFSTACK 20
#define MAXTDBUG 32
