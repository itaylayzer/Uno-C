#ifndef _INC_CONTROLLER_TYPES
#define _INC_CONTROLLER_TYPES

#include <stdbool.h>

#define MAX_COLORS 4

#define ubyte unsigned char
#define byte signed char

#define QUEUE sNode
#define DBLIST dNode

#define REGION(region) {
#define ENDREGION }

///////////////////// actions /////////////////////
// the action returns bitmap value
// 1th bit is change color
// 2th bit is done game
// the 5th bit are done turn
// the 6-7th bits is direction:
//       0 negative
//       1 none
//       2 positive
// return 1

#define ACTION_VARIABLE(var_name) ubyte (*var_name)(GameState, Array *, Array *, DBLIST *)
#define ACTION_FUNCTION(func_name) ubyte func_name(GameState, Array *, Array *, DBLIST *)

///////////////////// conditions /////////////////////
// the condition returns boolean value

#define CONDITION_VARIABLE(var_name) bool (*var_name)(GameState, ubyte)
#define CONDITION_FUNCTION(func_name) bool func_name(GameState, ubyte)

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
    bool player_turn;
    ubyte selected;

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