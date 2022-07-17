# Generated automatically from Makefile.in by configure.
# Makefile for GNU Emacs.
# Copyright (C) 1985, 87, 88, 93, 94, 95, 99, 2000, 2001
# Free Software Foundation, Inc.

# This file is part of GNU Emacs.

# GNU Emacs is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# GNU Emacs is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with GNU Emacs; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.


# Note that this file is edited by msdos/sed1v2.inp for MSDOS.  That
# script may need modifying in sync with changes made here.  Try to
# avoid shell-ism because the DOS build has to use the DOS shell.

# Don't try to replace the ccp processing using autoconf facilities,
# says rms.

# Here are the things that we expect ../configure to edit.
# We use $(srcdir) explicitly in dependencies so as not to depend on VPATH.
srcdir=/net/tmp/emacs-21.4/src
VPATH=/net/tmp/emacs-21.4/src
CC=cc
CPP=cc -E
CFLAGS=-g -O2
CPPFLAGS=-D_BSD_SOURCE  
LDFLAGS=
LN_S=ln -s
# Substitute an assignment for the MAKE variable, because
# BSD doesn't have it as a default.

# Don't use LIBS.  configure puts stuff in it that either shouldn't be
# linked with Emacs or is duplicated by the cpp stuff below.
# LIBS = -lm  
LIBOBJS = 

# On Xenix and the IBM RS6000, double-dot gets screwed up.
dot = .
dotdot = ${dot}${dot}
lispsource = ${srcdir}/$(dot)$(dot)/lisp/
libsrc = $(dot)$(dot)/lib-src/
etc = $(dot)$(dot)/etc/
oldXMenudir = $(dot)$(dot)/oldXMenu/
lwlibdir = $(dot)$(dot)/lwlib/

# Configuration files for .o files to depend on.
M_FILE = ${srcdir}/m/intel386.h
S_FILE = ${srcdir}/s/gnu-linux.h
config_h = config.h $(M_FILE) $(S_FILE)

# ========================== start of cpp stuff =======================
/* From here on, comments must be done in C syntax.  */

C_SWITCH_SYSTEM=

/* just to be sure the sh is used */
SHELL=/bin/sh

#define THIS_IS_MAKEFILE
#define NO_SHORTNAMES
#define NOT_C_CODE
#include "config.h"

/* We won't really call alloca;
   don't let the file name alloca.c get messed up.  */
#ifdef alloca
#undef alloca
#endif

/* Don't let the file name mktime.c get messed up.  */
#ifdef mktime
#undef mktime
#endif

/* Use HAVE_X11 as an alias for X11 in this file
   to avoid problems with X11 as a subdirectory name
   in -I and other such options which pass through this file. */

#ifdef X11
#define HAVE_X11
#undef X11
#endif

/* On some machines #define register is done in config;
   don't let it interfere with this file.  */
#undef register

/* On some systems we may not be able to use the system make command. */
#ifdef MAKE_COMMAND
MAKE = MAKE_COMMAND
#endif

#ifdef C_COMPILER
CC = C_COMPILER
#endif

/* GNU libc requires ORDINARY_LINK so that its own crt0 is used.
   Linux is an exception because it uses a funny variant of GNU libc.  */
#ifdef __GNU_LIBRARY__
#ifndef LINUX
#define ORDINARY_LINK
#endif
#endif

/* Some machines don't find the standard C libraries in the usual place.  */
#ifndef ORDINARY_LINK
#ifndef LIB_STANDARD
#define LIB_STANDARD -lc
#endif
#else
#ifndef LIB_STANDARD
#define LIB_STANDARD
#endif
#endif

/* Unless inhibited or changed, use -lg to link for debugging.  */
#ifndef LIBS_DEBUG
#define LIBS_DEBUG -lg
#endif

/* Some s/SYSTEM.h files define this to request special libraries.  */
#ifndef LIBS_SYSTEM
#define LIBS_SYSTEM
#endif

/* Some m/MACHINE.h files define this to request special libraries.  */
#ifndef LIBS_MACHINE
#define LIBS_MACHINE
#endif

#ifndef LIB_MATH
#  define LIB_MATH -lm
#endif /* LIB_MATH */

/* Some s/SYSTEM.h files define this to request special switches in ld.  */
#ifndef LD_SWITCH_SYSTEM
#if !defined (__GNUC__) && (defined(COFF_ENCAPSULATE) || (defined (BSD_SYSTEM) && !defined (COFF)))
#define LD_SWITCH_SYSTEM -X
#else /* ! defined(COFF_ENCAPSULATE) || (defined (BSD_SYSTEM) && !defined (COFF)) */
#define LD_SWITCH_SYSTEM
#endif /* ! defined(COFF_ENCAPSULATE) || (defined (BSD_SYSTEM) && !defined (COFF)) */
#endif /* LD_SWITCH_SYSTEM */

/* This holds special options for linking temacs
   that should be used for linking anything else.  */
#ifndef LD_SWITCH_SYSTEM_TEMACS
#define LD_SWITCH_SYSTEM_TEMACS
#endif

/* Some m/MACHINE.h files define this to request special switches in ld.  */
#ifndef LD_SWITCH_MACHINE
#define LD_SWITCH_MACHINE
#endif

/* This holds special options for linking temacs
   that should be used for linking anything else.  */
#ifndef LD_SWITCH_MACHINE_TEMACS
#define LD_SWITCH_MACHINE_TEMACS
#endif

/* Some m/MACHINE.h files define this to request special switches in cc.  */
#ifndef C_SWITCH_MACHINE
#define C_SWITCH_MACHINE
#endif

/* Some s/SYSTEM.h files define this to request special switches in cc.  */
#ifndef C_SWITCH_SYSTEM
#define C_SWITCH_SYSTEM
#endif

/* These macros are for switches specifically related to X Windows.  */
#ifndef C_SWITCH_X_MACHINE
#define C_SWITCH_X_MACHINE
#endif

#ifndef C_SWITCH_X_SYSTEM
#define C_SWITCH_X_SYSTEM
#endif

#ifndef C_SWITCH_X_SITE
#define C_SWITCH_X_SITE
#endif

#ifndef LD_SWITCH_X_SITE
#define LD_SWITCH_X_SITE
#endif

#ifndef LD_SWITCH_X_DEFAULT
#define LD_SWITCH_X_DEFAULT
#endif

/* These can be passed in from config.h to define special load and
   compile switches needed by individual sites */
#ifndef LD_SWITCH_SITE
#define LD_SWITCH_SITE
#endif

#ifndef C_SWITCH_SITE
#define C_SWITCH_SITE
#endif

#ifndef ORDINARY_LINK

#ifndef CRT0_COMPILE
#define CRT0_COMPILE $(CC) -c $(ALL_CFLAGS) C_SWITCH_ASM
#endif

#ifndef START_FILES
#ifdef NO_REMAP
#ifdef COFF_ENCAPSULATE
#define START_FILES pre-crt0.o /usr/local/lib/gcc-crt0.o
#else /* ! defined (COFF_ENCAPSULATE) */
#define START_FILES pre-crt0.o /lib/crt0.o
#endif /* ! defined (COFF_ENCAPSULATE) */
#else /* ! defined (NO_REMAP) */
#define START_FILES ecrt0.o
#endif /* ! defined (NO_REMAP) */
#endif /* START_FILES */
STARTFILES = START_FILES

#else /* ORDINARY_LINK */

/* config.h might want to force START_FILES anyway */
#ifdef START_FILES
STARTFILES = START_FILES
#endif /* START_FILES */

#endif /* not ORDINARY_LINK */


/* cc switches needed to make `asm' keyword work.
   Nothing special needed on most machines.  */
#ifndef C_SWITCH_ASM
#define C_SWITCH_ASM
#endif

#ifdef USE_X_TOOLKIT
#define USE_none
TOOLKIT_DEFINES = -DUSE_none
#else
TOOLKIT_DEFINES =
#endif

/* DO NOT use -R.  There is a special hack described in lastfile.c
   which is used instead.  Some initialized data areas are modified
   at initial startup, then labeled as part of the text area when
   Emacs is dumped for the first time, and never changed again. */

/* -Demacs is needed to make some files produce the correct version
   for use in Emacs.

   -DHAVE_CONFIG_H is needed for some other files to take advantage of
   the information in `config.h'.  */

/* C_SWITCH_X_SITE must come before C_SWITCH_X_MACHINE and C_SWITCH_X_SYSTEM
   since it may have -I options that should override those two.  */
ALL_CFLAGS=-Demacs -DHAVE_CONFIG_H $(TOOLKIT_DEFINES) $(MYCPPFLAGS) -I. -I${srcdir} C_SWITCH_MACHINE C_SWITCH_SYSTEM C_SWITCH_SITE C_SWITCH_X_SITE C_SWITCH_X_MACHINE C_SWITCH_X_SYSTEM ${CFLAGS}
.c.o:
	$(CC) -c $(CPPFLAGS) $(ALL_CFLAGS) $<

#ifndef LIBX10_MACHINE
#define LIBX10_MACHINE
#endif

#ifndef LIBX11_MACHINE
#define LIBX11_MACHINE
#endif

#ifndef LIBX10_SYSTEM
#define LIBX10_SYSTEM
#endif

#ifndef LIBX11_SYSTEM
#define LIBX11_SYSTEM
#endif

#ifndef LIB_X11_LIB
#define LIB_X11_LIB -lX11
#endif

#ifdef HAVE_X_WINDOWS
#ifdef HAVE_MENUS

/* Include xmenu.o in the list of X object files.  */
XOBJ= xterm.o xfns.o xselect.o xrdb.o fontset.o

/* The X Menu stuff is present in the X10 distribution, but missing
   from X11.  If we have X10, just use the installed library;
   otherwise, use our own copy.  */
#ifdef HAVE_X11
#ifdef USE_X_TOOLKIT
OLDXMENU=${lwlibdir}liblw.a
LIBXMENU= $(OLDXMENU)
#else /* not USE_X_TOOLKIT */
OLDXMENU= ${oldXMenudir}libXMenu11.a
LIBXMENU= $(OLDXMENU)
#endif /* not USE_X_TOOLKIT */
#else /* not HAVE_X11 */
LIBXMENU= -lXMenu
#endif /* not HAVE_X11 */

#else /* not HAVE_MENUS */

/* Otherwise, omit xmenu.o from the list of X object files, and
   don't worry about the menu library at all.  */
XOBJ= xterm.o xfns.o xselect.o xrdb.o fontset.o
LIBXMENU=
#endif /* not HAVE_MENUS */

#ifdef USE_X_TOOLKIT
#define none
#if defined (LUCID) || defined (ATHENA)
#if HAVE_XAW3D
LIBW= -lXaw3d
#else
LIBW= -lXaw
#endif
#endif
#ifdef MOTIF
#if defined (HAVE_MOTIF_2_1) && defined (HAVE_LIBXP)
#define LIB_MOTIF_EXTRA -lXp
#else
#define LIB_MOTIF_EXTRA
#endif
#ifdef LIB_MOTIF
LIBW= LIB_MOTIF LIB_MOTIF_EXTRA
#else
LIBW= -lXm LIB_MOTIF_EXTRA
#endif
#endif
#ifdef OPEN_LOOK
LIBW= -lXol
#endif

#ifdef HAVE_X11XTR6
#ifdef NEED_LIBW
LIBXTR6 = -lSM -lICE -lw
#else
LIBXTR6 = -lSM -lICE
#endif
#endif

#ifndef LIBXMU
#define LIBXMU -lXmu
#endif

#ifdef LIBXT_STATIC
/* We assume the config files have defined STATIC_OPTION
   since that might depend on the operating system.
   (Don't forget you need different definitions with and without __GNUC__.)  */
LIBXT= STATIC_OPTION $(LIBW) LIBXMU -lXt $(LIBXTR6) -lXext DYNAMIC_OPTION
#else /* not LIBXT_STATIC */
LIBXT= $(LIBW) LIBXMU -lXt $(LIBXTR6) -lXext
#endif /* not LIBXT_STATIC */

#else /* not USE_X_TOOLKIT */
LIBXT=
#endif /* not USE_X_TOOLKIT */

#if HAVE_XPM
#ifndef LIBXPM
#define LIBXPM -lXpm
#endif /* not defined LIBXPM */
#else /* not HAVE_XPM */
#define LIBXPM
#endif /* not HAVE_XPM */

#if HAVE_JPEG
#ifndef LIBJPEG
#define LIBJPEG -ljpeg
#endif /* not defined LIBJPEG */
#else /* not HAVE_JPEG */
#define LIBJPEG
#endif /* not HAVE_JPEG */

#if HAVE_PNG
#ifndef LIBPNG
#define LIBPNG -lpng -lz -lm
#endif /* not defined LIBPNG */
#else /* not HAVE_PNG */
#define LIBPNG
#endif /* not HAVE_PNG */

#if HAVE_TIFF
#ifndef LIBTIFF
#define LIBTIFF -ltiff
#endif /* not defined LIBTIFF */
#else /* not HAVE_TIFF */
#define LIBTIFF
#endif /* not HAVE_TIFF */

#if HAVE_GIF
#ifndef LIBGIF
#define LIBGIF -lungif
#endif /* not defined LIBGIF */
#else /* not HAVE_GIF */
#define LIBGIF
#endif /* not HAVE_GIF */

#ifdef HAVE_X11
/* LD_SWITCH_X_DEFAULT comes after everything else that specifies
   options for where to find X libraries, but before those libraries.  */
X11_LDFLAGS = LD_SWITCH_X_SITE LD_SWITCH_X_DEFAULT
LIBX= $(LIBXMENU) $(X11_LDFLAGS) $(LIBXT) LIBTIFF LIBJPEG LIBPNG LIBGIF LIBXPM LIB_X11_LIB LIBX11_MACHINE LIBX11_SYSTEM
#else /* not HAVE_X11 */
LIBX= $(LIBXMENU) LD_SWITCH_X_SITE -lX10 LIBX10_MACHINE LIBX10_SYSTEM
#endif /* not HAVE_X11 */
#endif /* not HAVE_X_WINDOWS */

LIBSOUND= 

#ifndef ORDINARY_LINK
/* Fix linking if compiled with GCC.  */
#ifdef __GNUC__

#if __GNUC__ > 1

#ifdef LINKER
#define LINKER_WAS_SPECIFIED
#endif

/* Versions of GCC >= 2.0 put their library, libgcc.a, in obscure
   places that are difficult to figure out at make time.  Fortunately,
   these same versions allow you to pass arbitrary flags on to the
   linker, so there's no reason not to use it as a linker.

   Well, it's not quite perfect.  The `-nostdlib' keeps GCC from
   searching for libraries in its internal directories, so we have to
   ask GCC explicitly where to find libgcc.a.  */

#ifndef LINKER
#define LINKER $(CC) -nostdlib
#endif

#ifndef LIB_GCC
/* Ask GCC where to find libgcc.a.  */
#define LIB_GCC `$(CC) -print-libgcc-file-name`
#endif /* not LIB_GCC */

GNULIB_VAR = LIB_GCC

#ifndef LINKER_WAS_SPECIFIED
/* GCC passes any argument prefixed with -Xlinker directly to the
   linker.  See prefix-args.c for an explanation of why we don't do
   this with the shell's `for' construct.
   Note that some people don't have '.'  in their paths, so we must
   use ./prefix-args.  */
#define YMF_PASS_LDFLAGS(flags) `./prefix-args -Xlinker flags`
#else
#define YMF_PASS_LDFLAGS(flags) flags
#endif

#else /* __GNUC__ < 2 */

#ifndef LIB_GCC
#define LIB_GCC /usr/local/lib/gcc-gnulib
#endif /* not LIB_GCC */
GNULIB_VAR = `if [ -f LIB_GCC ] ; then echo LIB_GCC; else echo; fi`
#endif /* __GNUC__ < 2 */
#else /* not __GNUC__ */
GNULIB_VAR =

#endif /* not __GNUC__ */
#endif /* not ORDINARY_LINK */

/* Specify address for ld to start loading at,
   if requested by configuration.  */
#ifdef LD_TEXT_START_ADDR
STARTFLAGS = -T LD_TEXT_START_ADDR -e __start
#endif

#ifdef ORDINARY_LINK
LD = $(CC)
#else
#ifdef COFF_ENCAPSULATE
LD=$(CC) -nostdlib
#else /* not ORDINARY_LINK */
#ifdef LINKER
LD=LINKER
#else /* not LINKER */
LD=ld
#endif /* not LINKER */
#endif /* not COFF_ENCAPSULATE */
#endif /* not ORDINARY_LINK */

ALL_LDFLAGS = LD_SWITCH_SYSTEM LD_SWITCH_SYSTEM_TEMACS LD_SWITCH_MACHINE \
	 LD_SWITCH_MACHINE_TEMACS LD_SWITCH_SITE $(LDFLAGS)

/* A macro which other sections of Makefile can redefine to munge the
   flags before they're passed to LD.  This is helpful if you have
   redefined LD to something odd, like "gcc".
   (The YMF prefix is a holdover from the old name "ymakefile".)
  */
#ifndef YMF_PASS_LDFLAGS
#define YMF_PASS_LDFLAGS(flags) flags
#endif

/* Allow config.h to specify a replacement file for unexec.c.  */
#ifndef UNEXEC
#define UNEXEC unexec.o
#endif
#ifndef UNEXEC_SRC
#define UNEXEC_SRC unexec.c
#endif

INTERVAL_SRC = intervals.h composite.h

GETLOADAVG_LIBS = 

#ifdef MSDOS
#ifdef HAVE_X_WINDOWS
MSDOS_OBJ = dosfns.o msdos.o
#else
MSDOS_OBJ = dosfns.o msdos.o w16select.o
#endif
#endif


/* lastfile must follow all files
   whose initialized data areas should be dumped as pure by dump-emacs.  */
obj=    dispnew.o frame.o scroll.o xdisp.o xmenu.o window.o \
	charset.o coding.o category.o ccl.o\
	cm.o term.o xfaces.o $(XOBJ) \
	emacs.o keyboard.o macros.o keymap.o sysdep.o \
	buffer.o filelock.o insdel.o marker.o \
	minibuf.o fileio.o dired.o filemode.o \
	cmds.o casetab.o casefiddle.o indent.o search.o regex.o undo.o \
	alloc.o data.o doc.o editfns.o callint.o \
	eval.o floatfns.o fns.o print.o lread.o \
	abbrev.o syntax.o UNEXEC mocklisp.o bytecode.o \
	process.o callproc.o \
	region-cache.o sound.o atimer.o \
	doprnt.o strftime.o intervals.o textprop.o composite.o md5.o \
	$(MSDOS_OBJ)

/* Object files used on some machine or other.
   These go in the DOC file on all machines
   in case they are needed there.  */
SOME_MACHINE_OBJECTS = sunfns.o dosfns.o msdos.o \
  xterm.o xfns.o xmenu.o xselect.o xrdb.o fontset.o


#ifdef TERMINFO
/* Used to be -ltermcap here.  If your machine needs that,
   define LIBS_TERMCAP in the m/MACHINE.h file.  */
#ifndef LIBS_TERMCAP
#define LIBS_TERMCAP -lcurses
#endif /* LIBS_TERMCAP */
termcapobj = terminfo.o
#else /* ! defined (TERMINFO) */
#ifndef LIBS_TERMCAP
#define LIBS_TERMCAP
termcapobj = termcap.o tparam.o
#else /* LIBS_TERMCAP */
termcapobj = tparam.o
#endif /* LIBS_TERMCAP */
#endif /* ! defined (TERMINFO) */


#ifndef SYSTEM_MALLOC

#ifdef DOUG_LEA_MALLOC
#ifdef REL_ALLOC
mallocobj = ralloc.o vm-limit.o
#else /* ! defined (REL_ALLOC) */
mallocobj = vm-limit.o
#endif /* ! defined (REL_ALLOC) */
#else /* ! defined (DOUG_LEA_MALLOC) */
#ifdef REL_ALLOC
mallocobj = gmalloc.o ralloc.o vm-limit.o
#else /* ! defined (REL_ALLOC) */
mallocobj = gmalloc.o vm-limit.o
#endif /* ! defined (REL_ALLOC) */
#endif /* ! defined (DOUG_LEA_MALLOC) */

#endif /* SYSTEM_MALLOC */


#ifndef HAVE_ALLOCA
allocaobj = alloca.o
#else
allocaobj =
#endif

#ifdef USE_X_TOOLKIT
widgetobj= widget.o
#else /* not USE_X_TOOLKIT */
widgetobj=
#endif /* not USE_X_TOOLKIT */


/* define otherobj as list of object files that make-docfile
   should not be told about.  */
otherobj= $(termcapobj) lastfile.o $(mallocobj) $(allocaobj) $(widgetobj) $(LIBOBJS)

#ifdef HAVE_MOUSE
#define MOUSE_SUPPORT ${lispsource}mouse.elc \
  ${lispsource}select.elc ${lispsource}scroll-bar.elc
#else
#define MOUSE_SUPPORT
#endif

#ifdef VMS
#define VMS_SUPPORT ${lispsource}vmsproc.elc ${lispsource}vms-patch.elc
#else
#define VMS_SUPPORT
#endif

#ifdef MSDOS
#define MSDOS_SUPPORT ${lispsource}ls-lisp.elc ${lispsource}disp-table.elc \
 ${lispsource}dos-fns.elc ${lispsource}dos-w32.elc ${lispsource}dos-vars.elc \
 ${lispsource}international/ccl.elc ${lispsource}international/codepage.elc

#else
#define MSDOS_SUPPORT
#endif

#ifdef WINDOWSNT
#define WINNT_SUPPORT ${lispsource}ls-lisp.elc ${lispsource}w32-fns.elc \
  ${lispsource}dos-w32.elc
#else
#define WINNT_SUPPORT
#endif

/* List of Lisp files loaded into the dumped Emacs.  It's arranged
   like this because it's easier to generate it semi-mechanically from
   loadup.el this way.

   Note that this list should not include lisp files which might not
   be present, like site-load.el and site-init.el; this makefile
   expects them all to be either present or buildable.

   Files which are loaded unconditionally should be in shortlisp as well.
   Files included conditionally here should be included (unconditionally)
   in SOME_MACHINE_LISP.  */

lisp= \
	${lispsource}abbrev.elc \
	${lispsource}buff-menu.elc \
	${lispsource}byte-run.elc \
	${lispsource}cus-start.el \
	${lispsource}custom.elc \
	${lispsource}emacs-lisp/lisp-mode.elc \
	${lispsource}emacs-lisp/lisp.elc \
	${lispsource}env.elc \
	${lispsource}faces.elc \
	${lispsource}files.elc \
	${lispsource}format.elc \
	${lispsource}facemenu.elc \
	MOUSE_SUPPORT \
	${lispsource}float-sup.elc \
	${lispsource}frame.elc\
	${lispsource}help.elc \
	${lispsource}indent.elc \
	${lispsource}isearch.elc \
	${lispsource}loadup.el \
	${lispsource}loaddefs.el \
	${lispsource}bindings.elc \
	${lispsource}map-ynp.elc \
	${lispsource}menu-bar.elc \
	${lispsource}international/mule.elc \
	${lispsource}international/mule-conf.el \
	${lispsource}international/mule-cmds.elc \
	${lispsource}international/characters.elc \
	${lispsource}international/utf-8.elc \
	${lispsource}international/utf-16.elc \
	${lispsource}international/latin-1.el \
	${lispsource}international/latin-2.el \
	${lispsource}international/latin-3.el \
	${lispsource}international/latin-4.el \
	${lispsource}international/latin-5.el \
	${lispsource}international/latin-8.el \
	${lispsource}international/latin-9.el \
	${lispsource}case-table.elc \
	${lispsource}language/chinese.elc \
	${lispsource}language/cyrillic.elc \
	${lispsource}language/indian.elc \
	${lispsource}language/devanagari.elc \
	${lispsource}language/english.elc \
	${lispsource}language/ethiopic.elc \
	${lispsource}language/european.elc \
	${lispsource}language/czech.elc \
	${lispsource}language/slovak.elc \
	${lispsource}language/romanian.elc \
	${lispsource}language/greek.elc \
	${lispsource}language/hebrew.elc \
	${lispsource}language/japanese.elc \
	${lispsource}language/korean.elc \
	${lispsource}language/lao.elc \
	${lispsource}language/thai.elc \
	${lispsource}language/tibetan.elc \
	${lispsource}language/vietnamese.elc \
	${lispsource}language/misc-lang.elc \
	${lispsource}international/ucs-tables.elc \
	${lispsource}paths.el \
	${lispsource}register.elc \
	${lispsource}replace.elc \
	${lispsource}simple.elc \
	${lispsource}startup.elc \
	${lispsource}subr.elc \
	${lispsource}term/tty-colors.elc \
	${lispsource}textmodes/fill.elc \
	${lispsource}textmodes/page.elc \
	${lispsource}textmodes/paragraphs.elc \
	${lispsource}textmodes/text-mode.elc \
	${lispsource}vc-hooks.elc \
	${lispsource}ediff-hook.elc \
	VMS_SUPPORT \
	MSDOS_SUPPORT \
	WINNT_SUPPORT \
	${lispsource}widget.elc \
	${lispsource}window.elc \
	${lispsource}version.el

/* These are relative file names for the Lisp files
   that are loaded unconditionally.  This is used in make-docfile.
   It need not contain the files that are loaded conditionally
   because SOME_MACHINE_LISP has those.  */
shortlisp= \
	../lisp/abbrev.elc \
	../lisp/buff-menu.elc \
	../lisp/byte-run.elc \
	../lisp/cus-start.el \
	../lisp/custom.elc \
	../lisp/emacs-lisp/backquote.elc \
	../lisp/emacs-lisp/lisp-mode.elc \
	../lisp/emacs-lisp/lisp.elc \
	../lisp/facemenu.elc \
	../lisp/faces.elc \
	../lisp/files.elc \
	../lisp/float-sup.elc \
	../lisp/format.elc \
	../lisp/frame.elc \
	../lisp/help.elc \
	../lisp/indent.elc \
	../lisp/isearch.elc \
	../lisp/loadup.el \
	../lisp/loaddefs.el \
	../lisp/bindings.elc \
	../lisp/map-ynp.elc \
	../lisp/env.elc \
	../lisp/international/mule.elc \
	../lisp/international/mule-conf.el \
	../lisp/international/mule-cmds.elc \
	../lisp/international/characters.elc \
	../lisp/international/utf-8.elc \
	../lisp/international/utf-16.elc \
	../lisp/international/latin-1.el \
	../lisp/international/latin-2.el \
	../lisp/international/latin-3.el \
	../lisp/international/latin-4.el \
	../lisp/international/latin-5.el \
	../lisp/international/latin-8.el \
	../lisp/international/latin-9.el \
	../lisp/case-table.elc \
	../lisp/language/chinese.elc \
	../lisp/language/cyrillic.elc \
	../lisp/language/indian.elc \
	../lisp/language/devanagari.elc \
	../lisp/language/english.elc \
	../lisp/language/ethiopic.elc \
	../lisp/language/european.elc \
	../lisp/language/czech.elc \
	../lisp/language/slovak.elc \
	../lisp/language/romanian.elc \
	../lisp/language/greek.elc \
	../lisp/language/hebrew.elc \
	../lisp/language/japanese.elc \
	../lisp/language/korean.elc \
	../lisp/language/lao.elc \
	../lisp/language/thai.elc \
	../lisp/language/tibetan.elc \
	../lisp/language/vietnamese.elc \
	../lisp/language/misc-lang.elc \
	../lisp/international/ucs-tables.elc \
	../lisp/menu-bar.elc \
	../lisp/paths.el \
	../lisp/register.elc \
	../lisp/replace.elc \
	../lisp/simple.elc \
	../lisp/startup.elc \
	../lisp/subr.elc \
	../lisp/term/tty-colors.elc \
	../lisp/textmodes/fill.elc \
	../lisp/textmodes/page.elc \
	../lisp/textmodes/paragraphs.elc \
	../lisp/textmodes/text-mode.elc \
	../lisp/vc-hooks.elc \
	../lisp/ediff-hook.elc \
	../lisp/widget.elc \
	../lisp/window.elc \
	../lisp/version.el

/* Lisp files that may or may not be used.
   We must unconditionally put them in the DOC file.
   We use ../lisp/ to start the file names
   to reduce the size of the argument list for make-docfile
   for the sake of systems which can't handle large ones.  */
SOME_MACHINE_LISP = ${dotdot}/lisp/mouse.elc \
  ${dotdot}/lisp/select.elc ${dotdot}/lisp/scroll-bar.elc \
  ${dotdot}/lisp/vmsproc.elc ${dotdot}/lisp/vms-patch.elc \
  ${dotdot}/lisp/ls-lisp.elc ${dotdot}/lisp/dos-fns.elc \
  ${dotdot}/lisp/w32-fns.elc ${dotdot}/lisp/dos-w32.elc \
  ${dotdot}/lisp/disp-table.elc ${dotdot}/lisp/dos-vars.elc \
  ${dotdot}/lisp/international/ccl.elc \
  ${dotdot}/lisp/international/codepage.elc

/* Construct full set of libraries to be linked.
   Note that SunOS needs -lm to come before -lc; otherwise, you get
   duplicated symbols.  If the standard libraries were compiled
   with GCC, we might need gnulib again after them.  */
LIBES = $(LOADLIBES) $(LIBS) $(LIBX) $(LIBSOUND) \
   LIBS_SYSTEM LIBS_MACHINE LIBS_TERMCAP \
   LIBS_DEBUG $(GETLOADAVG_LIBS) $(GNULIB_VAR) LIB_MATH LIB_STANDARD \
   $(GNULIB_VAR)

/* Enable recompilation of certain other files depending on system type.  */

#ifndef OTHER_FILES
#define OTHER_FILES
#endif

#ifndef OBJECTS_MACHINE
#define OBJECTS_MACHINE
#endif

all: emacs OTHER_FILES

emacs: temacs ${etc}DOC ${lisp}
#ifdef CANNOT_DUMP
	rm -f emacs
	ln temacs emacs
#else
#ifdef HAVE_SHM
	LC_ALL=C ./temacs -nl -batch -l loadup dump
#else /* ! defined (HAVE_SHM) */
	LC_ALL=C ./temacs -batch -l loadup dump
#endif /* ! defined (HAVE_SHM) */
#endif /* ! defined (CANNOT_DUMP) */
	-./emacs -q -batch -f list-load-path-shadows

/* We run make-docfile twice because the command line may get too long
   on some systems.  */
/* ${SOME_MACHINE_OBJECTS} comes before ${obj} because some files may
   or may not be included in ${obj}, but they are always included in
   ${SOME_MACHINE_OBJECTS}.  Since a file is processed when it is mentioned
   for the first time, this prevents any variation between configurations
   in the contents of the DOC file.
   Likewise for ${SOME_MACHINE_LISP}.  */
${etc}DOC: ${libsrc}make-docfile ${obj} ${shortlisp} ${SOME_MACHINE_LISP}
	-rm -f ${etc}DOC
	${libsrc}make-docfile -d ${srcdir} ${SOME_MACHINE_OBJECTS} ${obj} > ${etc}DOC
	${libsrc}make-docfile -a ${etc}DOC -d ${srcdir} ${SOME_MACHINE_LISP} ${shortlisp}

${libsrc}make-docfile:
	cd ${libsrc}; ${MAKE} ${MFLAGS} make-docfile

/* Some systems define this to cause parallel Make-ing.  */
#ifndef MAKE_PARALLEL
#define MAKE_PARALLEL
#endif

temacs: MAKE_PARALLEL $(LOCALCPP) $(STARTFILES) stamp-oldxmenu ${obj} ${otherobj} OBJECTS_MACHINE prefix-args
	$(LD) YMF_PASS_LDFLAGS (${STARTFLAGS} ${ALL_LDFLAGS}) \
    -o temacs ${STARTFILES} ${obj} ${otherobj}  \
    OBJECTS_MACHINE ${LIBES}

/* We don't use ALL_LDFLAGS because LD_SWITCH_SYSTEM and LD_SWITCH_MACHINE
   often contain options that have to do with using Emacs's crt0,
   which are only good with temacs.  */
prefix-args: prefix-args.c $(config_h)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) ${srcdir}/prefix-args.c -o prefix-args

/* Don't lose if this was not defined.  */
#ifndef OLDXMENU_OPTIONS
#define OLDXMENU_OPTIONS
#endif

/* Don't lose if this was not defined.  */
#ifndef LWLIB_OPTIONS
#define LWLIB_OPTIONS
#endif

#if defined (HAVE_X_WINDOWS) && defined (HAVE_X11) && defined (HAVE_MENUS)

/* We use stamp-xmenu with these two deps
   to both ensure that lwlib gets remade based on its dependencies
   in its own makefile,
   and remake temacs if lwlib gets changed by this.  */
stamp-oldxmenu: ${OLDXMENU} ../src/$(OLDXMENU) 
	touch stamp-oldxmenu
/* Supply an ordering for parallel make.  */
../src/$(OLDXMENU): ${OLDXMENU}

#ifdef USE_X_TOOLKIT
$(OLDXMENU): really-lwlib

/* Encode the values of these two macros in Make variables,
   so we can use $(...) to substitute their values within "...".  */
C_SWITCH_MACHINE_1 = C_SWITCH_MACHINE
C_SWITCH_SYSTEM_1 = C_SWITCH_SYSTEM
C_SWITCH_SITE_1 = C_SWITCH_SITE
C_SWITCH_X_SITE_1 = C_SWITCH_X_SITE
C_SWITCH_X_MACHINE_1 = C_SWITCH_X_MACHINE
C_SWITCH_X_SYSTEM_1 = C_SWITCH_X_SYSTEM
really-lwlib:
	cd ${lwlibdir}; ${MAKE} ${MFLAGS} LWLIB_OPTIONS \
    CC='${CC}' CFLAGS='${CFLAGS}' MAKE='${MAKE}' \
    "C_SWITCH_X_SITE=$(C_SWITCH_X_SITE_1)" \
    "C_SWITCH_X_MACHINE=$(C_SWITCH_X_MACHINE_1)" \
    "C_SWITCH_X_SYSTEM=$(C_SWITCH_X_SYSTEM_1)" \
    "C_SWITCH_SITE=$(C_SWITCH_SITE_1)" \
    "C_SWITCH_MACHINE=$(C_SWITCH_MACHINE_1)" \
    "C_SWITCH_SYSTEM=$(C_SWITCH_SYSTEM_1)"
	@true  /* make -t should not create really-lwlib.  */
.PHONY: really-lwlib
#else /* not USE_X_TOOLKIT */
$(OLDXMENU): really-oldXMenu

/* Encode the values of these two macros in Make variables,
   so we can use $(...) to substitute their values within "...".  */
C_SWITCH_MACHINE_1 = C_SWITCH_MACHINE
C_SWITCH_SYSTEM_1 = C_SWITCH_SYSTEM
C_SWITCH_SITE_1 = C_SWITCH_SITE
C_SWITCH_X_SITE_1 = C_SWITCH_X_SITE
C_SWITCH_X_MACHINE_1 = C_SWITCH_X_MACHINE
C_SWITCH_X_SYSTEM_1 = C_SWITCH_X_SYSTEM
really-oldXMenu:
	cd ${oldXMenudir}; ${MAKE} ${MFLAGS} OLDXMENU_OPTIONS \
    CC='${CC}' CFLAGS='${CFLAGS}' MAKE='${MAKE}' \
    "C_SWITCH_X_SITE=$(C_SWITCH_X_SITE_1)" \
    "C_SWITCH_X_MACHINE=$(C_SWITCH_X_MACHINE_1)" \
    "C_SWITCH_X_SYSTEM=$(C_SWITCH_X_SYSTEM_1)" \
    "C_SWITCH_SITE=$(C_SWITCH_SITE_1)" \
    "C_SWITCH_MACHINE=$(C_SWITCH_MACHINE_1)" \
    "C_SWITCH_SYSTEM=$(C_SWITCH_SYSTEM_1)"
	@true  /* make -t should not create really-oldXMenu.  */
.PHONY: really-oldXMenu
#endif /* not USE_X_TOOLKIT */
#else /* not (HAVE_X_WINDOWS && HAVE_X11 && HAVE_MENUS) */

/* We don't really need this, but satisfy the dependency.  */
stamp-oldxmenu:
	touch stamp-oldxmenu
#endif /* not (HAVE_X_WINDOWS && HAVE_X11 && HAVE_MENUS) */

../config.status:: epaths.in
	@echo "The file epaths.h needs to be set up from epaths.in."
	@echo "Please run the `configure' script again."
	exit 1

../config.status:: config.in
	@echo "The file config.h needs to be set up from config.in."
	@echo "Please run the `configure' script again."
	exit 1

/* Some machines have alloca built-in.
   They should define HAVE_ALLOCA, or may just let alloca.s
   be used but generate no code.
   Some have it written in assembler in alloca.s.
   Some use the C version in alloca.c (these define C_ALLOCA in config.h).
   */

#ifdef C_ALLOCA
/* We could put something in alloca.c to #define free and malloc
   whenever emacs was #defined, but that's not appropriate for all
   users of alloca in Emacs.  Check out ../lib-src/getopt.c.  */
alloca.o : alloca.c
	$(CC) -c $(CPPFLAGS) -DEMACS_FREE=xfree \
	$(ALL_CFLAGS) ${srcdir}/alloca.c
#else
#ifndef HAVE_ALLOCA
alloca.o : alloca.s $(config_h)
/* $(CPP) is cc -E, which may get confused by filenames
   that do not end in .c.  So copy file to a safe name.  */
	-rm -f allocatem.c
	cp ${srcdir}/alloca.s allocatem.c
/* Remove any ^L, blank lines, and preprocessor comments,
   since some assemblers barf on them.  Use a different basename for the
   output file, since some stupid compilers (Green Hill's) use that
   name for the intermediate assembler file. */
	$(CPP) $(CPPFLAGS) $(ALL_CFLAGS) allocatem.c | \
	sed -e 's///' -e 's/^#.*//' | \
	sed -n -e '/^..*$$/p' > allocax.s
	-rm -f alloca.o
/* Xenix, in particular, needs to run assembler via cc.  */
	$(CC) -c allocax.s
	mv allocax.o alloca.o
	-rm -f allocax.s allocatem.c
#endif /* HAVE_ALLOCA */
#endif /* ! defined (C_ALLOCA) */

/* Nearly all the following files depend on lisp.h,
   but it is not included as a dependency because
   it is so often changed in ways that do not require any recompilation
   and so rarely changed in ways that do require any.  */

abbrev.o: abbrev.c buffer.h window.h dispextern.h commands.h charset.h \
	$(config_h)
buffer.o: buffer.c buffer.h region-cache.h commands.h window.h \
   dispextern.h $(INTERVAL_SRC) blockinput.h atimer.h systime.h charset.h \
   $(config_h)
callint.o: callint.c window.h commands.h buffer.h mocklisp.h \
   keyboard.h dispextern.h $(config_h)
callproc.o: callproc.c epaths.h buffer.h commands.h $(config_h) \
	process.h systty.h syssignal.h charset.h coding.h ccl.h msdos.h \
        composite.h
casefiddle.o: casefiddle.c syntax.h commands.h buffer.h composite.h $(config_h)
casetab.o: casetab.c buffer.h $(config_h)
category.o: category.c category.h buffer.h charset.h $(config_h)
ccl.o: ccl.c ccl.h charset.h coding.h $(config_h)
charset.o: charset.c charset.h buffer.h coding.h composite.h disptab.h \
	$(config_h)
coding.o: coding.c coding.h ccl.h buffer.h charset.h $(config_h)
cm.o: cm.c cm.h termhooks.h $(config_h)
cmds.o: cmds.c syntax.h buffer.h charset.h commands.h window.h $(config_h) \
	msdos.h dispextern.h
pre-crt0.o: pre-crt0.c
ecrt0.o: ecrt0.c $(config_h)
	CRT0_COMPILE ${srcdir}/ecrt0.c
dired.o: dired.c commands.h buffer.h $(config_h) charset.h coding.h regex.h \
   systime.h
dispnew.o: dispnew.c  commands.h frame.h window.h buffer.h dispextern.h \
   termchar.h termopts.h termhooks.h cm.h disptab.h systty.h systime.h \
   xterm.h blockinput.h atimer.h charset.h msdos.h composite.h keyboard.h \
   $(config_h)
doc.o: doc.c $(config_h) epaths.h buffer.h keyboard.h charset.h
doprnt.o: doprnt.c charset.h $(config_h)
dosfns.o: buffer.h termchar.h termhooks.h frame.h msdos.h dosfns.h $(config_h)
editfns.o: editfns.c window.h buffer.h systime.h $(INTERVAL_SRC) charset.h \
   coding.h dispextern.h $(config_h)
emacs.o: emacs.c commands.h systty.h syssignal.h blockinput.h process.h \
   termhooks.h buffer.h atimer.h systime.h $(INTERVAL_SRC) $(config_h)
fileio.o: fileio.c window.h buffer.h systime.h $(INTERVAL_SRC) charset.h \
   coding.h ccl.h msdos.h dispextern.h $(config_h)
filelock.o: filelock.c buffer.h systime.h epaths.h $(config_h)
filemode.o: filemode.c  $(config_h)
frame.o: frame.c xterm.h window.h frame.h termhooks.h commands.h keyboard.h \
   buffer.h charset.h fontset.h msdos.h dosfns.h dispextern.h $(config_h)
fontset.o: dispextern.h fontset.h fontset.c ccl.h buffer.h charset.h frame.h \
   keyboard.h $(config_h)
getloadavg.o: getloadavg.c $(config_h)
indent.o: indent.c frame.h window.h indent.h buffer.h $(config_h) termchar.h \
   termopts.h disptab.h region-cache.h charset.h composite.h dispextern.h \
   keyboard.h
insdel.o: insdel.c window.h buffer.h $(INTERVAL_SRC) blockinput.h charset.h\
   dispextern.h atimer.h systime.h $(config_h)
keyboard.o: keyboard.c termchar.h termhooks.h termopts.h buffer.h charset.h \
   commands.h frame.h window.h macros.h disptab.h keyboard.h syssignal.h \
   systty.h systime.h dispextern.h syntax.h $(INTERVAL_SRC) blockinput.h \
   atimer.h xterm.h puresize.h msdos.h $(config_h)
keymap.o: keymap.c buffer.h commands.h keyboard.h termhooks.h blockinput.h \
   atimer.h systime.h puresize.h charset.h intervals.h $(config_h)
lastfile.o: lastfile.c  $(config_h)
macros.o: macros.c window.h buffer.h commands.h macros.h keyboard.h \
	dispextern.h $(config_h)
malloc.o: malloc.c $(config_h)
gmalloc.o: gmalloc.c $(config_h)
ralloc.o: ralloc.c $(config_h)
vm-limit.o: vm-limit.c mem-limits.h $(config_h)
marker.o: marker.c buffer.h charset.h $(config_h)
minibuf.o: minibuf.c syntax.h dispextern.h frame.h window.h keyboard.h \
   buffer.h commands.h charset.h msdos.h $(config_h)
mktime.o: mktime.c $(config_h)
mocklisp.o: mocklisp.c buffer.h $(config_h)
msdos.o: msdos.c msdos.h dosfns.h systime.h termhooks.h dispextern.h frame.h \
   termopts.h termchar.h charset.h coding.h ccl.h disptab.h window.h \
   keyboard.h $(config_h)
process.o: process.c process.h buffer.h window.h termhooks.h termopts.h \
   commands.h syssignal.h systime.h systty.h syswait.h frame.h dispextern.h \
   blockinput.h atimer.h charset.h coding.h ccl.h msdos.h composite.h \
   keyboard.h $(config_h)
regex.o: regex.c syntax.h buffer.h $(config_h) regex.h category.h charset.h
region-cache.o: region-cache.c buffer.h region-cache.h
scroll.o: scroll.c termchar.h dispextern.h frame.h msdos.h keyboard.h \
   $(config_h)
search.o: search.c regex.h commands.h buffer.h region-cache.h syntax.h \
   blockinput.h atimer.h systime.h category.h charset.h composite.h $(config_h)
strftime.o: strftime.c $(config_h)
syntax.o: syntax.c syntax.h buffer.h commands.h category.h charset.h \
   composite.h $(config_h)
sysdep.o: sysdep.c $(config_h) dispextern.h termhooks.h termchar.h termopts.h \
   frame.h syssignal.h systty.h systime.h syswait.h blockinput.h atimer.h \
   window.h msdos.h dosfns.h keyboard.h
term.o: term.c termchar.h termhooks.h termopts.h $(config_h) cm.h frame.h \
   disptab.h dispextern.h keyboard.h charset.h coding.h ccl.h msdos.h
termcap.o: termcap.c $(config_h)
terminfo.o: terminfo.c $(config_h)
tparam.o: tparam.c $(config_h)
undo.o: undo.c buffer.h commands.h $(config_h)
/* This hack is to discard any space that cpp might put at the beginning
   of UNEXEC when substituting it in.  */
UNEXEC_ALIAS=UNEXEC
$(UNEXEC_ALIAS): UNEXEC_SRC $(config_h)
w16select.o: w16select.c dispextern.h frame.h blockinput.h atimer.h systime.h \
   msdos.h $(config_h)
widget.o: widget.c xterm.h frame.h dispextern.h widgetprv.h \
   $(srcdir)/../lwlib/lwlib.h $(config_h)
window.o: window.c indent.h commands.h frame.h window.h buffer.h termchar.h \
   termhooks.h disptab.h keyboard.h dispextern.h msdos.h composite.h \
   $(config_h)
xdisp.o: xdisp.c macros.h commands.h indent.h buffer.h dispextern.h coding.h \
   termchar.h frame.h window.h disptab.h termhooks.h charset.h $(config_h) \
   msdos.h composite.h fontset.h
xfaces.o: xfaces.c dispextern.h frame.h xterm.h buffer.h blockinput.h \
   window.h charset.h msdos.h dosfns.h composite.h atimer.h systime.h $(config_h)
xfns.o: xfns.c buffer.h frame.h window.h keyboard.h xterm.h dispextern.h \
   $(srcdir)/../lwlib/lwlib.h blockinput.h atimer.h systime.h epaths.h \
   charset.h $(config_h)
xmenu.o: xmenu.c xterm.h termhooks.h window.h dispextern.h frame.h keyboard.h \
   buffer.h $(srcdir)/../lwlib/lwlib.h blockinput.h atimer.h systime.h \
   msdos.h $(config_h)
xterm.o: xterm.c xterm.h termhooks.h termopts.h termchar.h window.h buffer.h \
  dispextern.h frame.h disptab.h blockinput.h atimer.h systime.h syssignal.h \
  keyboard.h gnu.h charset.h ccl.h fontset.h composite.h \
  coding.h $(config_h)
xselect.o: xselect.c dispextern.h frame.h xterm.h blockinput.h charset.h \
  coding.h ccl.h buffer.h atimer.h systime.h $(config_h)
xrdb.o: xrdb.c $(config_h) epaths.h
hftctl.o: hftctl.c $(config_h)
sound.o: sound.c dispextern.h $(config_h)
atimer.o: atimer.c atimer.h systime.h $(config_h)

/* The files of Lisp proper */

alloc.o: alloc.c frame.h window.h buffer.h  puresize.h syssignal.h keyboard.h \
 blockinput.h atimer.h systime.h charset.h dispextern.h $(config_h) $(INTERVAL_SRC)
bytecode.o: bytecode.c buffer.h syntax.h charset.h $(config_h)
data.o: data.c buffer.h puresize.h charset.h syssignal.h keyboard.h $(config_h)
eval.o: eval.c commands.h keyboard.h blockinput.h atimer.h systime.h \
  $(config_h)
floatfns.o: floatfns.c $(config_h)
fns.o: fns.c commands.h $(config_h) frame.h buffer.h charset.h keyboard.h \
 frame.h window.h dispextern.h $(INTERVAL_SRC)
print.o: print.c process.h frame.h window.h buffer.h keyboard.h charset.h\
   $(config_h) dispextern.h msdos.h composite.h
lread.o: lread.c commands.h keyboard.h buffer.h epaths.h charset.h $(config_h) \
 termhooks.h msdos.h

/* Text properties support */
textprop.o: textprop.c buffer.h window.h dispextern.h $(INTERVAL_SRC) \
	$(config_h)
intervals.o: intervals.c buffer.h $(INTERVAL_SRC) keyboard.h puresize.h $(config_h)
composite.o: composite.c buffer.h  charset.h $(INTERVAL_SRC) $(config_h)

/* System-specific programs to be made.
   OTHER_FILES and OBJECTS_MACHINE
   select which of these should be compiled.  */

sunfns.o: sunfns.c buffer.h window.h dispextern.h $(config_h)

${libsrc}emacstool: ${libsrc}emacstool.c
	cd ${libsrc}; ${MAKE} ${MFLAGS} emacstool
mostlyclean:
	rm -f temacs prefix-args core *.core \#* *.o libXMenu11.a liblw.a
	rm -f ../etc/DOC
clean: mostlyclean
	rm -f emacs-* emacs bootstrap-emacs
/**/# This is used in making a distribution.
/**/# Do not use it on development directories!
distclean: clean
	rm -f epaths.h config.h Makefile Makefile.c config.stamp stamp-oldxmenu ../etc/DOC-*
maintainer-clean: distclean
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	rm -f TAGS
versionclean:
	-rm -f emacs emacs-* ../etc/DOC*
extraclean: distclean
	-rm -f *~ \#* m/?*~ s/?*~

/* The rule for the [sm] files has to be written a little funny to
   avoid looking like a C comment to CPP. */
SOURCES = *.[ch] [sm]/?* COPYING Makefile.in \
	config.in epaths.in README COPYING ChangeLog vms.pp-trans
unlock:
	chmod u+w $(SOURCES)

relock:
	chmod -w $(SOURCES)
	chmod +w epaths.h

/* Arrange to make a tags table TAGS-LISP for ../lisp,
   plus TAGS for the C files, which includes ../lisp/TAGS by reference.  */

ctagsfiles1 = [xyzXYZ]*.[hc] 
ctagsfiles2 = [a-wA-W]*.[hc]

TAGS: $(srcdir)/$(ctagsfiles1) $(srcdir)/$(ctagsfiles2)
	../lib-src/etags --include=TAGS-LISP --include=${lwlibdir}/TAGS \
	  --regex='/[ 	]*DEFVAR_[A-Z_ 	(]+"\([^"]+\)"/' \
	  $(srcdir)/$(ctagsfiles1) $(srcdir)/$(ctagsfiles2)
frc:
TAGS-LISP: frc
	$(MAKE) -f ${lispsource}Makefile TAGS-LISP ETAGS=../lib-src/etags

$(lwlibdir)TAGS:
	(cd $(lwlibdir); $(MAKE) -f $(lwlibdir)Makefile tags ETAGS=../lib-src/etags)

tags: TAGS TAGS-LISP $(lwlibdir)TAGS
.PHONY: tags


/* Bootstrapping.  */

bootstrap: bootstrap-emacs

/* Build a temacs with a sufficiently large PURESIZE to load the
   Lisp files from loadup.el in source form.  */

bootstrap-temacs: 
	LC_ALL=C $(MAKE) $(MFLAGS) temacs ALL_CFLAGS="$(ALL_CFLAGS) -DPURESIZE=5000000 -I../src"

/* Build a DOC file.  */

bootstrap-doc: ${libsrc}make-docfile
	-rm -f ${etc}DOC
	els=`echo ${shortlisp} ${SOME_MACHINE_LISP} \
		| sed -e "s/\\.elc/.el/g"`; \
	${libsrc}make-docfile -d ${srcdir} $$els ${obj} > ${etc}DOC

/* Dump an Emacs executable named bootstrap-emacs containing the 
   files from loadup.el in source form.  */

bootstrap-emacs: bootstrap-temacs bootstrap-doc
#ifdef CANNOT_DUMP
	ln temacs bootstrap-emacs
#else
#ifdef HAVE_SHM
	./temacs -nl -batch -l loadup bootstrap
#else /* ! defined (HAVE_SHM) */
	./temacs --batch --load loadup bootstrap
#endif /* ! defined (HAVE_SHM) */
#endif /* ! defined (CANNOT_DUMP) */
	mv -f emacs bootstrap-emacs
	rm -f temacs

