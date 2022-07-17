#!/usr/bin/awk
#
# Generate header files from a parameters definition file.

BEGIN       { outfile="prefix" }
/^!File:.*/ { if (outfile != "prefix") then close(outfile) ; outfile=$2 ; next }
            { print >> outfile }
