#include <vector>

#include <gtest/gtest.h>

#include <math/interpolation.hpp>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(InterpolationTests, Interpolation)
{
    std::vector<double> x = { 1.0, 2.0 };
    std::vector<double> y = { 1.0, 2.0 };
    double sx             = 1.5;
    double sy             = math::interpolate(x, y, sx);
    ASSERT_EQ(sy, 1.5);
}

// TEST(InterpolationTests, Spline)
// {
//     std::vector<double> x  = { 1.0, 2.0 };
//     std::vector<double> y  = { 1.0, 2.0 };
//     std::vector<double> sx = { 1.0, 1.5, 2.0 };
//     std::vector<double> sy = math::cubic_spline(x, y, sx);
//     ASSERT_EQ(sy[0], 1.0);
//     ASSERT_EQ(sy[1], 1.5);
//     ASSERT_EQ(sy[2], 2.0);
// }