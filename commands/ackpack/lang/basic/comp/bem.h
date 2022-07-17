/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <em.h>
#include <em_mes.h>

/* Author: M.L. Kersten
** Here all the global objects are defined.
*/
#include "symbols.h"
#include "graph.h"
#include "Lpars.h"

#ifndef NORCSID
# define RCS_BEM	"$Id: bem.h,v 1.1 2005/09/01 12:13:17 beng Exp $"
#endif

#define MAXINT		32768
#define MININT		-32767
/* #define EMINTSIZE	"EM_WSIZE" */
/* #define EMPTRSIZE	"EM_PSIZE" */
/* #define EMFLTSIZE	"EM_DSIZE" */

#define EMINTSIZE 4
#define EMPTRSIZE 4
#define EMFLTSIZE 8

#define MAXPIECES	100
#define MAXFILENAME	200

#define CHANNEL		0
#define THRESHOLD	40		/* for splitting blocks */

#if !defined( __STDC__ ) && !defined( _WIN32 )
#define void		int		/* Some C compilers don't know void */
#endif

extern int	BEMINTSIZE, BEMPTRSIZE, BEMFLTSIZE;
extern char	*program;		/* name of source program */
extern char	*inpfile;		/* input tko compiler */
extern char	*outfile;		/* output from compiler */

extern char	datfname[MAXFILENAME];	/* data statements file */

extern FILE	*emfile;		/* EM output file */
extern FILE	*datfile;		/* data file */
extern FILE	*yyin;			/* Compiler input */

extern int	endofinput;
extern int 	wflag;
extern int	hflag;
extern int	traceflag;
extern int	yydebug;
extern int	yylineno;
extern int	listing;
extern int	nolins;
extern int	threshold;
extern int	debug;
extern int 	tronoff;
extern label	err_goto_label;

extern int 	dataused;

extern Linerecord *currline;


extern char *myitoa(int);
extern char *salloc(unsigned int);

/* compile.c */
void compileprogram(void);

/* eval.c */
int exprtype(int ltype,int rtype);
void conversion(int oldtype,int newtype);
void extraconvert(int oldtype,int newtype,int topstack);
int boolop(int ltype,int rtype,int operator);
int relop(int ltype,int rtype,int operator);
int plusmin(int ltype,int rtype,int operator);
int muldiv(int ltype,int rtype,int operator);
int negate(int type);
int power(int ltype,int rtype);
int typesize(int ltype);
int typestring(int type);
void loadvar(int type);
int loadint(int value);
int loaddbl(char * value);
void loadstr(int value);
int loadaddr(Symbol * s);
void save_address(void);
void assign(int type,int lt);
void storevar(int lab,int type);
void newarrayload(Symbol * s);
int endarrayload(void);
void loadarray(int type);

/* func.c */
int callfcn(int fcnnr,int cnt,int *typetable);

/* gencode.c */
int genlabel(void);
int genemlabel(void);
void newemblock(int nr);
void datastmt(void);
void exceptstmt(int lab);
void errorstmt(int exprtype);
void openstmt(int recsize);
void printstmt(int exprtype);
void zone(int i);
void writestmt(int exprtype,int comma);
void restore(int lab);
void setchannel(int val);
void prompt(int qst);
void linestmt(int type);
void readelm(int type);
void swapstmt(int ltype,int rtype);
int ifstmt(int type);
int thenpart(int elselab);
void elsepart(int lab);
void forinit(Symbol *s);
void forexpr(int type);
void forlimit(int type);
void forstep(int type);
void nextstmt(Symbol *s);
void pokestmt(int type1,int type2);
void whilestart(void);
void whiletst(int exprtype);
void wend(void);
void prologcode(void);
void prolog2(void);
void epilogcode(void);

/* graph.c */
void linewarnings(void);
void newblock(int nr);
int gotolabel(int nr);
void gotostmt(int nr);
List * gosublabel(void);
void gosubstmt(int lab);
void genreturns(void);
void returnstmt(void);
void jumpelm(int nr);
void ongotostmt(int type);
void ongosubstmt(int type);

/* initialize.c */
void initialize(void);

/* parsepar.c */
void parseparams(int argc,char ** argv);

/* symbols.c */
void initdeftype(void);
Symbol * srchsymbol(char *str);
void dcltype(Symbol *s);
void dclarray(Symbol *s);
void defarray(Symbol *s);
int dclspace(int type);
void optionbase(int ival);
void setdefaulttype(int type);
void newscope(Symbol *s);
void heading(void);
int fcnsize(void);
void endscope(int type);
void dclparm(Symbol *s);
int fcncall(Symbol *s);
int fcnend(int parmcount);
void callparm(int ind,int type);

/* util.c */
void warning(const char *str);
void error(const char *str);
void fatal(char *str);
void notyetimpl(void);
void illegalcmd(void);
char * myitoa(int i);
char * salloc(unsigned int length);
