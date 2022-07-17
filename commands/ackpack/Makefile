#!/usr/bin/make
#
# Minix compiler sources makefile
# (C) 2005 Michael Kennett
#
# The best way to read this file is from bottom-to-top - the top
# level targets (i.e. the system build) are at the bottom of the
# file, and the lower-level files are at the top.
#
# All of the intermediate and object files are kept in the 'obj' ($o)
# subdirectory, with the final binaries in 'image' ($l). Consequently,
# 'cleaning' the build is as simple as removing these subdirectories.
#
# This makefile does not contain full dependency information, and
# is really only sufficient for building an image from scratch.
# The makefile is not suitable for development work, or rebuilding
# an image after modifying the source code - it might be possible to
# just delete the relevant obj ($o) subdirectory, but I'll make no
# guarantees that this is sufficient.

# -O2 takes longer
CC = exec cc

e = etc
h = h
m = modules/h
s = modules/src
u = util

# build directories
l = image
o = obj

# executables used only in the build (e.g. LLgen)
x = $o/bin

# installation directories
bin = /usr/bin
lib = /usr/lib
man = /usr/man

# installation program and common options
INSTALL = install -c -o bin -g operator
INSTALL_BIN = $(INSTALL) -m 555
INSTALL_TXT = $(INSTALL) -m 444

# short-hand macro definitions for executable groups
X_EGO = $l/ego/bo $l/ego/ca $l/ego/cf $l/ego/cj $l/ego/cs $l/ego/ic $l/ego/il $l/ego/lv $l/ego/ra $l/ego/sp $l/ego/sr $l/ego/ud $l/em_ego

# The 'front-end' consists of the language processes, optimisers,
# the grind debugger, and utilities for manipulating object files.
X_FRONT_END = $l/em_decode $l/em_encode $l/cpp.ansi $l/em_cemcom.ansi \
		$l/em_basic \
		$l/i386/libbas.a $l/em_m2 $l/m2mm $l/em_occam $l/i386/libocm.a \
		$l/em_pc $l/em_led $(X_EGO) $l/em_opt $l/em_opt2

# The 'back-end' is really processor specific, but currently only the x386
# and i86 processors are supported. There is an assembler, code-generator,
# and a binary image conversion program (which only works for i386).
X_BACK_END = $l/i386/as $l/i86/as $l/i386/cg $l/i86/cg $l/cv

# All the (somewhat) supported back-end CPU's
BACK_ENDS = i386 i86

all: $(X_FRONT_END) $(X_BACK_END)

# Executable/library targets (exported names)
x-tabgen : $x/tabgen
x-read_em : $o/libread_emeV.a $o/libread_emkV.a
x-module : $o/libmodule.a
x-em : $o/libeme.a $o/libemk.a
x-em_mes : $o/libem_mes.a
x-em_data : $o/libem_data.a
x-ncgg : $x/ncgg
x-LLgen : $x/LLgen
x-led : $l/em_led
x-encode : $l/em_encode
x-decode : $l/em_decode
x-ego : $(X_EGO)
x-cpp-ansi : $l/cpp.ansi
x-cem-ansi : $l/em_cemcom.ansi
x-basic : $l/em_basic $l/i386/libbas.a
x-m2 : $l/em_m2
x-m2mm : $l/m2mm
x-occam : $l/em_occam $l/i386/libocm.a
x-pc : $l/em_pc
x-opt : $l/em_opt $l/em_opt2
x-grind : $l/grind
x-cv : $l/cv
x-cg : $l/i386/cg $l/i86/cg
x-as : $l/i386/as $l/i86/as

$x/tabgen :
	[ -d obj/bin ] || mkdir -p obj/bin
	[ -d obj/tabgen ] || mkdir -p obj/tabgen
	CC="$(CC)" $(MAKE) -f make/Make.tabgen $@

$o/em_codeEK.h : $e/em_table
	[ -d obj ] || mkdir obj
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$o/libread_emeV.a :
	[ -d obj/read_emeV ] || mkdir -p obj/read_emeV
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$o/libread_emkV.a :
	[ -d obj/read_emkV ] || mkdir -p obj/read_emkV
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$o/libmodule.a :
	[ -d obj/module ] || mkdir -p obj/module
	CC="$(CC)" $(MAKE) -f make/Make.mod $@

$o/libemk.a : $o/em_codeEK.h
	[ -d obj/emk ] || mkdir -p obj/emk
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$o/libeme.a : $o/em_codeEK.h
	[ -d obj/eme ] || mkdir -p obj/eme
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$o/libem_mes.a : $o/em_codeEK.h
	[ -d obj/em_mes ] || mkdir -p obj/em_mes
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$o/libem_data.a : $o/em_codeEK.h
	[ -d obj/em_data ] || mkdir -p obj/em_data
	CC="$(CC)" $(MAKE) -f make/Make.em $@

$x/cgg : $o/libem_data.a
	[ -d obj/bin ] || mkdir -p obj/bin
	[ -d obj/cgg ] || mkdir -p obj/cgg
	CC="$(CC)" $(MAKE) -f make/Make.cgg $@

$x/ncgg : $o/libem_data.a
	[ -d obj/bin ] || mkdir -p obj/bin
	[ -d obj/ncgg ] || mkdir -p obj/ncgg
	CC="$(CC)" $(MAKE) -f make/Make.ncgg $@

$x/LLgen : $o/libmodule.a
	[ -d obj/bin ] || mkdir -p obj/bin
	[ -d obj/LLgen ] || mkdir -p obj/LLgen
	CC="$(CC)" $(MAKE) -f make/Make.llgen $@

$l/em_led : $o/libmodule.a
	[ -d image ] || mkdir image
	[ -d obj/led ] || mkdir -p obj/led
	CC="$(CC)" $(MAKE) -f make/Make.led $@

$l/em_decode : $o/libeme.a $o/libmodule.a $o/libread_emkV.a $o/libem_data.a
	[ -d image ] || mkdir image
	CC="$(CC)" $(MAKE) -f make/Make.encode $@

$l/em_encode : $o/libemk.a $o/libmodule.a $o/libread_emeV.a $o/libem_data.a
	[ -d image ] || mkdir image
	CC="$(CC)" $(MAKE) -f make/Make.encode $@

$l/ego/bo : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/ca : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/ca ] || mkdir -p obj/ego/ca
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/cf : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/cf ] || mkdir -p obj/ego/cf
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/cj : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/cs : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/cs ] || mkdir -p obj/ego/cs
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/ic : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/ic ] || mkdir -p obj/ego/ic
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/il : $o/libem_data.a $o/libmodule.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/il ] || mkdir -p obj/ego/il
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/lv : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/ra : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/ra ] || mkdir -p obj/ego/ra
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/sp : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/sr : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/sr ] || mkdir -p obj/ego/sr
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/ego/ud : $o/libem_data.a
	[ -d image/ego ] || mkdir -p image/ego
	[ -d obj/ego/shared ] || mkdir -p obj/ego/shared
	[ -d obj/ego/ud ] || mkdir -p obj/ego/ud
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/em_ego : $o/libmodule.a
	CC="$(CC)" $(MAKE) -f make/Make.ego $@

$l/cpp.ansi : $x/LLgen $x/tabgen $o/libmodule.a
	[ -d image ] || mkdir image
	[ -d obj/cpp.ansi ] || mkdir -p obj/cpp.ansi
	CC="$(CC)" $(MAKE) -f make/Make.cpp $@

$l/em_cemcom.ansi : $x/LLgen $x/tabgen $o/libmodule.a $o/libem_data.a $o/libem_mes.a $o/libemk.a
	[ -d image ] || mkdir image
	[ -d obj/ca ] || mkdir -p obj/ca
	CC="$(CC)" $(MAKE) -f make/Make.cemcom $@

$l/em_basic : $x/LLgen $o/libmodule.a $o/libem_data.a $o/libem_mes.a $o/libemk.a
	if [ -f make/Make.basic ] ; then \
		[ -d image ] || mkdir image ; \
		[ -d obj/bc ] || mkdir -p obj/bc ; \
		CC="$(CC)" $(MAKE) -f make/Make.basic $@ ; \
	else echo [Basic package not installed] ; fi

# Basic is not a standard Minix language; build the standard library.
$l/i386/libbas.a :
	if [ -f make/Make.libbas ] ; then \
		[ -d image/i386 ] || mkdir image/i386 ; \
		[ -d obj/libbas ] || mkdir -p obj/libbas ; \
		CC="$(CC)" $(MAKE) -f make/Make.libbas $@ ; fi

$l/em_m2 : $x/LLgen $x/tabgen $o/libmodule.a $o/libem_data.a $o/libem_mes.a $o/libemk.a
	if [ -f make/Make.m2 ] ; then \
		[ -d image ] || mkdir image ; \
		[ -d obj/m2 ] || mkdir -p obj/m2 ; \
		CC="$(CC)" $(MAKE) -f make/Make.m2 $@ ; \
	else echo [Modula-2 package not installed] ; fi

$l/m2mm : $x/LLgen $x/tabgen $o/libmodule.a
	if [ -f make/Make.m2mm ] ; then \
		[ -d image ] || mkdir image ; \
		[ -d obj/m2mm ] || mkdir -p obj/m2mm ; \
		CC="$(CC)" $(MAKE) -f make/Make.m2mm $@ ; fi

$l/em_occam : $x/LLgen $o/libmodule.a $o/libem_data.a $o/libem_mes.a $o/libemk.a
	if [ -f make/Make.occam ] ; then \
		[ -d image ] || mkdir image ; \
		[ -d obj/occam ] || mkdir -p obj/occam ; \
		CC="$(CC)" $(MAKE) -f make/Make.occam $@ ; \
	else echo [Occam package not installed] ; fi

# Occam is not a standard Minix language; build the standard library.
# There is an error in the standard Minix em_encode, and the dependency below
# ensures that the new binary is available.
$l/i386/libocm.a : $l/em_encode
	if [ -f make/Make.libocm ] ; then \
		[ -d image/i386 ] || mkdir image/i386 ; \
		[ -d obj/libocm ] || mkdir -p obj/libocm ; \
		CC="$(CC)" $(MAKE) -f make/Make.libocm $@ ; fi

$l/em_pc : $x/LLgen $x/tabgen $o/libmodule.a $o/libem_data.a $o/libem_mes.a $o/libemk.a
	if [ -f make/Make.pc ] ; then \
		[ -d image ] || mkdir image ; \
		[ -d obj/pc ] || mkdir -p obj/pc ; \
		CC="$(CC)" $(MAKE) -f make/Make.pc $@ ; \
	else echo [Pascal package not installed] ; fi

$l/em_opt : $o/libmodule.a $o/libem_data.a $l/cpp.ansi
	[ -d image ] || mkdir image
	[ -d obj/opt ] || mkdir -p obj/opt
	CC="$(CC)" $(MAKE) -f make/Make.opt $@

$l/em_opt2 : $o/libmodule.a $o/libem_data.a $l/cpp.ansi
	[ -d image ] || mkdir image
	[ -d obj/opt ] || mkdir -p obj/opt
	CC="$(CC)" $(MAKE) -f make/Make.opt $@

# Grind is not yet ready for prime-time; keep it separate for now.
grind : $l/grind

$l/grind : $x/LLgen $x/tabgen $o/libmodule.a
	if [ -f make/Make.grind ] ; then \
		[ -d image ] || mkdir image ; \
		[ -d obj/grind ] || mkdir -p obj/grind ; \
		CC="$(CC)" $(MAKE) -f make/Make.grind $@ ; \
	else echo [Debugger package not installed] ; fi

## Backend (i.e. target specific)

$l/cv : $o/libmodule.a
	[ -d image ] || mkdir image
	CC="$(CC)" $(MAKE) -f make/minix/Make.cv $@

$l/i386/cg : $x/ncgg $o/libmodule.a $o/libem_data.a
	[ -d image/i386 ] || mkdir image/i386
	[ -d obj/cg/i386 ] || mkdir -p obj/cg/i386
	CC="$(CC)" $(MAKE) -f make/i386/Make.cg $@

$l/i86/cg : $x/ncgg $o/libmodule.a $o/libem_data.a
	[ -d image/i86 ] || mkdir image/i86
	[ -d obj/cg/i86 ] || mkdir -p obj/cg/i86
	CC="$(CC)" $(MAKE) -f make/i86/Make.cg $@

$l/i386/as : $o/libmodule.a
	[ -d image/i386 ] || mkdir image/i386
	[ -d obj/as/i386 ] || mkdir -p obj/as/i386
	CC="$(CC)" $(MAKE) -f make/i386/Make.as $@

$l/i86/as : $o/libmodule.a
	[ -d image/i86 ] || mkdir image/i86
	[ -d obj/as/i86 ] || mkdir -p obj/as/i86
	CC="$(CC)" $(MAKE) -f make/i86/Make.as $@

## Utility targets

clean:
	rm -rf $o core

very-clean: clean
	rm -rf $l dist

distribution:
	other/makedist

# Default stack is 128K (32kw)
install: all
	$(INSTALL_BIN) $l/cpp.ansi $(lib)
	$(INSTALL_BIN) -S 224kw $l/cv $(lib)
	$(INSTALL_BIN) -S 192kw $l/ego/bo $(lib)/ego
	$(INSTALL_BIN) -S 192kw $l/ego/ca $(lib)/ego
	$(INSTALL_BIN) -S 192kw $l/ego/cf $(lib)/ego
	$(INSTALL_BIN) -S 192kw $l/ego/cj $(lib)/ego
	$(INSTALL_BIN) $l/ego/cs $(lib)/ego
	$(INSTALL_BIN) -S 288kw $l/ego/ic $(lib)/ego
	$(INSTALL_BIN) $l/ego/il $(lib)/ego
	$(INSTALL_BIN) $l/ego/lv $(lib)/ego
	$(INSTALL_BIN) $l/ego/ra $(lib)/ego
	$(INSTALL_BIN) -S 192kw $l/ego/sp $(lib)/ego
	$(INSTALL_BIN) $l/ego/sr $(lib)/ego
	$(INSTALL_BIN) $l/ego/ud $(lib)/ego
	$(INSTALL_BIN) -S 224kw $l/em_cemcom.ansi $(lib)
	$(INSTALL_BIN) $l/em_decode $(lib)
	$(INSTALL_BIN) $l/em_ego $(lib)
	$(INSTALL_BIN) $l/em_encode $(lib)
	$(INSTALL_BIN) -S 96kw $l/em_led $(lib)
	$(INSTALL_BIN) -S 48kw $l/em_opt $(lib)
	$(INSTALL_BIN) $l/em_opt2 $(lib)
	#$(INSTALL_TXT) lang/cem/comp/cemcom.ansi.1 $(man)/man1
	$(INSTALL_TXT) lang/cem/cpp/ncpp.6 $(man)/man6
	$(INSTALL_TXT) $u/led/ack.out.5 $(man)/man5
	$(INSTALL_TXT) $u/led/led.6 $(man)/man6
	$(INSTALL_TXT) $u/LLgen/LLgen.1 $(man)/man1
	$(INSTALL_TXT) $u/misc/em_decode.6 $(man)/man6
	$(INSTALL_TXT) $u/ncgg/ncgg.6 $(man)/man6
	$(INSTALL_TXT) $u/opt/em_opt.6 $(man)/man6
	if [ -f make/Make.basic ] ; then \
		$(INSTALL_BIN) -S 112kw $l/em_basic $(lib) ; \
		$(INSTALL_TXT) $l/i386/libbas.a $(lib)/i386 ; fi
	if [ -f make/Make.m2 ] ; then \
		$(INSTALL_BIN) -S 224kw $l/em_m2 $(lib) ; \
		$(INSTALL_BIN) $l/m2mm $(bin) ; \
		$(INSTALL_TXT) lang/m2/comp/em_m2.6 $(man)/man6 ; \
		$(INSTALL_TXT) lang/m2/m2mm/m2mm.1 $(man)/man1 ; fi
	#$(INSTALL_TXT) lang/m2/comp/modula-2.1 $(man)/man1
	if [ -f make/Make.occam ] ; then \
		$(INSTALL_BIN) -S 112kw $l/em_occam $(lib) ; \
		$(INSTALL_TXT) $l/i386/libocm.a $(lib)/i386 ; \
		$(INSTALL_TXT) lang/occam/include/dec.ocm $(lib)/occam ; \
		$(INSTALL_TXT) lang/occam/include/printd.ocm $(lib)/occam ; \
		$(INSTALL_TXT) lang/occam/include/prints.ocm $(lib)/occam ; fi
	if [ -f make/Make.pc ] ; then \
		$(INSTALL_BIN) -S 112kw $l/em_pc $(lib) ; \
		$(INSTALL_TXT) lang/pc/comp/em_pc.6 $(man)/man6 ; fi
	for m in $(BACK_ENDS) ; do \
		[ -f $l/$$m/as ] && $(INSTALL_BIN) $l/$$m/as $(lib)/$$m ; \
		[ -f $l/$$m/cg ] && $(INSTALL_BIN) $l/$$m/cg $(lib)/$$m ; \
	done

## The debugger is not yet ready for prime-time...
install-grind: $l/grind
	if [ -d other/db -a -f other/db/Makefile ] ; then \
	( cd other/db ; $(MAKE) install ) ; \
	$(INSTALL_BIN) $l/grind $(bin) ; \
	$(INSTALL_TXT) $u/grind/grind.1 $(man)/man1 ; \
	grep DEBUG /usr/lib/descr > /dev/null || sh other/fixgrind ; \
	else echo ERROR: missing debug runtime support - install FAILED! && \
		exit 1 ; fi

## Testing (very simple - nothing sophisticated)
# XXX Should execute the built programs, and test output etc...

test: all test-basic test-cem test-m2 test-occam test-pc

test-basic: $l/em_basic
	if [ -f make/Test.basic ] ; then \
		[ -d obj/test ] || mkdir -p obj/test ; \
		[ -d obj/test/basic ] || mkdir -p obj/test/basic ; \
		CC="$(CC)" $(MAKE) -f make/Test.basic ; fi
test-cem: $l/em_cemcom.ansi
	@echo "[There are no tests for em_cemcom]"
test-m2: $l/em_m2
	if [ -f make/Test.m2 ] ; then \
		[ -d obj/test ] || mkdir -p obj/test ; \
		[ -d obj/test/m2 ] || mkdir -p obj/test/m2 ; \
		CC="$(CC)" $(MAKE) -f make/Test.m2 ; fi
test-occam: $l/em_occam
	if [ -f make/Test.occam ] ; then \
		[ -d obj/test ] || mkdir -p obj/test ; \
		[ -d obj/test/occam ] || mkdir -p obj/test/occam ; \
		CC="$(CC)" $(MAKE) -f make/Test.occam ; fi
test-pc: $l/em_pc
	if [ -f make/Test.pc ] ; then \
		[ -d obj/test ] || mkdir -p obj/test ; \
		[ -d obj/test/pc ] || mkdir -p obj/test/pc ; \
		CC="$(CC)" $(MAKE) -f make/Test.pc ; fi

## System patches and preparation

prepare-ack:
	sh other/prepare

fix-basic-support:
	sh other/fixbasic

fix-occam-support:
	sh other/fixoccam

fix-pascal-support:
	sh other/fixpascal

