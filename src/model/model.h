#ifndef _INC_MODEL
#define _INC_MODEL

#include <stdlib.h>
#include <stdbool.h>
#include "../controller/types.h"
#include "queue.h"
#include "dblist.h"

void uno_init(GameState, ubyte);

///////////////////// conditions /////////////////////
bool condition_true(GameState, DBLIST);
bool condition_put(GameState, DBLIST);

///////////////////// actions /////////////////////

// return 2
ubyte play_endturn(GameState, Array *, DBLIST *);

// 2  and above if yes and action
// 0 if not, 1 streak mode, 2 if nothing, 3 pick color
ubyte play_put(GameState, Array *, DBLIST *);

// return 2 always
ubyte play_stack(GameState, Array *, DBLIST *);

#endif