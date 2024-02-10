#include "raylib.h"
#include <iostream>
#include <vector>

enum class ShapeType {
    kCircle = 0,
    kSquare = 1,
    kTriangle = 2,
    num_values
};

class Shape {
    const int kMinSize = 100;
    const int kMaxSize = 200;
    const std::vector<Color> kPossibleColors = {WHITE, YELLOW, BLUE, RED, GREEN};
    public:
        std::vector<Color> colors;
        ShapeType type;
        Color color;
        int minSize;
        int maxSize;
        Shape() : colors(kPossibleColors), minSize(kMinSize), maxSize(kMaxSize) {};
};

class Circle : public Shape {
    public:
        float radius;
        Vector2 focus; // center point
        Circle(int screenWidth, int screenHeight) : Shape() {
            type = ShapeType::kCircle;
            radius = static_cast<float>(GetRandomValue(minSize, maxSize));
            focus = {static_cast<float>(GetRandomValue(0 + radius, screenWidth - radius)), static_cast<float>(GetRandomValue(0 + radius, screenHeight - radius))};
            int randomColor = GetRandomValue(0, colors.size()-1);
            color = colors[randomColor];
        }
};

class Square : public Shape {
    public:
        Vector2 size;
        Vector2 position; // top left corner
        Square(int screenWidth, int screenHeight) : Shape() {
            type = ShapeType::kSquare;
            float length = static_cast<float>(GetRandomValue(minSize, maxSize));
            size = {length, length};
            position = {static_cast<float>(GetRandomValue(0, screenWidth - length)), static_cast<float>(GetRandomValue(0, screenHeight - length))};
            int randomColor = GetRandomValue(0, colors.size()-1);
            color = colors[randomColor];
        }
};

class Triangle : public Shape {
    public:
        std::vector<Vector2> verticies; // top, bottom left, bottom right
        Triangle(int screenWidth, int screenHeight) : Shape() {
            type = ShapeType::kTriangle;
            float length = static_cast<float>(GetRandomValue(minSize, maxSize));
            Vector2 initialVertex = {
                static_cast<float>(GetRandomValue(0 + length/2, screenWidth - length/2)),
                static_cast<float>(GetRandomValue(0, screenHeight - length))
            };
            verticies.push_back(initialVertex);
            verticies.push_back({initialVertex.x - length/2, initialVertex.y + length});
            verticies.push_back({initialVertex.x + length/2, initialVertex.y + length});
            int randomColor = GetRandomValue(0, colors.size()-1);
            color = colors[randomColor];
        }
};

ShapeType getRandomShapeType() {
    return static_cast<ShapeType>(GetRandomValue(0, static_cast<int>(ShapeType::num_values)-1));
}

Shape* generateRandomShape(int screenWidth, int screenHeight) {
    ShapeType type = getRandomShapeType();
    switch (type) {
        case ShapeType::kCircle:
            return new Circle(screenWidth, screenHeight);
        case ShapeType::kSquare:
            return new Square(screenWidth, screenHeight);
        case ShapeType::kTriangle:
            return new Triangle(screenWidth, screenHeight);
        default:
            return nullptr;
    }
}

void DrawShape(Shape* shape) {
    switch (shape->type) {
        case ShapeType::kCircle:
            DrawCircleV(static_cast<Circle*>(shape)->focus, static_cast<Circle*>(shape)->radius, shape->color);
            break;
        case ShapeType::kSquare:
            DrawRectangleV(static_cast<Square*>(shape)->position, static_cast<Square*>(shape)->size, shape->color);
            break;
        case ShapeType::kTriangle:
            DrawTriangle(static_cast<Triangle*>(shape)->verticies[0], static_cast<Triangle*>(shape)->verticies[1], static_cast<Triangle*>(shape)->verticies[2], shape->color);
            break;
        default:
            break;
    }
}

bool CheckCollisionShape(Shape* shape) {
    switch (shape->type) {
        case ShapeType::kCircle:
            return CheckCollisionPointCircle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, static_cast<Circle*>(shape)->focus, static_cast<Circle*>(shape)->radius);
        case ShapeType::kSquare:
            return CheckCollisionPointRec({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, {static_cast<Square*>(shape)->position.x, static_cast<Square*>(shape)->position.y, static_cast<Square*>(shape)->size.x, static_cast<Square*>(shape)->size.y});
        case ShapeType::kTriangle:
            return CheckCollisionPointTriangle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, static_cast<Triangle*>(shape)->verticies[0], static_cast<Triangle*>(shape)->verticies[1], static_cast<Triangle*>(shape)->verticies[2]);
        default:
            return false;
    }
}

int main()
{
    const int kScreenWidth = 1200;
    const int kScreenHeight = 800;

    InitWindow(kScreenWidth, kScreenHeight, "Shape Slayer");

    SetTargetFPS(60);

    Shape* shape = generateRandomShape(kScreenWidth, kScreenHeight);
    
    int score = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        
        if (IsKeyPressed(KEY_SPACE)) {
            delete shape;
            shape = generateRandomShape(kScreenWidth, kScreenHeight);
        }

        if (shape != nullptr) {
            DrawShape(shape);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionShape(shape)) {
                score++;
                delete shape;
                shape = generateRandomShape(kScreenWidth, kScreenHeight);
            }
            // if (CheckCollisionPointCircle({static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}, shape.position, shape.size)) {
            //     TraceLog(LOG_INFO, "Clicked in circle!");
            //     score++;
            //     shape = initializeShape(kScreenWidth, kScreenHeight);
            // }
        }

        DrawText("Click to slay the shape!", 10, 10, 80, WHITE);
        DrawText(TextFormat("Score: %i", score), 10, 80, 60, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}