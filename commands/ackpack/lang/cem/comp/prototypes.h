/* prototypes.h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arith.h"
#include "dbsymtab.h"
#include "debug.h"
#include "idf.h"
#include "label.h"
#include <flt_arith.h>
#include "expr.h"
#include "def.h"
#include "tokenname.h"

struct declarator;
struct decspecs;
struct def;
struct expr;
struct field;
struct formal;
struct idf;
struct proto;
struct repl;
struct stack_level;
struct token;
struct type;

/* arith.c */
void arithbalance(struct expr **,int,struct expr **);
int any2arith(struct expr **,int);
void float2float(struct expr **,struct type *);
void int2float(struct expr **,struct type *);
void opnd2test(struct expr **,int);
void any2opnd(struct expr **,int);
int int2int(struct expr **,struct type *);
void field2arith(struct expr **);
void erroneous2int(struct expr **);
void function2pointer(struct expr *);
void array2pointer(struct expr *);
void string2pointer(struct expr *);
void float2int(struct expr **,struct type *);
void opnd2integral(struct expr **,int);
void relbalance(struct expr **,int,struct expr **);
void opnd2logical(struct expr **,int);
void switch_sign_fp(struct expr *);
void any2parameter(struct expr **);

/* blocks.c */
void store_block(arith,int);
void load_block(arith,int);
void copy_block(arith,int);

/* ch3.c */
void ch3cast(struct expr **,int,struct type *);
int is_integral_type(struct type *);
void ch3sel(struct expr **,int,struct idf *);
void ch3asgn(struct expr **,int,struct expr *);
int equal_type(struct type *,struct type *,int,int);
int is_arith_type(struct type *);
void ch3incr(struct expr **,int);
int recurqual(struct type *,int);

/* ch3bin.c */
void ch3bin(struct expr **,int,struct expr *);
void mk_binop(struct expr **,int,struct expr *,int);
void pointer_arithmetic(struct expr **,int,struct expr **);

/* ch3mon.c */
void ch3mon(int,struct expr **);

/* code.c */
void code_scope(const char *,struct def *);
void code_expr(struct expr *,int,int,label,label);
void code_declaration(struct idf *,struct expr *,int,int);
void code_continue(void);
void loc_init(struct expr *,struct idf *);
void formal_cvt(int,struct def *);
void db_line(const char *,unsigned int);
void init_code(char *);
void prepend_scopes(void);
void end_code(void);
void bss(struct idf *);
void stack_stmt(label,label);
void unstack_stmt(void);
void flush_strings(void);
void begin_proc(struct decspecs *,struct idf *);
void end_proc(arith);
void code_break(void);
void do_return_expr(struct expr *);
void do_return(void);
label code_string(char *val,int len);

/* conversion.c */
void conversion(struct type *,struct type *);

/* cstoper.c */
void cut_size(struct expr *);
void cstbin(struct expr **,int,struct expr *);
void init_cst(void);

/* dataflow.c */
void DfaCallFunction(const char *);
void DfaEndFunction(void);
void DfaStartFunction(const char *);

/* declarator.c */
void reject_params(struct declarator *);
void remove_declarator(struct declarator *);
void add_decl_unary(struct declarator *,int,int,arith,struct formal *,struct proto *);
void check_array_subscript(struct expr *);
struct type * declare_type(struct type *tp,struct declarator *dc);

/* decspecs.c */
void do_decspecs(struct decspecs *);
struct type * qualifier_type(struct type *tp,int typequal);

/* domacro.c */
void macro_def(struct idf *,char *,int,int,int);
void domacro(void);
void do_undef(struct idf *);
struct idf * GetIdentifier(int skiponerr);

/* error.c */
void error(const char *fmt, ...);
void expr_error(struct expr *expr, const char *fmt, ...);
void lexstrict(const char *fmt, ...);
void strict(const char *fmt, ...);
void expr_strict(struct expr *expr, const char *fmt, ...);
#ifdef DEBUG
void debug(const char *fmt, ...);
#endif /* DEBUG */
void warning(const char *fmt, ...);
void expr_warning(struct expr *expr, const char *fmt, ...);
void lexerror(const char *fmt, ...);
void lexwarning(const char *fmt, ...);
void crash(const char *fmt, ...);
void fatal(const char *fmt, ...);

/* eval.c */
void EVAL(struct expr *,int,int,label,label);
void store_val(struct value *,struct type *);
void load_val(struct expr *,int);
void operands(struct expr *,int);
void assop(struct type *,int);
void load_cst(arith,arith);

/* expr.c */
int is_cp_cst(struct expr *);
void free_expression(struct expr *);
int is_fp_cst(struct expr *);
int is_ld_cst(struct expr *);
void fill_int_expr(struct expr *,arith,int);
void chk_cst_expr(struct expr **);
void dot2expr(struct expr **);
void string2expr(struct expr **,char *,int);
int rank_of(int);
int is_zero_cst(struct expr *);
void init_expression(struct expr ***,struct expr *);
struct expr *intexpr(arith ivalue,int fund);
struct expr *new_oper(struct type *tp,struct expr *e1,int oper,struct expr *e2);

/* field.c */
void eval_field(struct expr *,int);

/* fltcstoper.c */
void fltcstbin(struct expr **,int,struct expr *);

/* idf.c */
int is_anon_idf(struct idf *);
int regtype(struct type *);
void free_formals(struct formal *);
void add_def(struct idf *,int,struct type *,int);
int actual_declaration(int,struct type *);
void update_ahead(struct idf *);
void idf_initialized(struct idf *);
void check_formals(struct idf *,struct declarator *);
void declare_idf(struct decspecs *,struct declarator *,int);
void declare_enum(struct type *,struct idf *,arith);
void declare_params(struct declarator *);
void declare_formals(struct idf *,arith *);
struct idf * gen_idf(void);

/* init.c */
void init_pp(void);

/* input.c */
const char * getwdir(const char *fn);

/* ival.g */
void str_cst(char *str,int len,int inrom);

/* label.c */
void unstack_label(struct idf *);
void enter_label(struct idf *,int);

/* LLlex.c */
int GetToken(struct token *);
void skipcomment(void);
void PushLex(void);
void PopLex(void);

/* main.c */
void add_dependency(const char *);

/* make.tokcase */
char * symbol2str(int tok);

/* options.c */
void do_option(char *);

/* pragma.c */
void do_pragma(void);

/* program.g */
void If_expr(void);
void C_program(void);

/* proto.c */
void remove_proto_idfs(struct proto *);
void update_proto(struct type *,struct type *);
void check_for_void(struct proto *);
void call_proto(struct expr **);
void add_proto(struct proto *,struct decspecs *,struct declarator *,int);
void declare_protos(struct declarator *);

/* replace.c */
void add2repl(struct repl *,int);
void unstackrepl(void);
void EnableMacros(void);
int replace(struct idf *);
int actual(struct repl *);

/* skip.c */
int SkipToNewLine(void);
int skipspaces(int,int);

/* stab.c */
void stb_typedef(struct type *,const char *);
void stb_string(struct def *,int,const char *);
void stb_tag(struct tag *,const char *);

/* stack.c */
void stack_idf(struct idf *,struct stack_level *);
void stack_level(void);
void unstack_world(void);
void unstack_level(void);
struct stack_level * stack_level_of(int lvl);

/* struct.c */
int is_struct_or_union(int);
void declare_struct(int,struct idf *,struct type **);
void apply_struct(int,struct idf *,struct type **);
void add_sel(struct type *,struct type *,struct idf *,struct sdef ***,arith *,struct field *);
struct sdef * idf2sdef(struct idf *idf,struct type *tp);

/* switch.c */
void code_case(struct expr *);
void code_default(void);
void code_startswitch(struct expr **);
void code_endswitch(void);

/* tokenname.c */
void reserve(struct tokenname []);

/* type.c */
void idf2type(struct idf *,struct type **);
void completed(struct type *);
struct type *construct_type(int fund,struct type *tp,int qual,arith count,struct proto *pl);
arith size_of_type(struct type *tp,char nm[]);
struct type * pointer_to(struct type *tp,int qual);
arith align(arith pos,int al);
struct type * create_type(int fund);
struct type * promoted_type(struct type *tp);
struct type * standard_type(int fund,int sgn,int algn,arith sz);
struct type * array_of(struct type *tp,arith count,int qual);
struct type * function_of(struct type *tp,struct proto *pl,int qual);

/* util.c */
void FreeLocal(arith);
void LoadLocal(arith,arith);
void StoreLocal(arith,arith);
void LocalInit(void);
void LocalFinish(void);
void AddrLocal(arith);
void RegisterAccount(arith,arith,int,int);
arith NewLocal(arith sz,int al,int regtype,int sc);

