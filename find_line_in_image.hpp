#pragma once
#include <vector>
#include <functional>

enum PixelColor
{
    ZERO = 0,
    ONE
};

using Image = std::vector<std::vector<PixelColor>>;
using Point = std::pair<int, int>;
using Points = std::vector<Point>;

enum Edge
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

const Point find_point_in_edge(const Image &img, const Edge edge);

const Points find_line_in_image(const Image &img);

template <
    typename ReturnType,
    typename GetValueFunc,
    typename IndexMapper>
ReturnType search_for_point_in_line(const int length, GetValueFunc getValue, IndexMapper mapIndex);

int search_for_point_in_1d_line(std::vector<PixelColor> line);

float calculate_slope(Point point1, Point point2);
