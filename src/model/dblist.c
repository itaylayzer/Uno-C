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

    ((*list) != NULL) &&
        ((*list)->prev = temp);

    *list = temp;
    return temp;
}
bool dbl_node_last(DBLIST node)
{
    return node->next == NULL;
}
bool dbl_node_first(DBLIST node)
{
    return node->prev == NULL;
}
ubyte dbl_remove_after(DBLIST node)
{
    // puts("dbl_remove_after");
    DBLIST temp = node->next;
    node->next = temp->next;
    temp->next && (temp->next->prev = node);
    ubyte val = temp->val;
    free(temp);
    return val;
}
ubyte dbl_remove_prev(DBLIST node)
{
    // puts("dbl_remove_prev");
    DBLIST temp = node->prev;
    node->prev = temp->prev;
    temp->prev && (temp->prev->next = node);
    ubyte val = temp->val;
    free(temp);
    return val;
}
void dbl_removes(DBLIST node)
{
    // puts("\tA");

    ubyte (*remove_fn[])(DBLIST *) = {dbl_remove_prev, dbl_remove_after};
    // puts("\tB");

    DBLIST vals[] = {node->next, node->prev};
    // puts("\tC");

    bool islast = dbl_node_last(node);
    // puts("\tD");

    remove_fn[islast](vals[islast]);
}