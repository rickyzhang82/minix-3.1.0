/* Copyright (c) 1985 Ceriel J.H. Jacobs */

/* $Header: /cvsup/minix/src/commands/yap/prompt.h,v 1.1.1.1 2005/04/21 14:55:41 beng Exp $ */

# ifndef _PROMPT_
# define PUBLIC extern
# else
# define PUBLIC
# endif

VOID	give_prompt();
/*
 * void give_prompt()
 *
 * Displays a prompt, with possibly an error message
 */

VOID	error();
/*
 * void error(s)
 * char *s;		The error
 *
 * Takes care that there will be an error message in the next prompt.
 */

VOID	ret_to_continue();
/*
 * void ret_to_continue();
 *
 * Asks the user to type something before continuing.
 */

# undef PUBLIC
