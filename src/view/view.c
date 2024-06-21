#include "./view.h"

float lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}

float fmax(float x, float y)
{
    return x > y ? x : y;
}
float fmin(float x, float y)
{
    return x > y ? y : x;
}
float fclamp(float val, float _min, float _max)
{
    return fmax(fmin(val, _max), _min);
}
float fabs(float val)
{
    return val * (val < 0 ? -1 : 1);
}

bool fixed_key_pressed(int key)
{
    return IsKeyPressedRepeat(key) || IsKeyPressed(key);
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a > b ? b : a;
}
int clamp(int val, int _min, int _max)
{
    return max(min(val, _max), _min);
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
void DrawCard(unsigned char number, float hie, float x, float y, float size, float height_multiplier, Texture2D uno_texture, Texture2D txt_header, Texture2D txt_outline)
{
    Color tempColor;
    Color colors[5] = {
        (Color){200, 55, 55, 255},
        (Color){50, 88, 168, 255},
        (Color){245, 225, 10, 255},
        (Color){55, 168, 76, 255},
        (Color){0, 0, 0, 255},
    };
    const unsigned char texture_indexes[15] = {21, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22, 23, 24, 1, 6};

    memcpy(&tempColor, colors + (number >> 4), sizeof(Color));
    tempColor.a = (1 - hie) * 150 + 105;
    number = number & 0x0F;
    Color background = number <= 12 ? tempColor : RAYWHITE;
    Color Outline = number <= 12 ? (Color){0, 0, 0, 255} : tempColor;
    const unsigned char textind = texture_indexes[number % 15];

    DrawRectangleRounded((Rectangle){x, y, size, size * height_multiplier}, 0.2f, 10, background);

    DrawTexturePro(uno_texture, (Rectangle){calculateTextureX(textind), calculateTextureY(textind), text_x, text_y}, (Rectangle){x, y, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){background.a, background.a, background.a, 255});
    number > 9 &&
        (DrawTexturePro(txt_header, (Rectangle){0, 0, text_x, text_y}, (Rectangle){x, y, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){Outline.r, Outline.g, Outline.b, 255}), 1);

    DrawTexturePro(txt_outline, (Rectangle){0, 0, text_x, text_y}, (Rectangle){x, y, size, size * height_multiplier}, (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
}
void displayGame()
{
    // Initialization
    bool is_full = false, positive = true;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1330, 720, "@ItayL - Uno");

    SetWindowMinSize(800, 600);
    SetWindowMaxSize(1920, 1080);

    Texture2D uno_texture = LoadTexture("./assets/texture.png");
    Texture2D txt_header = LoadTexture("./assets/white.png");
    Texture2D txt_outline = LoadTexture("./assets/outline.png");

    int width, height;
    Rectangle pre_state;
    unsigned char max_cards = 9;
    int selected = max_cards / 2;
    float lerpSelected = selected;
    bool (*key_pressed)(int) = fixed_key_pressed;
    const double fps = 60;
    SetTargetFPS(fps);
    const float min_size = 70;
    const float max_size = 85;
    const float height_multiplier = 1.54819f;

    /*UNO_RED,
        UNO_BLUE,
        UNO_YELLOW,
        UNO_GREEN
        */

    unsigned char enemy_cards_size = 9;
    unsigned int flagg = FLAG_BORDERLESS_WINDOWED_MODE;

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
        if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT))
        {
            positive = false;
        }
        if (IsKeyPressed(KEY_KP_ADD) || IsKeyPressed(KEY_EQUAL))
        {
            positive = true;
        }
        selected += -(key_pressed(KEY_LEFT) || key_pressed(KEY_A)) + (key_pressed(KEY_RIGHT) || key_pressed(KEY_D));

        const unsigned char adding = num_key_down(1, ONE) + num_key_down(2, TWO) + num_key_down(3, THREE) + num_key_down(4, FOUR) + num_key_down(5, FIVE) + num_key_down(6, SIX) + num_key_down(7, SEVEN) + num_key_down(8, EIGHT) + num_key_down(9, NINE);
        selected += (positive ? 1 : -1) * adding;

        selected = fclamp(selected, 0, max_cards - 1);

        max_cards = clamp(max_cards + key_pressed(KEY_UP) - key_pressed(KEY_DOWN), 0, 30);

        lerpSelected = lerp(lerpSelected, (float)selected, 12.0f / fps);
        // printf("selected: %d | lerpSelected: %f\n", selected, lerpSelected);

        enemy_cards_size = clamp(enemy_cards_size + key_pressed(KEY_W) - key_pressed(KEY_S), 0, 30);

        BeginDrawing();
        ClearBackground((Color){9, 9, 10, 255});

        for (unsigned int index = 0; index < max_cards; index++)
        {
            const float hie = fabs(fclamp((float)index - lerpSelected, -1.0, 1.0));
            const float size = hie * (min_size - max_size) + max_size;

            const float x = width / 2 + index * min_size * 1.2 - size / 2 - lerpSelected * max_size;
            const float y = height - max_size + -size - 10;

            DrawCard(index % 15 + ((index % 4) << 4), hie, x, y, size, height_multiplier, uno_texture, txt_header, txt_outline);
        };
        // DrawRectangleRounded((Rectangle){x, localy, min_size, min_size * 2}, 0.2f, 10, (Color){155, 155, 155, 255});

        // draw bank
        float addon = (lerpSelected - (float)selected) * min_size / 3;
        float x = width / 2 - max_size / 2 + addon;
        float y = height / 2 - max_size;
        DrawRectangleRounded((Rectangle){x, y, max_size, max_size * height_multiplier}, 0.2f, 10, (Color){55, 55, 55, 255});
        x -= 150;

        DrawRectangleRounded((Rectangle){x + 20, y + max_size * 0.2f,
                                         max_size * 0.8f, max_size * 0.7f * height_multiplier},
                             0.2f, 10, (Color){55, 55, 55, 100});
        DrawRectangleRounded((Rectangle){x, y + max_size * 0.1f,
                                         max_size * 0.9f, max_size * 0.9f * height_multiplier},
                             0.2f, 10, (Color){55, 55, 55, 255});

        for (unsigned int index = 0; index < enemy_cards_size; index++)
        {

            const float x = addon + width / 2 - min_size / 2 + index * min_size * 1.2 - (((float)enemy_cards_size - 1) / 2.0f) * max_size;

            const float enemyy = min_size - min_size + 10;
            Color tempColor = (Color){200, 55, 55, 255};

            tempColor.a = 105;

            DrawTexturePro(uno_texture, (Rectangle){0, 0, text_x, text_y}, (Rectangle){x, enemyy, min_size, min_size * height_multiplier}, (Vector2){0, 0}, 0, (Color){120, 120, 120, 250});
        }
        if (IsKeyPressed(KEY_F))
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

        EndDrawing();
    }

    UnloadTexture(uno_texture);
    UnloadTexture(txt_header);
    UnloadTexture(txt_outline);

    CloseWindow(); // Close window and OpenGL context
}
