#include "raylib.h"
#include <iostream>

class Shape {
    public:
        float size;
        Vector2 position;
        Color color;
};

Shape initializeShape(int screenWidth, int screenHeight) {
    TraceLog(LOG_INFO, "Making new shape...");
    Shape shape;

    float size = static_cast<float>(GetRandomValue(100, 200));
    shape.size = size;
    TraceLog(LOG_INFO, "Shape Size: %f", size);

    float shapeX = static_cast<float>(GetRandomValue(0 + size, screenWidth - size));
    TraceLog(LOG_INFO, "Shape X: %f", shapeX);

    float shapeY = static_cast<float>(GetRandomValue(0 + size, screenHeight - size));
    TraceLog(LOG_INFO, "Shape Y: %f", shapeY);

    shape.position = {shapeX, shapeY};

    Color colors[5] = {WHITE, YELLOW, BLUE, RED, GREEN};
    int randomColor = GetRandomValue(0, sizeof(colors)/sizeof(Color)-1);
    shape.color = colors[randomColor];
    TraceLog(LOG_INFO, "Color: %x", colors[randomColor]);

    return shape;
}

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Circle Clicker");

    SetTargetFPS(60);

    Shape shape = initializeShape(screenWidth, screenHeight);
    
    int score = 0;

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(BLACK);

        DrawCircleV(shape.position, shape.size, shape.color);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, shape.position, shape.size)) {
                TraceLog(LOG_INFO, "Clicked in circle!");
                score++;
                shape = initializeShape(screenWidth, screenHeight);
            }
        }

        DrawText("Click the circle!", 10, 10, 80, WHITE);
        DrawText(TextFormat("Score: %i", score), 10, 80, 60, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}