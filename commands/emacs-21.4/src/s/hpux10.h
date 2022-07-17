#include "hpux9shr.h"

#define HPUX10

/* We have to go this route, rather than hpux9's approach of renaming the
   functions via macros.  The system's stdlib.h has fully prototyped
   declarations, which yields a conflicting definition of srand48; it
   tries to redeclare what was once srandom to be srand48.  So we go
   with HAVE_LRAND48 being defined.  */
#undef srandom
#undef random
#undef HAVE_RANDOM

#define FORCE_ALLOCA_H

/* AlainF 20-Jul-1996 says this is right.  */
#undef KERNEL_FILE
#define KERNEL_FILE "/stand/vmunix"

#ifdef LIBS_SYSTEM
#undef LIBS_SYSTEM
#endif
#ifdef HPUX_NET
#define LIBS_SYSTEM -ln -l:libdld.sl
#else
#define LIBS_SYSTEM -l:libdld.sl
#endif

/* Rainer Malzbender <rainer@displaytech.com> says definining
   HAVE_XRMSETDATABASE allows Emacs to compile on HP-UX 10.20
   using GCC.  */

#ifndef HAVE_XRMSETDATABASE
#define HAVE_XRMSETDATABASE
#endif

/* Make sure we get select from libc rather than from libcurses
   because libcurses on HPUX 10.10 has a broken version of select.
   We used to use -lc -lcurses, but this may be cleaner.  */
#define LIBS_TERMCAP -ltermcap

#undef C_SWITCH_X_SYSTEM
#undef LD_SWITCH_X_DEFAULT
/* However, HPUX 10 puts Xaw and Xmu in a strange place
   (if you install them at all).  So search that place.  */
#define C_SWITCH_X_SYSTEM  -I/usr/include/X11R6 -I/usr/include/X11R5 -I/usr/include/Motif1.2 -I/usr/contrib/X11R6/include -I/usr/contrib/X11R5/include
#define LD_SWITCH_X_DEFAULT -L/usr/lib/X11R6 -L/usr/lib/X11R5 -L/usr/lib/Motif1.2 -L/usr/contrib/X11R5/lib

/* 2000-11-21: Temporarily disable Unix 98 large file support found by
   configure.  It fails on HPUX 11, at least, because it enables
   header sections which lose when `static' is defined away, as it is
   on HP-UX.  (You get duplicate symbol errors on linking). */

#undef _FILE_OFFSET_BITS

/* Don't define _BSD */
#undef C_SWITCH_SYSTEM


/* HP-UX 10.10 seem to have problems with signals coming in
   Causes "poll: interrupted system call" messages when Emacs is run
   in an X window (see process.c) */
#define POLL_INTERRUPTED_SYS_CALL
