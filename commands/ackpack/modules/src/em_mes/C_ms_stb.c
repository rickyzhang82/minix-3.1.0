/* $Id: C_ms_stb.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */
/*
 * (c) copyright 1990 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <string.h>
#include <em.h>
#include <em_mes.h>

void
C_ms_stb_cst(const char *s,int e1,int e2,arith e3)
{
	C_mes_begin(ms_stb);
	if (s) C_scon(s, (arith) (strlen(s)+1));
	C_cst((arith)e1);
	C_cst((arith)e2);
	C_cst(e3);
	C_mes_end();
}

void
C_ms_stb_dlb(const char *s,int e1,int e2,label l,arith off)
{
	C_mes_begin(ms_stb);
	if (s) C_scon(s, (arith) (strlen(s)+1));
	C_cst((arith)e1);
	C_cst((arith)e2);
	C_dlb(l, off);
	C_mes_end();
}

void
C_ms_stb_dnam(const char *s,int e1,int e2,const char *l,arith off)
{
	C_mes_begin(ms_stb);
	if (s) C_scon(s, (arith) (strlen(s)+1));
	C_cst((arith)e1);
	C_cst((arith)e2);
	C_dnam(l, off);
	C_mes_end();
}

void
C_ms_stb_ilb(const char *s,int e1,int e2,label l)
{
	C_mes_begin(ms_stb);
	if (s) C_scon(s, (arith) (strlen(s)+1));
	C_cst((arith)e1);
	C_cst((arith)e2);
	C_ilb(l);
	C_mes_end();
}

void
C_ms_stb_pnam(const char *s,int e1,int e2,const char * p)
{
	C_mes_begin(ms_stb);
	if (s) C_scon(s, (arith) (strlen(s)+1));
	C_cst((arith)e1);
	C_cst((arith)e2);
	C_pnam(p);
	C_mes_end();
}
