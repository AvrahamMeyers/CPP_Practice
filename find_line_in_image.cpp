#include <vector>
#include <cstdio>
#include <cstdlib>
#include <array>
#include <optional>
#include <cstdint>
#include <map>
#include "find_line_in_image.hpp"
#include <stdexcept>

Points find_line_in_image(const Image &img)
{
    // check if the corners all are the same color
    if (check_all_corners_for_identical_color(img))
    {
        return {{-1, -1}};
    }

    std::map<Edge, uint8_t> flags = generate_flags_for_edges(img);

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
        { // both points found
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
ReturnType search_for_point_in_line(int length, GetValueFunc getValue, IndexMapper mapIndex)
{
    if (length == 0)
    {
        throw std::invalid_argument("length of line is 0");
    }

    if (length == 1)
    {
        PixelColor value = getValue(0);
        if (value == PixelColor::ONE)
        {
            return mapIndex(0);
        }
        else
        { // line has a single element in it, the value zero
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
    if (line.size() == 0)
    {
        throw std::invalid_argument("vector is empty");
    }

    auto getValue = [&](int i)
    { return line[i]; };
    auto mapIndex = [&](int i)
    { return i; };

    return search_for_point_in_line<int>(line.size(), getValue, mapIndex);
}

float calculate_slope(Point point1, Point point2)
{
    int run = point1.first - point2.first;

    // check if the line is vertical
    if (run == 0)
    {
        throw std::invalid_argument("line is vertical, slope is undefined");
    }

    int rise = point1.second - point2.second;

    if (rise == 0)
    {
        return 0.0f;
    }

    return static_cast<float>(rise / run);
}

bool check_all_corners_for_identical_color(const Image &img)
{
    int length = img.size();
    int width = img[0].size();

    int top_left = img[0][0];
    int top_right = img[0][width - 1];
    int bottom_left = img[length - 1][0];
    int bottom_right = img[length - 1][width - 1];

    // check if the corners all are the same color
    // the sum of the corners is either 0,1,2,3,4
    // if the corners are all zero, then the sum is 0, if 1 then the sum is 4
    // 0 % 4 and 4 % 4 both equal 0
    // 1 % 4 = 1, 2 % 4 = 2, 3 % 4 = 3
    if (((top_left + top_right + bottom_left + bottom_right) % 4) == 0)
    {
        return true;
    }
    return false;
}

std::map<Edge, uint8_t> generate_flags_for_edges(const Image &img)
{
    int length = img.size();
    int width = img[0].size();

    int top_left = img[0][0];
    int top_right = img[0][width - 1];
    int bottom_left = img[length - 1][0];
    int bottom_right = img[length - 1][width - 1];

    // find the two sides whose corners differ in color

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

    // determining which edges contain the line
    // calculated by checking if the two corners of the edge
    // differ in color
    for (auto &[edge, corners] : edges_to_corners)
    {
        if (corners[0] != corners[1])
        {
            flags[edge] = 1;
        }
    }

    return flags;
}

Point find_point_in_edge(const Image &img, Edge edge)
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
    default:
    {
        throw std::invalid_argument("no edge provided");
    }
    }
}
