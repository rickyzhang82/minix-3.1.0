/* Copyright (c) 1985 Ceriel J.H. Jacobs */

/* $Header: /cvsup/minix/src/commands/yap/options.h,v 1.1.1.1 2005/04/21 14:55:40 beng Exp $ */

# ifndef _OPTIONS_
# define PUBLIC extern
# else
# define PUBLIC
# endif

PUBLIC int	cflag;		/* no home before each page */
PUBLIC int	uflag;		/* no underlining */
PUBLIC int	nflag;		/* no pattern matching on input */
PUBLIC int	qflag;		/* no exit on the next page command */
PUBLIC char *	startcomm;	/* There was a command option */

char ** readoptions();
/*
 * char ** readoptions(argv)
 * char **argv;			Arguments given to yap.
 *
 * process the options from the arguments. Return 0 if there was an error,
 * otherwise return a pointer to where the filenames start.
 */

# undef PUBLIC
