#include "shape_recognition.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(SanityCheck, AlwaysFails)
{
    EXPECT_EQ(true, false);
}
