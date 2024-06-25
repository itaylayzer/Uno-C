#include "controller.h"

void start_uno()
{
    // seed random
    srand(time(NULL));

    // state & game initialization
    stateRec state;
    uno_init(&state, 7);

    // actions & conditions
    ubyte (*actions[])(GameState, Array *, DBLIST *) = {NULL, play_stack, play_put, play_endturn, NULL};
    bool (*conditions[])(GameState, DBLIST) = {condition_true, condition_true, condition_put, condition_true, condition_true};

    displayGame(&state, conditions, actions);
}