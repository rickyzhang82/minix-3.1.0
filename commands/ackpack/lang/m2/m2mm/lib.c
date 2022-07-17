/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* L I B R A R Y */

/* $Id: lib.c,v 1.1 2005/09/01 12:13:22 beng Exp $ */

#include <string.h>
#include <alloc.h>
#include "main.h"

/* XXX This needs fixing */
#if 0
#include <em_path.h>
#else
#define EM_DIR "/usr"
#endif

#ifdef OTHER_HOME
#undef EM_DIR
#define EM_DIR OTHER_HOME
#endif
static char lib_dir[128] = EM_DIR;

static struct liblist {
	int libno;
	struct liblist *libnext;
} *lblist;

int
is_library_dir(char *d)
{
	/*	Check if directory d is a directory containing
		"system" definition modules. Return 1 if it is, 0 otherwise.
	*/

	register struct liblist *p = lblist;

	while (p) {
		if (! strcmp(DEFPATH[p->libno], d)) return 1;
		p = p->libnext;
	}
	return 0;
}

#ifndef DEF_DIR
#define DEF_DIR	"lib/m2"
#endif

void
init_lib(void)
{
	strcat(lib_dir, "/");
	strcat(lib_dir, DEF_DIR);
	AddLibDir(lib_dir);
}

void
set_libdir(int n)
{
	register struct liblist *p = 
		(struct liblist *) Malloc(sizeof(struct liblist));

	p->libnext = lblist;
	p->libno = n;
	lblist = p;
}
