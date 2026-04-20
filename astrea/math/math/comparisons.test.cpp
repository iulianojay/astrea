/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <cmath>
#include <limits>

#include <gtest/gtest.h>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>

#include <math/comparisons.hpp>

using namespace astrea;
using namespace astrea::math;
using namespace mp_units;

using mp_units::si::unit_symbols::m;


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// ============================================================================
// ulp (scalar floating-point)
// ============================================================================

TEST(UlpScalar, PositiveValue)
{
    const double x        = 1.0;
    const double expected = std::nexttoward(x, std::numeric_limits<double>::infinity()) - x;
    EXPECT_DOUBLE_EQ(ulp(x), expected);
}

TEST(UlpScalar, NegativeValue)
{
    const double x        = -1.0;
    const double expected = x - std::nexttoward(x, -std::numeric_limits<double>::infinity());
    EXPECT_DOUBLE_EQ(ulp(x), expected);
    EXPECT_GT(ulp(x), 0.0);
}

TEST(UlpScalar, ZeroValue) { EXPECT_GT(ulp(0.0), 0.0); }

TEST(UlpScalar, LargeValue)
{
    const double x        = 1.0e15;
    const double expected = std::nexttoward(x, std::numeric_limits<double>::infinity()) - x;
    EXPECT_DOUBLE_EQ(ulp(x), expected);
    EXPECT_GT(ulp(x), ulp(1.0)); // ULP grows with magnitude
}

// ============================================================================
// ulp (quantity)
// ============================================================================

TEST(UlpQuantity, MatchesScalarUlp)
{
    const auto q      = 1.0 * m;
    const auto result = ulp(q);
    EXPECT_DOUBLE_EQ(result.numerical_value_in(m), ulp(1.0));
}

TEST(UlpQuantity, NegativeQuantity)
{
    const auto q      = -2.0 * m;
    const auto result = ulp(q);
    EXPECT_GT(result.numerical_value_in(m), 0.0);
    EXPECT_DOUBLE_EQ(result.numerical_value_in(m), ulp(-2.0));
}

// ============================================================================
// nearly_equal (tolerance-based: relTol / absTol)
// ============================================================================

TEST(NearlyEqualTolerance, ZeroTolerancesAlwaysTrue)
{
    // When both tolerances are zero all checks are skipped and the function returns true
    EXPECT_TRUE(nearly_equal(1.0 * m, 100.0 * m));
}

TEST(NearlyEqualTolerance, ExactlyEqualWithRelTol)
{
    const auto x = 5.0 * m;
    EXPECT_TRUE(nearly_equal(x, x, 1e-10 * one, 0.0 * one));
}

TEST(NearlyEqualTolerance, RelTolWithinTolerance)
{
    const auto x = 1.0 * m;
    const auto y = 1.005 * m;                               // 0.5% relative difference
    EXPECT_TRUE(nearly_equal(x, y, 0.01 * one, 0.0 * one)); // 1% rel tol
}

TEST(NearlyEqualTolerance, RelTolOutsideTolerance)
{
    const auto x = 1.0 * m;
    const auto y = 1.1 * m;                                  // 10% relative difference
    EXPECT_FALSE(nearly_equal(x, y, 0.01 * one, 0.0 * one)); // 1% rel tol
}

TEST(NearlyEqualTolerance, AbsTolWithinTolerance)
{
    const auto x = 1.0 * m;
    const auto y = 1.05 * m;                               // 0.05 m difference
    EXPECT_TRUE(nearly_equal(x, y, 0.0 * one, 0.1 * one)); // 0.1 m abs tol
}

TEST(NearlyEqualTolerance, AbsTolOutsideTolerance)
{
    const auto x = 1.0 * m;
    const auto y = 1.5 * m;                                 // 0.5 m difference
    EXPECT_FALSE(nearly_equal(x, y, 0.0 * one, 0.1 * one)); // 0.1 m abs tol
}

TEST(NearlyEqualTolerance, RelTolSkippedWhenValueIsZero)
{
    // relTol check requires both values nonzero; with one == 0 the check is skipped
    const auto x = 0.0 * m;
    const auto y = 1.0 * m;
    EXPECT_TRUE(nearly_equal(x, y, 0.01 * one, 0.0 * one));
}

TEST(NearlyEqualTolerance, BothTolerancesApplied)
{
    // Passes relTol but fails absTol
    const auto x = 1.0 * m;
    const auto y = 1.001 * m;
    EXPECT_FALSE(nearly_equal(x, y, 0.01 * one, 0.0005 * one)); // absTol 0.0005 m < diff 0.001 m
}

// ============================================================================
// nearly_equal (ULP-based)
// ============================================================================

TEST(NearlyEqualUlp, OneHalfUlpApart)
{
    const auto x = 3.14 * m;
    EXPECT_TRUE(nearly_equal_by_ulp(x, x, 0.5));
}

TEST(NearlyEqualUlp, OneUlpApart)
{
    const double val  = 1.0;
    const double next = std::nextafter(val, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(nearly_equal_by_ulp(val * m, next * m, 1)); // default maxUlps = 4
}

TEST(NearlyEqualUlp, FourUlpsApart)
{
    double val = 1.0;
    double far = val;
    for (int i = 0; i < 4; ++i) {
        far = std::nextafter(far, std::numeric_limits<double>::infinity());
    }

    EXPECT_TRUE(nearly_equal_by_ulp(val * m, far * m, 4)); // exactly at boundary (<=)
}

TEST(NearlyEqualUlp, FiveUlpsApartDefaultFails)
{
    double val = 1.0;
    double far = val;
    for (int i = 0; i < 5; ++i) {
        far = std::nextafter(far, std::numeric_limits<double>::infinity());
    }

    EXPECT_FALSE(nearly_equal_by_ulp(val * m, far * m, 4)); // 5 ULPs > maxUlps 4
}

TEST(NearlyEqualUlp, FiveUlpsApartCustomPasses)
{
    double val = 1.0;
    double far = val;
    for (int i = 0; i < 5; ++i) {
        far = std::nextafter(far, std::numeric_limits<double>::infinity());
    }

    EXPECT_TRUE(nearly_equal_by_ulp(val * m, far * m, 5));
}

TEST(NearlyEqualUlp, LargelyDifferent) { EXPECT_FALSE(nearly_equal_by_ulp(1.0 * m, 2.0 * m)); }

TEST(NearlyEqualUlp, LossyCalcs)
{
    const auto x = 1.0 * m;

    const double scale = 1e10;
    const auto offset  = 1.0 * m;

    // Lossy division
    auto y = x / scale;  // x / scale
    y += offset;         // x / scale + offset
    y *= scale;          // (x / scale + offset) * scale = x + offset * scale
    y -= offset / scale; // x + offset * scale - offset / scale = x
    EXPECT_FALSE(nearly_equal_by_ulp(x, y, 0.5));
    EXPECT_EQ(calculate_ulp_difference(x, y), 9) << "ULP difference (lossy division): " << calculate_ulp_difference(x, y) << " ULPs\n";

    // Non-lossy multiplication
    auto z = x * scale;  // x * scale
    z += offset;         // x * scale + offset
    z /= scale;          // (x * scale + offset) / scale = x + offset / scale
    z -= offset / scale; // x + offset / scale - offset / scale = x
    EXPECT_TRUE(nearly_equal_by_ulp(x, z, 0.5));
    EXPECT_EQ(calculate_ulp_difference(x, z), 0)
        << "ULP difference (non-lossy multiplication): " << calculate_ulp_difference(x, z) << " ULPs\n";
}