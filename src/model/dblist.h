#ifndef _INC_DBLIST

#define _INC_DBLIST

#include "../controller/types.h"
#include <stdbool.h>
#include <stdlib.h>

void dbl_init(DBLIST *);
DBLIST dbl_push(DBLIST *);

bool dbl_node_last(DBLIST);
bool dbl_node_first(DBLIST);

ubyte dbl_remove_after(DBLIST);
ubyte dbl_remove_prev(DBLIST);
void dbl_removes(DBLIST);
#endif