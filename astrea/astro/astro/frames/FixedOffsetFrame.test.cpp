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

#include <gtest/gtest.h>

#include <numbers>
#include <type_traits>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/FixedOffsetFrame.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;

// Default (zero-offset) instantiation
using ZeroEarthIcrf = FixedOffsetFrame<frames::earth::icrf, Distance::zero(), Distance::zero(), Distance::zero()>;
using ZeroMarsIcrf  = FixedOffsetFrame<frames::mars::icrf, Distance::zero(), Distance::zero(), Distance::zero()>;

static_assert(ZeroEarthIcrf::origin == CelestialBodyId::FIXED_OFFSET);
static_assert(ZeroEarthIcrf::parent::origin == CelestialBodyId::EARTH);
static_assert(ZeroMarsIcrf::origin == CelestialBodyId::FIXED_OFFSET);
static_assert(ZeroMarsIcrf::parent::origin == CelestialBodyId::MARS);
static_assert(HasSameOrigin<ZeroEarthIcrf, ZeroMarsIcrf>);
static_assert(!HasSameOrigin<ZeroEarthIcrf::parent, ZeroMarsIcrf::parent>);

TEST(FixedOffsetFrameOffset, DefaultOffsetXIsZero)
{
    EXPECT_DOUBLE_EQ(ZeroEarthIcrf::offset.get_x().numerical_value_in(km), 0.0);
}

TEST(FixedOffsetFrameOffset, DefaultOffsetYIsZero)
{
    EXPECT_DOUBLE_EQ(ZeroEarthIcrf::offset.get_y().numerical_value_in(km), 0.0);
}

TEST(FixedOffsetFrameOffset, DefaultOffsetZIsZero)
{
    EXPECT_DOUBLE_EQ(ZeroEarthIcrf::offset.get_z().numerical_value_in(km), 0.0);
}

TEST(FixedOffsetFrameOffset, OffsetIsConstexprAccessible)
{
    // Verifies offset is a constexpr static member
    constexpr auto& off = ZeroEarthIcrf::offset;
    (void)off;
    SUCCEED();
}

static_assert(IsFrame<ZeroEarthIcrf>);
static_assert(IsStaticFrame<ZeroEarthIcrf>);
static_assert(IsInertialFrame<ZeroEarthIcrf>);

static_assert(!HasSameOrigin<ZeroEarthIcrf, frames::earth::icrf>);
static_assert(HasSameOrigin<ZeroEarthIcrf::parent, frames::earth::icrf>);

static_assert(HasSameAxis<ZeroEarthIcrf, frames::earth::icrf>);
static_assert(HasSameAxis<ZeroEarthIcrf::parent, frames::earth::icrf>);

static_assert(!IsSameFrame<ZeroEarthIcrf, frames::earth::icrf>);
static_assert(IsSameFrame<ZeroEarthIcrf::parent, frames::earth::icrf>);

using Also = FixedOffsetFrame<frames::earth::icrf, Distance::zero(), Distance::zero(), Distance::zero()>;
static_assert(std::is_same_v<ZeroEarthIcrf, Also>);
static_assert(IsSameFrame<ZeroEarthIcrf, Also>);
static_assert(!IsSameFrame<ZeroEarthIcrf, ZeroMarsIcrf>);


constexpr Angle HALF_PI_RAD = std::numbers::pi / 2.0 * rad;

// Zero-angle angular offset (all defaults explicit)
using ZeroAngularEarthIcrf =
    FixedOffsetFrame<frames::earth::icrf, Angle::zero(), Angle::zero(), Angle::zero(), RotationSequence::XYZ>;

// XYZ sequence (default) — one axis rotated at a time
using RotXHalfPiXYZ = FixedOffsetFrame<frames::earth::icrf, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ>;
using RotYHalfPiXYZ = FixedOffsetFrame<frames::earth::icrf, Angle::zero(), HALF_PI_RAD, Angle::zero(), RotationSequence::XYZ>;
using RotZHalfPiXYZ = FixedOffsetFrame<frames::earth::icrf, Angle::zero(), Angle::zero(), HALF_PI_RAD, RotationSequence::XYZ>;
// ZYX sequence — same phi angle, different result
using RotXHalfPiZYX = FixedOffsetFrame<frames::earth::icrf, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::ZYX>;

static_assert(ZeroAngularEarthIcrf::origin == CelestialBodyId::FIXED_OFFSET);
static_assert(ZeroAngularEarthIcrf::parent::origin == CelestialBodyId::EARTH);
static_assert(RotXHalfPiXYZ::origin == CelestialBodyId::FIXED_OFFSET);
static_assert(RotXHalfPiXYZ::parent::origin == CelestialBodyId::EARTH);

static_assert(IsFrame<ZeroAngularEarthIcrf>);
static_assert(IsStaticFrame<ZeroAngularEarthIcrf>);
static_assert(IsInertialFrame<ZeroAngularEarthIcrf>);
static_assert(IsFrame<RotXHalfPiXYZ>);
static_assert(IsFrame<RotXHalfPiZYX>);

// Angular and positional FixedOffsetFrames are distinct types
static_assert(!std::is_same_v<ZeroAngularEarthIcrf, ZeroEarthIcrf>);
// Same angles, different sequence → different types
static_assert(!std::is_same_v<RotXHalfPiXYZ, RotXHalfPiZYX>);

static constexpr Unitless ANGULAR_TOL = 1.0e-10 * one;

// Zero-angle angular offset → identity misalignment

TEST(FixedOffsetFrameAngular, ZeroAnglesGivesIdentityMisalignment_Diagonal)
{
    const auto& dcm = get_dcm_from_frame<ZeroAngularEarthIcrf>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, ZeroAnglesGivesIdentityMisalignment_OffDiagonal)
{
    const auto& dcm = get_dcm_from_frame<ZeroAngularEarthIcrf>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
}

// XYZ(pi/2, 0, 0) → pure X-axis rotation:
//   [[1,  0,  0],
//    [0,  0, -1],
//    [0,  1,  0]]

TEST(FixedOffsetFrameAngular, XYZHalfPiPhiGivesXRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, XYZHalfPiPhiGivesXRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, XYZHalfPiPhiGivesXRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// XYZ(0, pi/2, 0) → pure Y-axis rotation:
//   [[ 0, 0, 1],
//    [ 0, 1, 0],
//    [-1, 0, 0]]

TEST(FixedOffsetFrameAngular, XYZHalfPiThetaGivesYRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotYHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 1.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, XYZHalfPiThetaGivesYRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotYHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, XYZHalfPiThetaGivesYRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotYHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// XYZ(0, 0, pi/2) → pure Z-axis rotation:
//   [[ 0, -1, 0],
//    [ 1,  0, 0],
//    [ 0,  0, 1]]

TEST(FixedOffsetFrameAngular, XYZHalfPiPsiGivesZRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotZHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, XYZHalfPiPsiGivesZRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotZHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, XYZHalfPiPsiGivesZRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotZHalfPiXYZ>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

// ZYX(pi/2, 0, 0) = XYZ(0, 0, pi/2) → Z-axis rotation, confirming rotation sequence is applied.
// This differs from XYZ(pi/2, 0, 0) which is an X-rotation.

TEST(FixedOffsetFrameAngular, ZYXHalfPiPhiGivesZRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiZYX>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, ZYXHalfPiPhiGivesZRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiZYX>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, ZYXHalfPiPhiGivesZRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiZYX>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

TEST(FixedOffsetFrameAngular, MisalignmentIsConstexprAccessible)
{
    constexpr auto& m = RotXHalfPiXYZ::misalignment;
    (void)m;
    SUCCEED();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
