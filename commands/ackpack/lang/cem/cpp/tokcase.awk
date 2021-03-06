#!/usr/bin/awk

BEGIN {
    print "/* Generated by tokcase.awk */"
    print "#include \"Lpars.h\""
    print ""
    print "char *"
    print "symbol2str(int tok)"
    print "{"
    print "    static char buf[2] = { '\\0', '\\0' };"
    print ""
    print "    if (040 <= tok && tok < 0177) {"
    print "        buf[0] = tok;"
    print "        buf[1] = '\\0';"
    print "        return buf;"
    print "    }"
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
    print "    case '\\n':"
    print "    case '\\f':"
    print "    case '\\v':"
    print "    case '\\r':"
    print "    case '\\t':"
    print "        buf[0] = tok;"
    print "        return buf;"
    print "    default:"
    print "        return \"bad token\";"
    print "    }"
    print "}"
}
