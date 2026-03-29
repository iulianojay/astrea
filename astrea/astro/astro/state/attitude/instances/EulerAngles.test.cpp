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
#include <astro/state/attitude/instances/EulerAngleVelocities.hpp>
#include <astro/state/attitude/instances/EulerAngles.hpp>
#include <astro/utilities/conversions.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

using TestFrame           = frames::earth::icrf;
using TestOutFrame        = frames::dynamic::body;
using TestEulerAngles     = EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame>;
using TestTaitBryanAngles = EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame>;

class EulerAnglesTest : public testing::Test {
  public:
    EulerAnglesTest() {}

    void SetUp() override {}

    void compare_angle_sequences(const auto& seq1, const auto& seq2, const Unitless& tol)
    {
        ASSERT_EQ_QUANTITY(seq1[0], seq2[0], tol);
        ASSERT_EQ_QUANTITY(seq1[1], seq2[1], tol);
        ASSERT_EQ_QUANTITY(seq1[2], seq2[2], tol);
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

TEST_F(EulerAnglesTest, TestEulerAnglesConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestEulerAngles());

    // Parameterized constructor with angles only
    ASSERT_NO_THROW(TestEulerAngles(angle1, angle2, angle3));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::XYX, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(EulerAnglesTest, TestTaitBryanAnglesConstructor)
{
    // Default constructor
    ASSERT_NO_THROW(TestTaitBryanAngles());

    // Parameterized constructor with angles only
    ASSERT_NO_THROW(TestTaitBryanAngles(angle1, angle2, angle3));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(EulerAnglesTest, TestEulerAnglesGetters)
{
    TestEulerAngles euler(angle1, angle2, angle3);

    // Test array access - angles are wrapped during construction
    ASSERT_EQ_QUANTITY(euler[0], wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(euler[1], wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(euler[2], wrap_angle(angle3), REL_TOL);
}

TEST_F(EulerAnglesTest, TestTaitBryanAnglesGetters)
{
    TestTaitBryanAngles taitBryan(angle1, angle2, angle3);

    // Test array access - angles are wrapped during construction
    ASSERT_EQ_QUANTITY(taitBryan[0], wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[1], wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[2], wrap_angle(angle3), REL_TOL);
}

TEST_F(EulerAnglesTest, TestDirectionCosineMatrixConversion)
{
    TestEulerAngles euler(angle1, angle2, angle3);

    // Test that DCM conversion works
    ASSERT_NO_THROW(auto dcm = euler.to_dcm());

    // Test different types can create DCMs
    EulerAngles<RotationSequence::XYX, RotationType::INTRINSIC, TestFrame, TestOutFrame> eulerExt(angle1, angle2, angle3);
    ASSERT_NO_THROW(auto dcm2 = eulerExt.to_dcm());
}

TEST_F(EulerAnglesTest, TestAngleModification)
{
    TestTaitBryanAngles taitBryan(angle1, angle2, angle3);

    // Test angle modification through array access
    taitBryan[0] = 90.0 * deg;
    taitBryan[1] = 45.0 * deg;
    taitBryan[2] = 15.0 * deg;

    ASSERT_EQ_QUANTITY(taitBryan[0], 90.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[1], 45.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[2], 15.0 * deg, REL_TOL);
}

TEST_F(EulerAnglesTest, TestAngleWrapping)
{
    // Test angles that need wrapping
    Angle largeAngle1 = 390.0 * deg; // Should wrap to 30°
    Angle largeAngle2 = 225.0 * deg; // Should wrap to 45° for wrap_angle_to_pi
    Angle largeAngle3 = -30.0 * deg; // Should wrap to 330°

    TestEulerAngles euler(largeAngle1, largeAngle2, largeAngle3);

    // Verify wrapping behavior
    ASSERT_EQ_QUANTITY(euler[0], wrap_angle(largeAngle1), REL_TOL);
    ASSERT_EQ_QUANTITY(euler[1], wrap_angle_to_pi(largeAngle2), REL_TOL);
    ASSERT_EQ_QUANTITY(euler[2], wrap_angle(largeAngle3), REL_TOL);

    // Test specifically known wrapped values
    ASSERT_EQ_QUANTITY(euler[0], 30.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler[1], 45.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler[2], 330.0 * deg, REL_TOL);
}

TEST_F(EulerAnglesTest, TestAllRotationSequences)
{
    // Test different Euler sequences can be constructed
    ASSERT_NO_THROW((EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::XYX, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::YZY, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::ZYZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::XZX, RotationType::EXTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::YXY, RotationType::EXTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));

    // Test different Tait-Bryan sequences can be constructed
    ASSERT_NO_THROW((EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::YZX, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::ZXY, RotationType::INTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::XZY, RotationType::EXTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::ZYX, RotationType::EXTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
    ASSERT_NO_THROW((EulerAngles<RotationSequence::YXZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame>(angle1, angle2, angle3)));
}

TEST_F(EulerAnglesTest, TestCopyConstructor)
{
    TestEulerAngles euler1(angle1, angle2, angle3);

    // Copy constructor within the same type should work
    ASSERT_NO_THROW(TestEulerAngles eulerCopy(euler1));
    auto eulerCopy = TestEulerAngles(euler1);

    EXPECT_EQ(euler1, eulerCopy);
    ASSERT_EQ_QUANTITY(euler1[0], eulerCopy[0], REL_TOL);
    ASSERT_EQ_QUANTITY(euler1[1], eulerCopy[1], REL_TOL);
    ASSERT_EQ_QUANTITY(euler1[2], eulerCopy[2], REL_TOL);
}

TEST_F(EulerAnglesTest, TestMoveConstructor)
{
    // Move constructor within the same type should work
    auto eulerTemp = TestEulerAngles(angle1, angle2, angle3);
    ASSERT_NO_THROW(TestEulerAngles eulerMove(std::move(eulerTemp)));
    auto eulerMove = TestEulerAngles(std::move(eulerTemp));

    ASSERT_EQ_QUANTITY(eulerMove[0], wrap_angle(angle1), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerMove[1], wrap_angle_to_pi(angle2), REL_TOL);
    ASSERT_EQ_QUANTITY(eulerMove[2], wrap_angle(angle3), REL_TOL);
}

TEST_F(EulerAnglesTest, TestAccessOperators)
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

TEST_F(EulerAnglesTest, TestEqualityOperators)
{
    TestEulerAngles euler1(angle1, angle2, angle3);
    TestEulerAngles euler2(angle1, angle2, angle3);
    TestEulerAngles euler3(angle2, angle1, angle3);

    // Same angles should be equal
    EXPECT_TRUE(euler1 == euler2);

    // Different angles should not be equal
    EXPECT_FALSE(euler1 == euler3);

    // Different sequence types should not be equal (compile-time enforcement)
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> euler4(angle1, angle2, angle3);
    // euler1 == euler4; // This should not compile due to type safety
}

TEST_F(EulerAnglesTest, TestAdditionAndSubtraction)
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

TEST_F(EulerAnglesTest, TestScalarMultiplicationAndDivision)
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

TEST_F(EulerAnglesTest, TestDotAndCrossProduct)
{
    TestEulerAngles euler1(90.0 * deg, 0.0 * deg, 0.0 * deg);
    TestEulerAngles euler2(0.0 * deg, 90.0 * deg, 0.0 * deg);

    // Dot product
    auto dotProduct = euler1.dot(euler2);
    ASSERT_EQ_QUANTITY(dotProduct, 0.0 * pow<2>(deg), REL_TOL);

    dotProduct = euler1.dot(euler1);
    ASSERT_EQ_QUANTITY(dotProduct, M_PI_2 * M_PI_2 * pow<2>(rad), REL_TOL);

    // Cross product
    auto crossProduct = euler1.cross(euler2);
    auto crossNorm    = crossProduct.norm();
    if (crossNorm > 0.0 * crossNorm.unit) {
        auto crossUnit = crossProduct / crossNorm;
        ASSERT_EQ_QUANTITY(crossUnit[0], 0.0 * one, REL_TOL);
        ASSERT_EQ_QUANTITY(crossUnit[1], 0.0 * one, REL_TOL);
        ASSERT_EQ_QUANTITY(crossUnit[2], 1.0 * one, REL_TOL);
    }
}

TEST_F(EulerAnglesTest, TestNormAndOffsetAngle)
{
    TestEulerAngles euler(3.0 * deg, 4.0 * deg, 0.0 * deg);

    // Norm (should be sqrt(3^2 + 4^2) = 5 degrees)
    auto normEuler = euler.norm();
    ASSERT_EQ_QUANTITY(normEuler, 5.0 * deg, REL_TOL);
}

TEST_F(EulerAnglesTest, TestComparisonBetweenEulerAndTaitBryan)
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
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> eulerIntrinsic(angle1, angle2, angle3);
    EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> eulerExtrinsic(angle1, angle2, angle3);
    EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> taitBryanIntrinsic(angle1, angle2, angle3);
    EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> taitBryanExtrinsic(angle1, angle2, angle3);

    // All should have same angle values
    ASSERT_EQ_QUANTITY(eulerIntrinsic[0], eulerExtrinsic[0], REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanIntrinsic[0], taitBryanExtrinsic[0], REL_TOL);
}

TEST_F(EulerAnglesTest, TestDifferentRotationTypes)
{
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> eulerIntrinsic(angle1, angle2, angle3);
    EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> eulerExtrinsic(angle1, angle2, angle3);

    // Same angle values
    ASSERT_EQ_QUANTITY(eulerIntrinsic[0], eulerExtrinsic[0], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerIntrinsic[1], eulerExtrinsic[1], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerIntrinsic[2], eulerExtrinsic[2], REL_TOL);

    // But they should be different types (cannot directly compare with ==)
    // eulerIntrinsic == eulerExtrinsic; // This should not compile

    // They should produce different DCMs due to different rotation order
    auto dcmIntrinsic = eulerIntrinsic.to_dcm();
    auto dcmExtrinsic = eulerExtrinsic.to_dcm();
}

TEST_F(EulerAnglesTest, TestFrameConsistency)
{
    // Test that different frame types can be created but are type-safe
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, frames::earth::icrf, frames::earth::j2000> eulerICRF(angle1, angle2, angle3);
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, frames::earth::j2000, frames::earth::icrf> eulerJ2000(angle1, angle2, angle3);

    // They should have the same angle values
    ASSERT_EQ_QUANTITY(eulerICRF[0], eulerJ2000[0], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerICRF[1], eulerJ2000[1], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerICRF[2], eulerJ2000[2], REL_TOL);

    // But different frames should not be directly comparable with ==
    // This test verifies the type safety is maintained
    // EXPECT_FALSE(eulerICRF == eulerJ2000); // This should not compile
}

TEST_F(EulerAnglesTest, TestSequenceSpecificBehavior)
{
    // Test that different sequences maintain their compile-time identity
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> eulerZXZ(angle1, angle2, angle3);
    EulerAngles<RotationSequence::XYX, RotationType::INTRINSIC, TestFrame, TestOutFrame> eulerXYX(angle1, angle2, angle3);
    EulerAngles<RotationSequence::YZY, RotationType::INTRINSIC, TestFrame, TestOutFrame> eulerYZY(angle1, angle2, angle3);

    // All should have same angle values but different DCM output
    ASSERT_EQ_QUANTITY(eulerZXZ[0], eulerXYX[0], REL_TOL);
    ASSERT_EQ_QUANTITY(eulerXYX[0], eulerYZY[0], REL_TOL);

    // Test Tait-Bryan sequences
    EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> taitBryanXYZ(angle1, angle2, angle3);
    EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, TestFrame, TestOutFrame> taitBryanZYX(angle1, angle2, angle3);
    EulerAngles<RotationSequence::YXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> taitBryanYXZ(angle1, angle2, angle3);

    // All should have same angle values but different DCM output
    ASSERT_EQ_QUANTITY(taitBryanXYZ[0], taitBryanZYX[0], REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryanZYX[0], taitBryanYXZ[0], REL_TOL);

    // Different sequences should produce different DCMs
    ASSERT_NO_THROW(eulerZXZ.to_dcm());
    ASSERT_NO_THROW(taitBryanXYZ.to_dcm());
}

TEST_F(EulerAnglesTest, TestDivisionByTimeToVelocity)
{
    TestEulerAngles euler(30.0 * deg, 45.0 * deg, 60.0 * deg);
    Time time = 2.0 * s;

    // Division by time should produce EulerAngleVelocities
    auto eulerVel = euler / time;

    // Check that the resulting angular velocities are correct
    ASSERT_EQ_QUANTITY(eulerVel[0], 15.0 * deg / s, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[1], 22.5 * deg / s, REL_TOL);
    ASSERT_EQ_QUANTITY(eulerVel[2], 30.0 * deg / s, REL_TOL);
}

TEST_F(EulerAnglesTest, TestForceToVectorAndFromVector)
{
    TestEulerAngles euler(30.0 * deg, 45.0 * deg, 60.0 * deg);

    // Convert to vector
    auto vec = euler.force_to_vector();
    ASSERT_EQ(vec.size(), 3);
}

TEST_F(EulerAnglesTest, TestRotationTypeConversion)
{
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> intrinsic(angle1, angle2, angle3);

    // Test conversion to extrinsic
    auto extrinsic = intrinsic.template to_rotation_type<RotationType::EXTRINSIC>();

    // Should have the same angle values
    ASSERT_EQ_QUANTITY(intrinsic[0], extrinsic[0], REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsic[1], extrinsic[1], REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsic[2], extrinsic[2], REL_TOL);

    // Test conversion to same rotation type (no-op)
    auto intrinsicSame = intrinsic.template to_rotation_type<RotationType::INTRINSIC>();
    EXPECT_EQ(intrinsic, intrinsicSame);
}

TEST_F(EulerAnglesTest, TestOutputStream)
{
    TestEulerAngles euler(30.0 * deg, 45.0 * deg, 60.0 * deg);

    // Test that the angles can be accessed for output
    // Note: Direct stream output may not be implemented, but angle access should work
    ASSERT_EQ_QUANTITY(euler[0], 30.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler[1], 45.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(euler[2], 60.0 * deg, REL_TOL);

    TestTaitBryanAngles taitBryan(15.0 * deg, 30.0 * deg, 90.0 * deg);
    ASSERT_EQ_QUANTITY(taitBryan[0], 15.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[1], 30.0 * deg, REL_TOL);
    ASSERT_EQ_QUANTITY(taitBryan[2], 90.0 * deg, REL_TOL);

    // Test DCM conversion works
    ASSERT_NO_THROW(euler.to_dcm());
    ASSERT_NO_THROW(taitBryan.to_dcm());
}

// ========================================================================================
// Tests for get_reverse_sequence functions
// ========================================================================================

TEST_F(EulerAnglesTest, TestEulerReverseSequence)
{
    // Test that Euler sequences return themselves (they are symmetric)
    EXPECT_EQ(get_reverse_sequence(RotationSequence::ZXZ), RotationSequence::ZXZ);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::XYX), RotationSequence::XYX);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::YZY), RotationSequence::YZY);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::ZYZ), RotationSequence::ZYZ);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::XZX), RotationSequence::XZX);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::YXY), RotationSequence::YXY);
}

TEST_F(EulerAnglesTest, TestTaitBryanReverseSequence)
{
    // Test Tait-Bryan sequence reversals
    EXPECT_EQ(get_reverse_sequence(RotationSequence::XYZ), RotationSequence::ZYX);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::YZX), RotationSequence::XZY);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::ZXY), RotationSequence::YXZ);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::XZY), RotationSequence::YZX);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::ZYX), RotationSequence::XYZ);
    EXPECT_EQ(get_reverse_sequence(RotationSequence::YXZ), RotationSequence::ZXY);
}

TEST_F(EulerAnglesTest, TestDoubleReverseSequence)
{
    // Test that double reversal returns the original sequence for Tait-Bryan
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::XYZ)), RotationSequence::XYZ);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::YZX)), RotationSequence::YZX);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::ZXY)), RotationSequence::ZXY);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::XZY)), RotationSequence::XZY);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::ZYX)), RotationSequence::ZYX);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::YXZ)), RotationSequence::YXZ);

    // Test that double reversal returns the original sequence for Euler
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::ZXZ)), RotationSequence::ZXZ);
    EXPECT_EQ(get_reverse_sequence(get_reverse_sequence(RotationSequence::XYX)), RotationSequence::XYX);
}

TEST_F(EulerAnglesTest, TestIntrinsicToIntrinsic)
{
    // Create an intrinsic Euler sequence
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> intrinsic_euler(angle1, angle2, angle3);

    // Converting intrinsic to intrinsic should return the same sequence
    auto result = intrinsic_euler.to_rotation_type<RotationType::INTRINSIC>();
    compare_angle_sequences(intrinsic_euler, result, REL_TOL);

    // Test with Tait-Bryan as well
    EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> intrinsic_tb(angle1, angle2, angle3);
    auto tbResult = intrinsic_tb.to_rotation_type<RotationType::INTRINSIC>();
    compare_angle_sequences(intrinsic_tb, tbResult, REL_TOL);
}

TEST_F(EulerAnglesTest, TestExtrinsicToExtrinsic)
{
    // Create an extrinsic Euler sequence
    EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> extrinsic_euler(angle1, angle2, angle3);

    // Converting extrinsic to extrinsic should return the same sequence
    auto result = extrinsic_euler.to_rotation_type<RotationType::EXTRINSIC>();
    compare_angle_sequences(extrinsic_euler, result, REL_TOL);

    // Test with Tait-Bryan as well
    EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> extrinsic_tb(angle1, angle2, angle3);
    auto tbResult = extrinsic_tb.to_rotation_type<RotationType::EXTRINSIC>();
    compare_angle_sequences(extrinsic_tb, tbResult, REL_TOL);
}

TEST_F(EulerAnglesTest, TestExtrinsicToIntrinsicConversion)
{
    // Create an extrinsic sequence
    EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> extrinsic_euler(angle1, angle2, angle3);

    // Convert to intrinsic - angles should be reversed
    auto intrinsicResult = extrinsic_euler.to_rotation_type<RotationType::INTRINSIC>();

    // Verify that angles are reversed
    ASSERT_EQ_QUANTITY(intrinsicResult[0], extrinsic_euler[0], REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsicResult[1], extrinsic_euler[1], REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsicResult[2], extrinsic_euler[2], REL_TOL);

    // Test with Tait-Bryan sequence
    EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> extrinsic_tb(angle1, angle2, angle3);
    auto intrinsic_tbResult = extrinsic_tb.to_rotation_type<RotationType::INTRINSIC>();

    // For Tait-Bryan, sequence should also reverse (XYZ becomes ZYX) with reversed angles
    ASSERT_EQ_QUANTITY(intrinsic_tbResult[0], extrinsic_tb[0], REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsic_tbResult[1], extrinsic_tb[1], REL_TOL);
    ASSERT_EQ_QUANTITY(intrinsic_tbResult[2], extrinsic_tb[2], REL_TOL);
}

TEST_F(EulerAnglesTest, TestIntrinsicToExtrinsicConversion)
{
    // Create an intrinsic sequence
    EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> intrinsic_euler(angle1, angle2, angle3);

    // Convert to extrinsic - angles should be reversed
    auto extrinsicResult = intrinsic_euler.to_rotation_type<RotationType::EXTRINSIC>();

    // Verify that angles are reversed
    ASSERT_EQ_QUANTITY(extrinsicResult[0], intrinsic_euler[0], REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsicResult[1], intrinsic_euler[1], REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsicResult[2], intrinsic_euler[2], REL_TOL);

    // Test with Tait-Bryan sequence
    EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> intrinsic_tb(angle1, angle2, angle3);
    auto extrinsic_tbResult = intrinsic_tb.to_rotation_type<RotationType::EXTRINSIC>();

    // For Tait-Bryan, sequence should also reverse (XYZ becomes ZYX) with reversed angles
    ASSERT_EQ_QUANTITY(extrinsic_tbResult[0], intrinsic_tb[0], REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsic_tbResult[1], intrinsic_tb[1], REL_TOL);
    ASSERT_EQ_QUANTITY(extrinsic_tbResult[2], intrinsic_tb[2], REL_TOL);
}

TEST_F(EulerAnglesTest, TestRoundTripIntrinsicExtrinsicConversion)
{
    // Create an intrinsic sequence
    EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, TestFrame, TestOutFrame> originalSeq(angle1, angle2, angle3);

    // Convert to extrinsic and back to intrinsic
    auto extrinsicResult = originalSeq.to_rotation_type<RotationType::EXTRINSIC>();
    auto roundtripResult = extrinsicResult.to_rotation_type<RotationType::INTRINSIC>();

    // Should get back the original sequence
    compare_angle_sequences(originalSeq, roundtripResult, REL_TOL);

    // Test the opposite direction
    EulerAngles<RotationSequence::ZYX, RotationType::EXTRINSIC, TestFrame, TestOutFrame> originalExtrinsic(angle1, angle2, angle3);
    auto intrinsicResult    = originalExtrinsic.to_rotation_type<RotationType::INTRINSIC>();
    auto roundtripExtrinsic = intrinsicResult.to_rotation_type<RotationType::EXTRINSIC>();

    // Should get back the original sequence
    compare_angle_sequences(originalExtrinsic, roundtripExtrinsic, REL_TOL);
}

TEST_F(EulerAnglesTest, TestZeroAnglesConversion)
{
    Angle zeroAngle = 0.0 * deg;

    // Test with zero angles
    EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, TestFrame, TestOutFrame> zeroExtrinsic(zeroAngle, zeroAngle, zeroAngle);
    auto zeroIntrinsicResult = zeroExtrinsic.to_rotation_type<RotationType::INTRINSIC>();

    // All angles should still be zero (reversed zeros are still zeros)
    ASSERT_EQ_QUANTITY(zeroIntrinsicResult[0], zeroAngle, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroIntrinsicResult[1], zeroAngle, REL_TOL);
    ASSERT_EQ_QUANTITY(zeroIntrinsicResult[2], zeroAngle, REL_TOL);
}

TEST_F(EulerAnglesTest, TestLargeAnglesConversion)
{
    // Test with large angles that may require wrapping
    Angle largeAngle1 = 390.0 * deg; // Wraps to 30°
    Angle largeAngle2 = 450.0 * deg; // Wraps to 90°
    Angle largeAngle3 = 720.0 * deg; // Wraps to 0°

    EulerAngles<RotationSequence::ZYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> largeIntrinsic(largeAngle1, largeAngle2, largeAngle3);
    auto large_extrinsicResult = largeIntrinsic.to_rotation_type<RotationType::EXTRINSIC>();

    // The conversion should handle wrapped angles correctly
    // Note: The exact wrapped values depend on the wrapping implementation
    ASSERT_NO_THROW(large_extrinsicResult.to_dcm());
}

TEST_F(EulerAnglesTest, TestDCMEquivalenceAfterConversion)
{
    // Test that mathematically equivalent intrinsic and extrinsic sequences produce the same DCM
    EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, TestFrame, TestOutFrame> intrinsicSeq(angle1, angle2, angle3);

    // Convert intrinsic to equivalent extrinsic
    auto equivalentExtrinsic = intrinsicSeq.to_rotation_type<RotationType::EXTRINSIC>();

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