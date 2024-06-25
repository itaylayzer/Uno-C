
#include "queue.h"

void queue_init(QUEUE *q)
{
    *q = NULL;
}
bool queue_empty(QUEUE q)
{
    return q == NULL;
}
void queue_destroy(QUEUE *q)
{
    while (!queue_empty(*q))
        dequeue(q);
}

// n=0
QUEUE insert_first(QUEUE *q)
{
    *q = malloc(sizeof(sLinkRec));
    (*q)->next = *q;
    return *q;
}
// n>1
QUEUE insert_end(QUEUE *q)
{
    QUEUE temp = malloc(sizeof(sLinkRec));
    temp->next = (*q)->next;
    (*q)->next = temp;
    *q = temp;
    return temp;
}

void enqueue(QUEUE *q, ubyte val)
{
    QUEUE(*actions[])
    (QUEUE *) = {insert_end, insert_first};
    actions[queue_empty(*q)](q)->val = val;
}

// n=1
ubyte remove_last(QUEUE *q)
{

    ubyte val = (*q)->val;
    free(*q);
    *q = NULL;
    return val;
}

// n>1
ubyte remove_after(QUEUE *q)
{
    QUEUE temp = (*q)->next;
    (*q)->next = temp->next;
    ubyte val = temp->val;
    free(temp);
    return val;
}

bool queue_is_last(QUEUE q)
{
    return q->next == q;
}

ubyte dequeue(QUEUE *q)
{

    ubyte (*actions[])(QUEUE *) = {remove_after, remove_last};
    return actions[queue_is_last(*q)](q);
}