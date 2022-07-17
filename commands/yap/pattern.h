/* Copyright (c) 1985 Ceriel J.H. Jacobs */

/* $Header: /cvsup/minix/src/commands/yap/pattern.h,v 1.1.1.1 2005/04/21 14:55:41 beng Exp $ */

# ifndef _PATTERN_
# define PUBLIC extern
# else
# define PUBLIC
# endif

char *	re_comp();
int	re_exec();

# undef PUBLIC
