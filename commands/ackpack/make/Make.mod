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

default : $o/libmodule.a

## Modules (alloc)

$o/module/botch.o : $s/alloc/botch.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/botch.c
$o/module/clear.o : $s/alloc/clear.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/clear.c
$o/module/Malloc.o : $s/alloc/Malloc.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/Malloc.c
$o/module/No_Mem.o : $s/alloc/No_Mem.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/alloc/No_Mem.c
$o/module/Realloc.o : $s/alloc/Realloc.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/Realloc.c
$o/module/Salloc.o : $s/alloc/Salloc.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/Salloc.c
$o/module/st_alloc.o : $s/alloc/st_alloc.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/st_alloc.c
$o/module/std_alloc.o : $s/alloc/std_alloc.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/alloc/std_alloc.c

## Modules (assert)

$o/module/BadAssert.o : $s/assert/BadAssert.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/assert/BadAssert.c

## Modules (flt_arith)

$o/module/b64_add.o : $s/flt_arith/b64_add.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/b64_add.c
$o/module/b64_sft.o : $s/flt_arith/b64_sft.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/b64_sft.c
$o/module/flt_add.o : $s/flt_arith/flt_add.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_add.c
$o/module/flt_ar2flt.o : $s/flt_arith/flt_ar2flt.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_ar2flt.c
$o/module/flt_chk.o : $s/flt_arith/flt_chk.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_chk.c
$o/module/flt_cmp.o : $s/flt_arith/flt_cmp.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_cmp.c
$o/module/flt_div.o : $s/flt_arith/flt_div.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_div.c
$o/module/flt_flt2ar.o : $s/flt_arith/flt_flt2ar.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_flt2ar.c
$o/module/flt_modf.o : $s/flt_arith/flt_modf.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_modf.c
$o/module/flt_mul.o : $s/flt_arith/flt_mul.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_mul.c
$o/module/flt_nrm.o : $s/flt_arith/flt_nrm.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_nrm.c
$o/module/flt_str2fl.o : $s/flt_arith/flt_str2fl.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_str2fl.c
$o/module/flt_umin.o : $s/flt_arith/flt_umin.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/flt_umin.c
$o/module/split.o : $s/flt_arith/split.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/split.c
$o/module/ucmp.o : $s/flt_arith/ucmp.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/flt_arith/ucmp.c

## Modules (object)

$o/module/rd.o : $s/object/rd.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd.c
$o/module/rd_arhdr.o : $s/object/rd_arhdr.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd_arhdr.c
$o/module/rd_bytes.o : $s/object/rd_bytes.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd_bytes.c
$o/module/rd_int2.o : $s/object/rd_int2.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd_int2.c
$o/module/rd_long.o : $s/object/rd_long.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd_long.c
$o/module/rd_ranlib.o : $s/object/rd_ranlib.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd_ranlib.c
$o/module/rd_unsig2.o : $s/object/rd_unsig2.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/rd_unsig2.c
$o/module/wr.o : $s/object/wr.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr.c
$o/module/wr_arhdr.o : $s/object/wr_arhdr.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr_arhdr.c
$o/module/wr_bytes.o : $s/object/wr_bytes.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr_bytes.c
$o/module/wr_int2.o : $s/object/wr_int2.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr_int2.c
$o/module/wr_long.o : $s/object/wr_long.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr_long.c
$o/module/wr_putc.o : $s/object/wr_putc.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr_putc.c
$o/module/wr_ranlib.o : $s/object/wr_ranlib.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/object/wr_ranlib.c

## Modules (string)

$o/module/bts2str.o : $s/string/bts2str.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/bts2str.c
$o/module/btscat.o : $s/string/btscat.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/btscat.c
$o/module/btscmp.o : $s/string/btscmp.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/btscmp.c
$o/module/btscpy.o : $s/string/btscpy.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/btscpy.c
$o/module/btszero.o : $s/string/btszero.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/btszero.c
$o/module/long2str.o : $s/string/long2str.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/long2str.c
$o/module/str2bts.o : $s/string/str2bts.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/str2bts.c
$o/module/str2long.o : $s/string/str2long.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/str2long.c
$o/module/strindex.o : $s/string/strindex.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/strindex.c
$o/module/strrindex.o : $s/string/strrindex.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/strrindex.c
$o/module/strzero.o : $s/string/strzero.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m $s/string/strzero.c

## Modules (system)

$o/module/read.o : $s/system/read.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/system/read.c
$o/module/seek.o : $s/system/seek.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/system/seek.c
#$o/module/time.o : $s/system/time.c
#	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/system/time.c
$o/module/write.o : $s/system/write.c
	$(CC) -c -DNDEBUG -o $@ -I$h -I$m -I$s/system $s/system/write.c

## *** Modules

MODULE_OBJS = $o/module/botch.o $o/module/clear.o $o/module/Malloc.o \
		$o/module/No_Mem.o $o/module/Realloc.o $o/module/Salloc.o \
		$o/module/st_alloc.o $o/module/std_alloc.o $o/module/BadAssert.o \
		$o/module/b64_add.o $o/module/b64_sft.o $o/module/flt_add.o \
		$o/module/flt_ar2flt.o $o/module/flt_chk.o $o/module/flt_cmp.o \
		$o/module/flt_div.o $o/module/flt_flt2ar.o $o/module/flt_modf.o \
		$o/module/flt_mul.o $o/module/flt_nrm.o $o/module/flt_str2fl.o \
		$o/module/flt_umin.o $o/module/split.o $o/module/ucmp.o \
		$o/module/rd.o $o/module/rd_arhdr.o $o/module/rd_bytes.o \
		$o/module/rd_int2.o $o/module/rd_long.o $o/module/rd_ranlib.o \
		$o/module/rd_unsig2.o $o/module/wr.o $o/module/wr_arhdr.o \
		$o/module/wr_bytes.o $o/module/wr_int2.o $o/module/wr_long.o \
		$o/module/wr_putc.o $o/module/wr_ranlib.o \
		$o/module/bts2str.o $o/module/btscat.o $o/module/btscmp.o \
		$o/module/btscpy.o $o/module/btszero.o $o/module/long2str.o \
		$o/module/str2bts.o $o/module/str2long.o $o/module/strindex.o \
		$o/module/strrindex.o $o/module/strzero.o \
		$o/module/read.o $o/module/seek.o $o/module/write.o

$o/libmodule.a : $(MODULE_OBJS)
	ar cr $@ $(MODULE_OBJS)
	touch $@
