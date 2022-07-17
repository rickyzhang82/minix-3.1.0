/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* I N S T A N T I A T I O N   O F   I N P U T   M O D U L E */

/* $Id: input.h,v 1.1 2005/09/01 12:13:22 beng Exp $ */

#include	"inputtype.h"

#define INP_NPUSHBACK 2
#define INP_TYPE	struct f_info
#define INP_VAR		file_info

#include <inp_pkg.spec>
