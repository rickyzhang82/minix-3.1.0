/* Copyright (c) 1991 by the Vrije Universiteit, Amsterdam, the Netherlands.
 * For full copyright and restrictions on use see the file COPYING in the top
 * level of the LLgen tree.
 */

/*
 *  L L G E N
 *
 *  An Extended LL(1) Parser Generator
 *
 *  Author : Ceriel J.H. Jacobs
 */

/*
 * $Id: extern.h,v 1.3 2005/09/01 12:13:29 beng Exp $
 * Miscellanious constants and
 * some variables that are visible in more than one file
 */

# define LTEXTSZ	256	/* Size of longest token */

/*
 * options for the identifier search routine
 */

# define ENTERING	1
# define BOTH		2

/*
 * Now for some	declarations
 */

extern char	ltext[];	/* input buffer	*/
extern int	nnonterms;	/* number of nonterminals */
extern int	ntokens;	/* number of terminals */
extern int	nterms;		/* number of terms */
extern int	nalts;		/* number of alternatives */
extern p_start	start;		/* will	contain	startsymbols */
#ifdef NON_CORRECTING
extern int	nsubstarts;	/* number of subparserstarts */
extern p_set	start_firsts;	/* Will contain the union of first sets of
				   startsymbols when -n -s option is on */
#endif
extern int	linecount;	/* line number */
extern int	assval;		/* to create difference	between	literals
				 * and other terminals
				 */
extern p_nont	nonterms;	/* the nonterminal array */
extern p_nont	maxnt;		/* is filled up until here */
extern p_token	tokens;		/* the token array */
extern p_token	maxt;		/* is filled up until here */
extern int	norder, torder;
				/* order of nonterminals in the grammar,
				 * important because actions are copied to
				 * a temporary file in the order in which they
				 * were read
				 */
extern const_string	e_noopen;	/* Error message string used often */
extern int	verbose;	/* Level of verbosity */
extern int	wflag;		/* warnings? */
extern const_string	lexical;	/* name of lexical analyser */
extern string	prefix;		/* prefix of externals */
extern string	onerror;	/* name of user error handler */
extern int	ntneeded;	/* ntneeded = 1 if nonterminals are included
				 * in the sets.
				 */
extern int	ntprint;	/* ntprint = 1 if they must be printed too in
				 * the LL.output file (-x option)
				 */
# ifndef NDEBUG
extern int	debug;
# endif /* not NDEBUG */
extern p_file	files,pfile;	/* pointers to file structure.
				 * "files" points to the start of the
				 * list */
extern p_file	maxfiles;
extern const_string	LLgenid;	/* LLgen identification string */
extern t_token	lextoken;	/* the current token */
extern int	nerrors;
extern string	rec_file, incl_file;
#ifdef NON_CORRECTING
extern string	nc_rec_file, nc_incl_file;
#endif
extern int	low_percentage, high_percentage;
extern int	min_cases_for_jmptable;
extern int	jmptable_option;
extern int	ansi_c;
#ifdef NON_CORRECTING
extern int	non_corr;
extern int	subpars_sim;
extern p_gram	illegal_gram;
#endif
extern int	strip_grammar;
extern int	in_production;
extern int	no_line_directives;

