/* $Id: go.h,v 1.3 2005/09/01 12:13:32 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*  S H A R E D    F I L E
 *
 *  G O . H
 *
 */


void go(int argc,char *argv[],void (*initialize)(void),
		void (*optimize)(proc_p),void (*phase_machinit)(FILE *),
		void (*proc_flag)(char *));
			/* ( int argc; char *argv[];
			 *   int (*initialize)(); int (*optimize)(); 
			 *   int (*phase_machinit)(); int (*proc_flag)()  )
			 * This is the main driving routine of the optimizer.
			 * It first processes the flags given as argument;
			 * for every flag it does not recognize itself, it
			 * calls 'proc_flag'; as soon as the -M flag is seen,
			 * it opens the machine descriptor file and
			 * reads phase-independend information (notably the
			 * wordsize and pointersize of the target machine);
			 * next it calls 'phase_machinit' with this file as
			 * parameter. Subsequently it calls 'initialize'.
			 * Finally, all procedures are read, one at a time,
			 * and 'optimize' is called with the current procedure
			 * as parameter.
			 */
void no_action(proc_p);/* ()
			 * Parameter to be supplied for e.g. 'initialize' if
			 * no action is required.
			 */
void core_usage(void);/* ()
			 * Report core usage, if core_flag is set.
			 */
void report(char *,int);	/* ( char *s; int n)
			 * Report number of optimizations found, if 
			 * report_flag is set
			 */
