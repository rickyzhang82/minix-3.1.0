/* Function prototypes */
/* Check out LL_ANSI_C */

#include <stdio.h>	/* FILE */
#include <stdlib.h>
#include <string.h>

#if !defined( _P )
#define _P(fn,args)	fn args
#endif

void p_init(void);

#ifndef LL_ANSI_C

void LLscan(int);
void LLread(void);
void LLerror(int);
void LLsafeerror(int);
#ifndef LLNOFIRSTS
int LLfirst(int,int);
#endif
int LLnext(int);
int LLskip(void);
void LLnewlevel(unsigned int*);
void LLoldlevel(unsigned int*);

#endif /* LL_ANSI_C */

p_mem alloc(unsigned int);
p_mem ralloc(p_mem,unsigned int);
p_mem new_mem(p_info);

void conflchecks(void);
void do_compute(void);
int t_safety(int,int,int,int);
int t_after(int,int,int);
void gencode(int);

void UNLINK(const_string);
void RENAME(const_string,const_string);
string libpath(const_string);

void comfatal(void);
void copyfile(const_string);
void install(const_string, const_string);

void name_init(void);
string store(const_string);
p_gram search(int,const_string,int);

void co_reach(void);

#ifdef NON_CORRECTING
void save_grammar(FILE *);
#endif

#ifndef LL_ANSI_C
int scanner(void);
#endif /* LL_ANSI_C */
int input(void);
void unput(int);
void skipcomment(int);
void LLmessage(int);

void warning(int,const char*,...);
void error(int,const char*,...);
void fatal(int,const char*,...);

void LLparse(void);

int empty(p_gram);
