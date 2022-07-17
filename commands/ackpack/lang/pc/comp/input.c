/* I N S T A N T I A T I O N   O F   I N P U T   P A C K A G E */

#include	"prototypes.h"
#include	"f_info.h"
struct f_info	file_info;
#include	"input.h"
#include	<em_arith.h>
#include	<inp_pkg.body>

int
AtEoIF(void)
{
	/*	Make the unstacking of input streams noticable to the
	   	lexical analyzer
	*/
	return 1;
}

/*	AtEoIT : a routine doing nothing. It is called at the end of an
	inserted text.
*/
int
AtEoIT(void)
{
	return 0;
}
