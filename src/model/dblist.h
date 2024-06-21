#ifndef _INC_DBLIST

#define _INC_DBLIST

#include "../controller/types.h"
#include <stdbool.h>
#include <stdlib.h>

#define DBLIST dNode

void dbl_init(DBLIST *);
DBLIST dbl_push(DBLIST *);
void dbl_remove_prev(DBLIST *);

#endif