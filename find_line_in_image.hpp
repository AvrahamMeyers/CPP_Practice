#pragma once
#include <vector>
#include <array>

using image = std::vector<std::vector<int>>;
using point = std::array<int, 2>;
using points = std::vector<point>;

const point find_point_in_edge();

const points find_line_in_image(const image &img);