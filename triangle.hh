#pragma once

#include "shape.hh"

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