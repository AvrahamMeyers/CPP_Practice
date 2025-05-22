#include <gtest/gtest.h>

using namespace ::testing;

#include "../find_line_in_image.hpp"

// TEST(SanityCheck, AlwaysFails)
// {
//     EXPECT_EQ(true, false);
// }

/** Type Definitions
 * using image = std::vector<std::vector<int>>;
 * using points = std::vector<std::array<int, 2>>;
 */

struct Tests : public ::testing::Test
{
    // images

    // Edge cases:
    // image has 1 pixel
    const Image one_pixel_1 = {{PixelColor::ONE}};
    const Image one_pixel_0 = {{PixelColor::ZERO}};

    // image is a single row
    const Image single_row = {{PixelColor::ONE, PixelColor::ZERO}};

    // image is a single column
    const Image single_col = {
        {PixelColor::ONE},
        {PixelColor::ZERO}};

    const Image all_1s = {
        {PixelColor::ONE, PixelColor::ONE},
        {PixelColor::ONE, PixelColor::ONE}};
    const Image all_0s = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ZERO}};

    const Image verticalLeftImage = {
        {PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ZERO}};

    const Image verticalRightImage = {
        {PixelColor::ZERO, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ONE}};

    const Image horizontalTopImage = {
        {PixelColor::ONE, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ZERO}};

    const Image horizontalBottomImage = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ONE}};

    const Image diagonalTopLeftImage = {
        {PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ZERO}};
    const Image diagonalTopRightImage = {
        {PixelColor::ZERO, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ZERO}};
    const Image diagonalBottomLeftImage = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ZERO}};
    const Image diagonalBottomRightImage = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ONE}};
    const Image verticalLargeImage = {
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ZERO}};
    const Image horizontalLargeImage = {
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ONE},
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ZERO, PixelColor::ZERO}};
    const Image largeImage = {
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ONE, PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ZERO, PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ZERO, PixelColor::ZERO, PixelColor::ZERO}};

    // points
    const Points default_point = {{-1, -1}};

    const Points verticalLeftPoints = {
        {0, 0}, {1, 0}};

    const Points verticalRightPoints = {
        {0, 1}, {1, 1}};

    const Points horizontalTopPoints = {
        {0, 0}, {0, 1}};

    const Points horizontalBottomPoints = {
        {1, 0}, {1, 1}};

    const Points diagonalTopLeftPoints = {
        {0, 0}};
    const Points diagonalTopRightPoints = {
        {0, 1}};
    const Points diagonalBottomLeftPoints = {
        {1, 0}};
    const Points diagonalBottomRightPoints = {
        {1, 1}};

    const Points verticalLargePoints = {
        {0, 1}, {2, 1}};

    const Points horizontalLargePoints = {
        {1, 0}, {1, 2}};

    const Points largePoints = {
        {0, 2}, {2, 0}};
};

TEST_F(Tests, LineEquationInImageTest)
{
    // image is entirely one color
    EXPECT_EQ(default_point, find_line_in_image(all_0s));
    EXPECT_EQ(default_point, find_line_in_image(all_1s));

    // Vertical
    // 1s on the left
    EXPECT_EQ(verticalLeftPoints, find_line_in_image(verticalLeftImage));
    // 1s on the right
    EXPECT_EQ(verticalRightPoints, find_line_in_image(verticalRightImage));

    // Horizontal
    // 1s on the top
    EXPECT_EQ(horizontalTopPoints, find_line_in_image(horizontalTopImage));
    // 1s on the bottom
    EXPECT_EQ(horizontalBottomPoints, find_line_in_image(horizontalBottomImage));

    // Diagonal
    // 1s on the top left
    EXPECT_EQ(diagonalTopLeftPoints, find_line_in_image(diagonalTopLeftImage));
    // 1s on the top right
    EXPECT_EQ(diagonalTopRightPoints, find_line_in_image(diagonalTopRightImage));
    // 1s on the bottom left
    EXPECT_EQ(diagonalBottomLeftPoints, find_line_in_image(diagonalBottomLeftImage));
    // 1s on the bottom right
    EXPECT_EQ(diagonalBottomRightPoints, find_line_in_image(diagonalBottomRightImage));

    EXPECT_EQ(verticalLargePoints, find_line_in_image(verticalLargeImage));

    EXPECT_EQ(horizontalLargePoints, find_line_in_image(horizontalLargeImage));

    EXPECT_EQ(largePoints, find_line_in_image(largeImage));
}

TEST(BasicFunctions, BasicFunctions)
{
    // 1d test for search for point in line
    std::vector<PixelColor> v1 = {PixelColor::ONE, PixelColor::ZERO};

    EXPECT_EQ(0, search_for_point_in_1d_line(v1));

    // test slope function
    Point p1 = {0, 0}, p2 = {1, 1};

    EXPECT_FLOAT_EQ(1.0f, calculate_slope(p1, p2));
}