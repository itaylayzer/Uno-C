#ifndef _INC_VIEW
#define _INC_VIEW

#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include "../controller/controller.h"

#define NUM_CARDS 20 // Number of cards to display
#define text_x 168
#define text_y 257
typedef enum
{
    UNO_RED,
    UNO_BLUE,
    UNO_YELLOW,
    UNO_GREEN,
    UNO_BLACK

} UNO_COLORS;

#define num_key_down(num, name) num *(IsKeyPressed(KEY_##name) || IsKeyPressed(KEY_KP_##num))

void displayGame(GameState);

#endif