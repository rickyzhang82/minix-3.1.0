/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: varinfo.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#define VI_NSTR 1
#define VI_NINT 3

typedef struct varinfo {
	struct varinfo *vi_next;
	char *vi_str[VI_NSTR];
	int vi_int[VI_NINT];
	struct varinfo *vi_vi;
} varinfo;

#define VI_NULL (struct varinfo *) 0
