#pragma once

#include "circle.hh"
#include "shape.hh"
#include "square.hh"
#include "triangle.hh"

class ShapeManager
{
  public:
    ShapeManager(int x, int y, int width, int height);
    ~ShapeManager();
    Shape *GenerateRandomShape();
    void DrawShape(Shape *shape);
    bool CheckCollisionShape(Shape *shape, Vector2 mousePosition);

  private:
    int width;
    int height;
    int startX;
    int startY;
    ShapeType getRandomShapeType();
};