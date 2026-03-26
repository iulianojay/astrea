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
#include <astro/state/orientation/AngularSequenceVelocity.hpp>
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
    AngularSequenceVelocity<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>;
using TestTaitBryanAngularVel =
    AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::XYZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>;

class AngularSequenceVelocityTest : public testing::Test {
  public:
    AngularSequenceVelocityTest() {}

    void SetUp() override {}

    void compare_angular_velocity_sequences(const auto& seq1, const auto& seq2, const Unitless& tol)
    {
        ASSERT_EQ_QUANTITY(seq1.get_phi_dot(), seq2.get_phi_dot(), tol);
        ASSERT_EQ_QUANTITY(seq1.get_theta_dot(), seq2.get_theta_dot(), tol);
        ASSERT_EQ_QUANTITY(seq1.get_psi_dot(), seq2.get_psi_dot(), tol);
    }

    Unitless REL_TOL = 1.0e-10 * one;

    // Test angular rates
    AngularRate angularRate1 = 0.1 * rad / s;
    AngularRate angularRate2 = 0.2 * rad / s;
    AngularRate angularRate3 = 0.3 * rad / s;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(AngularSequenceVelocityTest, TestEulerAngularVelocityConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestEulerAngularVel());

    // Parameterized constructor with angular rates only
    ASSERT_NO_THROW(TestEulerAngularVel(angularRate1, angularRate2, angularRate3));
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::XYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngularSequenceVelocityTest, TestTaitBryanAngularVelocityConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestTaitBryanAngularVel());

    // Parameterized constructor with angular rates only
    ASSERT_NO_THROW(TestTaitBryanAngularVel(angularRate1, angularRate2, angularRate3));
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::ZYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngularSequenceVelocityTest, TestEulerAngularVelocityGetters)
{
    TestEulerAngularVel eulerVel(angularRate1, angularRate2, angularRate3);

    // Test angular rate getters (phi_dot, theta_dot, psi_dot)
    ASSERT_EQ_QUANTITY(eulerVel.get_phi_dot(), angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel.get_theta_dot(), angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel.get_psi_dot(), angularRate3, REL_TOL);

    // Test array access
    ASSERT_EQ_QUANTITY(eulerVel[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[2], angularRate3, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestTaitBryanAngularVelocityGetters)
{
    TestTaitBryanAngularVel taitBryanVel(angularRate1, angularRate2, angularRate3);

    // Test angular rate getters (phi_dot, theta_dot, psi_dot)
    ASSERT_EQ_QUANTITY(taitBryanVel.get_phi_dot(), angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel.get_theta_dot(), angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel.get_psi_dot(), angularRate3, REL_TOL);

    // Test array access
    ASSERT_EQ_QUANTITY(taitBryanVel[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel[2], angularRate3, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestAngularRateModification)
{
    TestTaitBryanAngularVel taitBryanVel(angularRate1, angularRate2, angularRate3);

    // Test angular rate modification through phi_dot/theta_dot/psi_dot getters
    taitBryanVel.get_phi_dot()   = 0.5 * rad / s;
    taitBryanVel.get_theta_dot() = 0.25 * rad / s;
    taitBryanVel.get_psi_dot()   = 0.75 * rad / s;

    ASSERT_EQ_QUANTITY(taitBryanVel.get_phi_dot(), 0.5 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel.get_theta_dot(), 0.25 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanVel.get_psi_dot(), 0.75 * rad / s, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestAllEulerSequences)
{
    // Test different Euler sequences can be constructed
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::XYX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::YZY, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::ZYZ, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::XZX, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<EulerSequence, EulerSequence::YXY, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngularSequenceVelocityTest, TestAllTaitBryanSequences)
{
    // Test different Tait-Bryan sequences can be constructed
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::XYZ, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::YZX, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::ZXY, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::XZY, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::ZYX, RotationSequenceType::INTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
    ASSERT_NO_THROW((AngularSequenceVelocity<TaitBryanSequence, TaitBryanSequence::YXZ, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame>(
        angularRate1, angularRate2, angularRate3
    )));
}

TEST_F(AngularSequenceVelocityTest, TestCopyConstructor)
{
    TestEulerAngularVel eulerVel1(angularRate1, angularRate2, angularRate3);

    // Copy constructor within the same type should work
    ASSERT_NO_THROW(TestEulerAngularVel eulerVelCopy(eulerVel1));
    auto eulerVelCopy = TestEulerAngularVel(eulerVel1);

    EXPECT_EQ(eulerVel1, eulerVelCopy);
    ASSERT_EQ_QUANTITY(eulerVel1.get_phi_dot(), eulerVelCopy.get_phi_dot(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel1.get_theta_dot(), eulerVelCopy.get_theta_dot(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel1.get_psi_dot(), eulerVelCopy.get_psi_dot(), REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestMoveConstructor)
{
    // Move constructor within the same type should work
    auto eulerVelTemp = TestEulerAngularVel(angularRate1, angularRate2, angularRate3);
    ASSERT_NO_THROW(TestEulerAngularVel eulerVelMove(std::move(eulerVelTemp)));
    auto eulerVelMove = TestEulerAngularVel(std::move(eulerVelTemp));

    ASSERT_EQ_QUANTITY(eulerVelMove.get_phi_dot(), angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVelMove.get_theta_dot(), angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVelMove.get_psi_dot(), angularRate3, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestAccessOperators)
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

TEST_F(AngularSequenceVelocityTest, TestEqualityOperators)
{
    TestEulerAngularVel eulerVel1(angularRate1, angularRate2, angularRate3);
    TestEulerAngularVel eulerVel2(angularRate1, angularRate2, angularRate3);
    TestEulerAngularVel eulerVel3(angularRate2, angularRate1, angularRate3);

    // Same angular rates should be equal
    EXPECT_TRUE(eulerVel1 == eulerVel2);

    // Different angular rates should not be equal
    EXPECT_FALSE(eulerVel1 == eulerVel3);

    // Different sequence types should not be equal (compile-time enforcement)
    AngularSequenceVelocity<EulerSequence, EulerSequence::ZXZ, RotationSequenceType::EXTRINSIC, TestFrame, TestOutFrame> eulerVel4(
        angularRate1, angularRate2, angularRate3
    );
    // eulerVel1 == eulerVel4; // This should not compile due to type safety
}

TEST_F(AngularSequenceVelocityTest, TestAdditionAndSubtraction)
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

TEST_F(AngularSequenceVelocityTest, TestScalarMultiplicationAndDivision)
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

TEST_F(AngularSequenceVelocityTest, TestTimeOperations)
{
    TestEulerAngularVel eulerVel(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);
    Time dt = 2.0 * s;

    // Multiplication by time should produce an angle sequence (integration)
    auto angleSequence = eulerVel * dt;
    ASSERT_EQ_QUANTITY(angleSequence.get_phi(), 0.2 * rad, REL_TOL);
    ASSERT_EQ_QUANTITY(angleSequence.get_theta(), 0.4 * rad, REL_TOL);
    ASSERT_EQ_QUANTITY(angleSequence.get_psi(), 0.6 * rad, REL_TOL);

    // Division by time should produce angular acceleration
    auto acceleration = eulerVel / dt;
    ASSERT_EQ_QUANTITY(acceleration.get_phi_ddot(), 0.05 * rad / (s * s), REL_TOL);
    ASSERT_EQ_QUANTITY(acceleration.get_theta_ddot(), 0.1 * rad / (s * s), REL_TOL);
    ASSERT_EQ_QUANTITY(acceleration.get_psi_ddot(), 0.15 * rad / (s * s), REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestGetAngularRatesMethod)
{
    TestEulerAngularVel eulerVel(angularRate1, angularRate2, angularRate3);

    // Test that get_angleRates() returns the internal CartesianVector
    auto& angleRates = eulerVel.get_angleRates();
    ASSERT_EQ_QUANTITY(angleRates[0], angularRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(angleRates[1], angularRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(angleRates[2], angularRate3, REL_TOL);

    // Test that modifications through get_angleRates() work
    angleRates[0] = 0.5 * rad / s;
    ASSERT_EQ_QUANTITY(eulerVel.get_phi_dot(), 0.5 * rad / s, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestLargeAngularRates)
{
    // Test with larger angular rates to ensure no overflow/underflow issues
    AngularRate largeRate1 = 100.0 * rad / s;
    AngularRate largeRate2 = -50.0 * rad / s;
    AngularRate largeRate3 = 200.0 * rad / s;

    TestEulerAngularVel eulerVel(largeRate1, largeRate2, largeRate3);

    ASSERT_EQ_QUANTITY(eulerVel.get_phi_dot(), largeRate1, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel.get_theta_dot(), largeRate2, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel.get_psi_dot(), largeRate3, REL_TOL);

    // Test arithmetic with large values
    auto doubledVel = eulerVel * (2.0 * one);
    ASSERT_EQ_QUANTITY(doubledVel.get_phi_dot(), 200.0 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(doubledVel.get_theta_dot(), -100.0 * rad / s, REL_TOL);
    ASSERT_EQ_QUANTITY(doubledVel.get_psi_dot(), 400.0 * rad / s, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestZeroAngularRates)
{
    // Test with zero angular rates
    AngularRate zeroRate = 0.0 * rad / s;
    TestEulerAngularVel zeroVel(zeroRate, zeroRate, zeroRate);

    ASSERT_EQ_QUANTITY(zeroVel.get_phi_dot(), zeroRate, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroVel.get_theta_dot(), zeroRate, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroVel.get_psi_dot(), zeroRate, REL_TOL);

    // Test arithmetic operations with zero
    auto nonZeroVel  = TestEulerAngularVel(angularRate1, angularRate2, angularRate3);
    auto sumWithZero = nonZeroVel + zeroVel;
    compare_angular_velocity_sequences(sumWithZero, nonZeroVel, REL_TOL);

    auto productWithZero = zeroVel * (5.0 * one);
    compare_angular_velocity_sequences(productWithZero, zeroVel, REL_TOL);
}

TEST_F(AngularSequenceVelocityTest, TestUnitConversion)
{
    // Test with different units (deg/s vs rad/s)
    AngularRate rateInDegPerSec = 30.0 * deg / s;
    AngularRate rateInRadPerSec = rateInDegPerSec;

    TestEulerAngularVel eulerVel1(rateInDegPerSec, rateInDegPerSec, rateInDegPerSec);
    TestEulerAngularVel eulerVel2(rateInRadPerSec, rateInRadPerSec, rateInRadPerSec);

    // Should be equal since mp_units handles the conversion
    EXPECT_TRUE(eulerVel1 == eulerVel2);
}

TEST_F(AngularSequenceVelocityTest, TestChainedOperations)
{
    TestEulerAngularVel vel1(0.1 * rad / s, 0.2 * rad / s, 0.3 * rad / s);
    TestEulerAngularVel vel2(0.05 * rad / s, 0.1 * rad / s, 0.15 * rad / s);

    // Test chained operations
    auto result = (vel1 + vel2) * (2.0 * one) - vel1;
    TestEulerAngularVel expected(0.2 * rad / s, 0.4 * rad / s, 0.6 * rad / s);
    compare_angular_velocity_sequences(result, expected, REL_TOL);
}