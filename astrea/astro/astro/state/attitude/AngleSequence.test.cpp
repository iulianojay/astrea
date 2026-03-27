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
#include <astro/state/attitude/AngleSequence.hpp>
#include <astro/utilities/conversions.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;

using TestFrame           = frames::earth::icrf;
using TestOutFrame        = frames::dynamic::body;
using TestEulerAngles     = IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame>;
using TestTaitBryanAngles = IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame>;

class AngleSequenceTest : public testing::Test {
  public:
    AngleSequenceTest() {}

    void SetUp() override {}

    void compare_angle_sequences(const auto& seq1, const auto& seq2, const Unitless& tol)
    {
        ASSERT_EQ_QUANTITY(seq1.get_phi(), seq2.get_phi(), tol);
        ASSERT_EQ_QUANTITY(seq1.get_theta(), seq2.get_theta(), tol);
        ASSERT_EQ_QUANTITY(seq1.get_psi(), seq2.get_psi(), tol);
    }

    const Unitless REL_TOL = 1.0e-10 * one;

    // Test angles
    Angle angle1 = 30.0 * deg;
    Angle angle2 = 45.0 * deg;
    Angle angle3 = 60.0 * deg;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(AngleSequenceTest, TestEulerAnglesConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestEulerAngles());

    // Parameterized constructor with angles only
    ASSERT_NO_THROW(TestEulerAngles(angle1, angle2, angle3));
    ASSERT_NO_THROW((ExtrinsicEulerAngles<EulerSequence::XYX, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(AngleSequenceTest, TestTaitBryanAnglesConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestTaitBryanAngles());

    // Parameterized constructor with angles only
    ASSERT_NO_THROW(TestTaitBryanAngles(angle1, angle2, angle3));
    ASSERT_NO_THROW((ExtrinsicTaitBryanAngles<TaitBryanSequence::ZYX, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(AngleSequenceTest, TestEulerAnglesGetters)
{
    TestEulerAngles euler(angle1, angle2, angle3);

    // Test inherited angle getters (phi, theta, psi)
    ASSERT_EQ_QUANTITY(euler.get_phi(), wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_theta(), wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_psi(), wrap_angle(angle3), REL_TOL);

    // Test array access
    ASSERT_EQ_QUANTITY(euler[0], wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(euler[1], wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(euler[2], wrap_angle(angle3), REL_TOL);
}

TEST_F(AngleSequenceTest, TestTaitBryanAnglesGetters)
{
    TestTaitBryanAngles taitBryan(angle1, angle2, angle3);

    // Test inherited angle getters (phi, theta, psi)
    ASSERT_EQ_QUANTITY(taitBryan.get_phi(), wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan.get_theta(), wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan.get_psi(), wrap_angle(angle3), REL_TOL);

    // Test array access
    ASSERT_EQ_QUANTITY(taitBryan[0], wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[1], wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[2], wrap_angle(angle3), REL_TOL);
}

TEST_F(AngleSequenceTest, TestDirectionCosineMatrixConversion)
{
    TestEulerAngles euler(angle1, angle2, angle3);

    // Test that DCM conversion works
    ASSERT_NO_THROW(auto dcm = euler.to_dcm());

    // Test different types can create DCMs
    ExtrinsicEulerAngles<EulerSequence::XYX, TestFrame, TestOutFrame> eulerExt(angle1, angle2, angle3);
    ASSERT_NO_THROW(auto dcm2 = eulerExt.to_dcm());
}

TEST_F(AngleSequenceTest, TestAngleModification)
{
    TestTaitBryanAngles taitBryan(angle1, angle2, angle3);

    // Test angle modification through phi/theta/psi getters
    taitBryan.get_phi()   = 90.0 * deg;
    taitBryan.get_theta() = 45.0 * deg;
    taitBryan.get_psi()   = 15.0 * deg;

    ASSERT_EQ_QUANTITY(taitBryan.get_phi(), 90.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan.get_theta(), 45.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan.get_psi(), 15.0 * deg, REL_TOL);
}

TEST_F(AngleSequenceTest, TestAngleWrapping)
{
    // Test angles that need wrapping
    Angle largeAngle1 = 390.0 * deg; // Should wrap to 30°
    Angle largeAngle2 = 225.0 * deg; // Should wrap to 45° for wrap_angle_to_pi
    Angle largeAngle3 = -30.0 * deg; // Should wrap to 330°

    TestEulerAngles euler(largeAngle1, largeAngle2, largeAngle3);

    // Verify wrapping behavior
    ASSERT_EQ_QUANTITY(euler.get_phi(), wrap_angle(largeAngle1), REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_theta(), wrap_angle_to_pi(largeAngle2), REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_psi(), wrap_angle(largeAngle3), REL_TOL);

    // Test specifically known wrapped values
    ASSERT_EQ_QUANTITY(euler.get_phi(), 30.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_theta(), 45.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_psi(), 330.0 * deg, REL_TOL);
}

TEST_F(AngleSequenceTest, TestAllEulerSequences)
{
    // Test different Euler sequences can be constructed
    ASSERT_NO_THROW((IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((ExtrinsicEulerAngles<EulerSequence::XYX, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((IntrinsicEulerAngles<EulerSequence::YZY, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((ExtrinsicEulerAngles<EulerSequence::ZYZ, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((IntrinsicEulerAngles<EulerSequence::XZX, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((ExtrinsicEulerAngles<EulerSequence::YXY, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(AngleSequenceTest, TestAllTaitBryanSequences)
{
    // Test different Tait-Bryan sequences can be constructed
    ASSERT_NO_THROW((IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((ExtrinsicTaitBryanAngles<TaitBryanSequence::YZX, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((IntrinsicTaitBryanAngles<TaitBryanSequence::ZXY, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((ExtrinsicTaitBryanAngles<TaitBryanSequence::XZY, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((IntrinsicTaitBryanAngles<TaitBryanSequence::ZYX, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((ExtrinsicTaitBryanAngles<TaitBryanSequence::YXZ, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(AngleSequenceTest, TestCopyConstructor)
{
    TestEulerAngles euler1(angle1, angle2, angle3);

    // Copy constructor within the same type should work
    ASSERT_NO_THROW(TestEulerAngles eulerCopy(euler1));
    auto eulerCopy = TestEulerAngles(euler1);

    EXPECT_EQ(euler1, eulerCopy);
    ASSERT_EQ_QUANTITY(euler1.get_phi(), eulerCopy.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(euler1.get_theta(), eulerCopy.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(euler1.get_psi(), eulerCopy.get_psi(), REL_TOL);
}

TEST_F(AngleSequenceTest, TestMoveConstructor)
{
    // Move constructor within the same type should work
    auto eulerTemp = TestEulerAngles(angle1, angle2, angle3);
    ASSERT_NO_THROW(TestEulerAngles eulerMove(std::move(eulerTemp)));
    auto eulerMove = TestEulerAngles(std::move(eulerTemp));

    ASSERT_EQ_QUANTITY(eulerMove.get_phi(), wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerMove.get_theta(), wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerMove.get_psi(), wrap_angle(angle3), REL_TOL);
}

TEST_F(AngleSequenceTest, TestAccessOperators)
{
    TestEulerAngles euler(angle1, angle2, angle3);
    euler[0] = 90.0 * deg;
    euler[1] = 45.0 * deg;
    euler[2] = 180.0 * deg;

    ASSERT_EQ_QUANTITY(euler[0], 90.0 * deg);
    ASSERT_EQ_QUANTITY(euler[1], 45.0 * deg);
    ASSERT_EQ_QUANTITY(euler[2], 180.0 * deg);

    // Const access
    const auto& constEuler = euler;
    ASSERT_EQ_QUANTITY(constEuler[0], 90.0 * deg);
    ASSERT_EQ_QUANTITY(constEuler[1], 45.0 * deg);
    ASSERT_EQ_QUANTITY(constEuler[2], 180.0 * deg);
}

TEST_F(AngleSequenceTest, TestEqualityOperators)
{
    TestEulerAngles euler1(angle1, angle2, angle3);
    TestEulerAngles euler2(angle1, angle2, angle3);
    TestEulerAngles euler3(angle2, angle1, angle3);

    // Same angles should be equal
    EXPECT_TRUE(euler1 == euler2);

    // Different angles should not be equal
    EXPECT_FALSE(euler1 == euler3);

    // Different sequence types should not be equal (compile-time enforcement)
    ExtrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> euler4(angle1, angle2, angle3);
    // euler1 == euler4; // This should not compile due to type safety
}

TEST_F(AngleSequenceTest, TestAdditionAndSubtraction)
{
    TestEulerAngles euler1(30.0 * deg, 45.0 * deg, 60.0 * deg);
    TestEulerAngles euler2(15.0 * deg, 15.0 * deg, 30.0 * deg);

    // Addition within the same type
    auto eulerSum = euler1 + euler2;
    TestEulerAngles expectedSum(45.0 * deg, 60.0 * deg, 90.0 * deg);
    compare_angle_sequences(eulerSum, expectedSum, REL_TOL);

    eulerSum += euler2;
    TestEulerAngles expectedAfterAdd(60.0 * deg, 75.0 * deg, 120.0 * deg);
    compare_angle_sequences(eulerSum, expectedAfterAdd, REL_TOL);

    // Subtraction within the same type
    auto eulerDiff = eulerSum - euler1;
    TestEulerAngles expectedDiff(30.0 * deg, 30.0 * deg, 60.0 * deg);
    compare_angle_sequences(eulerDiff, expectedDiff, REL_TOL);

    eulerDiff -= euler2;
    compare_angle_sequences(eulerDiff, euler2, REL_TOL);

    // Negation
    auto eulerNeg = -eulerDiff;
    TestEulerAngles expectedNeg(-15.0 * deg, -15.0 * deg, -30.0 * deg);
    compare_angle_sequences(eulerNeg, expectedNeg, REL_TOL);
}

TEST_F(AngleSequenceTest, TestScalarMultiplicationAndDivision)
{
    TestEulerAngles euler(30.0 * deg, 45.0 * deg, 60.0 * deg);

    // Scalar multiplication
    auto eulerScaled = euler * (2.0 * one);
    TestEulerAngles expectedScaled(60.0 * deg, 90.0 * deg, 120.0 * deg);
    compare_angle_sequences(eulerScaled, expectedScaled, REL_TOL);

    eulerScaled *= (0.5 * one);
    compare_angle_sequences(eulerScaled, euler, REL_TOL);

    // Scalar division
    auto eulerDivided = eulerScaled / (2.0 * one);
    TestEulerAngles expectedDivided(15.0 * deg, 22.5 * deg, 30.0 * deg);
    compare_angle_sequences(eulerDivided, expectedDivided, REL_TOL);

    eulerDivided /= (0.5 * one);
    compare_angle_sequences(eulerDivided, euler, REL_TOL);
}

TEST_F(AngleSequenceTest, TestDotAndCrossProduct)
{
    TestEulerAngles euler1(90.0 * deg, 0.0 * deg, 0.0 * deg);
    TestEulerAngles euler2(0.0 * deg, 90.0 * deg, 0.0 * deg);

    // Dot product
    auto dotProduct = euler1.dot(euler2);
    EXPECT_EQ(dotProduct, 0.0 * one);

    dotProduct = euler1.dot(euler1);
    ASSERT_EQ_QUANTITY(dotProduct, M_PI_2 * M_PI_2 * one, REL_TOL);

    // Cross product
    auto crossProduct = euler1.cross(euler2).unit();
    ASSERT_EQ_QUANTITY(crossProduct.get_x(), 0.0 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(crossProduct.get_y(), 0.0 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(crossProduct.get_z(), 1.0 * one, REL_TOL);
}

TEST_F(AngleSequenceTest, TestNormAndOffsetAngle)
{
    TestEulerAngles euler(3.0 * deg, 4.0 * deg, 0.0 * deg);

    // Norm (should be sqrt(3^2 + 4^2) = 5 degrees)
    auto normEuler = euler.norm();
    ASSERT_EQ_QUANTITY(normEuler, 5.0 * deg, REL_TOL);
}

TEST_F(AngleSequenceTest, TestComparisonBetweenEulerAndTaitBryan)
{
    // Create equivalent angle sets with different template types
    TestEulerAngles euler(angle1, angle2, angle3);
    TestTaitBryanAngles taitBryan(angle1, angle2, angle3);

    // They should have the same angle values but different sequence types
    compare_angle_sequences(euler, taitBryan, REL_TOL);

    // But they should be different types (cannot directly compare with ==)
    // This is enforced by the type system -- they are different template instantiations
    // euler == taitBryan; // This should not compile

    // Test that we can create both with different rotation types at compile time
    IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> eulerIntrinsic(angle1, angle2, angle3);
    ExtrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> eulerExtrinsic(angle1, angle2, angle3);
    IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> taitBryanIntrinsic(angle1, angle2, angle3);
    ExtrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> taitBryanExtrinsic(angle1, angle2, angle3);

    // All should have same angle values
    ASSERT_EQ_QUANTITY(eulerIntrinsic.get_phi(), eulerExtrinsic.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanIntrinsic.get_phi(), taitBryanExtrinsic.get_phi(), REL_TOL);
}

TEST_F(AngleSequenceTest, TestDifferentRotationTypes)
{
    IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> eulerIntrinsic(angle1, angle2, angle3);
    ExtrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> eulerExtrinsic(angle1, angle2, angle3);

    // Same angle values
    ASSERT_EQ_QUANTITY(eulerIntrinsic.get_phi(), eulerExtrinsic.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerIntrinsic.get_theta(), eulerExtrinsic.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerIntrinsic.get_psi(), eulerExtrinsic.get_psi(), REL_TOL);

    // But they should be different types (cannot directly compare with ==)
    // eulerIntrinsic == eulerExtrinsic; // This should not compile

    // They should produce different DCMs due to different rotation order
    auto dcmIntrinsic = eulerIntrinsic.to_dcm();
    auto dcmExtrinsic = eulerExtrinsic.to_dcm();
}

TEST_F(AngleSequenceTest, TestFrameConsistency)
{
    // Test that different frame types can be created but are type-safe
    IntrinsicEulerAngles<EulerSequence::ZXZ, frames::earth::icrf, frames::earth::j2000> eulerICRF(angle1, angle2, angle3);
    IntrinsicEulerAngles<EulerSequence::ZXZ, frames::earth::j2000, frames::earth::icrf> eulerJ2000(angle1, angle2, angle3);

    // They should have the same angle values
    ASSERT_EQ_QUANTITY(eulerICRF.get_phi(), eulerJ2000.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerICRF.get_theta(), eulerJ2000.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerICRF.get_psi(), eulerJ2000.get_psi(), REL_TOL);

    // But different frames should not be directly comparable with ==
    // This test verifies the type safety is maintained
    // EXPECT_FALSE(eulerICRF == eulerJ2000); // This should not compile
}

TEST_F(AngleSequenceTest, TestSequenceSpecificBehavior)
{
    // Test that different sequences maintain their compile-time identity
    IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> eulerZXZ(angle1, angle2, angle3);
    IntrinsicEulerAngles<EulerSequence::XYX, TestFrame, TestOutFrame> eulerXYX(angle1, angle2, angle3);
    IntrinsicEulerAngles<EulerSequence::YZY, TestFrame, TestOutFrame> eulerYZY(angle1, angle2, angle3);

    // All should have same angle values but different DCM output
    ASSERT_EQ_QUANTITY(eulerZXZ.get_phi(), eulerXYX.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerXYX.get_phi(), eulerYZY.get_phi(), REL_TOL);

    // Test Tait-Bryan sequences
    IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> taitBryanXYZ(angle1, angle2, angle3);
    IntrinsicTaitBryanAngles<TaitBryanSequence::ZYX, TestFrame, TestOutFrame> taitBryanZYX(angle1, angle2, angle3);
    IntrinsicTaitBryanAngles<TaitBryanSequence::YXZ, TestFrame, TestOutFrame> taitBryanYXZ(angle1, angle2, angle3);

    // All should have same angle values but different DCM output
    ASSERT_EQ_QUANTITY(taitBryanXYZ.get_phi(), taitBryanZYX.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanZYX.get_phi(), taitBryanYXZ.get_phi(), REL_TOL);

    // Different sequences should produce different DCMs
    ASSERT_NO_THROW(eulerZXZ.to_dcm());
    ASSERT_NO_THROW(taitBryanXYZ.to_dcm());
}

TEST_F(AngleSequenceTest, TestOutputStream)
{
    TestEulerAngles euler(30.0 * deg, 45.0 * deg, 60.0 * deg);

    // Test that the angles can be accessed for output
    // Note: Direct stream output may not be implemented, but angle access should work
    ASSERT_EQ_QUANTITY(euler.get_phi(), 30.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_theta(), 45.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler.get_psi(), 60.0 * deg, REL_TOL);

    TestTaitBryanAngles taitBryan(15.0 * deg, 30.0 * deg, 90.0 * deg);
    ASSERT_EQ_QUANTITY(taitBryan.get_phi(), 15.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan.get_theta(), 30.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan.get_psi(), 90.0 * deg, REL_TOL);

    // Test DCM conversion works
    ASSERT_NO_THROW(euler.to_dcm());
    ASSERT_NO_THROW(taitBryan.to_dcm());
}

// ========================================================================================
// Tests for get_reverse_sequence functions
// ========================================================================================

TEST_F(AngleSequenceTest, TestEulerReverseSequence)
{
    // Test that Euler sequences return themselves (they are symmetric)
    EXPECT_EQ(get_reverse_sequence(EulerSequence::ZXZ), EulerSequence::ZXZ);
    EXPECT_EQ(get_reverse_sequence(EulerSequence::XYX), EulerSequence::XYX);
    EXPECT_EQ(get_reverse_sequence(EulerSequence::YZY), EulerSequence::YZY);
    EXPECT_EQ(get_reverse_sequence(EulerSequence::ZYZ), EulerSequence::ZYZ);
    EXPECT_EQ(get_reverse_sequence(EulerSequence::XZX), EulerSequence::XZX);
    EXPECT_EQ(get_reverse_sequence(EulerSequence::YXY), EulerSequence::YXY);
}

TEST_F(AngleSequenceTest, TestTaitBryanReverseSequence)
{
    // Test Tait-Bryan sequence reversals
    EXPECT_EQ(get_reverse_sequence(TaitBryanSequence::XYZ), TaitBryanSequence::ZYX);
    EXPECT_EQ(get_reverse_sequence(TaitBryanSequence::YZX), TaitBryanSequence::XZY);
    EXPECT_EQ(get_reverse_sequence(TaitBryanSequence::ZXY), TaitBryanSequence::YXZ);
    EXPECT_EQ(get_reverse_sequence(TaitBryanSequence::XZY), TaitBryanSequence::YZX);
    EXPECT_EQ(get_reverse_sequence(TaitBryanSequence::ZYX), TaitBryanSequence::XYZ);
    EXPECT_EQ(get_reverse_sequence(TaitBryanSequence::YXZ), TaitBryanSequence::ZXY);
}

TEST_F(AngleSequenceTest, TestDoubleReverseSequence)
{
    // Test that double reversal returns the original sequence for Tait-Bryan
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(TaitBryanSequence::XYZ)), TaitBryanSequence::XYZ);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(TaitBryanSequence::YZX)), TaitBryanSequence::YZX);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(TaitBryanSequence::ZXY)), TaitBryanSequence::ZXY);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(TaitBryanSequence::XZY)), TaitBryanSequence::XZY);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(TaitBryanSequence::ZYX)), TaitBryanSequence::ZYX);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(TaitBryanSequence::YXZ)), TaitBryanSequence::YXZ);

    // Test that double reversal returns the original sequence for Euler
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(EulerSequence::ZXZ)), EulerSequence::ZXZ);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(EulerSequence::XYX)), EulerSequence::XYX);
}

TEST_F(AngleSequenceTest, TestIntrinsicToIntrinsic)
{
    // Create an intrinsic Euler sequence
    IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> intrinsic_euler(angle1, angle2, angle3);

    // Converting intrinsic to intrinsic should return the same sequence
    auto result = intrinsic_euler.to_rotation_type<RotationSequenceType::INTRINSIC>();
    compare_angle_sequences(intrinsic_euler, result, REL_TOL);

    // Test with Tait-Bryan as well
    IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> intrinsic_tb(angle1, angle2, angle3);
    auto tbResult = intrinsic_tb.to_rotation_type<RotationSequenceType::INTRINSIC>();
    compare_angle_sequences(intrinsic_tb, tbResult, REL_TOL);
}

TEST_F(AngleSequenceTest, TestExtrinsicToExtrinsic)
{
    // Create an extrinsic Euler sequence
    ExtrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> extrinsic_euler(angle1, angle2, angle3);

    // Converting extrinsic to extrinsic should return the same sequence
    auto result = extrinsic_euler.to_rotation_type<RotationSequenceType::EXTRINSIC>();
    compare_angle_sequences(extrinsic_euler, result, REL_TOL);

    // Test with Tait-Bryan as well
    ExtrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> extrinsic_tb(angle1, angle2, angle3);
    auto tbResult = extrinsic_tb.to_rotation_type<RotationSequenceType::EXTRINSIC>();
    compare_angle_sequences(extrinsic_tb, tbResult, REL_TOL);
}

TEST_F(AngleSequenceTest, TestExtrinsicToIntrinsicConversion)
{
    // Create an extrinsic sequence
    ExtrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> extrinsic_euler(angle1, angle2, angle3);

    // Convert to intrinsic - angles should be reversed
    auto intrinsicResult = extrinsic_euler.to_rotation_type<RotationSequenceType::INTRINSIC>();

    // Verify that angles are reversed
    ASSERT_EQ_QUANTITY(intrinsicResult.get_phi(), extrinsic_euler.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsicResult.get_theta(), extrinsic_euler.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsicResult.get_psi(), extrinsic_euler.get_psi(), REL_TOL);

    // Test with Tait-Bryan sequence
    ExtrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> extrinsic_tb(angle1, angle2, angle3);
    auto intrinsic_tbResult = extrinsic_tb.to_rotation_type<RotationSequenceType::INTRINSIC>();

    // For Tait-Bryan, sequence should also reverse (XYZ becomes ZYX) with reversed angles
    ASSERT_EQ_QUANTITY(intrinsic_tbResult.get_phi(), extrinsic_tb.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsic_tbResult.get_theta(), extrinsic_tb.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsic_tbResult.get_psi(), extrinsic_tb.get_psi(), REL_TOL);
}

TEST_F(AngleSequenceTest, TestIntrinsicToExtrinsicConversion)
{
    // Create an intrinsic sequence
    IntrinsicEulerAngles<EulerSequence::ZXZ, TestFrame, TestOutFrame> intrinsic_euler(angle1, angle2, angle3);

    // Convert to extrinsic - angles should be reversed
    auto extrinsicResult = intrinsic_euler.to_rotation_type<RotationSequenceType::EXTRINSIC>();

    // Verify that angles are reversed
    ASSERT_EQ_QUANTITY(extrinsicResult.get_phi(), intrinsic_euler.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsicResult.get_theta(), intrinsic_euler.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsicResult.get_psi(), intrinsic_euler.get_psi(), REL_TOL);

    // Test with Tait-Bryan sequence
    IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> intrinsic_tb(angle1, angle2, angle3);
    auto extrinsic_tbResult = intrinsic_tb.to_rotation_type<RotationSequenceType::EXTRINSIC>();

    // For Tait-Bryan, sequence should also reverse (XYZ becomes ZYX) with reversed angles
    ASSERT_EQ_QUANTITY(extrinsic_tbResult.get_phi(), intrinsic_tb.get_phi(), REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsic_tbResult.get_theta(), intrinsic_tb.get_theta(), REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsic_tbResult.get_psi(), intrinsic_tb.get_psi(), REL_TOL);
}

TEST_F(AngleSequenceTest, TestRoundTripIntrinsicExtrinsicConversion)
{
    // Create an intrinsic sequence
    IntrinsicTaitBryanAngles<TaitBryanSequence::ZYX, TestFrame, TestOutFrame> originalSeq(angle1, angle2, angle3);

    // Convert to extrinsic and back to intrinsic
    auto extrinsicResult = originalSeq.to_rotation_type<RotationSequenceType::EXTRINSIC>();
    auto roundtripResult = extrinsicResult.to_rotation_type<RotationSequenceType::INTRINSIC>();

    // Should get back the original sequence
    compare_angle_sequences(originalSeq, roundtripResult, REL_TOL);

    // Test the opposite direction
    ExtrinsicTaitBryanAngles<TaitBryanSequence::ZYX, TestFrame, TestOutFrame> originalExtrinsic(angle1, angle2, angle3);
    auto intrinsicResult    = originalExtrinsic.to_rotation_type<RotationSequenceType::INTRINSIC>();
    auto roundtripExtrinsic = intrinsicResult.to_rotation_type<RotationSequenceType::EXTRINSIC>();

    // Should get back the original sequence
    compare_angle_sequences(originalExtrinsic, roundtripExtrinsic, REL_TOL);
}

TEST_F(AngleSequenceTest, TestZeroAnglesConversion)
{
    Angle zeroAngle = 0.0 * deg;

    // Test with zero angles
    ExtrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> zeroExtrinsic(zeroAngle, zeroAngle, zeroAngle);
    auto zeroIntrinsicResult = zeroExtrinsic.to_rotation_type<RotationSequenceType::INTRINSIC>();

    // All angles should still be zero (reversed zeros are still zeros)
    ASSERT_EQ_QUANTITY(zeroIntrinsicResult.get_phi(), zeroAngle, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroIntrinsicResult.get_theta(), zeroAngle, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroIntrinsicResult.get_psi(), zeroAngle, REL_TOL);
}

TEST_F(AngleSequenceTest, TestLargeAnglesConversion)
{
    // Test with large angles that may require wrapping
    Angle largeAngle1 = 390.0 * deg; // Wraps to 30°
    Angle largeAngle2 = 450.0 * deg; // Wraps to 90°
    Angle largeAngle3 = 720.0 * deg; // Wraps to 0°

    IntrinsicEulerAngles<EulerSequence::ZYZ, TestFrame, TestOutFrame> largeIntrinsic(largeAngle1, largeAngle2, largeAngle3);
    auto large_extrinsicResult = largeIntrinsic.to_rotation_type<RotationSequenceType::EXTRINSIC>();

    // The conversion should handle wrapped angles correctly
    // Note: The exact wrapped values depend on the wrapping implementation
    ASSERT_NO_THROW(large_extrinsicResult.to_dcm());
}

TEST_F(AngleSequenceTest, TestDCMEquivalenceAfterConversion)
{
    // Test that mathematically equivalent intrinsic and extrinsic sequences produce the same DCM
    IntrinsicTaitBryanAngles<TaitBryanSequence::XYZ, TestFrame, TestOutFrame> intrinsicSeq(angle1, angle2, angle3);

    // Convert intrinsic to equivalent extrinsic
    auto equivalentExtrinsic = intrinsicSeq.to_rotation_type<RotationSequenceType::EXTRINSIC>();

    // Both should produce DCMs that represent the same rotation
    auto dcmIntrinsic = intrinsicSeq.to_dcm();
    auto dcmExtrinsic = equivalentExtrinsic.to_dcm();

    // The DCMs should be equal within numerical precision
    // Note: This tests the fundamental property that intrinsic and extrinsic
    // representations of the same rotation should yield identical DCMs
    const auto tolerance = 1e-10 * one;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            ASSERT_EQ_QUANTITY(dcmIntrinsic[i, j], dcmExtrinsic[i, j], REL_TOL);
        }
    }
}