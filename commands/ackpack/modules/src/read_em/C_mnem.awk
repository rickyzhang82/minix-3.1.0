#!/usr/bin/awk
#
# Process {ACK}/etc/em_table. This file has three kinds of lines:
#    - two arguments
#    - three arguments; second an integer
#    - three arguments; second a two character code
#
# This script is interested in the two character code lines. There are
# the following cases (controlled by the first character)
#    - No arguments
#    - One integer constant argument
#    - Procedure name argument
#    - Instruction label argument
#    - 'generic' argument
#
# The scripts in modules/src/read_em, util/ceg/defaults are similar.
#
BEGIN {}
NF == 3 && $2 ~ "-." { narg[$1]=0 }
NF == 3 && $2 ~ "[cdflnorswz]." { iarg[$1]=0 }
NF == 3 && $2 ~ "p." { parg[$1]=0 }
NF == 3 && $2 ~ "b." { larg[$1]=0 }
NF == 3 && $2 ~ "g." { garg[$1]=0 }
END {
    print "switch(p->em_opcode) {"

    print "  /* no arguments */"
    for (x in narg) print "case op_" x ": C_" x "(); break;"

    print "  /* one integer constant argument */"
    for (x in iarg) print "case op_" x ": C_" x "(p->em_cst); break;"

    print "  /* procedure name argument */"
    for (x in parg) print "case op_" x ": C_" x "(p->em_pnam); break;"

    print "  /* instruction label argument */"
    for (x in larg) print "case op_" x ": C_" x "( (label) (p->em_cst) ); break;"

    print "  /* a 'generic' argument */"
    print "default:"
    print "  if(p->em_argtype == nof_ptyp) {"
    print "    switch(p->em_opcode) {"
    print "      default: EM_error = \"Illegal mnemonic\"; break;"

    for (x in garg) print "      case op_" x ": C_" x "_dlb(p->em_dlb,p->em_off); break;"

    print "    }"
    print "  } else if (p->em_argtype == sof_ptyp) {"
    print "    switch(p->em_opcode) {"
    print "      default: EM_error = \"Illegal mnemonic\"; break;"

    for (x in garg) print "      case op_" x ": C_" x "_dnam(p->em_dnam,p->em_off); break;"

    print "    }"
    print "  } else if (p->em_argtype == cst_ptyp) {"
    print "    switch(p->em_opcode) {"
    print "      default: EM_error = \"Illegal mnemonic\"; break;"

    for (x in garg) print "      case op_" x ": C_" x "(p->em_cst); break;"

    print "    }"
    print "  }"
    print "}"
    }
