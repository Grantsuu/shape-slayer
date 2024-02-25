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
    const int kStartTime = 30;
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
    int time = kStartTime;
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
                    time = kStartTime;
                    framesCounter = 0;
                    state = kGameModeCountdown;
                    score = 0;
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
                state = kGameModeCountdownEnd;
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
        case kGameModeCountdownEnd: {
            const char *kGameOverText = "Game Over!";
            const char *kFinalScoreText = TextFormat("Final Score: %i", score);
            const char *kRestartText = "Restart";
            const char *kBackToTitleText = "Back to Title";
            const char *kExitText = "Exit";

            const int kGameOverSize = 80;
            const int kFinalScoreSize = 70;
            const int kEndMenuSize = 60;

            const Rectangle kRestartButton = {
                static_cast<float>(kScreenWidth / 2 - MeasureText(kRestartText, kEndMenuSize) / 2),
                static_cast<float>(kScreenHeight / 2 + 50), static_cast<float>(MeasureText(kRestartText, kEndMenuSize)),
                static_cast<float>(kEndMenuSize)};

            const Rectangle kBackToTitleButton = {
                static_cast<float>(kScreenWidth / 2 - MeasureText(kBackToTitleText, kEndMenuSize) / 2),
                static_cast<float>(kScreenHeight / 2 + 150), static_cast<float>(MeasureText(kBackToTitleText, kEndMenuSize)),
                static_cast<float>(kEndMenuSize)};

            const Rectangle kExitButton = {
                static_cast<float>(kScreenWidth / 2 - MeasureText(kExitText, kEndMenuSize) / 2),
                static_cast<float>(kScreenHeight / 2 + 250), static_cast<float>(MeasureText(kExitText, kEndMenuSize)),
                static_cast<float>(kEndMenuSize)};

            DrawText(kGameOverText, kScreenWidth / 2 - MeasureText(kGameOverText, kGameOverSize) / 2,
                     kScreenHeight / 2 - 200, kGameOverSize, WHITE);
            DrawText(kFinalScoreText, kScreenWidth / 2 - MeasureText(kFinalScoreText, kFinalScoreSize) / 2,
                     kScreenHeight / 2 + -100, kFinalScoreSize, WHITE);
            DrawText(kRestartText, kRestartButton.x, kRestartButton.y, kEndMenuSize, WHITE);
            DrawText(kBackToTitleText, kBackToTitleButton.x, kBackToTitleButton.y, kEndMenuSize, WHITE);
            DrawText(kExitText, kExitButton.x, kExitButton.y, kEndMenuSize, WHITE);

            // Start menu input
            // --------------------------------------------------------------------
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                // Countdown button
                // --------------------------------------------------------------------
                if (CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                           kRestartButton))
                {
                    time = kStartTime;
                    framesCounter = 0;
                    state = kGameModeCountdown;
                    score = 0;
                }
                // --------------------------------------------------------------------

                // Back to title button
                // --------------------------------------------------------------------
                if (CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                           kBackToTitleButton))
                {
                    state = kStartMenu;
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
        }
        // --------------------------------------------------------------------

        EndDrawing();
        // ####################################################################
    }

    CloseWindow();

    return 0;
}