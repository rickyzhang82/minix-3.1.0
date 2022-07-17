#!/usr/bin/awk
BEGIN { print "#include \"operator.h\"" ;
	print "#include \"ops.h\"" ;
	print ;
	print "t_operator operators[] = {" }
{ print "{ " $2 ", " $3 "}, /* " $1 " */" }
END { print "{ 0, 0 }" ; print "};" }
