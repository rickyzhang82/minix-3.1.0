/* libmain - flex run-time support library "main" function */

/* $Header: /cvsup/minix/src/commands/flex-2.5.4/libmain.c,v 1.1 2005/07/11 12:54:07 philip Exp $ */

extern int yylex();

int main( argc, argv )
int argc;
char *argv[];
	{
	while ( yylex() != 0 )
		;

	return 0;
	}
