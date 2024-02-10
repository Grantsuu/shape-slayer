#include "raylib.h"
#include "shape.h"
#include <iostream>
#include <vector>

class Circle : public Shape
{
  public:
    float radius;
    Vector2 focus; // center point
    Circle(int x, int y, int screenWidth, int screenHeight) : Shape()
    {
        type = ShapeType::kCircle;
        radius = static_cast<float>(GetRandomValue(minSize, maxSize / 2));
        focus = {static_cast<float>(GetRandomValue(0 + radius + x, screenWidth - radius)),
                 static_cast<float>(GetRandomValue(0 + radius + y, screenHeight - radius))};
    }
};

class Square : public Shape
{
  public:
    Vector2 size;
    Vector2 position; // top left corner
    Square(int x, int y, int screenWidth, int screenHeight) : Shape()
    {
        type = ShapeType::kSquare;
        float length = static_cast<float>(GetRandomValue(minSize, maxSize));
        size = {length, length};
        position = {static_cast<float>(GetRandomValue(0 + x, screenWidth - length)),
                    static_cast<float>(GetRandomValue(0 + y, screenHeight - length))};
    }
};

class Triangle : public Shape
{
  public:
    std::vector<Vector2> verticies; // top, bottom left, bottom right
    Triangle(int x, int y, int screenWidth, int screenHeight) : Shape()
    {
        type = ShapeType::kTriangle;
        float length = static_cast<float>(GetRandomValue(minSize, maxSize));
        Vector2 initialVertex = {static_cast<float>(GetRandomValue(0 + length / 2 + x, screenWidth - length / 2)),
                                 static_cast<float>(GetRandomValue(0 + y, screenHeight - length))};
        verticies.push_back(initialVertex);
        verticies.push_back({initialVertex.x - length / 2, initialVertex.y + length});
        verticies.push_back({initialVertex.x + length / 2, initialVertex.y + length});
    }
};

ShapeType getRandomShapeType()
{
    return static_cast<ShapeType>(GetRandomValue(0, static_cast<int>(ShapeType::num_values) - 1));
}

Shape *generateRandomShape(int x, int y, int screenWidth, int screenHeight)
{
    ShapeType type = getRandomShapeType();
    switch (type)
    {
    case ShapeType::kCircle:
        return new Circle(x, y, screenWidth, screenHeight);
    case ShapeType::kSquare:
        return new Square(x, y, screenWidth, screenHeight);
    case ShapeType::kTriangle:
        return new Triangle(x, y, screenWidth, screenHeight);
    default:
        return nullptr;
    }
}

void DrawShape(Shape *shape)
{
    switch (shape->type)
    {
    case ShapeType::kCircle:
        DrawCircleV(static_cast<Circle *>(shape)->focus, static_cast<Circle *>(shape)->radius, shape->color);
        break;
    case ShapeType::kSquare:
        DrawRectangleV(static_cast<Square *>(shape)->position, static_cast<Square *>(shape)->size, shape->color);
        break;
    case ShapeType::kTriangle:
        DrawTriangle(static_cast<Triangle *>(shape)->verticies[0], static_cast<Triangle *>(shape)->verticies[1],
                     static_cast<Triangle *>(shape)->verticies[2], shape->color);
        break;
    default:
        break;
    }
}

bool CheckCollisionShape(Shape *shape)
{
    switch (shape->type)
    {
    case ShapeType::kCircle:
        return CheckCollisionPointCircle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                         static_cast<Circle *>(shape)->focus, static_cast<Circle *>(shape)->radius);
    case ShapeType::kSquare:
        return CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                      {static_cast<Square *>(shape)->position.x,
                                       static_cast<Square *>(shape)->position.y, static_cast<Square *>(shape)->size.x,
                                       static_cast<Square *>(shape)->size.y});
    case ShapeType::kTriangle:
        return CheckCollisionPointTriangle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())},
                                           static_cast<Triangle *>(shape)->verticies[0],
                                           static_cast<Triangle *>(shape)->verticies[1],
                                           static_cast<Triangle *>(shape)->verticies[2]);
    default:
        return false;
    }
}

int main()
{
    // Game constants
    // --------------------------------------------------------------------
    const int kScreenWidth = 1200;
    const int kScreenHeight = 800;
    const int kInfoAreaX = 0;
    const int kInfoAreaY = 100;
    const int kFPS = 60;
    const int kTime = 30;
    const int kScoreColor = 50;
    const int kWarningTime = 5;
    // --------------------------------------------------------------------

    // Game variables
    // --------------------------------------------------------------------
    Shape *shape = generateRandomShape(kInfoAreaX, kInfoAreaY, kScreenWidth, kScreenHeight);
    int score = 0;
    int framesCounter = 0;
    int time = kTime;
    bool exitWindow = false;
    // --------------------------------------------------------------------

    // Game window initialization
    // --------------------------------------------------------------------
    InitWindow(kScreenWidth, kScreenHeight, "Shape Slayer");
    SetTargetFPS(kFPS);
    // --------------------------------------------------------------------

    while (!exitWindow)
    {
        // Exit window
        // --------------------------------------------------------------------
        if (WindowShouldClose() || IsKeyPressed(KEY_SPACE))
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

        if (time < 1)
        {
            DrawText("Game Over!", kScreenWidth / 2 - 100, kScreenHeight / 2 - 50, 80, WHITE);
            DrawText(TextFormat("Final Score: %i", score), kScreenWidth / 2 - 100, kScreenHeight / 2 + 50, 60, WHITE);
            EndDrawing();
            continue;
        }
        else
        {
            if (shape != nullptr)
            {
                DrawShape(shape);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionShape(shape))
                {
                    score++;
                    delete shape;
                    shape = generateRandomShape(kInfoAreaX, kInfoAreaY, kScreenWidth, kScreenHeight);
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
            DrawText(TextFormat("Time: %i", time), 900, 10, 80, timeColor);
            // --------------------------------------------------------------------
        }

        EndDrawing();
        // ####################################################################
    }

    CloseWindow();

    return 0;
}