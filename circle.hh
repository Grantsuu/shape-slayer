#pragma once

#include "shape.hh"

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