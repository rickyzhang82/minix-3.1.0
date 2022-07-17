#!/usr/bin/awk
#
# Process {ACK}/etc/em_table. This file has three kinds of lines:
#    - two arguments
#    - three arguments; second an integer
#    - three arguments; second a two character code
#
# This script is interested in the two character code lines. There are
# the following cases (controlled by the first character)
#    - 'w'
#
# The scripts in modules/src/read_em, util/ceg/defaults are similar.
#
BEGIN {}
NF == 3 && $2 ~ "w." { warg[$1]=0 }
END {
    print "switch(p->em_opcode) {"

    for (x in warg) print "case op_" x ": C_" x "_narg(); break;"

    print "default: EM_error = \"Illegal mnemonic\";"
    print "}"
    }
