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

#include <gtest/gtest.h>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <math/comparisons.hpp>
#include <math/operations.hpp>

using namespace astrea;
using namespace astrea::math;
using namespace mp_units;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class OperationsTest : public testing::Test {
  public:
    OperationsTest() {}

    void SetUp() override {}

    const double REL_TOL = 1.0e-10;
};

// ============================================================================
// Max Function Tests
// ============================================================================

TEST_F(OperationsTest, MaxIntegerQuantities)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 5 * m;
    const auto q2 = 10 * m;

    const auto result = max(q1, q2);
    ASSERT_EQ(result.numerical_value_in(m), 10);
}

TEST_F(OperationsTest, MaxFloatQuantities)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 5.5 * m;
    const auto q2 = 10.3 * m;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), 10.3, REL_TOL);
}

TEST_F(OperationsTest, MaxFirstLarger)
{
    using mp_units::si::unit_symbols::kg;

    const auto q1 = 100.0 * kg;
    const auto q2 = 50.0 * kg;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(kg), 100.0, REL_TOL);
}

TEST_F(OperationsTest, MaxSecondLarger)
{
    using mp_units::si::unit_symbols::s;

    const auto q1 = 1.5 * s;
    const auto q2 = 2.5 * s;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(s), 2.5, REL_TOL);
}

TEST_F(OperationsTest, MaxEqualValues)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 7.0 * m;
    const auto q2 = 7.0 * m;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), 7.0, REL_TOL);
}

TEST_F(OperationsTest, MaxNegativeValues)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = -10.0 * m;
    const auto q2 = -5.0 * m;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), -5.0, REL_TOL);
}

TEST_F(OperationsTest, MaxWithZero)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 0.0 * m;
    const auto q2 = 5.0 * m;

    const auto result1 = max(q1, q2);
    ASSERT_NEAR(result1.numerical_value_in(m), 5.0, REL_TOL);

    const auto result2 = max(q2, q1);
    ASSERT_NEAR(result2.numerical_value_in(m), 5.0, REL_TOL);
}

TEST_F(OperationsTest, MaxAngularQuantities)
{
    using mp_units::angular::unit_symbols::rad;

    const auto q1 = 1.5 * rad;
    const auto q2 = 2.3 * rad;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(rad), 2.3, REL_TOL);
}

TEST_F(OperationsTest, MaxVelocityQuantities)
{
    using mp_units::si::unit_symbols::m;
    using mp_units::si::unit_symbols::s;

    const auto q1 = 10.0 * m / s;
    const auto q2 = 15.5 * m / s;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m / s), 15.5, REL_TOL);
}

// ============================================================================
// Min Function Tests
// ============================================================================

TEST_F(OperationsTest, MinIntegerQuantities)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 5 * m;
    const auto q2 = 10 * m;

    const auto result = min(q1, q2);
    ASSERT_EQ(result.numerical_value_in(m), 5);
}

TEST_F(OperationsTest, MinFloatQuantities)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 5.5 * m;
    const auto q2 = 10.3 * m;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), 5.5, REL_TOL);
}

TEST_F(OperationsTest, MinFirstSmaller)
{
    using mp_units::si::unit_symbols::kg;

    const auto q1 = 50.0 * kg;
    const auto q2 = 100.0 * kg;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(kg), 50.0, REL_TOL);
}

TEST_F(OperationsTest, MinSecondSmaller)
{
    using mp_units::si::unit_symbols::s;

    const auto q1 = 2.5 * s;
    const auto q2 = 1.5 * s;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(s), 1.5, REL_TOL);
}

TEST_F(OperationsTest, MinEqualValues)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 7.0 * m;
    const auto q2 = 7.0 * m;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), 7.0, REL_TOL);
}

TEST_F(OperationsTest, MinNegativeValues)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = -10.0 * m;
    const auto q2 = -5.0 * m;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), -10.0, REL_TOL);
}

TEST_F(OperationsTest, MinWithZero)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 0.0 * m;
    const auto q2 = 5.0 * m;

    const auto result1 = min(q1, q2);
    ASSERT_NEAR(result1.numerical_value_in(m), 0.0, REL_TOL);

    const auto result2 = min(q2, q1);
    ASSERT_NEAR(result2.numerical_value_in(m), 0.0, REL_TOL);
}

TEST_F(OperationsTest, MinAngularQuantities)
{
    using mp_units::angular::unit_symbols::rad;

    const auto q1 = 1.5 * rad;
    const auto q2 = 2.3 * rad;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(rad), 1.5, REL_TOL);
}

TEST_F(OperationsTest, MinVelocityQuantities)
{
    using mp_units::si::unit_symbols::m;
    using mp_units::si::unit_symbols::s;

    const auto q1 = 10.0 * m / s;
    const auto q2 = 15.5 * m / s;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m / s), 10.0, REL_TOL);
}

// ============================================================================
// Pow Function Tests (Dimensionless Quantities)
// ============================================================================

TEST_F(OperationsTest, PowDimensionlessSquare)
{
    const auto base     = 2.0 * one;
    const auto exponent = 2.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 4.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessCube)
{
    const auto base     = 3.0 * one;
    const auto exponent = 3.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 27.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessSquareRoot)
{
    const auto base     = 16.0 * one;
    const auto exponent = 0.5 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 4.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessNegativeExponent)
{
    const auto base     = 2.0 * one;
    const auto exponent = -2.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 0.25, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessZeroExponent)
{
    const auto base     = 5.0 * one;
    const auto exponent = 0.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 1.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessZeroBase)
{
    const auto base     = 0.0 * one;
    const auto exponent = 3.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 0.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessOne)
{
    const auto base     = 7.0 * one;
    const auto exponent = 1.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 7.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessFractional)
{
    const auto base     = 8.0 * one;
    const auto exponent = (1.0 / 3.0) * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 2.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessNegativeBase)
{
    const auto base     = -2.0 * one;
    const auto exponent = 3.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), -8.0, REL_TOL);
}

TEST_F(OperationsTest, PowDimensionlessLargeExponent)
{
    const auto base     = 2.0 * one;
    const auto exponent = 10.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 1024.0, REL_TOL);
}

// ============================================================================
// Edge Cases and Mixed Tests
// ============================================================================

TEST_F(OperationsTest, MaxMinConsistency)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 5.0 * m;
    const auto q2 = 10.0 * m;

    const auto maxResult = max(q1, q2);
    const auto minResult = min(q1, q2);

    // Max should be >= both values
    ASSERT_GE(maxResult.numerical_value_in(m), q1.numerical_value_in(m));
    ASSERT_GE(maxResult.numerical_value_in(m), q2.numerical_value_in(m));

    // Min should be <= both values
    ASSERT_LE(minResult.numerical_value_in(m), q1.numerical_value_in(m));
    ASSERT_LE(minResult.numerical_value_in(m), q2.numerical_value_in(m));
}

TEST_F(OperationsTest, MaxWithVeryLargeValues)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 1.0e100 * m;
    const auto q2 = 1.0e99 * m;

    const auto result = max(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), 1.0e100, 1.0e90);
}

TEST_F(OperationsTest, MinWithVerySmallValues)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 1.0e-100 * m;
    const auto q2 = 1.0e-99 * m;

    const auto result = min(q1, q2);
    ASSERT_NEAR(result.numerical_value_in(m), 1.0e-100, 1.0e-110);
}

TEST_F(OperationsTest, PowWithVerySmallBase)
{
    const auto base     = 0.01 * one;
    const auto exponent = 2.0 * one;

    const auto result = pow(base, exponent);
    ASSERT_NEAR(result.numerical_value_in(one), 0.0001, REL_TOL);
}

TEST_F(OperationsTest, MaxMinWithSameValue)
{
    using mp_units::si::unit_symbols::kg;

    const auto q1 = 42.0 * kg;
    const auto q2 = 42.0 * kg;

    const auto maxResult = max(q1, q2);
    const auto minResult = min(q1, q2);

    ASSERT_NEAR(maxResult.numerical_value_in(kg), 42.0, REL_TOL);
    ASSERT_NEAR(minResult.numerical_value_in(kg), 42.0, REL_TOL);
}

TEST_F(OperationsTest, ForceQuantities)
{
    using mp_units::si::unit_symbols::N;

    const auto f1 = 100.0 * N;
    const auto f2 = 250.0 * N;

    const auto maxForce = max(f1, f2);
    const auto minForce = min(f1, f2);

    ASSERT_NEAR(maxForce.numerical_value_in(N), 250.0, REL_TOL);
    ASSERT_NEAR(minForce.numerical_value_in(N), 100.0, REL_TOL);
}

TEST_F(OperationsTest, AccelerationQuantities)
{
    using mp_units::si::unit_symbols::m;
    using mp_units::si::unit_symbols::s;

    const auto a1 = 9.8 * m / (s * s);
    const auto a2 = 1.6 * m / (s * s); // Moon's gravity

    const auto maxAccel = max(a1, a2);
    const auto minAccel = min(a1, a2);

    ASSERT_NEAR(maxAccel.numerical_value_in(m / (s * s)), 9.8, REL_TOL);
    ASSERT_NEAR(minAccel.numerical_value_in(m / (s * s)), 1.6, REL_TOL);
}

TEST_F(OperationsTest, PowChaining)
{
    // Test: ((2^2)^2) = 2^4 = 16
    const auto base = 2.0 * one;
    const auto exp2 = 2.0 * one;

    const auto result1 = pow(base, exp2);
    const auto result2 = pow(result1, exp2);

    ASSERT_NEAR(result2.numerical_value_in(one), 16.0, REL_TOL);
}

TEST_F(OperationsTest, MaxMinSequence)
{
    using mp_units::si::unit_symbols::m;

    const auto q1 = 1.0 * m;
    const auto q2 = 5.0 * m;
    const auto q3 = 3.0 * m;

    // max(q1, min(q2, q3)) should give 3.0
    const auto minQ2Q3 = min(q2, q3);
    const auto result  = max(q1, minQ2Q3);

    ASSERT_NEAR(result.numerical_value_in(m), 3.0, REL_TOL);
}
