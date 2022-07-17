#!/usr/bin/make
#
# Minix compiler sources makefile
# (C) 2005 Michael Kennett

l = image
s = lang/m2/test
t = obj/test/m2

M2 = $l/em_m2 -I/usr/lib/m2 -WR -Vw4.4i4.4p4.4l4.4f4.4d8.4
OPT = $l/em_opt
CG = $l/i386/cg -F__fp_hook
AS = $l/i386/as
LED = $l/em_led -a0:4 -a1:4 -a2:4 -a3:4 -b0:0 -b1:0
CV = $l/cv -x -mi386

HEAD = /usr/lib/i386/m2rtso.o
TAIL = /usr/lib/i386/libm2.a /usr/lib/i386/libc.a /usr/lib/i386/libfp.a \
	/usr/lib/i386/libe.a /usr/lib/i386/end.a

# Building K_OBJECTS just tests the front-end
K_OBJECTS = $t/getenv.k $t/m2p.k $t/queens.k $t/LifeGame.k $t/Shoes.k \
	$t/StoreFetch.k $t/bold.k $t/characters.k $t/PowersOf2.k \
	$t/TableHandl.k $t/XREF.k

# Testing the EM processing pipeline
M_OBJECTS = $t/getenv.m $t/m2p.m $t/queens.m $t/LifeGame.m $t/Shoes.m \
	$t/StoreFetch.m $t/bold.m $t/characters.m $t/PowersOf2.m \
	$t/TableHandl.m $t/XREF.m
S_OBJECTS = $t/getenv.s $t/m2p.s $t/queens.s $t/LifeGame.s $t/Shoes.s \
	$t/StoreFetch.s $t/bold.s $t/characters.s $t/PowersOf2.s \
	$t/TableHandl.s $t/XREF.s
O_OBJECTS = $t/getenv.o $t/m2p.o $t/queens.o $t/LifeGame.o $t/Shoes.o \
	$t/StoreFetch.o $t/bold.o $t/characters.o $t/PowersOf2.o \
	$t/TableHandl.o $t/XREF.o

# [[what is the req'd magic for combining modules?
#  $s/Wirth/TableHandl, $s/Wirth/XREF must be combined.]]
# $t/StoreFetch currently dumps core (same as old minix compiler)
PROGRAMS = $t/getenv $t/m2p $t/queens $t/LifeGame $t/Shoes \
	$t/StoreFetch $t/bold $t/characters $t/PowersOf2

default : x-compiler $(O_OBJECTS) $(PROGRAMS)

x-compiler :
	@if [ ! -x $l/em_m2 ] ; then \
		echo "Error: modula-2 front-end not built" ; exit 1 ; fi

$t/getenv.k : $s/getenv.mod
	$(M2) $< $@
$t/getenv.m : $t/getenv.k
	$(OPT) $< > $@
$t/getenv.s : $t/getenv.m
	$(CG) $< > $@
$t/getenv.o : $t/getenv.s
	$(AS) - -o $@ $<
$t/getenv.img : $t/getenv.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/getenv : $t/getenv.img
	$(CV) $< $@

$t/m2p.k : $s/m2p.mod
	$(M2) $< $@
$t/m2p.m : $t/m2p.k
	$(OPT) $< > $@
$t/m2p.s : $t/m2p.m
	$(CG) $< > $@
$t/m2p.o : $t/m2p.s
	$(AS) - -o $@ $<
$t/m2p.img : $t/m2p.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/m2p : $t/m2p.img
	$(CV) $< $@

$t/queens.k : $s/queens.mod
	$(M2) $< $@
$t/queens.m : $t/queens.k
	$(OPT) $< > $@
$t/queens.s : $t/queens.m
	$(CG) $< > $@
$t/queens.o : $t/queens.s
	$(AS) - -o $@ $<
$t/queens.img : $t/queens.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/queens : $t/queens.img
	$(CV) $< $@

$t/LifeGame.k : $s/Thalmann/LifeGame.mod
	$(M2) $< $@
$t/LifeGame.m : $t/LifeGame.k
	$(OPT) $< > $@
$t/LifeGame.s : $t/LifeGame.m
	$(CG) $< > $@
$t/LifeGame.o : $t/LifeGame.s
	$(AS) - -o $@ $<
$t/LifeGame.img : $t/LifeGame.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/LifeGame : $t/LifeGame.img
	$(CV) $< $@

$t/Shoes.k : $s/Thalmann/Shoes.mod
	$(M2) $< $@
$t/Shoes.m : $t/Shoes.k
	$(OPT) $< > $@
$t/Shoes.s : $t/Shoes.m
	$(CG) $< > $@
$t/Shoes.o : $t/Shoes.s
	$(AS) - -o $@ $<
$t/Shoes.img : $t/Shoes.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/Shoes : $t/Shoes.img
	$(CV) $< $@

$t/StoreFetch.k : $s/Thalmann/StoreFetch.mod
	$(M2) $< $@
$t/StoreFetch.m : $t/StoreFetch.k
	$(OPT) $< > $@
$t/StoreFetch.s : $t/StoreFetch.m
	$(CG) $< > $@
$t/StoreFetch.o : $t/StoreFetch.s
	$(AS) - -o $@ $<
$t/StoreFetch.img : $t/StoreFetch.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/StoreFetch : $t/StoreFetch.img
	$(CV) $< $@

$t/bold.k : $s/Thalmann/bold.mod
	$(M2) $< $@
$t/bold.m : $t/bold.k
	$(OPT) $< > $@
$t/bold.s : $t/bold.m
	$(CG) $< > $@
$t/bold.o : $t/bold.s
	$(AS) - -o $@ $<
$t/bold.img : $t/bold.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/bold : $t/bold.img
	$(CV) $< $@

$t/characters.k : $s/Thalmann/characters.mod
	$(M2) $< $@
$t/characters.m : $t/characters.k
	$(OPT) $< > $@
$t/characters.s : $t/characters.m
	$(CG) $< > $@
$t/characters.o : $t/characters.s
	$(AS) - -o $@ $<
$t/characters.img : $t/characters.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/characters : $t/characters.img
	$(CV) $< $@

$t/PowersOf2.k : $s/Wirth/PowersOf2.mod
	$(M2) $< $@
$t/PowersOf2.m : $t/PowersOf2.k
	$(OPT) $< > $@
$t/PowersOf2.s : $t/PowersOf2.m
	$(CG) $< > $@
$t/PowersOf2.o : $t/PowersOf2.s
	$(AS) - -o $@ $<
$t/PowersOf2.img : $t/PowersOf2.o
	$(LED) -o $@ $(HEAD) $< $(TAIL)
$t/PowersOf2 : $t/PowersOf2.img
	$(CV) $< $@

$t/TableHandl.k : $s/Wirth/TableHandl.mod
	$(M2) $< $@
$t/TableHandl.m : $t/TableHandl.k
	$(OPT) $< > $@
$t/TableHandl.s : $t/TableHandl.m
	$(CG) $< > $@
$t/TableHandl.o : $t/TableHandl.s
	$(AS) - -o $@ $<

$t/XREF.k : $s/Wirth/XREF.mod
	$(M2) $< $@
$t/XREF.m : $t/XREF.k
	$(OPT) $< > $@
$t/XREF.s : $t/XREF.m
	$(CG) $< > $@
$t/XREF.o : $t/XREF.s
	$(AS) - -o $@ $<

