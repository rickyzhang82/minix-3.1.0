/* $Id: operator.h,v 1.1 2005/09/01 12:13:33 beng Exp $ */

#include "ops.h"

typedef struct operator {
	int	op_nargs;
	void	(*op_fun)(p_tree);
} t_operator, *p_operator;

extern t_operator operators[];

#define nargs(n)	(operators[(n)].op_nargs)
