/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#define RCSID2 "$Id: mach2.c,v 1.1 2005/09/01 12:13:16 beng Exp $"

/*
 * INTEL 8086 tokens
 */

%token <y_word> R16
%token <y_word> R8
%token <y_word> RSEG
%token <y_word> PREFIX
%token <y_word> NOOP_1
%token <y_word> NOOP_2
%token <y_word> JOP
%token <y_word> PUSHOP
%token <y_word> IOOP
%token <y_word> ADDOP
%token <y_word> ROLOP
%token <y_word> INCOP
%token <y_word> NOTOP
%token <y_word> CALLOP
%token <y_word> CALFOP
%token <y_word> LEAOP
%token <y_word> ARPLOP
%token <y_word> ESC
%token <y_word> INT
%token <y_word> RET
%token <y_word> XCHG
%token <y_word> TEST
%token <y_word> MOV

/* Intel 80268 tokens */
%token <y_word> IMUL
%token <y_word> ENTER
%token <y_word> EXTOP
%token <y_word> EXTOP1

/* Intel 8087 coprocessor tokens */
%token <y_word> FNOOP
%token <y_word> FMEM
%token <y_word> FST_I
%token <y_word> FST_ST
%token <y_word> FST_ST2
%token <y_word> ST

%type <y_valu> st_i

/* Prototypes (c.f. mach5.c) */
%{
void ea_1(int);
void ea_2(int);
void reverse(void);
void badsyntax(void);
void regsize(int);
void indexed(void);
void branch(int,expr_t);
void pushop(int);
void addop(int);
void rolop(int);
void incop(int);
void callop(int);
void xchg(int);
void test(int);
void mov(int);
void imul(int);
%}

