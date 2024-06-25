#ifndef _INC_CONTROLLER_TYPES
#define _INC_CONTROLLER_TYPES

#define ubyte unsigned char
#define byte signed char

#define QUEUE sNode
#define DBLIST dNode

#define REGION(region) {
#define ENDREGION }

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

typedef struct
{
    ubyte size;
    dNode arr;
} Array;

typedef struct stateType
{
    Array player;
    Array enemy;
    ubyte card;
    sNode queue;

} stateRec, *GameState;

typedef enum
{
    UNO_RED,
    UNO_BLUE,
    UNO_YELLOW,
    UNO_GREEN,
    UNO_BLACK

} UNO_COLORS;

#endif