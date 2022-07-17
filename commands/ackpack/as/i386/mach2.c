/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#define RCSID2 "$Id: mach2.c,v 1.1 2005/09/01 12:13:15 beng Exp $"

/*
 * INTEL 80386 tokens
 */

%token <y_word> ATOGGLE
%token <y_word> OTOGGLE
%token <y_word> USE16
%token <y_word> USE32
%token <y_word> R32
%token <y_word> R16
%token <y_word> R8
%token <y_word> RSEG
%token <y_word> RSYSCR
%token <y_word> RSYSDR
%token <y_word> RSYSTR
%token <y_word> PREFIX
%token <y_word> ADDOP
%token <y_word> ARPLOP
%token <y_word> BITTEST
%token <y_word> CALFOP
%token <y_word> CALLOP
%token <y_word> ENTER
%token <y_word> EXTEND
%token <y_word> EXTOP
%token <y_word> EXTOP1
%token <y_word> IMUL
%token <y_word> IMULB
%token <y_word> INCOP
%token <y_word> INT
%token <y_word> IOOP
%token <y_word> JOP
%token <y_word> JOP2
%token <y_word> LEAOP
%token <y_word> LEAOP2
%token <y_word> LSHFT
%token <y_word> MOV
%token <y_word> NOOP_1
%token <y_word> NOOP_2
%token <y_word> NOTOP
%token <y_word> PUSHOP
%token <y_word> RET
%token <y_word> ROLOP
%token <y_word> SETCC
%token <y_word> TEST
%token <y_word> XCHG

/* Intel 80[23]87 coprocessor tokens */
%token <y_word> FNOOP
%token <y_word> FMEM
%token <y_word> FMEM_AX
%token <y_word> FST_I
%token <y_word> FST_ST
%token <y_word> FST_ST2
%token <y_word> ST

/* Intel 80486 tokens */
%token <y_word> EXTOPBW
%token <y_word> BSWAP
%type <y_valu> st_i
%type <y_valu> reg

/* Prototypes (c.f. mach5.c) */
%{
void ea_1(int param);
void ea_2(int param);
int checkscale(valu_t val);
void regsize(int sz);
void indexed(void);
void ebranch(int opc,expr_t exp);
void branch(int opc,expr_t exp);
void pushop(int opc);
void adsize_exp(expr_t exp,int relpc);
void addop(int opc);
void rolop(int opc);
void incop(int opc);
void callop(int opc);
void xchg(int opc);
void test(int opc);
void mov(int opc);
void extshft(int opc,int reg);
void bittestop(int opc);
void imul(int reg);
%}
