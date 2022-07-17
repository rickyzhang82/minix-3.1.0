/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* M I S C E L L A N E O U S    R O U T I N E S */

/* $Id: misc.c,v 1.1 2005/09/01 12:13:21 beng Exp $ */

#include	<alloc.h>
#include	<em_arith.h>
#include	<em_label.h>

#include	"prototypes.h"
#include	"f_info.h"
#include	"misc.h"

void
match_id(t_idf *id1,t_idf *id2)
{
	/*	Check that identifiers id1 and id2 are equal. If they
		are not, check that we did'nt generate them in the
		first place, and if not, give an error message
	*/
	if (id1 != id2 && !is_anon_idf(id1) && !is_anon_idf(id2)) {
		error("name \"%s\" does not match block name \"%s\"",
		      id1->id_text,
		      id2->id_text
		);
	}
}

t_idf *
gen_anon_idf(void)
{
	/*	A new idf is created out of nowhere, to serve as an
		anonymous name.
	*/
	static int name_cnt;
	char *s = Malloc(strlen(FileName)+50);

	sprintf(s, "#%d in %s, line %u",
			++name_cnt, FileName, LineNumber);
	s = Realloc(s, strlen(s)+1);
	return str2idf(s, 0);
}

void
not_declared(char *what,t_node *id,char *where)
{
	/*	The identifier "id" is not declared. If it is not generated,
		give an error message
	*/
	if (!is_anon_idf(id->nd_IDF)) {
		node_error(id,
		 	   "%s \"%s\" not declared%s",
			   what,
			   id->nd_IDF->id_text,
			   where);
	}
}
