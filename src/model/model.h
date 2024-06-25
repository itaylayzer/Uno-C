#ifndef _INC_MODEL
#define _INC_MODEL

#include <stdlib.h>
#include <stdbool.h>
#include "../controller/types.h"
#include "queue.h"
#include "dblist.h"

#define CONDITION_HEADER(func_name) bool func_name(GameState state, DBLIST node)
#define ACTION_HEADER(func_name) ubyte func_name(GameState state, Array *arr, DBLIST *node)

void uno_init(GameState, ubyte);

// conditions
CONDITION_FUNCTION(condition_true);
CONDITION_FUNCTION(condition_put);

// actions
ACTION_FUNCTION(play_endturn);
ACTION_FUNCTION(play_put);
ACTION_FUNCTION(play_stack);

#endif