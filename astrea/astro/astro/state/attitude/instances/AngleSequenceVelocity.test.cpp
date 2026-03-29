/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/frames.hpp>
#include <astro/frames/instances/dynamic_body_frame.hpp>
#include <astro/state/attitude/instances/AngleSequenceVelocity.hpp>
#include <astro/utilities/conversions.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

using TestFrame    = frames::earth::icrf;
using TestOutFrame = frames::dynamic::body;
using TestEulerAngularVel =
    AngleSequenceVelocity<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>;
using TestTaitBryanAngularVel =
    AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::XYZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>;

class AngleSequenceVelocityTest : public testing::Test {
  public:
    AngleSequenceVelocityTest() {}

    void SetUp() override {}

    void compare_angular_velocity_sequences(const auto& seq1, const auto& seq2, const Unitless& tol)
    {
        ASSERT_EQ_QUANTITY(seq1[0], seq2[0], tol);
        ASSERT_EQ_QUANTITY(seq1[1], seq2[1], tol);
        ASSERT_EQ_QUANTITY(seq1[2], seq2[2], tol);
    }

    Unitless REL_TOL = 1.0e-10 * one;

    // Test angular rates
    AngularVelocity angularRate1 = 0.1 * rad / s;
    AngularVelocity angularRate2 = 0.2 * rad / s;
    AngularVelocity angularRate3 = 0.3 * rad / s;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(AngleSequenceVelocityTest, TestEulerAngularVelocityConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestEulerAngularVel());

    // Parameterized constructor with angular rates only
    ASSERT_NO_THROW(TestEulerAngularVel(angularRate1, angularRate2, angularRate3));
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::XYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngleSequenceVelocityTest, TestTaitBryanAngularVelocityConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestTaitBryanAngularVel());

    // Parameterized constructor with angular rates only
    ASSERT_NO_THROW(TestTaitBryanAngularVel(angularRate1, angularRate2, angularRate3));
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::ZYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngleSequenceVelocityTest, TestEulerAngularVelocityGetters)
{
    TestEulerAngularVel eulerVel(angularRate1, angularRate2, angularRate3);

    // Test array access
    ASSERT_EQ_QUANTITY(eulerVel[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[2], angularRate3, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestTaitBryanAngularVelocityGetters)
{
    TestTaitBryanAngularVel taitBryanVel(angularRate1, angularRate2, angularRate3);

    // Test array access
    ASSERT_EQ_QUANTITY(taitBryanVel[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel[2], angularRate3, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestAngularVelocityModification)
{
    TestTaitBryanAngularVel taitBryanVel(angularRate1, angularRate2, angularRate3);

    // Test angular rate modification through array access
    taitBryanVel[0] = 0.5 * rad / s;
    taitBryanVel[1] = 0.25 * rad / s;
    taitBryanVel[2] = 0.75 * rad / s;

    ASSERT_EQ_QUANTITY(taitBryanVel[0], 0.5 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel[1], 0.25 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel[2], 0.75 * rad / s, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestAllEulerSequences)
{
    // Test different Euler sequences can be constructed
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::XYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::YZY, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::ZYZ, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::XZX, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<EulerSequence, EulerSequence::YXY, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngleSequenceVelocityTest, TestAllTaitBryanSequences)
{
    // Test different Tait-Bryan sequences can be constructed
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::XYZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::YZX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::ZXY, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::XZY, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::ZYX, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngleSequenceVelocity<TaitBryanSequence, TaitBryanSequence::YXZ, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngleSequenceVelocityTest, TestCopyConstructor)
{
    TestEulerAngularVel eulerVel1(angularRate1, angularRate2, angularRate3);

    // Copy constructor within the same type should work
    ASSERT_NO_THROW(TestEulerAngularVel eulerVelCopy(eulerVel1));
    auto eulerVelCopy = TestEulerAngularVel(eulerVel1);

    EXPECT_EQ(eulerVel1, eulerVelCopy);
    ASSERT_EQ_QUANTITY(eulerVel1[0], eulerVelCopy[0], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel1[1], eulerVelCopy[1], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel1[2], eulerVelCopy[2], REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestMoveConstructor)
{
    // Move constructor within the same type should work
    auto eulerVelTemp = TestEulerAngularVel(angularRate1, angularRate2, angularRate3);
    ASSERT_NO_THROW(TestEulerAngularVel eulerVelMove(std::move(eulerVelTemp)));
    auto eulerVelMove = TestEulerAngularVel(std::move(eulerVelTemp));

    ASSERT_EQ_QUANTITY(eulerVelMove[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVelMove[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVelMove[2], angularRate3, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestAccessOperators)
{
    TestEulerAngularVel eulerVel(angularRate1, angularRate2, angularRate3);
    eulerVel[0] = 0.5 * rad / s;
    eulerVel[1] = 0.25 * rad / s;
    eulerVel[2] = 0.75 * rad / s;

    ASSERT_EQ_QUANTITY(eulerVel[0], 0.5 * rad / s);
    ASSERT_EQ_QUANTITY(eulerVel[1], 0.25 * rad / s);
    ASSERT_EQ_QUANTITY(eulerVel[2], 0.75 * rad / s);

    // Const access
    const auto& constEulerVel = eulerVel;
    ASSERT_EQ_QUANTITY(constEulerVel[0], 0.5 * rad / s);
    ASSERT_EQ_QUANTITY(constEulerVel[1], 0.25 * rad / s);
    ASSERT_EQ_QUANTITY(constEulerVel[2], 0.75 * rad / s);
}

TEST_F(AngleSequenceVelocityTest, TestEqualityOperators)
{
    TestEulerAngularVel eulerVel1(angularRate1, angularRate2, angularRate3);
    TestEulerAngularVel eulerVel2(angularRate1, angularRate2, angularRate3);
    TestEulerAngularVel eulerVel3(angularRate2, angularRate1, angularRate3);

    // Same angular rates should be equal
    EXPECT_TRUE(eulerVel1 == eulerVel2);

    // Different angular rates should not be equal
    EXPECT_FALSE(eulerVel1 == eulerVel3);

    // Different sequence types should not be equal (compile-time enforcement)
    AngleSequenceVelocity<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame> eulerVel4(
        angularRate1, angularRate2, angularRate3
    );
    // eulerVel1 == eulerVel4; // This should not compile due to type safety
}

TEST_F(AngleSequenceVelocityTest, TestAdditionAndSubtraction)
{
    TestEulerAngularVel eulerVel1(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);
    TestEulerAngularVel eulerVel2(0.05 * rad / s, 0.1 * rad / s, 0.15 * rad / s);

    // Addition within the same type
    auto eulerVelSum = eulerVel1 + eulerVel2;
    TestEulerAngularVel expectedSum(0.15 * rad / s, 0.3 * rad / s, 0.45 * rad / s);
    compare_angular_velocity_sequences(eulerVelSum, expectedSum, REL_TOL);

    eulerVelSum += eulerVel2;
    TestEulerAngularVel expectedAfterAdd(0.2 * rad / s, 0.4 * rad / s, 0.6 * rad / s);
    compare_angular_velocity_sequences(eulerVelSum, expectedAfterAdd, REL_TOL);

    // Subtraction within the same type
    auto eulerVelDiff = eulerVelSum - eulerVel1;
    TestEulerAngularVel expectedDiff(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);
    compare_angular_velocity_sequences(eulerVelDiff, expectedDiff, REL_TOL);

    eulerVelDiff -= eulerVel2;
    compare_angular_velocity_sequences(eulerVelDiff, eulerVel2, REL_TOL);

    // Negation
    auto eulerVelNeg = -eulerVelDiff;
    TestEulerAngularVel expectedNeg(-0.05 * rad / s, -0.1 * rad / s, -0.15 * rad / s);
    compare_angular_velocity_sequences(eulerVelNeg, expectedNeg, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestScalarMultiplicationAndDivision)
{
    TestEulerAngularVel eulerVel(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);

    // Scalar multiplication
    auto eulerVelScaled = eulerVel * (2.0 * one);
    TestEulerAngularVel expectedScaled(0.2 * rad / s, 0.4 * rad / s, 0.6 * rad / s);
    compare_angular_velocity_sequences(eulerVelScaled, expectedScaled, REL_TOL);

    eulerVelScaled *= (0.5 * one);
    compare_angular_velocity_sequences(eulerVelScaled, eulerVel, REL_TOL);

    // Scalar division
    auto eulerVelDivided = eulerVelScaled / (2.0 * one);
    TestEulerAngularVel expectedDivided(0.05 * rad / s, 0.1 * rad / s, 0.15 * rad / s);
    compare_angular_velocity_sequences(eulerVelDivided, expectedDivided, REL_TOL);

    eulerVelDivided /= (0.5 * one);
    compare_angular_velocity_sequences(eulerVelDivided, eulerVel, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestTimeOperations)
{
    TestEulerAngularVel eulerVel(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);
    Time dt = 2.0 * s;

    // Multiplication by time should produce an angle sequence (integration)
    auto angleSequence = eulerVel * dt;
    ASSERT_EQ_QUANTITY(angleSequence[0], 0.2 * rad, REL_TOL);
    ASSERT_EQ_QUANTITY(angleSequence[1], 0.4 * rad, REL_TOL);
    ASSERT_EQ_QUANTITY(angleSequence[2], 0.6 * rad, REL_TOL);

    // Division by time should produce angular acceleration
    auto acceleration = eulerVel / dt;
    ASSERT_EQ_QUANTITY(acceleration[0], 0.05 * rad / (s * s), REL_TOL);
    ASSERT_EQ_QUANTITY(acceleration[1], 0.1 * rad / (s * s), REL_TOL);
    ASSERT_EQ_QUANTITY(acceleration[2], 0.15 * rad / (s * s), REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestGetAngularVelocitysMethod)
{
    TestEulerAngularVel eulerVel(angularRate1, angularRate2, angularRate3);

    // Test array access to the angular velocity components
    ASSERT_EQ_QUANTITY(eulerVel[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[2], angularRate3, REL_TOL);

    // Test that modifications through array access work
    eulerVel[0] = 0.5 * rad / s;
    ASSERT_EQ_QUANTITY(eulerVel[0], 0.5 * rad / s, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestLargeAngularVelocitys)
{
    // Test with larger angular rates to ensure no overflow/underflow issues
    AngularVelocity largeRate1 = 100.0 * rad / s;
    AngularVelocity largeRate2 = -50.0 * rad / s;
    AngularVelocity largeRate3 = 200.0 * rad / s;

    TestEulerAngularVel eulerVel(largeRate1, largeRate2, largeRate3);

    ASSERT_EQ_QUANTITY(eulerVel[0], largeRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[1], largeRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[2], largeRate3, REL_TOL);

    // Test arithmetic with large values
    auto doubledVel = eulerVel * (2.0 * one);
    ASSERT_EQ_QUANTITY(doubledVel[0], 200.0 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(doubledVel[1], -100.0 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(doubledVel[2], 400.0 * rad / s, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestZeroAngularVelocitys)
{
    // Test with zero angular rates
    AngularVelocity zeroRate = 0.0 * rad / s;
    TestEulerAngularVel zeroVel(zeroRate, zeroRate, zeroRate);

    ASSERT_EQ_QUANTITY(zeroVel[0], zeroRate, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroVel[1], zeroRate, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroVel[2], zeroRate, REL_TOL);

    // Test arithmetic operations with zero
    auto nonZeroVel  = TestEulerAngularVel(angularRate1, angularRate2, angularRate3);
    auto sumWithZero = nonZeroVel + zeroVel;
    compare_angular_velocity_sequences(sumWithZero, nonZeroVel, REL_TOL);

    auto productWithZero = zeroVel * (5.0 * one);
    compare_angular_velocity_sequences(productWithZero, zeroVel, REL_TOL);
}

TEST_F(AngleSequenceVelocityTest, TestUnitConversion)
{
    // Test with different units (deg/s vs rad/s)
    AngularVelocity rateInDegPerSec = 30.0 * deg / s;
    AngularVelocity rateInRadPerSec = rateInDegPerSec;

    TestEulerAngularVel eulerVel1(rateInDegPerSec, rateInDegPerSec, rateInDegPerSec);
    TestEulerAngularVel eulerVel2(rateInRadPerSec, rateInRadPerSec, rateInRadPerSec);

    // Should be equal since mp_units handles the conversion
    EXPECT_TRUE(eulerVel1 == eulerVel2);
}

TEST_F(AngleSequenceVelocityTest, TestChainedOperations)
{
    TestEulerAngularVel vel1(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);
    TestEulerAngularVel vel2(0.05 * rad / s, 0.1 * rad / s, 0.15 * rad / s);

    // Test chained operations
    auto result = (vel1 + vel2) * (2.0 * one) - vel1;
    TestEulerAngularVel expected(0.2 * rad / s, 0.4 * rad / s, 0.6 * rad / s);
    compare_angular_velocity_sequences(result, expected, REL_TOL);
}

// Tests for AngleSequenceAcceleration
using TestEulerAcceleration =
    AngleSequenceAcceleration<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>;
using TestTaitBryanAcceleration =
    AngleSequenceAcceleration<TaitBryanSequence, TaitBryanSequence::XYZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>;

class AngleSequenceAccelerationTest : public testing::Test {
  public:
    AngleSequenceAccelerationTest() {}

    void SetUp() override {}

    void compare_angular_acceleration_sequences(const auto& seq1, const auto& seq2, const Unitless& tol)
    {
        ASSERT_EQ_QUANTITY(seq1[0], seq2[0], tol);
        ASSERT_EQ_QUANTITY(seq1[1], seq2[1], tol);
        ASSERT_EQ_QUANTITY(seq2[2], seq2[2], tol);
    }

    Unitless REL_TOL = 1.0e-10 * one;

    // Test angular accelerations
    AngularAcceleration angularAccel1 = 0.1 * rad / (s * s);
    AngularAcceleration angularAccel2 = 0.2 * rad / (s * s);
    AngularAcceleration angularAccel3 = 0.3 * rad / (s * s);
};

TEST_F(AngleSequenceAccelerationTest, TestConstructors)
{
    // Default constructor
    ASSERT_NO_THROW(TestEulerAcceleration());

    // Parameterized constructor with angular accelerations
    ASSERT_NO_THROW(TestEulerAcceleration(angularAccel1, angularAccel2, angularAccel3));
    ASSERT_NO_THROW((AngleSequenceAcceleration<EulerSequence, EulerSequence::XYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularAccel1, angularAccel2, angularAccel3
    )));
}

TEST_F(AngleSequenceAccelerationTest, TestAccess)
{
    TestEulerAcceleration accel(angularAccel1, angularAccel2, angularAccel3);

    // Test array access
    ASSERT_EQ_QUANTITY(accel[0], angularAccel1, REL_TOL);
    ASSERT_EQ_QUANTITY(accel[1], angularAccel2, REL_TOL);
    ASSERT_EQ_QUANTITY(accel[2], angularAccel3, REL_TOL);
}

TEST_F(AngleSequenceAccelerationTest, TestMultiplicationByTime)
{
    TestEulerAcceleration accel(angularAccel1, angularAccel2, angularAccel3);
    Time dt = 2.0 * s;

    // Multiplication by time should produce angular velocity
    auto velocity = accel * dt;
    ASSERT_EQ_QUANTITY(velocity[0], 0.2 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(velocity[1], 0.4 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(velocity[2], 0.6 * rad / s, REL_TOL);
}

TEST_F(AngleSequenceAccelerationTest, TestForceToVector)
{
    TestEulerAcceleration accel(angularAccel1, angularAccel2, angularAccel3);

    // Convert to vector
    auto vec = accel.force_to_vector();
    ASSERT_EQ(vec.size(), 3);

    // Check values (normalized by unit)
    EXPECT_EQ_QUANTITY(vec[0], 0.1 * one, REL_TOL);
    EXPECT_EQ_QUANTITY(vec[1], 0.2 * one, REL_TOL);
    EXPECT_EQ_QUANTITY(vec[2], 0.3 * one, REL_TOL);
}