/* E X P R E S S I O N   C H E C K I N G */

extern int	(*ExprChkTable[])(struct node *);	/* table of expression checking
					   functions, indexed by node class
					*/

extern int	(*VarAccChkTable[])(struct node *);	/* table of variable-access checking
					   functions, indexed by node class
					*/

#define	ChkExpression(expp)	((*ExprChkTable[(expp)->nd_class])(expp))
#define	ChkVarAccess(expp)	((*VarAccChkTable[(expp)->nd_class])(expp))
