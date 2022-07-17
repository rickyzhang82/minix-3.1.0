/* $Id: langdep.h,v 1.1 2005/09/01 12:13:33 beng Exp $ */

#include <stdio.h>
#include "tree.h"

/* language-dependent routines and formats, together in one structure: */

struct langdep {
  /* language info: */
  int	has_bool_type;		/* set if language has a boolean type */

  /* formats (for fprintf): */
  char	*decint_fmt;		/* decimal ints (format for long) */
  char	*octint_fmt;		/* octal ints (format for long) */
  char	*hexint_fmt;		/* hexadecimal ints (format for long) */
  char	*uns_fmt;		/* unsigneds (format for long) */
  char	*addr_fmt;		/* address (format for long) */
  char	*real_fmt;		/* real (format for double) */

  /* display openers and closers: */
  char	*open_array_display;
  char	*close_array_display;
  char	*open_struct_display;
  char	*close_struct_display;
  char	*open_set_display;
  char	*close_set_display;

  /* language dependant routines: */
  void	(*printstring)(FILE *,char *,int);
  void	(*printchar)(int);
  long	(*arrayelsize)(long);
  int	(*binop_prio)(int);
  int	(*unop_prio)(int);
  int	(*get_string)(int);
  int	(*get_name)(int);
  int	(*get_number)(int);
  int	(*get_token)(int);
  void	(*printop)(FILE *, p_tree);
  void	(*fix_bin_to_pref)(p_tree);
};

extern struct langdep	*m2_dep, *c_dep, *pascal_dep, *currlang;

void find_language(char *);
void init_languages(void);

