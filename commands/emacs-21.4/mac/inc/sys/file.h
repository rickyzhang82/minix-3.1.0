/* Replacement sys/file.h file for building GNU Emacs on the Macintosh.
   Copyright (C) 1999, 2000 Free Software Foundation, Inc.

This file is part of GNU Emacs.

GNU Emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* Contributed by Andrew Choi (akochoi@users.sourceforge.net).  */

#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#include <Files.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __MRC__
#undef open
#undef creat

#define open mpw_open
#define creat mpw_creat

#include <fcntl.h>

#undef open
#undef creat

#define open sys_open
#define creat sys_creat
#endif

#ifdef __MWERKS__
#include <unix.h>
#endif

mode_t umask(mode_t);

void abort(void);
void _exit(int);
int kill(int,int);
int alarm(int);
int pause(void);
char *getwd(char *);

#endif  /* _SYS_FILE_H */
