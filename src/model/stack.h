#ifndef _INC_STACK

#define _INC_STACK

#include <stdbool.h>
#include <stdlib.h>
#include "../controller/types.h"

#define STACK sNode

void stack_init(STACK *);
void stack_push(STACK *, ubyte);
ubyte stack_pop(STACK *);
bool stack_empty(STACK);
void stack_destroy(STACK *);

#endif