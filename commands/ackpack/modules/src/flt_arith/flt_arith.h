/*
 * (c) copyright 1989 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: flt_arith.h,v 1.3 2005/09/01 12:13:26 beng Exp $ */

#ifndef __FLT_INCLUDED__
#define __FLT_INCLUDED__

#ifndef arith
#define arith long
#endif

struct flt_mantissa {
	long	flt_h_32;	/* high order 32 bits of mantissa */
	long	flt_l_32;	/* low order 32 bits of mantissa */
};

typedef struct flt_arith {
	short	flt_sign;	/* 0 for positive, 1 for negative */
	short	flt_exp;	/* between -16384 and 16384 */
	struct flt_mantissa flt_mantissa;	/* normalized, in [1,2). */
} flt_arith;

extern int	flt_status;
#define FLT_OVFL	001
#define FLT_UNFL	002
#define FLT_DIV0	004
#define	FLT_NOFLT	010
#define FLT_BTSM	020

#define FLT_STRLEN	32	/* max length of result of flt_flt2str() */

void flt_add(flt_arith *, flt_arith *, flt_arith *);
void flt_sub(flt_arith *, flt_arith *, flt_arith *);
void flt_mul(flt_arith *, flt_arith *, flt_arith *);
void flt_div(flt_arith *, flt_arith *, flt_arith *);
void flt_modf(flt_arith *, flt_arith *, flt_arith *);
int flt_cmp(flt_arith *, flt_arith *);
void flt_str2flt(char *, flt_arith *);
void flt_flt2str(flt_arith *, char *, int);
void flt_arith2flt(arith, flt_arith *, int);
arith flt_flt2arith(flt_arith *, int);
void flt_b64_sft(struct flt_mantissa *, int);
void flt_umin(flt_arith *);

#endif /* __FLT_INCLUDED__ */
