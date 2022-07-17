/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* I N S T A N T I A T I O N   O F   I N P U T   P A C K A G E */

/* $Id: input.c,v 1.1 2005/09/01 12:13:21 beng Exp $ */

#include	"f_info.h"
struct f_info	file_info;
#include	"input.h"
#include	<inp_pkg.body>

int
AtEoIF(void)
{
	/*	Make the unstacking of input streams noticable to the
	   	lexical analyzer
	*/
	if (WorkingDir && WorkingDir[0] != '\0') free(WorkingDir);
	return 1;
}

int
AtEoIT(void)
{
	/*	Make the end of the text noticable
	*/
	return 1;
}
