#include "controller.h"

void start_uno()
{
    // seed random
    srand(time(NULL));

    // state & game initialization
    stateRec state;
    uno_init(&state, 7);

    // actions & conditions
    ACTION_VARIABLE(actions[]) = {NULL, play_stack, play_put,  NULL};
    CONDITION_VARIABLE(conditions[]) = {condition_true, condition_true, condition_put, condition_true};

    displayGame(&state, conditions, actions, compute_play);
}