/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <numbers>

#include <mp-units/systems/si.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/state/attitude/EulerAngles.hpp>

#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::si::unit_symbols::rad;

inline constexpr auto InFrame  = frames::earth::icrf;
inline constexpr auto OutFrame = frames::earth::j2000;
using TestDcm                  = DCM<InFrame, OutFrame>;
using TestVec                  = CartesianVector<Unitless, InFrame>;

class DirectionCosineMatrixTest : public testing::Test {
  public:
    const TestVec x_hat = { 1.0 * one, 0.0 * one, 0.0 * one };
    const TestVec y_hat = { 0.0 * one, 1.0 * one, 0.0 * one };
    const TestVec z_hat = { 0.0 * one, 0.0 * one, 1.0 * one };
    const TestVec neg_x = { -1.0 * one, 0.0 * one, 0.0 * one };
    const TestVec neg_y = { 0.0 * one, -1.0 * one, 0.0 * one };
    const TestVec neg_z = { 0.0 * one, 0.0 * one, -1.0 * one };

    const Unitless REL_TOL = 1.0e-10 * one;
    const Unitless ABS_TOL = 1.0e-14 * one;

    const Angle PI_OVER_2 = std::numbers::pi / 2.0 * rad;
    const Angle PI        = std::numbers::pi * rad;
    const Angle ZERO_RAD  = 0.0 * rad;
};

TEST_F(DirectionCosineMatrixTest, IdentityDeterminantIsOne)
{
    const auto dcm = TestDcm::identity();
    EXPECT_TRUE(math::nearly_equal(dcm.determinant(), 1.0 * one, REL_TOL));
}

TEST_F(DirectionCosineMatrixTest, IdentityTraceIsThree)
{
    const auto dcm = TestDcm::identity();
    EXPECT_TRUE(math::nearly_equal(dcm.trace(), 3.0 * one, REL_TOL));
}

TEST_F(DirectionCosineMatrixTest, IdentityMultipliesXHatToXHat)
{
    const auto result = TestDcm::identity() * x_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 1.0 * one, 0.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, IdentityMultipliesYHatToYHat)
{
    const auto result = TestDcm::identity() * y_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, IdentityMultipliesZHatToZHat)
{
    const auto result = TestDcm::identity() * z_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 0.0 * one, 1.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, IdentityRowAccessMatchesRows)
{
    const auto dcm = TestDcm::identity();
    EXPECT_TRUE(nearly_equal(dcm.row(0), x_hat, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm.row(1), y_hat, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm.row(2), z_hat, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, IdentityElementAccessMatchesDiagonal)
{
    const auto dcm = TestDcm::identity();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, REL_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, REL_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, REL_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, REL_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, REL_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, REL_TOL));
}

TEST_F(DirectionCosineMatrixTest, XZeroRotationEqualsIdentity)
{
    const auto dcm = TestDcm::X(ZERO_RAD);
    EXPECT_TRUE(nearly_equal(dcm, TestDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XHalfPiLeavesXHatUnchanged)
{
    // x-axis rotation leaves x-hat unchanged
    const auto result = TestDcm::X(PI_OVER_2) * x_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 1.0 * one, 0.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XHalfPiRotatesYHatToZHat)
{
    // R_x(90°) * y = z
    const auto result = TestDcm::X(PI_OVER_2) * y_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 0.0 * one, 1.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XHalfPiRotatesZHatToNegYHat)
{
    // R_x(90°) * z = -y
    const auto result = TestDcm::X(PI_OVER_2) * z_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, -1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XPiRotatesYHatToNegYHat)
{
    const auto result = TestDcm::X(PI) * y_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, -1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XRotationDeterminantIsOne)
{
    EXPECT_TRUE(math::nearly_equal(TestDcm::X(PI_OVER_2).determinant(), 1.0 * one, REL_TOL));
}

TEST_F(DirectionCosineMatrixTest, YZeroRotationEqualsIdentity)
{
    const auto dcm = TestDcm::Y(ZERO_RAD);
    EXPECT_TRUE(nearly_equal(dcm, TestDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, YHalfPiLeavesYHatUnchanged)
{
    const auto result = TestDcm::Y(PI_OVER_2) * y_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, YHalfPiRotatesZHatToXHat)
{
    // R_y(90°) * z = x
    const auto result = TestDcm::Y(PI_OVER_2) * z_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 1.0 * one, 0.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, YHalfPiRotatesXHatToNegZHat)
{
    // R_y(90°) * x = -z
    const auto result = TestDcm::Y(PI_OVER_2) * x_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 0.0 * one, -1.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, YRotationDeterminantIsOne)
{
    EXPECT_NEAR(TestDcm::Y(PI_OVER_2).determinant().numerical_value_in(one), 1.0, 1e-12);
}

TEST_F(DirectionCosineMatrixTest, ZZeroRotationEqualsIdentity)
{
    const auto dcm = TestDcm::Z(ZERO_RAD);
    EXPECT_TRUE(nearly_equal(dcm, TestDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZHalfPiLeavesZHatUnchanged)
{
    const auto result = TestDcm::Z(PI_OVER_2) * z_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 0.0 * one, 1.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZHalfPiRotatesXHatToYHat)
{
    // R_z(90°) * x = y
    const auto result = TestDcm::Z(PI_OVER_2) * x_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, 1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZHalfPiRotatesYHatToNegXHat)
{
    // R_z(90°) * y = -x
    const auto result = TestDcm::Z(PI_OVER_2) * y_hat;
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ -1.0 * one, 0.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZRotationDeterminantIsOne)
{
    EXPECT_NEAR(TestDcm::Z(PI_OVER_2).determinant().numerical_value_in(one), 1.0, 1e-12);
}

TEST_F(DirectionCosineMatrixTest, TransposeOfIdentityIsIdentity)
{
    using ReverseDcm      = DCM<OutFrame, InFrame>;
    const auto transposed = TestDcm::identity().transpose();
    EXPECT_TRUE(nearly_equal(transposed, ReverseDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XRotationTransposeIsInverse)
{
    // R^T * R * v = v for any v
    const auto dcm      = TestDcm::X(PI_OVER_2);
    const auto inv      = dcm.transpose(); // DCM<OutFrame, InFrame>
    const auto rotated  = dcm * x_hat;
    const auto restored = inv * rotated;
    EXPECT_TRUE(nearly_equal(restored, x_hat, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, YRotationTransposeIsInverse)
{
    const auto dcm      = TestDcm::Y(PI_OVER_2);
    const auto inv      = dcm.transpose();
    const auto rotated  = dcm * z_hat;
    const auto restored = inv * rotated;
    EXPECT_TRUE(nearly_equal(restored, z_hat, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZRotationTransposeIsInverse)
{
    const auto dcm      = TestDcm::Z(PI_OVER_2);
    const auto inv      = dcm.transpose();
    const auto rotated  = dcm * y_hat;
    const auto restored = inv * rotated;
    EXPECT_TRUE(nearly_equal(restored, y_hat, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, TransposeSwapsFrameParameters)
{
    const auto transposed = TestDcm::identity().transpose();
    static_assert(std::is_same_v<std::remove_const_t<decltype(transposed)>, DCM<OutFrame, InFrame>>);
    SUCCEED();
}

TEST_F(DirectionCosineMatrixTest, FromVectorsWithBasisProducesIdentity)
{
    const auto dcm = TestDcm::from_vectors(x_hat, y_hat, z_hat);
    EXPECT_TRUE(nearly_equal(dcm, TestDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromVectorsAppliedToXHatGivesFirstRow)
{
    // from_vectors(a, b, c) * x = a
    const TestVec row0 = { 0.0 * one, 1.0 * one, 0.0 * one };
    const TestVec row1 = { -1.0 * one, 0.0 * one, 0.0 * one };
    const TestVec row2 = z_hat;
    const auto dcm     = TestDcm::from_vectors(row0, row1, row2);
    const auto result  = dcm * x_hat; // Should equal -row0 cause these make a left-handed system
    EXPECT_TRUE(nearly_equal(result, CartesianVector<Unitless, OutFrame>{ 0.0 * one, -1.0 * one, 0.0 * one }, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZeroMatrixThrowsOnConstruction)
{
    EXPECT_THROW((TestDcm{ { 0.0 * one, 0.0 * one, 0.0 * one }, { 0.0 * one, 0.0 * one, 0.0 * one }, { 0.0 * one, 0.0 * one, 0.0 * one } }), std::runtime_error);
}

TEST_F(DirectionCosineMatrixTest, XYZWithZeroAnglesEqualsIdentity)
{
    const auto dcm = TestDcm::XYZ(ZERO_RAD, ZERO_RAD, ZERO_RAD);
    EXPECT_TRUE(nearly_equal(dcm, TestDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZYXWithZeroAnglesEqualsIdentity)
{
    const auto dcm = TestDcm::ZYX(ZERO_RAD, ZERO_RAD, ZERO_RAD);
    EXPECT_TRUE(nearly_equal(dcm, TestDcm::identity(), REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, ZYXWithSingleAngleMatchesSingleAxisRotation)
{
    // ZYX(alpha=π/2, 0, 0) should equal Z(π/2)
    const auto zyx = TestDcm::ZYX(PI_OVER_2, ZERO_RAD, ZERO_RAD);
    const auto z   = TestDcm::Z(PI_OVER_2);
    EXPECT_TRUE(nearly_equal(zyx, z, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XYZWithSingleAngleMatchesSingleAxisRotation)
{
    // XYZ(0, 0, gamma=π/2) should equal Z(π/2)
    const auto xyz = TestDcm::XYZ(ZERO_RAD, ZERO_RAD, PI_OVER_2);
    const auto z   = TestDcm::Z(PI_OVER_2);
    EXPECT_TRUE(nearly_equal(xyz, z, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, XYZDeterminantIsOne)
{
    const auto dcm = TestDcm::XYZ(0.1 * rad, 0.2 * rad, 0.3 * rad);
    EXPECT_TRUE(math::nearly_equal(dcm.determinant(), 1.0 * one, REL_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesXYZProducesSameResultAsXYZ)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::XYZ, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcmi1    = TestDcm::XYZ(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcmi2    = intrinsic.to_dcm();
    const TestDcm dcmi3 = DCM<InFrame, InFrame>::X(intrinsic[0]) * DCM<InFrame, InFrame>::Y(intrinsic[1]) *
                          DCM<InFrame, OutFrame>::Z(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcmi1, dcmi2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcmi1, dcmi3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::XYZ, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcme1    = TestDcm::ZYX(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcme2    = extrinsic.to_dcm();
    const TestDcm dcme3 = DCM<InFrame, InFrame>::Z(extrinsic[2]) * DCM<InFrame, InFrame>::Y(extrinsic[1]) *
                          DCM<InFrame, OutFrame>::X(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcme1, dcme2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcme1, dcme3, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesZYXProducesSameResultAsZYX)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::ZYX, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcmi1    = TestDcm::ZYX(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcmi2    = intrinsic.to_dcm();
    const TestDcm dcmi3 = DCM<InFrame, InFrame>::Z(intrinsic[0]) * DCM<InFrame, InFrame>::Y(intrinsic[1]) *
                          DCM<InFrame, OutFrame>::X(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcmi1, dcmi2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcmi1, dcmi3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::ZYX, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcme1    = TestDcm::XYZ(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcme2    = extrinsic.to_dcm();
    const TestDcm dcme3 = DCM<InFrame, InFrame>::X(extrinsic[2]) * DCM<InFrame, InFrame>::Y(extrinsic[1]) *
                          DCM<InFrame, OutFrame>::Z(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcme1, dcme2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcme1, dcme3, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesYXZProducesSameResultAsYXZ)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::YXZ, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcmi1    = TestDcm::YXZ(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcmi2    = intrinsic.to_dcm();
    const TestDcm dcmi3 = DCM<InFrame, InFrame>::Y(intrinsic[0]) * DCM<InFrame, InFrame>::X(intrinsic[1]) *
                          DCM<InFrame, OutFrame>::Z(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcmi1, dcmi2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcmi1, dcmi3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::YXZ, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcme1    = TestDcm::ZXY(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcme2    = extrinsic.to_dcm();
    const TestDcm dcme3 = DCM<InFrame, InFrame>::Z(extrinsic[2]) * DCM<InFrame, InFrame>::X(extrinsic[1]) *
                          DCM<InFrame, OutFrame>::Y(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcme1, dcme2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcme1, dcme3, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesXZXProducesSameResultAsXZX)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::XZX, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::XZX(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::X(intrinsic[0]) * DCM<InFrame, InFrame>::Z(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::X(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::XZX, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::XZX(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::X(extrinsic[2]) * DCM<InFrame, InFrame>::Z(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::X(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesZXYProducesSameResultAsZXY)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::ZXY, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::ZXY(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::Z(intrinsic[0]) * DCM<InFrame, InFrame>::X(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::Y(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::ZXY, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::YXZ(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::Y(extrinsic[2]) * DCM<InFrame, InFrame>::X(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::Z(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesYZYProducesSameResultAsYZY)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::YZY, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::YZY(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::Y(intrinsic[0]) * DCM<InFrame, InFrame>::Z(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::Y(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::YZY, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::YZY(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::Y(extrinsic[2]) * DCM<InFrame, InFrame>::Z(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::Y(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesZYZProducesSameResultAsZYZ)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::ZYZ, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::ZYZ(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::Z(intrinsic[0]) * DCM<InFrame, InFrame>::Y(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::Z(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::ZYZ, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::ZYZ(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::Z(extrinsic[2]) * DCM<InFrame, InFrame>::Y(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::Z(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesYXYProducesSameResultAsYXY)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::YXY, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::YXY(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::Y(intrinsic[0]) * DCM<InFrame, InFrame>::X(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::Y(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::YXY, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::YXY(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::Y(extrinsic[2]) * DCM<InFrame, InFrame>::X(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::Y(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesXZYProducesSameResultAsXZY)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::XZY, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::XZY(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::X(intrinsic[0]) * DCM<InFrame, InFrame>::Z(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::Y(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::XZY, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::YZX(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::Y(extrinsic[2]) * DCM<InFrame, InFrame>::Z(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::X(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesXYXProducesSameResultAsXYX)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::XYX, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::XYX(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::X(intrinsic[0]) * DCM<InFrame, InFrame>::Y(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::X(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::XYX, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::XYX(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::X(extrinsic[2]) * DCM<InFrame, InFrame>::Y(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::X(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

TEST_F(DirectionCosineMatrixTest, FromEulerAnglesZXZProducesSameResultAsZXZ)
{
    const auto intrinsic =
        EulerAngles<RotationSequence::ZXZ, RotationType::INTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm1    = TestDcm::ZXZ(intrinsic[0], intrinsic[1], intrinsic[2]);
    const auto dcm2    = intrinsic.to_dcm();
    const TestDcm dcm3 = DCM<InFrame, InFrame>::Z(intrinsic[0]) * DCM<InFrame, InFrame>::X(intrinsic[1]) *
                         DCM<InFrame, OutFrame>::Z(intrinsic[2]);
    EXPECT_TRUE(nearly_equal(dcm1, dcm2, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm1, dcm3, REL_TOL, ABS_TOL));

    const auto extrinsic =
        EulerAngles<RotationSequence::ZXZ, RotationType::EXTRINSIC, InFrame, OutFrame>(0.1 * rad, 0.2 * rad, 0.3 * rad);
    const auto dcm4    = TestDcm::ZXZ(extrinsic[2], extrinsic[1], extrinsic[0]);
    const auto dcm5    = extrinsic.to_dcm();
    const TestDcm dcm6 = DCM<InFrame, InFrame>::Z(extrinsic[2]) * DCM<InFrame, InFrame>::X(extrinsic[1]) *
                         DCM<InFrame, OutFrame>::Z(extrinsic[0]);
    EXPECT_TRUE(nearly_equal(dcm4, dcm5, REL_TOL, ABS_TOL));
    EXPECT_TRUE(nearly_equal(dcm4, dcm6, REL_TOL, ABS_TOL));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}