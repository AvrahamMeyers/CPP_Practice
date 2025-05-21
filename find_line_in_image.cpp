#include <vector>
#include <cstdio>
#include <cstdlib>
#include <array>

#include "find_line_in_image.hpp"
#include <optional>

// ** Type Definitions

const

    const points
    find_line_in_image(const image &img)
{
    int length = img.size();
    int width = img[0].size();

    int top_left = img[0][0];
    int top_right = img[0][width - 1];
    int bottom_left = img[length - 1][0];
    int bottom_right = img[length - 1][width - 1];

    if (((top_left + top_right + bottom_left + bottom_right) % 4) == 0)
    {
        return {{-1, -1}};
    }

    // six options for how the line can cross the image
    // vertically
    // horizontally
    // high forward diagonal
    // low forward diagonal
    // high backward diagonal
    // low backward diagonal

    // need to find the two sides whose corners differ in color

    std::optional<std::array<int, 2>> first_point, second_point;

    if (top_left != top_right)
    {
        first_point = find_point_in_edge(img, Edge::TOP);
    }

    // default
    return {{1, 1}};
}

const point find_point_in_edge(const image &image, Edge edge)
{
}
