s:^.*[ 	]ALLOCDEF[ 	].*"\(.*\)"[ 	]*\([0-9][0-9]*\).*$:\
/* allocation definitions of struct \1 */\
#include "alloc.h" /* st_alloc() */ \
extern struct \1 *h_\1;\
#define	new_\1() ((struct \1 *) st_alloc((char **)\&h_\1, sizeof(struct \1), \2))\
#define	free_\1(p) st_free(p, \&h_\1, sizeof(struct \1))\
:
