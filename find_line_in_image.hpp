#pragma once
#include <vector>
#include <functional>

enum PixelColor
{
    ZERO = 0,
    ONE
};

using image = std::vector<std::vector<PixelColor>>;
using Point = std::pair<int, int>;
using Points = std::vector<Point>;

enum Edge
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

const Point find_point_in_edge(const image &img, const Edge edge);

const Points find_line_in_image(const image &img);

template <
    typename ReturnType,
    typename GetValueFunc,
    typename IndexMapper>
ReturnType search_for_point_in_line(const int length, GetValueFunc getValue, IndexMapper mapIndex);