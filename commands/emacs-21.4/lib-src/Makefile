# Generated automatically from Makefile.in by configure.
# Makefile for lib-src subdirectory in GNU Emacs.
# Copyright (C) 1985, 1987, 1988, 1993, 1994 Free Software Foundation, Inc.

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

# Avoid trouble on systems where the `SHELL' variable might be
# inherited from the environment.
SHELL = /bin/sh

# ==================== Things `configure' will edit ====================

CC=cc
CFLAGS=-g -O1
ALLOCA=
YACC=bison -y
version=21.4
configuration=i686-pc-minix

# ==================== Where To Install Things ====================

# The default location for installation.  Everything is placed in
# subdirectories of this directory.  The default values for many of
# the variables below are expressed in terms of this one, so you may
# not need to change them.  This is set with the --prefix option to
# `../configure'.
prefix=/usr/local

# Like `prefix', but used for architecture-specific files.  This is
# set with the --exec-prefix option to `../configure'.
exec_prefix=${prefix}

# Where to install Emacs and other binaries that people will want to
# run directly (like etags).  This is set with the --bindir option
# to `../configure'.
bindir=${exec_prefix}/bin

# Where to install and expect executable files to be run by Emacs
# rather than directly by users, and other architecture-dependent
# data.  ${archlibdir} is usually below this.  This is set with the
# --libexecdir option to `../configure'.
libexecdir=${exec_prefix}/libexec

# Where to find the source code.  This is set by the configure
# script's `--srcdir' option.  However, the value of ${srcdir} in
# this makefile is not identical to what was specified with --srcdir,
# since the variable here has `/lib-src' added at the end.

# We use $(srcdir) explicitly in dependencies so as not to depend on VPATH.
srcdir=${top_srcdir}/lib-src
VPATH=${srcdir)

# The top-level source directory, also set by configure.
top_srcdir=

# ==================== Emacs-specific directories ====================

# These variables hold the values Emacs will actually use.  They are
# based on the values of the standard Make variables above.

# Where to put executables to be run by Emacs rather than the user.
# This path usually includes the Emacs version and configuration name,
# so that multiple configurations for multiple versions of Emacs may
# be installed at once.  This can be set with the --archlibdir option
# to `../configure'.
archlibdir=${libexecdir}/emacs/${version}/${configuration}

# ==================== Utility Programs for the Build =================

# ../configure figures out the correct values for these.
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
# By default, we uphold the dignity of our programs.
INSTALL_STRIP =

# ========================== Lists of Files ===========================

# Things that a user might actually run,
# which should be installed in bindir.
INSTALLABLES = etags ctags emacsclient b2m ebrowse
INSTALLABLE_SCRIPTS = rcs-checkin grep-changelog

# Things that Emacs runs internally, or during the build process,
#  which should not be installed in bindir.
UTILITIES=  profile digest-doc \
	sorted-doc movemail cvtmail fakemail yow emacsserver hexl

DONT_INSTALL= test-distrib make-docfile

# Like UTILITIES, but they're not system-dependent, and should not be
#  deleted by the distclean target.
SCRIPTS= rcs2log vcdiff

EXECUTABLES= ${UTILITIES} ${INSTALLABLES} ${SCRIPTS} ${INSTALLABLE_SCRIPTS}

SOURCES = COPYING ChangeLog Makefile.in README emacs.csh \
	makedoc.com *.[chy] rcs2log vcdiff

# Additional -D flags for movemail (add to MOVE_FLAGS if desired):
# MAIL_USE_POP		Support mail retrieval from a POP mailbox.
# MAIL_USE_MMDF		Support MMDF mailboxes.
# MAIL_USE_FLOCK	Use flock for file locking (see the comments
#			about locking in movemail.c)
# MAIL_UNLINK_SPOOL	Unlink the user's spool mailbox after reading
#			it (instead of just emptying it).
# KERBEROS		Support Kerberized POP.
# KRB5			Support Kerberos Version 5 pop instead of
#			Version 4 (define this in addition to
#			KERBEROS).
# HESIOD		Support Hesiod lookups of user mailboxes.
# MAILHOST		A string, the host name of the default POP
#			mail host for the site.
MOVE_FLAGS=

# ========================== start of cpp stuff =======================
LIBS_MOVE=$(KRB4LIB) $(DESLIB) $(KRB5LIB) $(CRYPTOLIB) $(COM_ERRLIB) $(HESIODLIB)
LOADLIBES= -lc
ALL_CFLAGS = -D_BSD_SOURCE -DHAVE_CONFIG_H -I. -I../src -I${srcdir} -I${srcdir}/../src ${LDFLAGS} ${CPPFLAGS} ${CFLAGS}
LINK_CFLAGS = -D_BSD_SOURCE -DHAVE_CONFIG_H -I. -I../src -I${srcdir} -I${srcdir}/../src ${LDFLAGS} ${CFLAGS}
CPP_CFLAGS = -D_BSD_SOURCE -DHAVE_CONFIG_H -I. -I../src -I${srcdir} -I${srcdir}/../src ${CPPFLAGS} ${CFLAGS}
BASE_CFLAGS = -D_BSD_SOURCE -DHAVE_CONFIG_H -I. -I../src -I${srcdir} -I${srcdir}/../src ${CPPFLAGS} ${CFLAGS}
.c.o:
	       ${CC} -c ${CPP_CFLAGS} $<
all: ${DONT_INSTALL} ${UTILITIES} ${INSTALLABLES}
maybe-blessmail:
${archlibdir}: all
	       @echo
	       @echo "Installing utilities run internally by Emacs."
	       sh $(top_srcdir)/mkinstalldirs ${archlibdir}
	       if [ `(cd ${archlibdir} && /bin/pwd)` != `/bin/pwd` ]; then for file in ${UTILITIES}; do $(INSTALL_PROGRAM) $(INSTALL_STRIP) $$file ${archlibdir}/$$file ; done ; fi
	       if [ `(cd ${archlibdir} && /bin/pwd)` != `(cd ${srcdir} && /bin/pwd)` ]; then for file in ${SCRIPTS}; do $(INSTALL_PROGRAM) ${srcdir}/$$file ${archlibdir}/$$file; done ; fi
install: ${archlibdir}
	       @echo
	       @echo "Installing utilities for users to run."
	       for file in ${INSTALLABLES} ; do $(INSTALL_PROGRAM) $(INSTALL_STRIP) $${file} ${bindir}/$${file} ; chmod a+rx ${bindir}/$${file}; done
	       for file in ${INSTALLABLE_SCRIPTS} ; do $(INSTALL_PROGRAM) ${srcdir}/$${file} ${bindir}/$${file} ; chmod a+rx ${bindir}/$${file}; done
uninstall:
	       (cd ${bindir}; rm -f ${INSTALLABLES} ${INSTALLABLE_SCRIPTS})
	       (cd ${archlibdir}; rm -f ${UTILITIES} ${INSTALLABLES} ${SCRIPTS} ${INSTALLABLE_SCRIPTS})
mostlyclean:
	       -rm -f core *.o
clean: mostlyclean
	       -rm -f ${INSTALLABLES} ${UTILITIES} ${DONT_INSTALL}
	       -rm -f ../etc/DOC* fns*.el *.tab.c *.tab.h
distclean: clean
	       -rm -f TAGS
	       -rm -f Makefile Makefile.c blessmail
maintainer-clean: distclean
	       true
extraclean: maintainer-clean
	       -rm -f *~ \#*
unlock:
	       chmod u+w $(SOURCES)
relock:
	       chmod u-w $(SOURCES)
check:
	       @echo "We don't have any tests for GNU Emacs yet."
tags: TAGS
TAGS: etags
	       etags *.[ch]
test-distrib: ${srcdir}/test-distrib.c
	       $(CC) ${ALL_CFLAGS} -o test-distrib ${srcdir}/test-distrib.c
	       ./test-distrib ${srcdir}/testfile
GETOPTOBJS = getopt.o getopt1.o $(ALLOCA)
GETOPTDEPS = $(GETOPTOBJS) ${srcdir}/getopt.h
getopt.o: ${srcdir}/getopt.c ${srcdir}/getopt.h
	       ${CC} -c ${CPP_CFLAGS} ${srcdir}/getopt.c
getopt1.o: ${srcdir}/getopt1.c ${srcdir}/getopt.h
	       ${CC} -c ${CPP_CFLAGS} ${srcdir}/getopt1.c
alloca.o: ${srcdir}/alloca.c
	       ${CC} -Demacs -c ${BASE_CFLAGS} ${srcdir}/alloca.c
REGEXPOBJ = regex.o
REGEXPDEPS = $(REGEXPOBJ) $(srcdir)/../src/regex.h
regex.o: $(srcdir)/../src/regex.c $(srcdir)/../src/regex.h ../src/config.h
	       ${CC} -c ${BASE_CFLAGS} -DCONFIG_BROKETS -DINHIBIT_STRING_HEADER ${srcdir}/../src/regex.c
etags: ${srcdir}/etags.c $(GETOPTDEPS) $(REGEXPDEPS) ../src/config.h
	       $(CC) ${ALL_CFLAGS} -DVERSION="\"${version}\"" ${srcdir}/etags.c  $(GETOPTOBJS) $(REGEXPOBJ) $(LOADLIBES) -o etags
ebrowse: ${srcdir}/ebrowse.c $(GETOPTDEPS) ../src/config.h
	       $(CC) ${ALL_CFLAGS} -DVERSION="\"${version}\"" ${srcdir}/ebrowse.c $(GETOPTOBJS) $(LOADLIBES) -o ebrowse
ctags: etags
	       $(CC) ${ALL_CFLAGS} -DCTAGS -DVERSION="\"${version}\"" ${srcdir}/etags.c $(GETOPTOBJS) $(REGEXPOBJ) $(LOADLIBES) -o ctags
profile: ${srcdir}/profile.c ../src/config.h
	       $(CC) ${ALL_CFLAGS} ${srcdir}/profile.c $(LOADLIBES) -o profile
make-docfile: ${srcdir}/make-docfile.c ../src/config.h
	       $(CC) ${ALL_CFLAGS} ${srcdir}/make-docfile.c $(LOADLIBES) -o make-docfile
digest-doc: ${srcdir}/digest-doc.c
	       $(CC) ${ALL_CFLAGS} ${srcdir}/digest-doc.c $(LOADLIBES) -o digest-doc
sorted-doc: ${srcdir}/sorted-doc.c ${ALLOCA}
	       $(CC) ${ALL_CFLAGS} ${srcdir}/sorted-doc.c ${ALLOCA} $(LOADLIBES) -o sorted-doc
b2m: ${srcdir}/b2m.c ../src/config.h $(GETOPTDEPS)
	       $(CC) ${ALL_CFLAGS} ${srcdir}/b2m.c -DVERSION="\"${version}\"" $(GETOPTOBJS) $(LOADLIBES) -o b2m
movemail: movemail.o pop.o $(GETOPTDEPS)
	       $(CC) ${LINK_CFLAGS} ${MOVE_FLAGS} movemail.o pop.o $(GETOPTOBJS) $(LOADLIBES) $(LIBS_MAIL) $(LIBS_MOVE) -o movemail
movemail.o: ${srcdir}/movemail.c ../src/config.h
	       $(CC) -c ${CPP_CFLAGS} -Demacs ${MOVE_FLAGS} ${srcdir}/movemail.c
pop.o: ${srcdir}/pop.c ../src/config.h
	       $(CC) -c ${CPP_CFLAGS} ${MOVE_FLAGS} ${srcdir}/pop.c
cvtmail: ${srcdir}/cvtmail.c
	       $(CC) ${ALL_CFLAGS} ${srcdir}/cvtmail.c $(LOADLIBES) -o cvtmail
fakemail: ${srcdir}/fakemail.c ../src/config.h
	       $(CC) ${ALL_CFLAGS} ${srcdir}/fakemail.c $(LOADLIBES) -o fakemail
yow: ${srcdir}/yow.c ../src/epaths.h
	       $(CC) ${ALL_CFLAGS} ${srcdir}/yow.c $(LOADLIBES) -o yow
emacsserver: ${srcdir}/emacsserver.c ../src/config.h
	       $(CC) ${ALL_CFLAGS} ${srcdir}/emacsserver.c $(LOADLIBES) -o emacsserver
emacsclient: ${srcdir}/emacsclient.c ../src/config.h $(GETOPTDEPS)
	       $(CC) ${ALL_CFLAGS} ${srcdir}/emacsclient.c $(GETOPTOBJS) -DVERSION=`sed -n -e '/(defconst emacs-version/ s/^[^"]*\("[^"]*"\).*/\1/p' ${srcdir}/../lisp/version.el` $(LOADLIBES) -o emacsclient
hexl: ${srcdir}/hexl.c ../src/config.h
	       $(CC) ${ALL_CFLAGS} ${srcdir}/hexl.c $(LOADLIBES) -o hexl
emacstool: ${srcdir}/emacstool.c
	       $(CC) ${srcdir}/emacstool.c -o emacstool ${ALL_CFLAGS} -lsuntool -lsunwindow -lpixrect $(LOADLIBES)
nemacstool: ${srcdir}/emacstool.c
	       $(CC) -o nemacstool -DJLE ${ALL_CFLAGS} ${srcdir}/emacstool.c -lsuntool -lmle -lsunwindow -lpixrect $(LOADLIBES)
xvetool: ${srcdir}/emacstool.c
	       $(CC) -o xvetool -DXVIEW ${ALL_CFLAGS} ${srcdir}/emacstool.c -lxview -lX -I$(OPENWINHOME)/include -L$(OPENWINHOME)/lib $(LOADLIBES)
xveterm: ${srcdir}/emacstool.c
	       $(CC) -o xveterm -DXVIEW -DTTERM ${ALL_CFLAGS} ${srcdir}/emacstool.c -lxview -lolgx -lX -I$(OPENWINHOME)/include -L$(OPENWINHOME)/lib $(LOADLIBES)
