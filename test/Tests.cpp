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
    const image one_pixel_1 = {{PixelColor::ONE}};
    const image one_pixel_0 = {{PixelColor::ZERO}};

    // image is a single row
    const image single_row = {{PixelColor::ONE, PixelColor::ZERO}};

    // image is a single column
    const image single_col = {
        {PixelColor::ONE},
        {PixelColor::ZERO}};

    const image all_1s = {
        {PixelColor::ONE, PixelColor::ONE},
        {PixelColor::ONE, PixelColor::ONE}};
    const image all_0s = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ZERO}};

    const image verticalLeftImage = {
        {PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ZERO}};

    const image verticalRightImage = {
        {PixelColor::ZERO, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ONE}};

    const image horizontalTopImage = {
        {PixelColor::ONE, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ZERO}};

    const image horizontalBottomImage = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ONE}};

    const image diagonalTopLeftImage = {
        {PixelColor::ONE, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ZERO}};
    const image diagonalTopRightImage = {
        {PixelColor::ZERO, PixelColor::ONE},
        {PixelColor::ZERO, PixelColor::ZERO}};
    const image diagonalBottomLeftImage = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ONE, PixelColor::ZERO}};
    const image diagonalBottomRightImage = {
        {PixelColor::ZERO, PixelColor::ZERO},
        {PixelColor::ZERO, PixelColor::ONE}};

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
}

TEST(BasicFunctions, BasicFunctions)
{
}