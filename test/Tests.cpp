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
    const image one_pixel_1 = {{1}};
    const image one_pixel_0 = {{0}};

    // image is a single row
    const image single_row = {{1, 0}};

    // image is a single column
    const image single_col = {
        {1},
        {0}};

    const image all_1s = {
        {1, 1},
        {1, 1}};
    const image all_0s = {
        {0, 0},
        {0, 0}};

    const image verticalLeftImage = {
        {1, 0},
        {1, 0}};

    const image verticalRightImage = {
        {0, 1},
        {0, 1}};

    const image horizontalTopImage = {
        {1, 1},
        {0, 0}};

    const image horizontalBottomImage = {
        {0, 0},
        {1, 1}};

    const image diagonalTopLeftImage = {
        {1, 0},
        {0, 0}};
    const image diagonalTopRightImage = {
        {0, 1},
        {0, 0}};
    const image diagonalBottomLeftImage = {
        {0, 0},
        {1, 0}};
    const image diagonalBottomRightImage = {
        {0, 0},
        {0, 1}};

    // points
    const points default_point = {{-1, -1}};

    const points verticalLeftPoints = {
        {0, 0}, {1, 0}};

    const points verticalRightPoints = {
        {0, 1}, {1, 1}};

    const points horizontalTopPoints = {
        {0, 0}, {0, 1}};

    const points horizontalBottomPoints = {
        {1, 0}, {1, 1}};

    const points diagonalTopLeftPoints = {
        {0, 0}};
    const points diagonalTopRightPoints = {
        {0, 1}};
    const points diagonalBottomLeftPoints = {
        {1, 0}};
    const points diagonalBottomRightPoints = {
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