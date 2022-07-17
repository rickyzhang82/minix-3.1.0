#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# include <io.h>		/* mktemp() */
#endif

#include "types.h"
#include "pattern.h"

short readshort(void);	/* getline.c */
#ifdef LONGOFF
offset readoffset(void);
#endif
void draininput(void);
short getint(void);
sym_p getsym(int);
offset getoff(void);
void make_string(int);
void inident(void);
int table3(int);
int table1(void);
int table2(void);
void getlines(void);
void argstring(offset length,argb_p abp);
line_p arglist(int);
offset aoff(arg_p ap,int n);
int inpseudo(short);
void tstinpro(void);

void process(void);
void relabel(void);
void symknown(void);
void cleanlocals(void);
void checklocs(void);
offset align(offset,offset);
void symvalue(void);
void do_tes(void);

void backward(void);

line_p	newline(int);
void oldline(line_p);
arg_p newarg(int);
void oldargs(arg_p);
void oldargb(argb_p);
reg_p newreg(void);
void oldreg(reg_p);
num_p newnum(void);
void oldnum(num_p);
offset *newrom(void);
sym_p newsym(int);
argb_p newargb(void);
void compactcore(void);
short *grabcore(int);
short *newcore(int);
char *mymalloc(int);
void myfree(void*);
void oldcore(short *,int);
void coreinit(short *,short *);
short *freshcore(int);
short *myalloc(int);

void putlines(line_p);
void putargs(arg_p);
void putstr(argb_p);
void outdef(sym_p);
void outocc(sym_p);
void outpro(void);
void outend(void);
void outinst(int);
void outoff(offset);
void outint(short);
void outshort(short);
void numlab(num_p);
void outnum(num_p);
void outsym(sym_p);

void cleanup(void);

void opcheck(byte *);
void hashpatterns(void);
bool peephole(void);
bool optimize(void);
offset oabs(offset);
line_p repline(eval_t,int);
offset rotate(offset,offset);
/*eval_t compute();*/
bool tryrepl(line_p*,byte*,int);
bool trypat(line_p*,byte*,int);
int basicblock(line_p*);
int repl_mul(line_p,line_p*,line_p*);

void flow(void);
void findreach(void);
void reach(line_p);
void cleaninstrs(void);

void init_state(void);
void tes_pseudos(void);
void tes_instr(line_p,line_p,line_p);
void assign_label(num_p);
void do_inst_label(line_p);

void regvar(arg_p);
int inreg(offset);
void outregs(void);
void outtes(void);
void incregusage(offset);

void error(char *,...);
#ifndef NDEBUG
void badassertion(char * file,unsigned int line);
#endif
