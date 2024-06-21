#include "controller.h"

void start_uno()
{
    stateRec state;
    srand(time(NULL));
    uno_init(&state, 7);
    displayGame(&state);
}