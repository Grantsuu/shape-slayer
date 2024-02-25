#pragma once

#include "shape.hh"

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