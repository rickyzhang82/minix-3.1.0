/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: types.h,v 1.3 2005/09/01 12:13:35 beng Exp $ */

typedef char byte;
typedef char bool;
typedef struct line line_t;
typedef struct line *line_p;
typedef struct sym sym_t;
typedef struct sym *sym_p;
typedef struct num num_t;
typedef struct num *num_p;
typedef struct arg arg_t;
typedef struct arg *arg_p;
typedef struct argbytes argb_t;
typedef struct argbytes *argb_p;
typedef struct regs reg_t;
typedef struct regs *reg_p;
#ifdef LONGOFF
typedef long offset;
#else
typedef short offset;
#endif
