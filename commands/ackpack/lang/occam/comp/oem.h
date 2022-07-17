/* $Id: oem.h,v 1.1 2005/09/01 12:13:23 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#ifndef nil
#define nil 0
#endif

char * Malloc( unsigned int );		/* c.f module/alloc/alloc.h */

#define word_constant(c)	(-32768L<=(c) && (c)<=32767L)

extern char *curr_file;
extern int Lflag;
extern int ind;

/* Variable size, wordsize, pointer size.  Offsets for local variables. */

extern int wz, pz, vz;
extern int curr_level, curr_offset, min_offset;

/* Expressions */

#define E_NODE	0
#define E_VAR	1	/* Variable *or* channel */
#define E_CONST	2
#define E_TABLE	3
#define E_BTAB	4
#define E_NOW	5
#define E_IO	6
#define E_CALL	7

struct table {
	struct table	*next;
	long	val;
};

struct expr;

struct expr_list {
	struct expr_list	*next;
	struct expr *arg;
};

struct symbol;

struct expr {
	short kind;
	short type;
	int arr_siz;
	union {
		struct {
			int op;
			struct expr *left, *right;
		} node;

		struct symbol *var;

		long cst;

		int tab;

		struct {
			int out;
			struct expr *chan;
			struct expr_list *args;
		} io;

		struct {
			struct expr *c_proc;
			struct expr_list *c_args;
		} call;
	} u;
};

#define valueless(e)		(((e)->type&T_TYPE)==T_VOID)
#define valued(e)		(((e)->type&T_TYPE)==T_VALUE)
#define input_process(e)	((e)->kind==E_IO && !(e)->u.io.out)
#define constant(e)		((e)->kind==E_CONST)
#define arr_constant(e)		((e)->kind==E_TABLE || (e)->kind==E_BTAB)

/* code */

struct replicator {	/* Info transferred from rep_init to rep_test */
	int counter;
	int begin;
	int end;
};

extern struct token {
	long	t_lval;
	char	*t_sval;
} token;

	/* Symbol/Expression type: */
#define	T_VAR		0x0000
#define	T_CHAN		0x0001
#define	T_CONST		0x0002
#define	T_VALUE		0x0003
#define	T_PROC		0x0004
#define T_NOW		0x0005
#define T_VOID		0x0006

#define	T_TYPE		0x0007	/* Mask for type bits */

	/* Flags: */
#define	T_ARR		0x0008	/* Object is an array */
#define	T_BYTE		0x0010	/* Object is a byte array if T_ARR */
#define	T_PARAM		0x0020	/* Formal parameter */
#define	T_LVALUE	0x0040	/* This object may be assigned */
#define T_NOTDECL	0x0080	/* If you didn't declare it */
#define T_USED		0x0100	/* If you've used it */
#define T_ASSIGNED	0x0200	/* Or assigned it */
#define T_REP		0x0400	/* Replicator index */
#define T_BUILTIN	0x0800	/* Builtin name */
#define T_RECURS	0x1000	/* This proc is now compiled */
/* Note that some types and flags are only used for symbols, and others only
 * for expressions.
 */

struct par_list {	/* List of parameter types for a proc object */
	struct par_list *pr_next;
	struct symbol *pr_var;	/* The formal parameter while visible */
	int pr_type;		/* Its type */
};

union storage {		/* An object is found */
	int level;	/* either at a certain local level */
	char *builtin;	/* or using a global builtin name */
};

union type_info {
	struct {
		union storage st;
		int offset;	/* from its local level or builtin name */
	} vc;			/* Variable or channel */

	struct expr *t_const;

	struct {
		union storage st;
		char *file;	/* file it is in */
		int label;	/* A unique id*/
		struct par_list *pars;
	} proc;
};

extern union type_info none;

struct symbol {
	char	*s_name;
	short	s_type;
	int	s_arr_siz;
	union type_info	s_info;
	struct symbol	*s_left, *s_right;
};

#define var_constant(v)	(((v)->s_type&T_TYPE)==T_CONST)
#define var_proc(v)	(((v)->s_type&T_TYPE)==T_PROC)
#define var_declared(v)	(! ((v)->s_type&T_NOTDECL))

struct symtab {
	struct symbol *local;
	struct symtab *global;
	int old_offset;
};

/* Prototypes */

int set_file(char *);
void Label(int);
void dot_label(int);
void branch(int *);
int new_label(int *);
int new_dot_label(int *);
char *proc_label(int,char *);

void cwv(void);
void cvw(void);
void bxx(int,int,int);
void Loc(long);
void Lol(int);
void Lolp(int);
void Lil(int);
void Lof(int);
void Lofp(int);
void Lif(int);
void Txx(int);
void xxi(int);
void Stl(int);
void Inl(int);
void Del(int);
void Loe(char *,int);
void cmi(void);
void ngi(void);
void and(void);
void ior(void);
void xor(void);
void sli(void);
void sri(void);
void com(void);
void lar(void);
void lxl(int);
void lxa(int);
void lfr(int);
void ste(char *,int);
void lae(char *,int);
void aar(void);
void lal(int);
void adp(int);
void ldc0(void);
void zeq(int);
void zne(int);
void zlt(int);
void zgt(int);
void blm(int);
void sti(int);
void cal(char *);
void asp(int);
void loc(int);
void lor0(void);
void loi(int);
void pro(char *);
void ret(int);
void x_end(int);
void stl(int);
void laedot(int);
void del(int);
void lol(int);
void ldl(int);
void meswp(void);
void meserr(void);
void init_rt(void);
void exp(char *);
void rom(int,long);
void blt(int);
void magic(void);
void lin(void);
void tst(void);
void fil(void);
void trp(void);
void main_fil(void);
void init(void);
void openfile(char *);
void closefile(void);
void maxdes(void);

void par_begin(void);
void par_fork(int *);
void par_end(void);
void resumenext(void);
void no_deadlock(void);

struct expr *new_node(int,struct expr *,struct expr *,int);
struct expr *new_var(struct symbol *);
struct expr *new_const(long);
struct expr *new_table(int,struct table *);
struct expr *new_now(void);
struct expr *new_io(int,struct expr *,struct expr_list *);
struct expr *new_call(struct expr *,struct expr_list *);
struct expr *copy_const(struct expr *);
void table_add(struct table ***,long);
void expr_list_add(struct expr_list ***,struct expr *);
void check_param(struct par_list **,struct expr *,int *);
void check_io(int,struct expr *);
void check_wait(struct expr *);
void destroy(struct expr *);
void used(struct expr *);

void rep_init(struct symbol *,struct expr *,struct expr *,struct replicator *);
void rep_test(struct symbol *,struct expr *,struct expr *,struct replicator *);

void code_val(struct expr *);
void code_addr(struct expr *);
void code_void(struct expr *);
void code_assignment(struct expr *);
void code_input(struct expr *);
void code_any(struct expr *,int *);
void code_output(struct expr *);

int memory(int z);

void code_bool(struct expr *,int,int *,int *);
#define positive 1	/* Use positive logic for boolean expression */
#define negative 0	/* Use negative logic, i.e. 0 = true */

void epilogue(struct symbol *);
void prologue(struct symbol *);
void leader(void);
void header(void);
void trailer(void);

void chan_init(union type_info *,int);

void repeat_token(int);
char *tokenname(int,int);
int tabulated(int,int);
int keyword(char *str);
char * keyname(int);

struct symbol *insert(char *name,int type,int arr_siz,union type_info *info);
struct symbol *searchall(char *);

void sym_down(void);
void sym_up(void);
void var_memory(union type_info *,int,int);
void chan_memory(union type_info *,int);

void pars_add(struct par_list ***,int,struct symbol *);
int form_offsets(struct par_list *);
void check_recursion(struct expr *);

void report(const char * fmt, ... );
void warning(const char * fmt, ... );
void fatal(const char * fmt, ... );

