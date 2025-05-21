#include <vector>
#include <cstdio>
#include <cstdlib>
#include <array>

#include "find_line_in_image.hpp"
#include <optional>
#include <cstdint>
#include <map>

// ** Type Definitions

const Points find_line_in_image(const Image &img)
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

    std::optional<Point> first_point, second_point;

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
            break;
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

template <
    typename ReturnType,
    typename GetValueFunc,
    typename IndexMapper>
ReturnType search_for_point_in_line(const int length, GetValueFunc getValue, IndexMapper mapIndex)
{
    if (length == 1)
    {
        PixelColor value = getValue(0);
        if (value == PixelColor::ONE)
        {
            return mapIndex(0);
        }
        else
        {
            if constexpr (std::is_same_v<ReturnType, int>)
                return -1;
            else if constexpr (std::is_same_v<ReturnType, std::pair<int, int>>)
                return std::make_pair(-1, -1);
        }
    }

    int left = 0, right = length - 1;

    int left_value = getValue(left);
    int right_value = getValue(right);

    while (left < right - 1)
    {
        int mid = (left + right) / 2;
        int mid_value = getValue(mid);

        if (mid_value == left_value)
        {
            left = mid;
            left_value = mid_value;
        }
        else
        {
            right = mid;
            right_value = mid_value;
        }
    }

    if (left_value == PixelColor::ONE)
    {
        return mapIndex(left);
    }
    else
        return mapIndex(right);
}

int search_for_point_in_1d_line(std::vector<PixelColor> line)
{

    auto getValue = [&](int i)
    { return line[i]; };
    auto mapIndex = [&](int i)
    { return i; };

    return search_for_point_in_line<int>(line.size(), getValue, mapIndex);
}

const Point find_point_in_edge(const Image &img, Edge edge)
{
    switch (edge)
    {
    case Edge::TOP:
    {
        int length = img[0].size();
        auto getValue = [&](int i)
        { return img[0][i]; };
        auto mapIndex = [&](int i)
        { return std::make_pair(0, i); };
        return search_for_point_in_line<Point>(length, getValue, mapIndex);
    }
    case Edge::BOTTOM:
    {
        int length = img[0].size();
        auto getValue = [&](int i)
        { return img[img.size() - 1][i]; };
        auto mapIndex = [&](int i)
        { return std::make_pair(img.size() - 1, i); };
        return search_for_point_in_line<Point>(length, getValue, mapIndex);
    }
    case Edge::LEFT:
    {
        int length = img.size();
        auto getValue = [&](int i)
        { return img[i][0]; };
        auto mapIndex = [&](int i)
        { return std::make_pair(i, 0); };
        return search_for_point_in_line<Point>(length, getValue, mapIndex);
    }
    case Edge::RIGHT:
    {
        int length = img.size();
        auto getValue = [&](int i)
        { return img[i][img[0].size() - 1]; };
        auto mapIndex = [&](int i)
        { return std::make_pair(i, img[0].size() - 1); };
        return search_for_point_in_line<Point>(length, getValue, mapIndex);
    }
    }
}
