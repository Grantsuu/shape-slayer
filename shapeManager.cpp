#include "shapeManager.hh"
#include "raylib.h"

ShapeManager::ShapeManager(int x, int y, int width, int height)
{
    startX = x;
    startY = y;
    this->width = width;
    this->height = height;
}

ShapeManager::~ShapeManager()
{
}

ShapeType ShapeManager::getRandomShapeType()
{
    return static_cast<ShapeType>(GetRandomValue(0, 2));
}

Shape* ShapeManager::GenerateRandomShape()
{
    ShapeType type = getRandomShapeType();
    switch (type)
    {
    case ShapeType::kCircle:
        return new Circle(startX, startY, width, height);
    case ShapeType::kSquare:
        return new Square(startX, startY, width, height);
    case ShapeType::kTriangle:
        return new Triangle(startX, startY, width, height);
    default:
        return nullptr;
    }
}

void ShapeManager::DrawShape(Shape *shape)
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

bool ShapeManager::CheckCollisionShape(Shape *shape, Vector2 mousePosition)
{
    switch (shape->type)
    {
    case ShapeType::kCircle:
        return CheckCollisionPointCircle({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)},
                                         static_cast<Circle *>(shape)->focus, static_cast<Circle *>(shape)->radius);
    case ShapeType::kSquare:
        return CheckCollisionPointRec({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)},
                                      {static_cast<Square *>(shape)->position.x,
                                       static_cast<Square *>(shape)->position.y, static_cast<Square *>(shape)->size.x,
                                       static_cast<Square *>(shape)->size.y});
    case ShapeType::kTriangle:
        return CheckCollisionPointTriangle({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)},
                                           static_cast<Triangle *>(shape)->verticies[0],
                                           static_cast<Triangle *>(shape)->verticies[1],
                                           static_cast<Triangle *>(shape)->verticies[2]);
    default:
        return false;
    }
}