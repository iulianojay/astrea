/*
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <vector>

#include <gtest/gtest.h>

#include <math/interpolation.hpp>

using namespace astrea;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(InterpolationTests, Interpolation)
{
    std::vector<double> x = { 1.0, 2.0 };
    std::vector<double> y = { 1.0, 2.0 };
    ASSERT_EQ(math::interpolate(x, y, 1.0), 1.0);
    ASSERT_EQ(math::interpolate(x, y, 1.5), 1.5);
    ASSERT_EQ(math::interpolate(x, y, 2.0), 2.0);
    ASSERT_ANY_THROW(math::interpolate(x, y, 0.0));
    ASSERT_ANY_THROW(math::interpolate(x, y, 3.0));
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