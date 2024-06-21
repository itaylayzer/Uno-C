#ifndef _INC_QUEUE

#define _INC_QUEUE

#include <stdbool.h>
#include <stdlib.h>
#include "../controller/types.h"

#define QUEUE sNode

void queue_init(QUEUE *);
void enqueue(QUEUE *, ubyte);
ubyte dequeue(QUEUE *);
bool queue_empty(QUEUE);
void queue_destroy(QUEUE *);

#endif