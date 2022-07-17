/* $Id: em_code.h,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "em_mesX.h"

void C_ms_com(const char *);
void C_ms_ego(int, arith, arith, int);
void C_ms_emx( arith, arith);
void C_ms_err(void);
void C_ms_flt(void);
void C_ms_gto(void);
void C_ms_opt(void);
void C_ms_par(arith);
void C_ms_reg(arith, arith, int, int);
void C_ms_src(int, const char *);
void C_ms_stb_cst(const char *, int, int, arith);
void C_ms_stb_dlb(const char *, int, int, label, arith);
void C_ms_stb_dnam(const char *, int, int, const char *, arith);
void C_ms_stb_ilb(const char *, int, int, label);
void C_ms_stb_pnam(const char *, int, int, const char *);
void C_ms_std(const char *, int, int);

#ifdef PEEPHOLE
#include "em_codeO.h"
#include "emO_code.h"
#else
#ifdef CODE_EXPANDER
#include "em_codeCE.h"
#else
#include "em_codeEK.h"
#endif
#endif
