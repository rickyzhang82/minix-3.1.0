/* prototypes.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "param.h"
#include "tables.h"
#include "types.h"
#include <cgg_cg.h>
#include "data.h"
#include "result.h"
#include "state.h"
#include "glosym.h"
#include "mach.h"		/* machine dependent */

#ifdef USE_TES
#include "label.h"
#endif

/* codegen.c */
unsigned int codegen(byte *, int, int, unsigned int, int);
void readcodebytes( void ); /* main.c */

/* compute.c */
void compute( node_p, result_t * );
string mystrcpy(string);
string tostring(word n);

/* equiv.c */
struct perm * tuples( rl_p *, int );

/* fillem.c */
void in_init( char * );     /* main.c */
void in_start( void );      /* main.c */
void dopseudo( void );      /* codegen.c */
void swtxt( void );         /* codegen.c regvar.c */
void fillemlines( void );   /* nextem.c */

/* gencode.c */
void out_init( char * );    /* main.c */
void out_finish( void );
void tstoutput( void );     /* fillem.c */
void genstr( int );         /* codegen.c */
string ad2str( xaddr_t );   /* codegen.c */
void gennl( void );         /* codegen.c */
void prtoken( token_p, int );/* codegen.c */
#ifdef USE_TES
void printlabel( int );     /* codegen.c */
#endif

/* glosym.c */
void enterglo( string, word * );
glosym_p lookglo( string );

/* label.c */
#ifdef USE_TES
void add_label( int, int, int );
label_p get_label( word );
void kill_labels( void );
#endif

/* machine dependent... (mach.c) */
void con_float(void); /* CODE_GENERATOR */
void con_mult(word);
void con_part(int,word);
void f_regsave(void);
void i_regsave(void);
void mes(word);
void prolog(full);
void regreturn(void);
void regsave(char *,long,int);
int regscore(long,int,int,int,int);
#ifdef MACH_OPTIONS
void mach_option(char *);
#endif

/* move.c */
int move( token_p, token_p, int, int, unsigned int );
void setcc( token_p );
int test( token_p, int, int, unsigned int );

/* nextem.c */
byte * nextem( int );

/* reg.c */
void chrefcount( int, int, int );
int getrefcount( int, int );
void erasereg( int );
void cleanregs( void );
#ifndef NDEBUG
void chkregs( void );
#endif

/* regvar.c */
#ifdef REGVARS
struct regvar * linkreg( long, int, int, int );
void tryreg( struct regvar *, int );
void fixregvars( int );
int isregvar( long );
int isregtyp( long );
void unlinkregs( void );
#endif

/* salloc.c */
string myalloc( int );
void myfree( string );
void popstr( int );
char * salloc( int );
void garbage_collect( void );

/* savestatus.c */
void savestatus( state_p sp );
void restorestatus( state_p sp );
void bmove( short *, short *, int );

/* subr.c */
int match( token_p, set_p, int );
void instance( int, token_p );
int eqtoken( token_p, token_p );
int distance( int );
unsigned int costcalc( cost_t );
int ssize( int );
int tsize( token_p );
void tref( token_p, int );
int in_stack( int );
#ifdef MAXSPLIT
int split( token_p, int *, int, int );
#endif
unsigned int docoerc( token_p, c3_p, int, int, int );
unsigned int stackupto( token_p, int, int );
c3_p findcoerc( token_p, set_p );
void itokcost( void );
void error(char *,...);
void fatal(char *,...);
#ifndef NDEBUG
void badassertion( char *, char *, int );
#endif



