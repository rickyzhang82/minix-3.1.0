/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: file_info.h,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* F I L E   I N F O R M A T I O N   S T R U C T U R E */

struct file_info {
	unsigned int	fil_lino;
	const char	*fil_name;
	const char	*fil_wdir;
};

#define LineNumber	finfo.fil_lino
#define FileName	finfo.fil_name
#define WorkingDir	finfo.fil_wdir

extern struct file_info finfo;	/* input.c */
