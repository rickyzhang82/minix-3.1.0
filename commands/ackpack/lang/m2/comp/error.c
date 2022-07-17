/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* E R R O R   A N D   D I A G N O S T I C   R O U T I N E S */

/* $Id: error.c,v 1.1 2005/09/01 12:13:21 beng Exp $ */

/*	This file contains the (non-portable) error-message and diagnostic
	giving functions.  Be aware that they are called with a variable
	number of arguments!
*/

#include	"errout.h"
#include	"debug.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<stdarg.h>

#include	<system.h>
#include	<em_arith.h>
#include	<em_label.h>
#include	<em_code.h>

#include	"prototypes.h"
#include	"strict3rd.h"
#include	"input.h"
#include	"f_info.h"
#include	"main.h"
#include	"warning.h"
#include	"nostrict.h"

/* error classes */
#define	ERROR		1
#define	WARNING		2
#define	LEXERROR	3
#define	LEXWARNING	4
#define	CRASH		5
#define	FATAL		6
#ifdef DEBUG
#define VDEBUG		7
#endif

int err_occurred;

/*	There are three general error-message functions:
		lexerror()	lexical and pre-processor error messages
		error()		syntactic and semantic error messages
		node_error()	errors in nodes
	The difference lies in the place where the file name and line
	number come from.
	Lexical errors report from the global variables LineNumber and
	FileName, node errors get their information from the
	node, whereas other errors use the information in the token.
*/

static
void
_error(int class,t_node * node,char * fmt,va_list ap,int warn_class)
{
	/*	_error attempts to limit the number of error messages
		for a given line to MAXERR_LINE.
	*/
	unsigned int ln = 0;
	register char *remark = 0;
	
	/* check visibility of message */
	if (class == ERROR || class == WARNING) {
		if (token_nmb < tk_nmb_at_last_syn_err + ERR_SHADOW)
			/* warning or error message overshadowed */
			return;
	}
	/*	Since name and number are gathered from different places
		depending on the class, we first collect the relevant
		values and then decide what to print.
	*/
	/* preliminaries */
	switch (class)	{
	case ERROR:
	case LEXERROR:
	case CRASH:
	case FATAL:
		if (C_busy()) C_ms_err();
		err_occurred = 1;
		break;
	}

	/* the remark */
	switch (class)	{	
	case WARNING:
	case LEXWARNING:
		if (! (warn_class & warning_classes)) return;
		switch(warn_class) {
#ifndef STRICT_3RD_ED
		case W_OLDFASHIONED:
			remark = "(old-fashioned use)";
			break;
#endif
#ifndef NOSTRICT
		case W_STRICT:
			remark = "(strict)";
			break;
#endif
		default:
			remark = "(warning)";
			break;
		}
		break;
	case CRASH:
		remark = "CRASH\007";
		break;
	case FATAL:
		remark = "fatal error --";
		break;
#ifdef DEBUG
	case VDEBUG:
		remark = "(debug)";
		break;
#endif /* DEBUG */
	}
	
	/* the place */
	switch (class)	{	
	case WARNING:
	case ERROR:
		ln = node ? node->nd_lineno : dot.tk_lineno;
		break;
	case LEXWARNING:
	case LEXERROR:
	case CRASH:
	case FATAL:
#ifdef DEBUG
	case VDEBUG:
#endif /* DEBUG */
		ln = LineNumber;
		break;
	}

	if (FileName) fprintf(ERROUT, "\"%s\", line %u: ", FileName, ln);

	if (remark) fprintf(ERROUT, "%s ", remark);

	vfprintf(ERROUT, fmt, ap);		/* contents of error */
	fprintf(ERROUT, "\n");
}

#ifdef DEBUG
/*VARARGS*/
void
debug(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(VDEBUG, NULLNODE, ap, 0);
	}
	va_end(ap);
}
#endif /* DEBUG */

/*VARARGS*/
void
error(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(ERROR, NULLNODE, fmt, ap, 0);
	}
	va_end(ap);
}

/*VARARGS*/
void
node_error(t_node *node, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(ERROR, node, fmt, ap, 0);
	}
	va_end(ap);
}

/*VARARGS*/
void
warning(int class, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(WARNING, NULLNODE, fmt, ap, class);
	}
	va_end(ap);
}

/*VARARGS*/
void
node_warning(t_node *node, int class, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(WARNING, node, fmt, ap, class);
	}
	va_end(ap);
}

/*VARARGS*/
void
lexerror(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(LEXERROR, NULLNODE, fmt, ap, 0);
	}
	va_end(ap);
}

/*VARARGS*/
void
lexwarning(int class, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(LEXWARNING, NULLNODE, fmt, ap, class);
	}
	va_end(ap);
}

/*VARARGS*/
void
fatal(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(FATAL, NULLNODE, fmt, ap, 0);
	}
	va_end(ap);
	exit( 1 );
}

/*VARARGS*/
void
crash(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	{
		_error(CRASH, NULLNODE, fmt, ap, 0);
	}
	va_end(ap);
#ifdef DEBUG
	abort( );
#else
	exit( 1 );
#endif
}
