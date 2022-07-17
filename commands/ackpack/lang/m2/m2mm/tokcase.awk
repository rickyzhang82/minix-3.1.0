#!/usr/bin/awk

BEGIN {
    print "/* Generated by tokcase.awk */"
    print "#include \"Lpars.h\""
    print ""
    print "char *"
    print "symbol2str(int tok)"
    print "{"
    print "#define SIZBUF 8"
    print "    /* allow for a few invocations in f.i. an argument list */"
    print "    static char buf[SIZBUF];"
    print "    static int index;"
    print ""
    print "    switch (tok) {"
}

/{[A-Z]/ {
    match($1,/[A-Z][A-Z_0-9]*/)
    x=substr($1,RSTART,RLENGTH)
    raw=($2 " " $3)
    match(raw,/".*"/)
    y=substr(raw,RSTART,RLENGTH)
    print "    case", x ": return", y ";"
}

END {
    print "    default:"
    print "        if (tok <= 0) return \"end of file\";"
    print "        if (tok < 040 || tok >= 0177) {"
    print "            return \"bad token\";"
    print "        }"
    print "        index = (index+4) & (SIZBUF-1);"
    print "        buf[index] = tok;"
    print "        return &buf[index-1];"
    print "    }"
    print "}"
}
