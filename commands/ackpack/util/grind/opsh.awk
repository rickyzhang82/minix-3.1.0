#!/usr/bin/awk
BEGIN	{ n = 0; print "#include \"tree.h\"" }
	{ print "#define " $1 " " n; n++
	  if ($3 !~ /0/) print "void " $3 "(p_tree);" ;
	}

