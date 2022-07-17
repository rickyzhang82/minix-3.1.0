/* $Id: em_private.h,v 1.3 2005/09/01 12:13:25 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* private inclusion file */

#include <em_arith.h>
#include <em_label.h>

/* include the EM description files */
#include	<em_spec.h>
#include	<em_pseu.h>
#include	<em_mnem.h>
#include	<em_reg.h>

#include	"em_codeEK.h"

#ifdef READABLE_EM
/* macros used in the definitions of the interface functions C_* */
#define	OP(x)		C_pt_op(x)
#define	CST(x)		C_pt_cst(x)
#define	DCST(x)		C_pt_cst(x)
#define	SCON(x,y)	C_pt_scon((x), (y))
#define	PS(x)		C_pt_ps(x)
#define	DLB(x)		C_pt_dlb(x)
#define DFDLB(x)	C_pt_dlb(x)
#define	ILB(x)		C_pt_ilb(x)
#define	DFILB(x)	C_pt_dfilb(x)
#define	NOFF(x,y)	C_pt_noff((x), (y))
#define	DOFF(x,y)	C_pt_doff((x), (y))
#define	PNAM(x)		C_pt_pnam(x)
#define	DNAM(x)		C_pt_dnam(x)
#define	DFDNAM(x)	C_pt_dnam(x)
#define	CEND()
#define CCEND()		C_pt_ccend()
#define	WCON(x,y,z)	C_pt_wcon((x), (y), (z))
#define COMMA()		C_pt_comma()
#define NL()		C_pt_nl()
#define CILB(x)		C_pt_ilb(x)

#else
/* macros used in the definitions of the interface functions C_* */
#define	OP(x)		C_pt_op(x)
#define	CST(x)		C_pt_cst(x)
#define	DCST(x)		C_pt_cst(x)
#define	SCON(x,y)	C_pt_scon((x), (y))
#define	PS(x)		C_pt_ps(x)
#define	DLB(x)		C_pt_dlb(x)
#define DFDLB(x)	C_pt_dlb(x)
#define	ILB(x)		C_pt_ilb(x)
#define	DFILB(x)	C_pt_ilb(x)
#define	NOFF(x,y)	C_pt_noff((x), (y))
#define	DOFF(x,y)	C_pt_doff((x), (y))
#define	PNAM(x)		C_pt_pnam(x)
#define	DNAM(x)		C_pt_dnam(x)
#define	DFDNAM(x)	C_pt_dnam(x)
#define	CEND()		C_pt_cend()
#define CCEND()		C_pt_cend()
#define	WCON(x,y,z)	C_pt_wcon((x), (y), (z))
#define COMMA()
#define NL()
#define CILB(x)		CST((arith) x)

#define	C_pt_cend()	C_putbyte(sp_cend)
#define	C_pt_op(x)	C_putbyte(x)
#define	C_pt_ps(x)	C_putbyte(x)

void C_putbyte(int);

#endif /* READABLE_EM */

void C_pt_dnam(const char *);
void C_pt_ilb(label);
void C_pt_cst(arith);
void C_pt_scon(const char *, arith);
void C_pt_dlb(label);
void C_pt_doff(label, arith);
void C_pt_noff(const char *, arith);
void C_pt_pnam(const char *);
void C_pt_dfilb(label);
void C_pt_wcon(int, const char *, arith);
#ifdef READABLE_EM
void C_pt_ps(int);
void C_pt_op(int);
void C_pt_nl(void);
void C_pt_comma(void);
void C_pt_ccend(void);
#endif /* READABLE_EM */
