#!/usr/bin/awk
#

/^#define/ && NF==3 { def[$2]=$3; next; }
/^#/                { next; }
NF==2               { kwd[$1]=$2; }
                    {}
END {
    print "#include \"lookup.h\""
    print "int"
    print "enterkeyw(void) {"
    print "    register symbol *sy_p;"
    for (txt in kwd)
    {
        sym=kwd[txt]
        if (sym in def)
            print "    sy_p=lookup(\""txt"\",symkeyw,newsymbol); sy_p->sy_value.syv_keywno="def[kwd[txt]]";"
    }
    print "    return 0;"
    print "}"
}
