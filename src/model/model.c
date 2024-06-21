#include "model.h"
#define cn(color, num) (color << 4) + num

int _random(int lower, int upper)
{
    const int val = (rand() % (upper - lower + 1)) + lower;

    return val;
}

void vector_shuffle(ubyte *arr, ubyte size)
{
    ubyte offset;
    for (offset = 0; offset < size; offset++)
    {
        ubyte temp = arr[offset];
        ubyte rand_offset = (ubyte)(_random(0, size - 1));
        arr[offset] = arr[rand_offset];
        arr[rand_offset] = temp;
    }
}
void random_stacking(STACK *stk)
{

    const ubyte cards[] = {
        cn(0, 0),
        cn(1, 0),
        cn(2, 0),
        cn(3, 0),

        cn(0, 1),
        cn(0, 1),
        cn(1, 1),
        cn(1, 1),
        cn(2, 1),
        cn(2, 1),
        cn(3, 1),
        cn(3, 1),

        cn(0, 2),
        cn(0, 2),
        cn(1, 2),
        cn(1, 2),
        cn(2, 2),
        cn(2, 2),
        cn(3, 2),
        cn(3, 2),

        cn(0, 3),
        cn(0, 3),
        cn(1, 3),
        cn(1, 3),
        cn(2, 3),
        cn(2, 3),
        cn(3, 3),
        cn(3, 3),

        cn(0, 4),
        cn(0, 4),
        cn(1, 4),
        cn(1, 4),
        cn(2, 4),
        cn(2, 4),
        cn(3, 4),
        cn(3, 4),

        cn(0, 5),
        cn(0, 5),
        cn(1, 5),
        cn(1, 5),
        cn(2, 5),
        cn(2, 5),
        cn(3, 5),
        cn(3, 5),

        cn(0, 6),
        cn(0, 6),
        cn(1, 6),
        cn(1, 6),
        cn(2, 6),
        cn(2, 6),
        cn(3, 6),
        cn(3, 6),

        cn(0, 7),
        cn(0, 7),
        cn(1, 7),
        cn(1, 7),
        cn(2, 7),
        cn(2, 7),
        cn(3, 7),
        cn(3, 7),

        cn(0, 8),
        cn(0, 8),
        cn(1, 8),
        cn(1, 8),
        cn(2, 8),
        cn(2, 8),
        cn(3, 8),
        cn(3, 8),

        cn(0, 9),
        cn(0, 9),
        cn(1, 9),
        cn(1, 9),
        cn(2, 9),
        cn(2, 9),
        cn(3, 9),
        cn(3, 9),

        cn(0, 10),
        cn(0, 10),
        cn(1, 10),
        cn(1, 10),
        cn(2, 10),
        cn(2, 10),
        cn(3, 10),
        cn(3, 10),

        cn(0, 11),
        cn(0, 11),
        cn(1, 11),
        cn(1, 11),
        cn(2, 11),
        cn(2, 11),
        cn(3, 11),
        cn(3, 11),

        cn(0, 12),
        cn(0, 12),
        cn(1, 12),
        cn(1, 12),
        cn(2, 12),
        cn(2, 12),
        cn(3, 12),
        cn(3, 12),

        cn(4, 13),
        cn(4, 13),
        cn(4, 13),
        cn(4, 13),
        cn(4, 14),
        cn(4, 14),
        cn(4, 14),
        cn(4, 14),

    };
    const ubyte count = sizeof(cards) / sizeof(cards[0]);
    vector_shuffle(cards, count);

    for (ubyte offset = 0; offset < count; offset++)
    {
        stack_push(stk, cards[offset]);
    }
}

void uno_init(GameState state, ubyte start_count)
{
    dbl_init(&state->player);
    dbl_init(&state->enemy);
    stack_init(&state->stack);

    random_stacking(&state->stack);

    state->card = stack_pop(&state->stack);
    state->pcount = state->ecount = start_count;

    while (start_count--)
    {
        dbl_push(&state->player)->val = (stack_pop(&state->stack));
        dbl_push(&state->enemy)->val = (stack_pop(&state->stack));
    }
}