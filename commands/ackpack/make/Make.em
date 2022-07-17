#!/usr/bin/make
#
# Minix compiler sources makefile
# (C) 2005 Michael Kennett

e = etc
h = h
m = modules/h
s = modules/src
u = util

# Build directories
l = image
o = obj

# executables used only in the build (e.g. LLgen)
x = $o/bin

default : $o/libem_data.a

## em_codeEK.h

$o/em_codeEK.h : $e/em_table
	ed -s $e/em_table < $s/em_code/em.gen.ed > $@
	cat $s/em_code/em.nogen >> $@

## read_emeV, read_emkV

$o/C_mnem : $e/em_table
	awk -f$s/read_em/C_mnem.awk $e/em_table > $@
$o/C_mnem_narg : $e/em_table
	awk -f$s/read_em/C_mnem_na.awk $e/em_table > $@

# The following files are included by the sources, and hence,
# are prerequisites.

GEN_READ_EM = $o/C_mnem $o/C_mnem_narg $o/em_codeEK.h

CREAD_EMEV=-I$o -I$h -I$m -I$s/alloc -I$s/string -I$s/system -DCHECKING -DPRIVATE=static -DEXPORT=

$o/read_emeV/EM_vars.o : $s/read_em/EM_vars.c $(GEN_READ_EM)
	$(CC) -c -DNDEBUG -o $@ $(CREAD_EMEV) $s/read_em/EM_vars.c
$o/read_emeV/mkcalls.o : $s/read_em/mkcalls.c $(GEN_READ_EM)
	$(CC) -c -DNDEBUG -o $@ $(CREAD_EMEV) $s/read_em/mkcalls.c
$o/read_emeV/read_em.o : $s/read_em/read_em.c $(GEN_READ_EM)
	$(CC) -c -DNDEBUG -o $@ $(CREAD_EMEV) $s/read_em/read_em.c

READ_EMEV_OBJS = $o/read_emeV/EM_vars.o $o/read_emeV/mkcalls.o \
		$o/read_emeV/read_em.o

$o/libread_emeV.a : $o/read_emeV $(READ_EMEV_OBJS)
	ar cr $@ $(READ_EMEV_OBJS)
	touch $@

CREAD_EMKV=$(CREAD_EMEV) -DCOMPACT

$o/read_emkV/EM_vars.o : $s/read_em/EM_vars.c $(GEN_READ_EM)
	$(CC) -c -DNDEBUG -o $@ $(CREAD_EMKV) $s/read_em/EM_vars.c
$o/read_emkV/mkcalls.o : $s/read_em/mkcalls.c $(GEN_READ_EM)
	$(CC) -c -DNDEBUG -o $@ $(CREAD_EMKV) $s/read_em/mkcalls.c
$o/read_emkV/read_em.o : $s/read_em/read_em.c $(GEN_READ_EM)
	$(CC) -c -DNDEBUG -o $@ $(CREAD_EMKV) $s/read_em/read_em.c

READ_EMKV_OBJS = $o/read_emkV/EM_vars.o $o/read_emkV/mkcalls.o \
		$o/read_emkV/read_em.o

$o/libread_emkV.a : $o/read_emkV $(READ_EMKV_OBJS)
	ar cr $@ $(READ_EMKV_OBJS)
	touch $@

## eme, emk

CEMK=-I$o -I$h -I$m -I$s/alloc -I$s/em_code -I$s/read_em -I$s/string -I$s/system

$o/emk/bhcst.o : $s/em_code/bhcst.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhcst.c
$o/emk/bhdlb.o : $s/em_code/bhdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhdlb.c
$o/emk/bhdnam.o : $s/em_code/bhdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhdnam.c
$o/emk/bhfcon.o : $s/em_code/bhfcon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhfcon.c
$o/emk/bhicon.o : $s/em_code/bhicon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhicon.c
$o/emk/bhilb.o : $s/em_code/bhilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhilb.c
$o/emk/bhpnam.o : $s/em_code/bhpnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhpnam.c
$o/emk/bhucon.o : $s/em_code/bhucon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/bhucon.c
$o/emk/C_out.o : $s/em_code/C_out.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/C_out.c
$o/emk/crcst.o : $s/em_code/crcst.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crcst.c
$o/emk/crdlb.o : $s/em_code/crdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crdlb.c
$o/emk/crdnam.o : $s/em_code/crdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crdnam.c
$o/emk/crilb.o : $s/em_code/crilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crilb.c
$o/emk/crpnam.o : $s/em_code/crpnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crpnam.c
$o/emk/crscon.o : $s/em_code/crscon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crscon.c
$o/emk/crxcon.o : $s/em_code/crxcon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/crxcon.c
$o/emk/cst.o : $s/em_code/cst.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/cst.c
$o/emk/dfdlb.o : $s/em_code/dfdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/dfdlb.c
$o/emk/dfdnam.o : $s/em_code/dfdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/dfdnam.c
$o/emk/dfilb.o : $s/em_code/dfilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/dfilb.c
$o/emk/dlb.o : $s/em_code/dlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/dlb.c
$o/emk/dnam.o : $s/em_code/dnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/dnam.c
$o/emk/em.o : $s/em_code/em.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/em.c
$o/emk/end.o : $s/em_code/end.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/end.c
$o/emk/endarg.o : $s/em_code/endarg.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/endarg.c
$o/emk/exc.o : $s/em_code/exc.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/exc.c
$o/emk/failed.o : $s/em_code/failed.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/failed.c
$o/emk/fcon.o : $s/em_code/fcon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/fcon.c
$o/emk/getid.o : $s/em_code/getid.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/getid.c
$o/emk/icon.o : $s/em_code/icon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/icon.c
$o/emk/ilb.o : $s/em_code/ilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/ilb.c
$o/emk/insert.o : $s/em_code/insert.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/insert.c
$o/emk/internerr.o : $s/em_code/internerr.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/internerr.c
$o/emk/msend.o : $s/em_code/msend.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/msend.c
$o/emk/msstart.o : $s/em_code/msstart.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/msstart.c
$o/emk/op.o : $s/em_code/op.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/op.c
$o/emk/opcst.o : $s/em_code/opcst.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/opcst.c
$o/emk/opdlb.o : $s/em_code/opdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/opdlb.c
$o/emk/opdnam.o : $s/em_code/opdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/opdnam.c
$o/emk/opilb.o : $s/em_code/opilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/opilb.c
$o/emk/opnarg.o : $s/em_code/opnarg.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/opnarg.c
$o/emk/oppnam.o : $s/em_code/oppnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/oppnam.c
$o/emk/pnam.o : $s/em_code/pnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/pnam.c
$o/emk/pro.o : $s/em_code/pro.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/pro.c
$o/emk/pronarg.o : $s/em_code/pronarg.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/pronarg.c
$o/emk/psdlb.o : $s/em_code/psdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/psdlb.c
$o/emk/psdnam.o : $s/em_code/psdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/psdnam.c
$o/emk/pspnam.o : $s/em_code/pspnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/pspnam.c
$o/emk/scon.o : $s/em_code/scon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/scon.c
$o/emk/ucon.o : $s/em_code/ucon.c
	$(CC) -c -DNDEBUG -o $@ $(CEMK) $s/em_code/ucon.c

EMK_OBJS = $o/emk/bhcst.o $o/emk/bhdlb.o $o/emk/bhdnam.o \
		$o/emk/bhfcon.o $o/emk/bhicon.o $o/emk/bhilb.o \
		$o/emk/bhpnam.o $o/emk/bhucon.o $o/emk/C_out.o \
		$o/emk/crcst.o $o/emk/crdlb.o $o/emk/crdnam.o \
		$o/emk/crilb.o $o/emk/crpnam.o $o/emk/crscon.o \
		$o/emk/crxcon.o $o/emk/cst.o $o/emk/dfdlb.o \
		$o/emk/dfdnam.o $o/emk/dfilb.o $o/emk/dlb.o \
		$o/emk/dnam.o $o/emk/em.o $o/emk/end.o \
		$o/emk/endarg.o $o/emk/exc.o $o/emk/failed.o \
		$o/emk/fcon.o $o/emk/getid.o $o/emk/icon.o \
		$o/emk/ilb.o $o/emk/insert.o $o/emk/internerr.o \
		$o/emk/msend.o $o/emk/msstart.o $o/emk/op.o \
		$o/emk/opcst.o $o/emk/opdlb.o $o/emk/opdnam.o \
		$o/emk/opilb.o $o/emk/opnarg.o $o/emk/oppnam.o \
		$o/emk/pnam.o $o/emk/pro.o $o/emk/pronarg.o \
		$o/emk/psdlb.o $o/emk/psdnam.o $o/emk/pspnam.o \
		$o/emk/scon.o $o/emk/ucon.o

$o/libemk.a : $o/em_codeEK.h $o/emk $(EMK_OBJS)
	ar cr $@ $(EMK_OBJS)
	touch $@

CEME=$(CEMK) -DREADABLE_EM

$o/eme/bhcst.o : $s/em_code/bhcst.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhcst.c
$o/eme/bhdlb.o : $s/em_code/bhdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhdlb.c
$o/eme/bhdnam.o : $s/em_code/bhdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhdnam.c
$o/eme/bhfcon.o : $s/em_code/bhfcon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhfcon.c
$o/eme/bhicon.o : $s/em_code/bhicon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhicon.c
$o/eme/bhilb.o : $s/em_code/bhilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhilb.c
$o/eme/bhpnam.o : $s/em_code/bhpnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhpnam.c
$o/eme/bhucon.o : $s/em_code/bhucon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/bhucon.c
$o/eme/C_out.o : $s/em_code/C_out.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/C_out.c
$o/eme/crcst.o : $s/em_code/crcst.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crcst.c
$o/eme/crdlb.o : $s/em_code/crdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crdlb.c
$o/eme/crdnam.o : $s/em_code/crdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crdnam.c
$o/eme/crilb.o : $s/em_code/crilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crilb.c
$o/eme/crpnam.o : $s/em_code/crpnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crpnam.c
$o/eme/crscon.o : $s/em_code/crscon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crscon.c
$o/eme/crxcon.o : $s/em_code/crxcon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/crxcon.c
$o/eme/cst.o : $s/em_code/cst.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/cst.c
$o/eme/dfdlb.o : $s/em_code/dfdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/dfdlb.c
$o/eme/dfdnam.o : $s/em_code/dfdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/dfdnam.c
$o/eme/dfilb.o : $s/em_code/dfilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/dfilb.c
$o/eme/dlb.o : $s/em_code/dlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/dlb.c
$o/eme/dnam.o : $s/em_code/dnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/dnam.c
$o/eme/em.o : $s/em_code/em.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/em.c
$o/eme/end.o : $s/em_code/end.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/end.c
$o/eme/endarg.o : $s/em_code/endarg.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/endarg.c
$o/eme/exc.o : $s/em_code/exc.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/exc.c
$o/eme/failed.o : $s/em_code/failed.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/failed.c
$o/eme/fcon.o : $s/em_code/fcon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/fcon.c
$o/eme/getid.o : $s/em_code/getid.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/getid.c
$o/eme/icon.o : $s/em_code/icon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/icon.c
$o/eme/ilb.o : $s/em_code/ilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/ilb.c
$o/eme/insert.o : $s/em_code/insert.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/insert.c
$o/eme/internerr.o : $s/em_code/internerr.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/internerr.c
$o/eme/msend.o : $s/em_code/msend.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/msend.c
$o/eme/msstart.o : $s/em_code/msstart.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/msstart.c
$o/eme/op.o : $s/em_code/op.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/op.c
$o/eme/opcst.o : $s/em_code/opcst.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/opcst.c
$o/eme/opdlb.o : $s/em_code/opdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/opdlb.c
$o/eme/opdnam.o : $s/em_code/opdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/opdnam.c
$o/eme/opilb.o : $s/em_code/opilb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/opilb.c
$o/eme/opnarg.o : $s/em_code/opnarg.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/opnarg.c
$o/eme/oppnam.o : $s/em_code/oppnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/oppnam.c
$o/eme/pnam.o : $s/em_code/pnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/pnam.c
$o/eme/pro.o : $s/em_code/pro.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/pro.c
$o/eme/pronarg.o : $s/em_code/pronarg.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/pronarg.c
$o/eme/psdlb.o : $s/em_code/psdlb.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/psdlb.c
$o/eme/psdnam.o : $s/em_code/psdnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/psdnam.c
$o/eme/pspnam.o : $s/em_code/pspnam.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/pspnam.c
$o/eme/scon.o : $s/em_code/scon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/scon.c
$o/eme/ucon.o : $s/em_code/ucon.c
	$(CC) -c -DNDEBUG -o $@ $(CEME) $s/em_code/ucon.c

EME_OBJS = $o/eme/bhcst.o $o/eme/bhdlb.o $o/eme/bhdnam.o \
		$o/eme/bhfcon.o $o/eme/bhicon.o $o/eme/bhilb.o \
		$o/eme/bhpnam.o $o/eme/bhucon.o $o/eme/C_out.o \
		$o/eme/crcst.o $o/eme/crdlb.o $o/eme/crdnam.o \
		$o/eme/crilb.o $o/eme/crpnam.o $o/eme/crscon.o \
		$o/eme/crxcon.o $o/eme/cst.o $o/eme/dfdlb.o \
		$o/eme/dfdnam.o $o/eme/dfilb.o $o/eme/dlb.o \
		$o/eme/dnam.o $o/eme/em.o $o/eme/end.o \
		$o/eme/endarg.o $o/eme/exc.o $o/eme/failed.o \
		$o/eme/fcon.o $o/eme/getid.o $o/eme/icon.o \
		$o/eme/ilb.o $o/eme/insert.o $o/eme/internerr.o \
		$o/eme/msend.o $o/eme/msstart.o $o/eme/op.o \
		$o/eme/opcst.o $o/eme/opdlb.o $o/eme/opdnam.o \
		$o/eme/opilb.o $o/eme/opnarg.o $o/eme/oppnam.o \
		$o/eme/pnam.o $o/eme/pro.o $o/eme/pronarg.o \
		$o/eme/psdlb.o $o/eme/psdnam.o $o/eme/pspnam.o \
		$o/eme/scon.o $o/eme/ucon.o

$o/libeme.a : $o/em_codeEK.h $o/eme $(EME_OBJS)
	ar cr $@ $(EME_OBJS)
	touch $@

## em_mes

CEMMES=-I$o -I$h -I$m

$o/em_mes/C_ms_com.o : $s/em_mes/C_ms_com.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_com.c
$o/em_mes/C_ms_ego.o : $s/em_mes/C_ms_ego.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_ego.c
$o/em_mes/C_ms_emx.o : $s/em_mes/C_ms_emx.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_emx.c
$o/em_mes/C_ms_err.o : $s/em_mes/C_ms_err.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_err.c
$o/em_mes/C_ms_flt.o : $s/em_mes/C_ms_flt.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_flt.c
$o/em_mes/C_ms_gto.o : $s/em_mes/C_ms_gto.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_gto.c
$o/em_mes/C_ms_opt.o : $s/em_mes/C_ms_opt.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_opt.c
$o/em_mes/C_ms_par.o : $s/em_mes/C_ms_par.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_par.c
$o/em_mes/C_ms_reg.o : $s/em_mes/C_ms_reg.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_reg.c
$o/em_mes/C_ms_src.o : $s/em_mes/C_ms_src.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_src.c
$o/em_mes/C_ms_stb.o : $s/em_mes/C_ms_stb.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_stb.c
$o/em_mes/C_ms_std.o : $s/em_mes/C_ms_std.c
	$(CC) -c -DNDEBUG -o $@ $(CEMMES) $s/em_mes/C_ms_std.c

EM_MES_OBJS = $o/em_mes/C_ms_com.o $o/em_mes/C_ms_ego.o $o/em_mes/C_ms_emx.o \
		$o/em_mes/C_ms_err.o $o/em_mes/C_ms_flt.o $o/em_mes/C_ms_gto.o \
		$o/em_mes/C_ms_opt.o $o/em_mes/C_ms_par.o $o/em_mes/C_ms_reg.o \
		$o/em_mes/C_ms_src.o $o/em_mes/C_ms_stb.o $o/em_mes/C_ms_std.o

$o/libem_mes.a : $o/em_codeEK.h $o/em_mes $(EM_MES_OBJS)
	ar cr $@ $(EM_MES_OBJS)
	touch $@

## em_data

$o/em_data/em_flag.o : $u/data/em_flag.c
	$(CC) -c -DNDEBUG -o $@ -I$h $u/data/em_flag.c
$o/em_data/em_mnem.o : $u/data/em_mnem.c
	$(CC) -c -DNDEBUG -o $@ -I$h $u/data/em_mnem.c
$o/em_data/em_pseu.o : $u/data/em_pseu.c
	$(CC) -c -DNDEBUG -o $@ -I$h $u/data/em_pseu.c
$o/em_data/em_ptyp.p : $u/data/em_ptyp.c
	$(CC) -c -DNDEBUG -o $@ -I$h $u/data/em_ptyp.c

EM_DATA_OBJS = $o/em_data/em_flag.o $o/em_data/em_mnem.o \
		$o/em_data/em_pseu.o $o/em_data/em_ptyp.p

$o/libem_data.a : $o/em_codeEK.h $(EM_DATA_OBJS)
	ar cr $@ $(EM_DATA_OBJS)
	touch $@
