#ifndef _INC_MODEL
#define _INC_MODEL

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "queue.h"
#include "dblist.h"
#include "compute.h"
#include "../controller/types.h"

#define CONDITION_HEADER(func_name) bool func_name(GameState state, ubyte card)
#define ACTION_HEADER(func_name) ubyte func_name(GameState state, Array *arr, Array *other, DBLIST *node)

void uno_init(GameState, ubyte);

// conditions
CONDITION_FUNCTION(condition_true);
CONDITION_FUNCTION(condition_put);

// actions
ACTION_FUNCTION(play_endturn);
ACTION_FUNCTION(play_put);
ACTION_FUNCTION(play_stack);

// computer player thread
void *compute_play(GameState);
#endif