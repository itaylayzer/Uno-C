#ifndef _INC_CONTROLLER_TYPES
#define _INC_CONTROLLER_TYPES

#define ubyte unsigned char
#define byte signed char

typedef struct dblLinkNode
{
    struct dblLinkNode *next;
    struct dblLinkNode *prev;
    ubyte val;
} dLinkRec, *dNode;

typedef struct sLinkNode
{
    struct dblLinkNode *next;
    ubyte val;
} sLinkRec, *sNode;

typedef struct stateType
{
    dNode player;
    dNode enemy;
    ubyte card;
    ubyte pcount;
    ubyte ecount;
    sNode stack;

} stateRec, *GameState;

#endif