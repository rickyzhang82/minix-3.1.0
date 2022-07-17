/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* F I L E   D E S C R I P T O R   S T R U C T U R E */

/* $Id: f_info.h,v 1.1 2005/09/01 12:13:22 beng Exp $ */

struct f_info {
	unsigned short f_lineno;
	char *f_fn;
	char *f_workingdir;
};

extern struct f_info file_info;
#define LineNumber file_info.f_lineno
#define FileName file_info.f_fn
#define WorkingDir file_info.f_workingdir
