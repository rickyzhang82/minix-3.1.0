#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arith.h"
#include "LLlex.h"

struct idf;
struct repl;
struct token;

/* ch3bin.c */
void ch3bin(arith *,int *,int,arith,int);

/* ch3mon.c */
void ch3mon(int,arith *,int *);

/* domacro.c */
void domacro(void);
void do_undef(char *);
void macro_def(struct idf *,char *,int,int,int);

/* error.c */
void error(char *fmt, ...);
void warning(char *fmt, ...);
void strict(char *fmt, ...);
void crash(char *fmt, ...);
void fatal(char *fmt, ...);

/* expr.c */
int rank_of(int);

/* init.c */
void init_pp(void);

/* LLlex.c */
int GetToken(struct token *);
void skipcomment(void);

/* main.c */
void add_dependency(const char *);

/* options.c */
void do_option(char *);

/* preprocess.c */
void do_pragma(void);
void preprocess(const char *);

/* replace.c */
void add2repl(struct repl *,int);
void unstackrepl(void);
void EnableMacros(void);
int replace(struct idf *);

/* skip.c */
int skipspaces(int,int);
int SkipToNewLine(void);

/* expression.g */
void If_expr(void);

/* external (inp_pkg.spec) */
int InsertFile(const char *, const char **, const char **);
