#include "dblist.h"

void dbl_init(DBLIST *list)
{
    *list = NULL;
}
DBLIST dbl_push(DBLIST *list)
{
    DBLIST temp = malloc(sizeof(dLinkRec));
    temp->next = *list;
    temp->prev = NULL;
    if ((*list) != NULL)
    {
        (*list)->prev = temp;
    }
    *list = temp;
    return temp;
}
void dbl_remove_prev(DBLIST *list)
{
}