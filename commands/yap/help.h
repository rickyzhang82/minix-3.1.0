/* Copyright (c) 1985 Ceriel J.H. Jacobs */

/* $Header: /cvsup/minix/src/commands/yap/help.h,v 1.1.1.1 2005/04/21 14:55:39 beng Exp $ */

# ifndef _HELP_
# define PUBLIC extern
# else
# define PUBLIC
# endif

int	do_help();
/*
 * int do_help(cnt);
 * long cnt;			This is ignored, but a count is given
 *				to any command
 *
 * Give a summary of commands
 */

# undef PUBLIC
