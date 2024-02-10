#include <raylib.h>
#include <vector>

enum class ShapeType
{
    kCircle = 0,
    kSquare = 1,
    kTriangle = 2,
    num_values
};

class Shape
{
    const int kMinSize = 125;
    const int kMaxSize = 200;
    const std::vector<Color> kPossibleColors = {WHITE, YELLOW, BLUE,  RED,     GREEN, PURPLE, PINK,      ORANGE,
                                                GOLD,  LIME,   BEIGE, SKYBLUE, GRAY,  MAROON, LIGHTGRAY, MAGENTA};

  public:
    std::vector<Color> colors;
    ShapeType type;
    Color color;
    int minSize;
    int maxSize;
    Shape() : colors(kPossibleColors), minSize(kMinSize), maxSize(kMaxSize)
    {
        int randomColor = GetRandomValue(0, colors.size() - 1);
        color = colors[randomColor];
    };
};