/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: extern.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#include "param.h"
#include "expr.h"
#include "instruct.h"
#include "iocc.h"
#include "set.h"
#include "varinfo.h"
#include <cgg_cg.h>

extern int wordsize;
extern int pointersize;
extern int nregs;
extern int nprops;
extern int ntokens;
extern int nsets;
extern int ninstr;
extern int empatlen;
extern int emrepllen;
extern int tokrepllen;
extern int emmnem[];
extern int empatexpr;
extern int codeindex;
extern int tokpatlen;
extern int maxtokpatlen;
extern int maxempatlen;
extern int maxemrepllen;
extern int maxtokrepllen;
extern int tokpatro[];
extern int tokpatset[];
extern int nallreg;
extern int allreg[];
extern int cursetno;
extern int allsetno;
extern int inproc;
extern int callproc;
extern int procarg[];
extern int fc1,fc2,fc3,fc4;
extern int maxmembers;
extern int regclass;
extern int maxtokensize;
extern int nprocargs, maxprocargs;
extern int use_tes;

char *mystrcpy(char *);
char *myalloc(int);

int tabovf(char *);
void dopattern(int,varinfo*,varinfo*,varinfo*,varinfo*,varinfo*);
void n_move(int,int,int,int,varinfo*);
int subset(unsigned short *,unsigned short *,int);
void error(char *,...);
void n_test(int,int,varinfo*);
void checkstacking(unsigned short*);
void n_coerc0(int,varinfo*,varinfo*,varinfo*,iocc_t);
void n_coerc1(int,int,varinfo*,varinfo*,varinfo*);
void freevi(varinfo*);
void nexthall(unsigned short*);
void errorexit(void);
int ex_lookup(int,int,int);
int hall(void);
int setlookup(set_t);
void subregset(unsigned short*,int,unsigned short*);
int membset(int,char*,unsigned short*,char*,int,int*);
int hashvalue(char*);
void fatal(char *,...);
void initemhash(void);
int enterkeyw(void);
void initnodes(void);
void initio(void);
int yyparse(void);
void finishio(void);
void statistics(void);
void hallverbose(void);
int strlookup(char *);
int cmustbeset(char *);
int vilength(varinfo *);
void n_set(char *,int);
void make_std_sets(void);
void n_const(char *,int);
void make_const(void);
void n_prop(char *,int);
void regline(varinfo*,varinfo*,int);
int n_reg(char *,char *,int,int,int);
void n_sconst(char *,char *);
void n_tok(char *,varinfo *,int,varinfo *,varinfo *);
void n_instr(char *,char *,operand *,varinfo *,varinfo *);
void checkprintformat(int);
void n_stack(int,int,int,varinfo*);
int mlookup(char *);
void inithall(void);
void checkhall(void);
void outpatterns(void);
void n_proc(char *);
void checkunstacking(int);
void setallreg(varinfo *);
void prophall(int);
int existalmove(iocc_t,int);
int argtyp(int);
int i_expr(expr_t);
int chkincl(int,int,int);
int eq2expr(expr_t,expr_t);
int ne2expr(expr_t,expr_t);
int b_expr(expr_t);
void yyerror(char *);

#ifndef NDEBUG
void badassertion(char *,char *,int);
#endif

