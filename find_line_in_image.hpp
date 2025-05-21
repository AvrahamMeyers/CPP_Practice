#pragma once
#include <vector>
#include <functional>

using image = std::vector<std::vector<int>>;
using point = std::pair<int, int>;
using points = std::vector<point>;

enum PixelColors
{
    ZERO = 0,
    ONE
};

enum Edge
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

const point find_point_in_edge(const image &img, const Edge edge);

const points find_line_in_image(const image &img);

const point search_for_point_in_line(const image &img, const int length, std::function<point(int)> mapIndex);