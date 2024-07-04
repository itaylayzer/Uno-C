#include "./view.h"

const Color colors[5] = {
    (Color){200, 55, 55, 255},
    (Color){50, 88, 168, 255},
    (Color){234, 200, 61, 255},
    (Color){55, 168, 76, 255},
    (Color){0, 0, 0, 255},
};

bool fixed_key_pressed(int key)
{
    return IsKeyPressedRepeat(key) || IsKeyPressed(key);
}

float calculateTextureX(int index)
{
    index %= 12;
    return index * text_x;
}
float calculateTextureY(int index)
{
    index /= 12;
    return index * text_y;
}
void DrawCard(unsigned char number, float hie, float x, float y, float size, float height_multiplier, Texture2D uno_texture)
{
    Color tempColor;

    const unsigned char texture_indexes[15] = {21, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 1, 6};

    memcpy(&tempColor, colors + (number >> 4), sizeof(Color));
    tempColor.a = hie * 180 + 75;
    number = number & 0x0F;
    Color background = number <= 12 ? tempColor : (Color){255, 255, 255, tempColor.a};
    Color Outline = number <= 12 ? (Color){0, 0, 0, tempColor.a} : tempColor;
    const unsigned char textind = texture_indexes[number % 15];

    DrawRectangleRounded((Rectangle){x, y, size, size * height_multiplier}, 0.2f, 10, background);

    number > 9 &&
        (DrawTexturePro(uno_texture, (Rectangle){text_x * 2, 0, text_x, text_y}, (Rectangle){x, y, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){Outline.r, Outline.g, Outline.b, 255}), 1);

    DrawTexturePro(uno_texture, (Rectangle){text_x * 3, 0, text_x, text_y}, (Rectangle){x, y, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){tempColor.a, tempColor.a, tempColor.a, 255});
    DrawTexturePro(uno_texture, (Rectangle){calculateTextureX(textind), calculateTextureY(textind), text_x, text_y}, (Rectangle){x, y, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){background.a, background.a, background.a, 255});
}

bool start_thread(void *(*compute_play)(GameState),
                  GameState state)
{

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, compute_play, state);
}

void displayGame(GameState state,
                 CONDITION_VARIABLE(conditions[]),
                 ACTION_VARIABLE(actions[]),
                 void *(*compute_play)(GameState))

{

    const char *colorsNames[] = {"RED", "BLUE", "YELLOW", "GREEN", "BLACK"};
    DBLIST pnode = state->player.arr;
    ubyte color_selected = 0;
    state->selected = 0;

    { // go to middle
        ubyte offset = 0;
        for (offset = 0; offset * 2 < state->player.size - 1; offset++)
        {
            pnode = pnode->next;
            state->selected++;
        }
    }

    // Initialization
    bool is_full = false, positive = true;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1330, 720, "@ItayL - Uno");
    SetWindowMinSize(800, 600);

    Texture2D uno_texture = LoadTexture("./assets/texture.png");

    int width, height;
    Rectangle pre_state;
    float lerpSelected = state->selected, lerpColoredSelected = color_selected, lerpShowColors = 0, lerpPlayerTurn = 0, lerpEnemyTurn = 0;
    bool change_color = false, reset_change_color = false, start_enemy_after_color = false,
         (*key_pressed)(int) = fixed_key_pressed;
    const double fps = 240;
    SetTargetFPS(fps);
    const float min_size = 70;
    const float max_size = 85;
    const float height_multiplier = 1.54819f;
    float lerp2 = 0;

    // Main game loop
    while (!WindowShouldClose())
    {

        width = GetRenderWidth();
        height = GetRenderHeight();
        if (!IsWindowFullscreen())
        {
            pre_state.height = height;
            pre_state.width = width;
            pre_state.x = GetWindowPosition().x;
            pre_state.y = GetWindowPosition().y;
        }

        ubyte action_index = clamp(
            (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_B) || IsKeyPressed(KEY_C) || (IsKeyPressed(KEY_DOWN))) + 2 * (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_X) || IsKeyPressed(KEY_UP)), 0, 3);

        CONDITION_VARIABLE(selected_condition) = conditions[action_index];
        ACTION_VARIABLE(selected_action) = actions[action_index];

        if (selected_action != NULL && selected_condition(state, pnode->val) && !change_color && state->player_turn)
        {
            ubyte action_avl = selected_action(state, &state->player, &state->enemy, &pnode);
            bool end_turn, done_game;

            change_color = action_avl & 0x01;
            end_turn = (action_avl >> 4) & 0x01;
            done_game = (action_avl >> 1) & 0x01;

            start_enemy_after_color = change_color && end_turn;

            (!change_color && end_turn && !done_game) && (start_thread(compute_play, state));

            byte direction = (action_avl >> 5) - 1;
            state->selected += direction;
        }

        if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_X) || IsKeyPressed(KEY_UP)) && change_color && reset_change_color && state->player_turn)
        {
            change_color = false;
            state->card = (color_selected << 4) + (state->card & 0x0f);

            (start_enemy_after_color) && (start_enemy_after_color = false, start_thread(compute_play, state));
        }

        short select_addon, old_select = state->selected, _movement = 0;

        _movement += -(key_pressed(KEY_LEFT) || key_pressed(KEY_A)) + (key_pressed(KEY_RIGHT) || key_pressed(KEY_D));
        _movement += (positive ? 1 : -1) * (num_key_down(1, ONE) + num_key_down(2, TWO) + num_key_down(3, THREE) + num_key_down(4, FOUR) + num_key_down(5, FIVE) + num_key_down(6, SIX) + num_key_down(7, SEVEN) + num_key_down(8, EIGHT) + num_key_down(9, NINE));

        _movement += -5 * IsKeyPressed(KEY_G) - IsKeyPressed(KEY_H) + IsKeyPressed(KEY_J) + 5 * IsKeyPressed(KEY_K);
        state->selected = clamp(state->selected + _movement * (!change_color), 0, state->player.size - 1);
        color_selected = clamp(color_selected + _movement * change_color, 0, MAX_COLORS - 1);

        bool _pos = (select_addon = state->selected - old_select) > 0;

        select_addon = sabs(select_addon);
        while (select_addon--)
        {
            DBLIST nodes[] = {pnode->prev, pnode->next};
            pnode = nodes[_pos];
        }

        // max_cards = clamp(max_cards + key_pressed(KEY_UP) - key_pressed(KEY_DOWN), 0, 30);
        lerpSelected = lerp(lerpSelected, (float)state->selected, 12.0f / fps);
        lerpColoredSelected = lerp(lerpColoredSelected, (float)color_selected, 12.0f / fps);
        lerpShowColors = lerp(lerpShowColors, (float)change_color, 12.0f / fps);
        lerpEnemyTurn = lerp(lerpEnemyTurn, !(float)state->player_turn, 12.0f / fps);
        lerpPlayerTurn = lerp(lerpPlayerTurn, (float)state->player_turn, 12.0f / fps);

        // change full screen ----------------------------------------------------------------------------
        // found this solution online
        if (IsKeyPressed(KEY_F) || IsKeyPressed(KEY_F11))
        {
            if (!IsWindowFullscreen())
            {
                int monitor = GetCurrentMonitor();

                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
                ToggleFullscreen();
            }
            else
            {
                ToggleFullscreen();
                SetWindowSize(pre_state.width, pre_state.height);
                SetWindowPosition(pre_state.x, pre_state.y);
            }
        }

        BeginDrawing();
        ClearBackground((Color){9, 9, 10, 255});
        // player cards ----------------------------------------------------------------------------
        unsigned char index;
        DBLIST node;

        for (index = 0, node = state->player.arr; node; node = node->next, index++)
        {
            // hie is a cool variable name for misleading ppls
            const float hie = fabs(fclamp((float)index - lerpSelected, -1.0, 1.0));
            const float hie_color = conditions[2](state, node->val) * 0.5 + state->player_turn * conditions[2](state, node->val) * 0.5;

            const float lerpTurn = lerpEnemyTurn * 8;
            const float downscale = hie * (min_size - max_size);
            const float size = downscale + max_size - lerpTurn;

            const float x = width / 2 + index * (min_size - lerpTurn) * 1.2 - size / 2 - lerpSelected * (max_size - lerpTurn);
            const float y = height - max_size + -size - 10;
            DrawCard(node->val, hie_color - change_color * 0.5, x, y, size, height_multiplier, uno_texture);
        };

        float addon = (lerpSelected - (float)state->selected) * min_size;

        // draw bank ----------------------------------------------------------------------------
        lerp2 = lerp(lerp2, addon, 0.1);
        addon = lerp2;
        float x = width / 2 - max_size / 2 + addon;
        float y = height / 2 - max_size;

        DrawCard(state->card, 1, x, y, max_size, height_multiplier, uno_texture);

        // draw colors ----------------------------------------------------------------------------

        for (unsigned char color_offset = 0; color_offset < MAX_COLORS; color_offset++)
        {
            const float size = max_size + fabs(fclamp(lerpColoredSelected - color_offset, -1, 1)) * (min_size - max_size);
            const float _y = height / 2 + 80 - size / 8;
            const float _x = width / 2 - size / 2 - (lerpColoredSelected - color_offset) * size * 1.2;
            Color color = colors[color_offset];
            color.a = lerpShowColors * 255;
            DrawRectangleRounded((Rectangle){_x, _y, size, size / 8}, 0.2, 10, color);
        }
        // DrawRectangleRounded((Rectangle){x, y, max_size, max_size * height_multiplier}, 0.2f, 10, (Color){55, 55, 55, 255});
        x -= 150;

        DrawTexturePro(uno_texture, (Rectangle){0, 0, text_x, text_y}, (Rectangle){x + 20, y + max_size * 0.2f, max_size * 0.8f, max_size * 0.7f * height_multiplier}, (Vector2){0, 0}, 0, (Color){120, 120, 120, 100});
        DrawTexturePro(uno_texture, (Rectangle){0, 0, text_x, text_y}, (Rectangle){x, y + max_size * 0.1f, max_size * 0.9f, max_size * 0.9f * height_multiplier}, (Vector2){0, 0}, 0, (Color){120, 120, 120, 250});

        // draw enemy ----------------------------------------------------------------------------
        for (unsigned int index = 0; index < state->enemy.size; index++)
        {
            const float lerpTurn = lerpPlayerTurn * 8;
            const float size = min_size - lerpTurn;
            const float x = addon + width / 2 - size / 2 + index * size * 1.2 - (((float)state->enemy.size - 1) / 2.0f) * (max_size - lerpTurn);

            const float enemyy = -size + 100;

            DrawTexturePro(uno_texture, (Rectangle){0, 0, text_x, text_y}, (Rectangle){x, enemyy, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){lerpEnemyTurn * 60 + 60, lerpEnemyTurn * 60 + 60, lerpEnemyTurn * 60 + 60, 250});
        }

        // draw turn rectangels ----------------------------------------------------------------------------
        {
            float x = width / 2 - max_size / 2 + addon + (max_size - min_size * 0.8) / 2;
            float y = height / 2 - max_size - 15;

            Color _color = {255, 255, 255, lerpEnemyTurn * 180 + 75};

            DrawRectangleRounded((Rectangle){x, y, min_size * 0.8, 5}, 2, 10, _color);
            _color.a = lerpPlayerTurn * 180 + 75;

            y += +max_size * height_multiplier + 25;
            DrawRectangleRounded((Rectangle){x, y, min_size * 0.8, 5}, 2, 10, _color);
        }
        {
            char text[100] = {0};
            // sprintf(text, "color selected %d\n\nselected %d\npnode %d (%s)", color_selected, state->selected, pnode->val & 0x0f, colorsNames[pnode->val >> 4]);
            DrawText(text, 0, 0, 20, WHITE);
        }
        reset_change_color = change_color;

        EndDrawing();
    }

    UnloadTexture(uno_texture);

    CloseWindow();
}
