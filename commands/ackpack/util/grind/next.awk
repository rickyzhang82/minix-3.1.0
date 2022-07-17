#!/usr/bin/awk
#
# Generate next.c from files processed by allocd.sed
#
# The input contain lines like:
#       /* ALLOCDEF "string_cst" 5 */
# that get processed.

/ALLOCDEF/ {
    len=length($3)
    field=substr($3,2,len-2)
    print "struct", field, "*h_" field, "= 0;"
    print "#ifdef DEBUG"
    print "int cnt_" field, "= 0;"
    print "#endif"
}
