
#include "stack.h"

void stack_init(STACK *stk)
{
    *stk = NULL;
}
void stack_push(STACK *stk, ubyte val)
{
    STACK element = malloc(sizeof(sLinkRec));
    element->next = *stk;
    element->val = val;
    *stk = element;
}
ubyte stack_pop(STACK *stk)
{
    ubyte val = (*stk)->val;
    STACK temp = *stk;
    (*stk) = (*stk)->next;
    free(temp);
    return val;
}
bool stack_empty(STACK stk)
{
    return stk == NULL;
}
void stack_destroy(STACK *stk)
{
    while (!stack_empty(*stk))
    {
        stack_pop(stk);
    }
}