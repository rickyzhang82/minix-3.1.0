#!/usr/bin/awk
#
# Generate next.c from *.str files (stdin)
#
# The *.str files contain lines:
#       /* ALLOCDEF "string_cst" 5 */
# that get processed.


BEGIN { print "#include \"debug.h\"" }
/ALLOCDEF/ {
    len=length($3)
    field=substr($3,2,len-2)
    print "struct", field, "*h_" field, "= 0;"
    print "#ifdef DEBUG"
    print "int cnt_" field, "= 0;"
    print "#endif"
}
