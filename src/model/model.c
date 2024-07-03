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
void random_stacking(QUEUE *q)
{

    ubyte cards[] = {
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
        enqueue(q, cards[offset]);
    }
}

void uno_init(GameState state, ubyte start_count)
{
    dbl_init(&state->player.arr);
    dbl_init(&state->enemy.arr);
    queue_init(&state->queue);

    random_stacking(&state->queue);

    state->card = dequeue(&state->queue);

    // make sure the start card be a number
    while ((state->card & 0x0F) / 10)
    {
        enqueue(&state->queue, state->card);
        state->card = dequeue(&state->queue);
    }

    state->player.size = state->enemy.size = start_count;

    while (start_count--)
    {
        dbl_push(&state->player.arr)->val = (dequeue(&state->queue));
        dbl_push(&state->enemy.arr)->val = (dequeue(&state->queue));
        // dbl_push(&state->player.arr)->val = cn(4, 14);
    }

    state->player_turn = true;
}

///////////////////// conditions /////////////////////

CONDITION_HEADER(condition_true)
{
    return true;
}
CONDITION_HEADER(condition_put)
{
    bool same_color = (state->card >> 4) == (card >> 4);
    bool same_number = (state->card & 0x0f) == (card & 0x0f);
    bool black_color = (card >> 4) == UNO_BLACK;
    return same_color || same_number || black_color;
}

///////////////////// actions /////////////////////
// the action returns bitmap value
// the 1-4th bits are states bitmap:
//                  1th bit is change color
// the 5th bit are done turn
// the 6-7th bits is direction:
//       0 negative
//       1 none
//       2 positive
// return 1

ACTION_HEADER(play_endturn)
{
    return 1;
}

// 2  and above if yes and action
// 0 if not, 1 end streak mode, 2 if nothing, 3 pick color, 4 start streak mode
ACTION_HEADER(play_put)
{

    ubyte ret, num;
    bool is_first, is_last, done_turn, change_color;

    enqueue(&state->queue, state->card);
    state->card = (*node)->val;
    arr->size--;

    is_first = dbl_node_first(*node);
    is_last = dbl_node_last(*node);

    if (is_first && is_last)
    {
        free(*node);
        arr->arr = *node = NULL;
        return (1 << 5) + (1 << 4) + 0;
    }

    DBLIST next_node[] = {(*node)->next, (*node)->prev};
    *node = next_node[is_last];
    DBLIST delete_node[] = {(*node)->prev, (*node)->next};

    dbl_removes(delete_node[is_last]);

    is_first && (arr->arr = *node);

    num = state->card & 0x0f;
    done_turn = num < 10 || num == 13;
    change_color = num > 12;
    ret = ((!is_last) << 5) + (done_turn << 4) + change_color;

    // move cards if its takes2 or takes4
    unsigned char times_to_move_to_other = (0.5 * num - 3) * (num == 10 || num == 14);
    while (times_to_move_to_other--)
    {
        play_stack(state, other, NULL, NULL);
    }

    return ret;
}

// return 2 always
ACTION_HEADER(play_stack)
{

    dbl_push(&arr->arr)->val = dequeue(&state->queue);

    arr->size++;
    // (*node) && (*node = (*node)->prev);
    // (!*node) && (*node = arr->arr);

    return (2 << 5) + (1 << 4);
}

// computer player thread
void *compute_play(GameState state)
{

    state->player_turn = false;
    puts("before");

    ubyte card;
    bool change_turn = false;
    DBLIST node = state->enemy.arr;

    while (!change_turn)
    {
        usleep(800000);
        puts("\theauristic");
        card = heauristic_alg(state->enemy.arr, state->card);

        // card is useable so take from stack
        puts("\tcondition_put");
        printf("\tcard=%d(%d)\n", card & 0x0f, card >> 4);
        if (!condition_put(state, card))
        {
            play_stack(state, &state->enemy, &state->player, NULL);
            break;
        }
        puts("\tfind node");

        // find node
        while (node->val != card && node)
        {
            node = node->next;
        }
        printf("\tcard=%d(%d)\n", node->val & 0x0f, node->val >> 4);

        if (!node)
        {
            break;
        }
        puts("\tplay_put");
        ubyte res = play_put(state, &state->enemy, &state->player, &node);

        // change color
        puts("\tchange color");

        if (res & 0x01)
        {
            usleep(800000);

            ubyte color = prioritise_color(state->enemy.arr);
            state->card = (color << 4) + (state->card & 0x0f);
        }

        puts("\tstop turning");

        // stop turning
        if ((res >> 4) & 0x01)
        {
            break;
        }
    }

    usleep(800000);

    puts("after");

    state->player_turn = true;

    // return NULL;
}