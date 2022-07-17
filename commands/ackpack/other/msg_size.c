/* Calculate the size of a system message
 *
 * Minix 3 defines the constant 'MESS_SIZE', whereas Minix 2 does not.
 * Another difference is the header file defining 'struct message'.
 */

#include <minix/config.h>
#include <minix/const.h>
#ifdef MESS_SIZE /* Minix 3 */
# include <ansi.h>
# include <minix/ipc.h>
#endif
#include <minix/type.h>
#include <stdio.h>
int
main( int argc, char ** argv )
{
    printf( "%d\n", sizeof( message ) );
    return 0;
}

