#pragma once
#include <vector>
#include <functional>
#include <map>
#include <cstdint>

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

/**
 * @brief Finds a point in the edge of an image
 *
 * This function checks the specified edge of the image
 * and finds the first point where the color changes
 * from ONE to ZERO.
 *
 * The function uses a generic approach to search
 * for the point in the line.
 *
 * @param img The image to check.
 * @param edge The edge to check (TOP, BOTTOM, LEFT, RIGHT).
 * @return The point in the edge where the color changes.
 *
 * @throws invalid_argument: if the edge is not valid.
 */
Point find_point_in_edge(const Image &img, Edge edge);

/**
 * @brief Finds the line in an image
 *
 * This function checks if the corners of the image are of the same color.
 * If they are, it returns a default point (-1, -1).
 * Otherwise, it generates flags for edges and finds points in the image.
 *
 * @param img The image to check.
 * @return A vector of points representing the line in the image.
 */
Points find_line_in_image(const Image &img);

/**
 * @brief Searches a 1D sequence for the crossing point from ONEs to ZEROs
 *
 * Iterates over a line (1D range of indices) of a given length,
 * using the provided `getValue` function to evaluate each point and
 * `mapIndex` to translate logical indices to physical or transformed indices.
 *
 * The function is generic over the return type and the logic used to access
 * and interpret each point in the line.
 *
 * @tparam ReturnType The return type of the function (e.g., int or Point (std::pair<int, int>)).
 * @tparam GetValueFunc A callable that takes an integer index and returns the value at that logical index.
 * @tparam IndexMapper A callable that maps logical indices (0 to length-1) to actual indices of the underlying data structure.
 *
 * @param length The number of elements to search through.
 * @param getValue A function or lambda that takes an index and returns the value at that index.
 * @param mapIndex A function or lambda that maps a logical index to the actual data index.
 *
 * @return ReturnType The index of the first ONE next to a ZERO in the line.
 *
 * @throws invalid_argument: if length == 0.
 */
template <
    typename ReturnType,
    typename GetValueFunc,
    typename IndexMapper>
ReturnType search_for_point_in_line(int length, GetValueFunc getValue, IndexMapper mapIndex);

/**
 * @brief Searches a 1D line for the crossing point from ONEs to ZEROs.
 *
 * This function is a specialized version of search_for_point_in_line
 * for a 1D line of PixelColor values.
 *
 * @param line The line to search through.
 * @return The index of the first ONE next to a ZERO in the line.
 *
 * @throws invalid_argument: if the vector is empty.
 */
int search_for_point_in_1d_line(std::vector<PixelColor> line);

/**
 * @brief Calculates the slope between two points.
 *
 * @param point1 The first point.
 * @param point2 The second point.
 * @return The slope between the two points.
 *
 * @throws invalid_argument: if the line is vertical (undefined slope).
 */
float calculate_slope(Point point1, Point point2);

/**
 * @brief Checks if all corners of the image are of the same color.
 *
 * @param img The image to check.
 * @return true if all corners are of the same color, false otherwise.
 */
bool check_all_corners_for_identical_color(const Image &img);

/**
 * @brief Generates flags for edges based on the image.
 *
 * @param img The image to check.
 * @return A map of edges to flags (0 or 1).
 */
std::map<Edge, uint8_t> generate_flags_for_edges(const Image &img);

/**
 * @brief Displays the line function and point.
 *
 * @param point The point to display.
 * @param slope The slope of the line.
 */
void display_line_function(const Point &point, float slope);