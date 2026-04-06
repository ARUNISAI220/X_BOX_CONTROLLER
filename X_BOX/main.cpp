#include "raylib.h"

// Gamepad aliases
#define XBOX_ALIAS_1 "xbox"
#define XBOX_ALIAS_2 "x-box"
#define PS_ALIAS_1   "playstation"
#define PS_ALIAS_2   "sony"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input gamepad");

    Texture2D texPs3Pad = LoadTexture("resources/ps3.png");
    Texture2D texXboxPad = LoadTexture("resources/xbox.png");

    const float leftStickDeadzoneX = 0.1f;
    const float leftStickDeadzoneY = 0.1f;
    const float rightStickDeadzoneX = 0.1f;
    const float rightStickDeadzoneY = 0.1f;
    const float leftTriggerDeadzone = -0.9f;
    const float rightTriggerDeadzone = -0.9f;

    Rectangle vibrateButton{};

    SetTargetFPS(60);

    int gamepad = 0;

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_LEFT) && gamepad > 0) gamepad--;
        if (IsKeyPressed(KEY_RIGHT)) gamepad++;

        Vector2 mousePosition = GetMousePosition();

        vibrateButton = Rectangle{ 10, 70.0f + 20 * GetGamepadAxisCount(gamepad) + 20, 75, 24 };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(mousePosition, vibrateButton))
        {
            SetGamepadVibration(gamepad, 1.0f, 1.0f, 1.0f);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsGamepadAvailable(gamepad))
        {
            DrawText(TextFormat("GP%d: %s", gamepad, GetGamepadName(gamepad)), 10, 10, 10, BLACK);

            float leftStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
            float leftStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
            float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
            float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
            float leftTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
            float rightTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);

            // Deadzones
            if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
            if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;
            if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX) rightStickX = 0.0f;
            if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY) rightStickY = 0.0f;
            if (leftTrigger < leftTriggerDeadzone) leftTrigger = -1.0f;
            if (rightTrigger < rightTriggerDeadzone) rightTrigger = -1.0f;

            // Detect controller type
            const char* name = GetGamepadName(gamepad);

            if ((TextFindIndex(TextToLower(name), XBOX_ALIAS_1) > -1) ||
                (TextFindIndex(TextToLower(name), XBOX_ALIAS_2) > -1))
            {
                DrawTexture(texXboxPad, 0, 0, DARKGRAY);

                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) DrawCircle(394, 89, 19, RED);

                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) DrawCircle(436, 150, 9, ORANGE);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) DrawCircle(352, 150, 9, PURPLE);

                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) DrawCircle(501, 151, 15, BLUE);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) DrawCircle(536, 187, 15, LIME);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) DrawCircle(572, 151, 15, MAROON);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) DrawCircle(536, 115, 15, GOLD);

                DrawRectangle(317, 202, 19, 71, BLACK);
                DrawRectangle(293, 228, 69, 19, BLACK);

                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) DrawRectangle(317, 202, 19, 26, RED);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) DrawRectangle(317, 247, 19, 26, RED);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) DrawRectangle(292, 228, 25, 19, RED);
                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) DrawRectangle(336, 228, 26, 19, RED);

                // Joysticks
                DrawCircle(259, 152, 34, LIGHTGRAY);
                DrawCircle(259 + (int)(leftStickX * 20), 152 + (int)(leftStickY * 20), 25, RED);

                DrawCircle(461, 237, 33, LIGHTGRAY);
                DrawCircle(461 + (int)(rightStickX * 20), 237 + (int)(rightStickY * 20), 25, RED);
            }
            else
            {
                DrawRectangleRounded(Rectangle{ 175,110,460,220 }, 0.3f, 16, DARKGRAY);

                DrawCircle(345 + (int)(leftStickX * 20), 260 + (int)(leftStickY * 20), 25, RED);
                DrawCircle(465 + (int)(rightStickX * 20), 260 + (int)(rightStickY * 20), 25, RED);

                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE))
                    DrawCircle(405, 170, 10, GREEN);

                if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP))
                    DrawCircle(551, 155, 15, RED);
            }

            DrawText(TextFormat("AXIS COUNT: %i", GetGamepadAxisCount(gamepad)), 10, 50, 10, MAROON);

            for (int i = 0; i < GetGamepadAxisCount(gamepad); i++)
            {
                DrawText(TextFormat("AXIS %i: %.02f", i, GetGamepadAxisMovement(gamepad, i)),
                    20, 70 + 20 * i, 10, DARKGRAY);
            }

            DrawRectangleRec(vibrateButton, SKYBLUE);
            DrawText("VIBRATE", (int)vibrateButton.x + 10, (int)vibrateButton.y + 5, 10, BLACK);

            if (GetGamepadButtonPressed() != GAMEPAD_BUTTON_UNKNOWN)
                DrawText(TextFormat("BUTTON: %i", GetGamepadButtonPressed()), 10, 430, 10, RED);
        }
        else
        {
            DrawText("GAMEPAD NOT DETECTED", 10, 10, 20, GRAY);
        }

        EndDrawing();
    }

    UnloadTexture(texPs3Pad);
    UnloadTexture(texXboxPad);

    CloseWindow();

    return 0;
}