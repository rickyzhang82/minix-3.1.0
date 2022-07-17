/* $Id: rd.h,v 1.1 2005/09/01 12:13:33 beng Exp $ */

#include	<out.h>

#define O_CONVERTED	0x202

/* Signatures match functions in module/src/object/object.h */
int rd_open( char * );
void rd_ohead( struct outhead * );
void rd_name( struct outname *, unsigned int );
void rd_string( char *, long );
void rd_close( void );

