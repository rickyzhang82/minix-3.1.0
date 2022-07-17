/* $Id: oem.c,v 1.1 2005/09/01 12:13:23 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oem.h"
#include "Lpars.h"
#include <em.h>

/* This file is used to shield code.c as much as possible from em dependant
 * details.  It introduces some call overhead but not enough for a coffee
 * break. (Sorry)
 * Note that functions with a leading upper case letter normally decide between
 * word or double word arith.
 */

int wz = 4, pz = 4, vz = 4;
int Lflag;
static Lab=0;

void
init(void)
{
	C_init((arith) wz, (arith) pz);
}

void
openfile(char *file)
{
	if (C_open(file) < 0) {
		fatal("Could not open output file");
	}
}

void
meswp(void)
{
	C_ms_emx((arith) wz, (arith) pz);
}

void
maxdes(void)
{
	long max = (1L << (8*wz-1)) - 1;
	C_df_dnam("maxcdes");
	rom(wz, 0L); rom(wz, max); rom(wz, (long) (wz+vz));
	C_df_dnam("maxwdes");
	rom(wz, 0L); rom(wz, max); rom(wz, (long) vz);
	C_df_dnam("maxbdes");
	rom(wz, 0L); rom(wz, max); rom(wz, 1L);
}

int
new_label(int *L)
{
	if (*L==0) *L= ++Lab;
	return *L;
}

void
Label(int L)
{
	if (L!=0) C_df_ilb((label) L);
}

static Dot_label=0;

int
new_dot_label(int *L)
{
	return *L= ++Dot_label;
}

void
dot_label(int L)
{
	C_df_dlb((label) L);
}

void
branch(int *L)
{
	C_bra((label) new_label(L));
}

char *
proc_label(int L,char * name)
{
	static char *lab=nil;
	register char *n;

	if (lab!=nil) free(lab);

	lab=Malloc(strlen(name)+(1+sizeof(int)*3+1));
		/* That is: P<L><name>\0 */

	sprintf(lab, "P%d", L);

	n=lab+strlen(lab);

	while (*name!=0) {
		*n++ = *name=='.' ? '_' : *name;
		name++;
	}
	*n=0;
	return lab;
}

void
magic(void)	/* magic? should be called invisible */
{
	C_magic();
}

void
cwv(void)
{
	if (vz>wz) {
		C_loc((arith) wz);
		C_loc((arith) vz);
		C_cii();
	}
}

void
cvw(void)
{
	if (vz>wz) {
		C_loc((arith) vz);
		C_loc((arith) wz);
		C_cii();
	}
}

void
Loc(long cst)
{
	if (vz>wz) C_ldc((arith) cst); else C_loc((arith) cst);
}

void
Lol(int offset)
{
	if (vz>wz) C_ldl((arith) offset); else C_lol((arith) offset);
}

void
Lolp(int offset)
{
	if (pz>wz) C_ldl((arith) offset); else C_lol((arith) offset);
}

void
Lil(int offset)
{
	if (vz>wz) {
		Lolp(offset);
		C_loi((arith) vz);
	} else
		C_lil((arith) offset);
}

void
Lof(int offset)
{
	if (vz>wz) C_ldf((arith) offset); else C_lof((arith) offset);
}

void
Lofp(int offset)
{
	if (pz>wz) C_ldf((arith) offset); else C_lof((arith) offset);
}

void
Lif(int offset)
{
	Lofp(offset);
	C_loi((arith) vz);
}

void
Stl(int offset)
{
	if (vz>wz) C_sdl((arith) offset); else C_stl((arith) offset);
}

void
Inl(int offset)
{
	if (vz>wz) {
		C_ldl((arith) offset);
		C_ldc((arith) 1);
		C_adi((arith) vz);
		C_sdl((arith) offset);
	} else
		C_inl((arith) offset);
}

void
Del(int offset)
{
	if (vz>wz) {
		C_ldl((arith) offset);
		C_ldc((arith) 1);
		C_sbi((arith) vz);
		C_sdl((arith) offset);
	} else
		C_del((arith) offset);
}

void
Loe(char *name,int offset)
{
	if (vz>wz)
		C_lde_dnam(name, (arith) offset);
	else
		C_loe_dnam(name, (arith) offset);
}

static int operators[]=	{ '<', '>', '=',  GE,  LE,  NE };

void
bxx(int pos,int op,int L)
{
	register i;

	if (op==AFTER) {
		C_sbi((arith) vz);
		if (vz>wz) {
			C_ldc((arith) 0);
			C_cmi((arith) vz);
		}
		if (pos) C_zle((label) L); else C_zgt((label) L);
	} else {
		for (i=0; operators[i]!=op; i++) ;
		if (pos && (i+=3)>=6) i-=6;
		if (vz>wz) {
			C_cmi((arith) vz);
			switch(i) {
			case 0:
				C_zlt((label) L);
				break;
			case 1:
				C_zgt((label) L);
				break;
			case 2:
				C_zeq((label) L);
				break;
			case 3:
				C_zge((label) L);
				break;
			case 4:
				C_zle((label) L);
				break;
			case 5:
				C_zne((label) L);
				break;
			}
		} else {
			switch(i) {
			case 0:
				C_blt((label) L);
				break;
			case 1:
				C_bgt((label) L);
				break;
			case 2:
				C_beq((label) L);
				break;
			case 3:
				C_bge((label) L);
				break;
			case 4:
				C_ble((label) L);
				break;
			case 5:
				C_bne((label) L);
				break;
			}
		}
	}
}

void
Txx(int op)
{
	switch(op) {
	case '<':
		C_tlt();
		break;
	case '>':
		C_tgt();
		break;
	case '=':
		C_teq();
		break;
	case GE:
		C_tge();
		break;
	case LE:
		C_tle();
		break;
	case NE:
		C_tne();
		break;
	}
	cwv();
	C_ngi((arith) vz);
}

void
xxi(int op)
{
	switch(op) {
	case '+':
		C_adi((arith) vz);
		break;
	case '-':
		C_sbi((arith) vz);
		break;
	case '*':
		C_mli((arith) vz);
		break;
	case '/':
		C_dvi((arith) vz);
		break;
	case BS:
		C_rmi((arith) vz);
		break;
	}
}

void aar(void)			{	C_aar((arith) wz); }
void adp(int offset)		{	C_adp((arith) offset); }
void and(void)			{	C_and((arith) vz); }
void asp(int size)		{	C_asp((arith) size); }
void blm(int size)		{	C_blm((arith) size); }
void blt(int lab)		{	C_blt((label) lab); }
void cal(char *lab)		{	C_cal(lab); }
void cmi(void)			{	C_cmi((arith) vz); }
void com(void)			{	C_com((arith) vz); }
void del(int offset)		{	C_del((arith) offset); }
void x_end(int size)		{	C_end((arith) size); }
void exp(char *lab)		{	C_exp(lab); }
void ior(void)			{	C_ior((arith) vz); }
void lae(char *lab,int offset)	{	C_lae_dnam(lab, (arith) offset); }
void laedot(int lab)		{	C_lae_dlb((label) lab, (arith) 0); }
void lal(int offset)		{	C_lal((arith) offset); }
void lar(void)			{	C_lar((arith) wz); }
void ldc0(void)			{	C_ldc((arith) 0); }
void ldl(int offset)		{	C_ldl((arith) offset); }
void lfr(int size)		{	C_lfr((arith) size); }
void loc(int cst)		{	C_loc((arith) cst); }
void loi(int size)		{	C_loi((arith) size); }
void lol(int offset)		{	C_lol((arith) offset); }
void lor0(void)			{	C_lor((arith) 0); }
void lxa(int offset)		{	C_lxa((arith) offset); }
void lxl(int offset)		{	C_lxl((arith) offset); }
void meserr(void)		{	C_ms_err(); }
void ngi(void)			{	C_ngi((arith) vz); }
void pro(char *lab)		{	C_pro_narg(lab); }
void ret(int size)		{	C_ret((arith) size); }
void init_rt(void)		{	C_cal("init");	}
void sli(void)			{	C_sli((arith) vz); }
void sri(void)			{	C_sri((arith) vz); }
void ste(char *lab,int offset)	{	C_ste_dnam(lab, (arith) offset); }
void sti(int size)		{	C_sti((arith) size); }
void stl(int offset)		{	C_stl((arith) offset); }
void trp(void)			{	C_trp(); }
void tst(void)			{	/* No flags in EM */ }
void xor(void)			{	C_xor((arith) vz); }
void zeq(int lab)		{	C_zeq((label) lab); }
void zgt(int lab)		{	C_zgt((label) lab); }
void zlt(int lab)		{	C_zlt((label) lab); }
void zne(int lab)		{	C_zne((label) lab); }

static
char *
myitoa(long i)
{
	static char a[sizeof(long)*3];
	sprintf(a, "%ld", i);
	return a;
}

void
rom(int size,long c)
{
	C_rom_icon(myitoa(c), (arith) size);
}

void
lin(void)
{
	static oldline=0;
	extern lineno;

	if (Lflag) return;
	if (lineno!=oldline)
		C_lin((arith) (oldline=lineno));
}

static struct ftree {
	char *file;
	int lab;
	struct ftree *left, *right;
} std_f = { "stdin", 0, nil, nil }, *curr_f= &std_f, *main_f=nil;

char *curr_file="stdin";

static
void
do_fil(struct ftree *f)
{
	if (Lflag) return;
	if (f->lab==0) {
		dot_label(new_dot_label(&f->lab));
		C_rom_scon(f->file, (arith) (strlen(f->file)+1));
	}
	C_fil_dlb((label) f->lab, (arith) 0);
}

void
fil(void)
{
	do_fil(curr_f);
}

void
main_fil(void)
{
	do_fil(main_f==nil ? &std_f : main_f);
}

int
set_file(char *f)
{
	static struct ftree *ftop=nil;
	register struct ftree *pf, **apf= &ftop;
	register cmp;

	while ((pf= *apf)!=nil && (cmp=strcmp(f, pf->file))!=0)
		apf= cmp<0 ? &pf->left : &pf->right;

	if (pf==nil) {
		*apf= pf= (struct ftree *) Malloc(sizeof *pf);
		pf->file=strcpy(Malloc(strlen(f)+1), f);
		pf->lab=0;
		pf->left=pf->right=nil;
	}
	curr_f=pf;
	curr_file=pf->file;
	if (main_f==nil) {
		main_f=curr_f;
		return 0;
	} else
		return curr_f!=main_f;
}

void
par_begin(void)
{
	C_zer((arith) pz);
	C_lal((arith) curr_offset);
	C_cal("pc_begin");
	C_asp((arith) (2*pz));
}

void
par_fork(int *NONZERO)
{
	C_zer((arith) pz);
	C_cal("pc_fork");
	C_asp((arith) pz);
	C_lfr((arith) wz);
	C_zne((label) new_label(NONZERO));
}

void
resumenext(void)
{
	C_cal("resumenext");
}

void
no_deadlock(void)
{
	C_zre_dnam("deadlock", (arith) 0);
}

void
par_end(void)
{
	C_cal("parend");
}

void
closefile(void)
{
	C_close();
}
