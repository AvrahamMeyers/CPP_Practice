#include <vector>
#include <cstdio>
#include <cstdlib>
#include <array>

#include "find_line_in_image.hpp"
#include <optional>
#include <cstdint>
#include <map>

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

    std::map<Edge, uint8_t> flags = {
        {Edge::TOP, 0},
        {Edge::LEFT, 0},
        {Edge::RIGHT, 0},
        {Edge::BOTTOM, 0}};

    const std::map<Edge, std::array<int, 2>> edges_to_corners = {
        {Edge::TOP, {top_left, top_right}},
        {Edge::LEFT, {top_left, bottom_left}},
        {Edge::RIGHT, {top_right, bottom_right}},
        {Edge::BOTTOM, {bottom_left, bottom_right}}};

    for (auto &[edge, corner] : edges_to_corners)
    {
        if (corner[0] != corner[1])
        {
            flags[edge] = 1;
        }
    }

    std::optional<std::array<int, 2>> first_point, second_point;

    for (auto &[edge, flag] : flags)
    {
        if (!flag)
            continue;

        auto point = find_point_in_edge(img, edge);

        if (!first_point.has_value())
        {
            first_point = point;
        }
        else if (!second_point.has_value())
        {
            second_point = point;
        }
        else
        {
            break; // Stop after the two points are found
        }
    }

    if (first_point && second_point)
    {
        return (first_point == second_point) ? std::vector{*first_point} : std::vector{*first_point, *second_point};
    }
    else if (first_point)
    {
        return std::vector{*first_point};
    }
    else
    {
        return {};
    }
}

const point find_point_in_edge(const image &image, Edge edge)
{
}
