#pragma once
#include <vector>
#include <array>

using image = std::vector<std::vector<int>>;
using points = std::vector<std::array<int, 2>>;

const points find_line_in_image(const image &img);