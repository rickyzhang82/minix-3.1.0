/* $Id: comm1.h,v 1.1 2005/09/01 12:13:16 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* @(#)comm1.h	1.5 */
/*
 * variable declarations
 */

#ifdef _include
_include <stdlib.h>
_include <string.h>
_ifndef WIN32
_include <unistd.h>
_endif
#else
# include <stdlib.h>
# include <string.h>
# ifndef WIN32
#  include <unistd.h>
# endif
#endif

#ifdef extern
#define	INIT(x)		= x
#else
#define	INIT(x)		/* empty */
#endif

extern short	pass INIT(PASS_1);
				/* PASS 1, 2 or 3 */
extern short	peekc;		/* push back symbol (PASS_1) */
extern short	unresolved;	/* number of unresolved references */
extern long	lineno;		/* input line number */
extern short	hllino;		/* high-level language line number */
extern short	nerrors;	/* terminate at end of pass if set */
extern short	sflag INIT(SYM_DEF);
				/* -s option (symbol table info) */
extern char	*progname;	/* for error messages */
extern char	*modulename;	/* for error messages */
extern common_t	*commons;	/* header of commons list */

#ifdef ASLD
extern short	archmode;	/* scanning archives */
extern long	archsize;	/* size of individual archive entries */
#else
extern short	uflag;		/* if 1 make undefineds extern */
				/* symbol table index for last S_UND */
#endif

#ifdef LISTING
extern short	dflag;		/* -d option (list mode) */
#endif

#ifdef ASLD
#ifdef RELOCATION
extern short	rflag;		/* -r option (relocation info) */
#endif /* RELOCATION */
#else
#define	rflag	1
extern valu_t	relonami;
#endif /* ASLD */

#ifdef THREE_PASS
extern short	bflag;		/* -b option (no optimizations) */
#endif

extern char	*aoutpath INIT("a.out");
extern char	temppath[50];

extern FILE	*input;
extern FILE	*tempfile;

extern char	*stringbuf;	/* contains last string value */
extern int	stringlen;	/* contains length of last string value */

extern sect_t	sect[SECTMAX];

/*
 * specials for the location counter
 */
extern sect_t	*DOTSCT;	/* &sect[DOTTYP-S_MIN] or NULL */
extern ADDR_T	DOTVAL;		/* DOTSCT->s_size + DOTSCT->s_base */
extern short	DOTTYP;		/* S_MIN..S_MAX or S_UND */

extern unsigned short	nname;		/* Counts name table index in PASS_3 */

extern item_t	*hashtab[H_TOTAL];
extern short	hashindex;	/* see item_search() */

extern item_t	*fb_ptr[4*FB_SIZE];

#ifdef THREE_PASS
#define BITCHUNK	(8 * MEMINCR)
extern int	nbits;
extern int	bitindex;	/* bitindex * MEMINCR * 8 + nbits gives
				   number of decisions so far
				*/
#endif

#ifdef LISTING
extern short	listmode;	/* -d option for current pass */
extern short	listtemp;	/* listmode if .list seen */
extern short	listflag;	/* copied from listtemp at '\n' */
extern short	listcolm;	/* column on output */
extern short	listeoln INIT(1);
				/* set by endline, tested by emit1 */
extern FILE	*listfile;	/* copy of source text */
extern char	listpath[50];
#endif

#ifndef extern
extern item_t		keytab[];
extern struct outhead	outhead;
#endif

extern int	curr_token;

/* ANSI prototypes */
long new_string(char * s);
void newsymb(char * name, int type, int desc, valu_t valu);
void newident(item_t * ip, int typ);
void newequate(item_t * ip,int typ);
void newlabel(item_t * ip);
void switchsect(int newtyp);
void newmodule(char * s);
void newsect(item_t * ip);
void newbase(valu_t base);
void new_common(item_t * ip);
void newcomm(item_t * ip, valu_t val);
void align(valu_t bytes);
#ifdef RELOCATION
void newrelo(int s,int n);
#endif

int hash(char * p);
item_t * item_search(char * p);
void item_insert(item_t * ip,int h);
item_t * item_alloc(int typ);
item_t * fb_alloc(int lab);
item_t * fb_shift(int lab);
int nextchar(void);
void putval(int c);
int getval(int c);
void readcode(int n);
int induo(int c);
int inident(int c);
#ifdef ASLD
char * readident(int c);
#endif
int infbsym(char * p);
int innumber(int c);
int inescape(void);
int instring(int termc);
int yylex(void);

void fatal(const char * fmt, ...);
void nosect(void);
void wr_fatal(void);
#if DEBUG == 2
void assert2(const char * file, int line);
#endif
#if DEBUG == 1
void assert1(void);
#endif
void serror(const char * fmt, ...);
void warning(const char * fmt, ...);
void nofit(void);
valu_t load(item_t * ip);
int store(item_t * ip,valu_t val);
char * remember(char * s);
int combine(int typ1,int typ2,int op);
#ifdef LISTING
int printx(int ndig,valu_t val);
void listline(int textline);
#endif
#ifdef THREE_PASS
int small(int fitsmall,int gain);
#endif
void emit1(int arg);
void emit2(int arg);
void emit4(long arg);
void emitx(valu_t val,int n);
void emitstr(int zero);
void ffreopen(char * s,FILE * f);
FILE * fftemp(char * path,char * tail);
void stop(void);


/* ========== Machine dependent C declarations ========== */

#include	"mach1.c"
