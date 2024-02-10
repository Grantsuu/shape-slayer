#include "raylib.h"
#include "shapeManager.hh"
#include <iostream>
#include <vector>

int main()
{
    enum GameState
    {
        kStartMenu,
        kGameModeCountdown,
        kGameModeCountdownEnd,
        num_values
    };

    // Game constants
    // --------------------------------------------------------------------
    const int kScreenWidth = 1200;
    const int kScreenHeight = 800;
    const char *kWindowTitle = "Shape Slayer";
    const int kInfoAreaX = 0;
    const int kInfoAreaY = 100;
    const int kFPS = 60;
    const int kTime = 30;
    const int kScoreColor = 50;
    const int kWarningTime = 5;
    // --------------------------------------------------------------------

    // Game variables
    // --------------------------------------------------------------------
    GameState state = kStartMenu;
    ShapeManager sm = ShapeManager(kInfoAreaX, kInfoAreaY, kScreenWidth, kScreenHeight);
    Shape *shape = sm.GenerateRandomShape();
    int score = 0;
    int framesCounter = 0;
    int time = kTime;
    bool exitWindow = false;
    // --------------------------------------------------------------------

    // Game window initialization
    // --------------------------------------------------------------------
    InitWindow(kScreenWidth, kScreenHeight, kWindowTitle);
    SetTargetFPS(kFPS);
    // --------------------------------------------------------------------

    while (!exitWindow)
    {
        // Exit window
        // --------------------------------------------------------------------
        if (WindowShouldClose())
        {
            exitWindow = true;
        }
        // --------------------------------------------------------------------

        // Timer
        // --------------------------------------------------------------------
        framesCounter++;
        if ((framesCounter / 60) % 2 == 1)
        {
            time--;
            framesCounter = 0;
        }
        // --------------------------------------------------------------------

        // Draw
        // ####################################################################
        BeginDrawing();

        ClearBackground(BLACK);

        // Game screens to draw
        // --------------------------------------------------------------------
        switch (state)
        {
        case kStartMenu: {
            // Start menu constants
            // --------------------------------------------------------------------
            const char *kTitleText = "Welcome to Shape Slayer!";
            const char *kCountdownText = "Play Countdown";
            const char *kExitText = "Exit";
            const int kTitleSize = 80;
            const int kTitleMenuSize = 60;
            const Rectangle kCountdownButton = {
                static_cast<float>(kScreenWidth / 2 - MeasureText(kCountdownText, kTitleMenuSize) / 2),
                static_cast<float>(kScreenHeight / 2 - 50),
                static_cast<float>(MeasureText(kCountdownText, kTitleMenuSize)), static_cast<float>(kTitleMenuSize)};
            const Rectangle kExitButton = {
                static_cast<float>(kScreenWidth / 2 - MeasureText(kExitText, kTitleMenuSize) / 2),
                static_cast<float>(kScreenHeight / 2 + 50), static_cast<float>(MeasureText(kExitText, kTitleMenuSize)),
                static_cast<float>(kTitleMenuSize)};
            // --------------------------------------------------------------------

            // Draw start menu
            // --------------------------------------------------------------------
            DrawText(kTitleText, kScreenWidth / 2 - MeasureText(kTitleText, kTitleSize) / 2, kScreenHeight / 2 - 200,
                     kTitleSize, BEIGE);
            DrawText(kCountdownText, kCountdownButton.x, kCountdownButton.y, kTitleMenuSize, WHITE);
            DrawText(kExitText, kExitButton.x, kExitButton.y, kTitleMenuSize, WHITE);
            // --------------------------------------------------------------------

            // Start menu input
            // --------------------------------------------------------------------
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // Countdown button
                // --------------------------------------------------------------------
                if (CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                           kCountdownButton))
                {
                    state = kGameModeCountdown;
                }
                // --------------------------------------------------------------------

                // Exit button
                // --------------------------------------------------------------------
                if (CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                           kExitButton))
                {
                    exitWindow = true;
                }
                // --------------------------------------------------------------------
            }
            // --------------------------------------------------------------------
            break;
        }
        case kGameModeCountdown: {
            if (time < 1)
            {
                DrawText("Game Over!", kScreenWidth / 2 - 100, kScreenHeight / 2 - 50, 80, WHITE);
                DrawText(TextFormat("Final Score: %i", score), kScreenWidth / 2 - 100, kScreenHeight / 2 + 50, 60,
                         WHITE);
                EndDrawing();
                continue;
            }
            else
            {
                if (shape != nullptr)
                {
                    sm.DrawShape(shape);
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if (sm.CheckCollisionShape(shape,
                                               {static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}))
                    {
                        score++;
                        delete shape;
                        shape = sm.GenerateRandomShape();
                    }
                    else
                    {
                        score--;
                    }
                }

                // Information display
                // --------------------------------------------------------------------
                DrawRectangleRec({0, 0, kScreenWidth, kInfoAreaY}, WHITE);
                Color scoreColor = score >= kScoreColor ? GREEN : BLACK;
                DrawText(TextFormat("Score: %i", score), 10, 10, 80, scoreColor);
                Color timeColor = time <= kWarningTime ? RED : BLACK;
                DrawText(TextFormat("Time: %i", time), 850, 10, 80, timeColor);
                // --------------------------------------------------------------------
            }
            break;
        }
        }
        // --------------------------------------------------------------------

        EndDrawing();
        // ####################################################################
    }

    CloseWindow();

    return 0;
}