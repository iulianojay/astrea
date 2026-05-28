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

#include <astro/frames/framework/FixedOffsetFrame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/frames/frames.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;

class FixedOffsetFrameTest : public testing::Test {
  public:
    FixedOffsetFrameTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// Default (zero-offset) instantiation
using ZeroEarthIcrf = FixedOffsetFrame<frames::earth::icrf, Distance::zero(), Distance::zero(), Distance::zero()>;
using ZeroMarsIcrf  = FixedOffsetFrame<frames::mars::icrf, Distance::zero(), Distance::zero(), Distance::zero()>;

static_assert(HasSpatialOffset<ZeroEarthIcrf>);
static_assert(ZeroEarthIcrf::parent.origin == planets::Earth);
static_assert(HasSpatialOffset<ZeroMarsIcrf>);
static_assert(ZeroMarsIcrf::parent.origin == planets::Mars);
static_assert(ZeroEarthIcrf::origin == ZeroMarsIcrf::origin); // share the same origin (FixedOffsetOrigin), but different parents (Earth vs Mars)
static_assert(ZeroEarthIcrf::parent.origin != ZeroMarsIcrf::parent.origin); // different parents (Earth vs Mars)

TEST_F(FixedOffsetFrameTest, DefaultOffsetXIsZero)
{
    EXPECT_DOUBLE_EQ(get_offset_from_frame<ZeroEarthIcrf{}>().get_x().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, DefaultOffsetYIsZero)
{
    EXPECT_DOUBLE_EQ(get_offset_from_frame<ZeroEarthIcrf{}>().get_y().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, DefaultOffsetZIsZero)
{
    EXPECT_DOUBLE_EQ(get_offset_from_frame<ZeroEarthIcrf{}>().get_z().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, OffsetIsConstexprAccessible)
{
    // Verifies offset is a constexpr static member
    constexpr auto off = get_offset_from_frame<ZeroEarthIcrf{}>();
    (void)off;
    SUCCEED();
}

static_assert(IsFrame<ZeroEarthIcrf>);
static_assert(IsStaticFrame<ZeroEarthIcrf>);
static_assert(IsInertialFrame<ZeroEarthIcrf>);

static_assert(ZeroEarthIcrf{}.origin != frames::earth::icrf.origin);
static_assert(ZeroEarthIcrf::parent.origin == frames::earth::icrf.origin);

static_assert(ZeroEarthIcrf{}.axis == frames::earth::icrf.axis);
static_assert(ZeroEarthIcrf::parent.axis == frames::earth::icrf.axis);

static_assert(ZeroEarthIcrf{} != frames::earth::icrf);
static_assert(ZeroEarthIcrf::parent == frames::earth::icrf);

using Also = FixedOffsetFrame<frames::earth::icrf, Distance::zero(), Distance::zero(), Distance::zero()>;
static_assert(std::is_same_v<ZeroEarthIcrf, Also>);
static_assert(ZeroEarthIcrf{} == Also{});
static_assert(ZeroEarthIcrf{} != ZeroMarsIcrf{});


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

static_assert(HasAngularOffset<ZeroAngularEarthIcrf>);
static_assert(ZeroAngularEarthIcrf::parent.origin == planets::Earth);
static_assert(HasAngularOffset<RotXHalfPiXYZ>);
static_assert(RotXHalfPiXYZ::parent.origin == planets::Earth);

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

TEST_F(FixedOffsetFrameTest, ZeroAnglesGivesIdentityMisalignment_Diagonal)
{
    const auto& dcm = get_dcm_from_frame<ZeroAngularEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, ZeroAnglesGivesIdentityMisalignment_OffDiagonal)
{
    const auto& dcm = get_dcm_from_frame<ZeroAngularEarthIcrf{}>();
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

TEST_F(FixedOffsetFrameTest, XYZHalfPiPhiGivesXRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, XYZHalfPiPhiGivesXRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, XYZHalfPiPhiGivesXRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// XYZ(0, pi/2, 0) → pure Y-axis rotation:
//   [[ 0, 0, 1],
//    [ 0, 1, 0],
//    [-1, 0, 0]]

TEST_F(FixedOffsetFrameTest, XYZHalfPiThetaGivesYRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotYHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, XYZHalfPiThetaGivesYRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotYHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, XYZHalfPiThetaGivesYRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotYHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// XYZ(0, 0, pi/2) → pure Z-axis rotation:
//   [[ 0, -1, 0],
//    [ 1,  0, 0],
//    [ 0,  0, 1]]

TEST_F(FixedOffsetFrameTest, XYZHalfPiPsiGivesZRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotZHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, XYZHalfPiPsiGivesZRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotZHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, XYZHalfPiPsiGivesZRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotZHalfPiXYZ{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

// ZYX(pi/2, 0, 0) = XYZ(0, 0, pi/2) → Z-axis rotation, confirming rotation sequence is applied.
// This differs from XYZ(pi/2, 0, 0) which is an X-rotation.

TEST_F(FixedOffsetFrameTest, ZYXHalfPiPhiGivesZRotation_FirstRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiZYX{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, ZYXHalfPiPhiGivesZRotation_SecondRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiZYX{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, ZYXHalfPiPhiGivesZRotation_ThirdRow)
{
    const auto& dcm = get_dcm_from_frame<RotXHalfPiZYX{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, MisalignmentIsConstexprAccessible)
{
    constexpr auto& m = RotXHalfPiXYZ::axis.misalignment;
    (void)m;
    SUCCEED();
}

// ==================== Combined (offset + angular misalignment) ====================

constexpr Distance ONE_KM   = 1.0 * km;
constexpr Distance TWO_KM   = 2.0 * km;
constexpr Distance THREE_KM = 3.0 * km;

// Frame with both translational offset and angular misalignment (phi = pi/2, XYZ).
// offset = (1, 2, 3) km; misalignment = Rx(pi/2)
using CombinedEarthIcrf =
    FixedOffsetFrame<frames::earth::icrf, ONE_KM, TWO_KM, THREE_KM, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ>;

static_assert(HasSpatialOffset<CombinedEarthIcrf>);
static_assert(HasAngularOffset<CombinedEarthIcrf>);
static_assert(IsFixedOffsetFrame<CombinedEarthIcrf>);

// get_offset_from_frame returns the declared translational offset
TEST_F(FixedOffsetFrameTest, GetOffsetFromFrameReturnsCorrectX)
{
    const auto off = get_offset_from_frame<CombinedEarthIcrf{}>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromFrameReturnsCorrectY)
{
    const auto off = get_offset_from_frame<CombinedEarthIcrf{}>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromFrameReturnsCorrectZ)
{
    const auto off = get_offset_from_frame<CombinedEarthIcrf{}>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 3.0);
}

// get_dcm_from_frame returns Rx(pi/2) — same result as RotXHalfPiXYZ despite also having an offset
// [[1, 0,  0],
//  [0, 0, -1],
//  [0, 1,  0]]
TEST_F(FixedOffsetFrameTest, GetDcmFromFrameFirstRow)
{
    const auto dcm = get_dcm_from_frame<CombinedEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, GetDcmFromFrameSecondRow)
{
    const auto dcm = get_dcm_from_frame<CombinedEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, GetDcmFromFrameThirdRow)
{
    const auto dcm = get_dcm_from_frame<CombinedEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// get_offset_from_root_frame for a non-derived parent is identical to get_offset_from_frame
TEST_F(FixedOffsetFrameTest, GetOffsetFromRootFrameMatchesFromFrameX)
{
    const auto off = get_offset_from_root_frame<CombinedEarthIcrf{}>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromRootFrameMatchesFromFrameY)
{
    const auto off = get_offset_from_root_frame<CombinedEarthIcrf{}>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromRootFrameMatchesFromFrameZ)
{
    const auto off = get_offset_from_root_frame<CombinedEarthIcrf{}>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 3.0);
}

// get_dcm_from_root_frame for a non-derived parent is identical to get_dcm_from_frame
TEST_F(FixedOffsetFrameTest, GetDcmFromRootFrameMatchesFromFrameFirstRow)
{
    const auto dcm = get_dcm_from_root_frame<CombinedEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, GetDcmFromRootFrameMatchesFromFrameSecondRow)
{
    const auto dcm = get_dcm_from_root_frame<CombinedEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, GetDcmFromRootFrameMatchesFromFrameThirdRow)
{
    const auto dcm = get_dcm_from_root_frame<CombinedEarthIcrf{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// ==================== Chained frames ====================

// Pure spatial offset chain: 1 km in X, then 2 km in Y from that child frame.
using ChainOffset1 = FixedOffsetFrame<frames::earth::icrf, ONE_KM, Distance::zero(), Distance::zero()>;
using ChainOffset2 = FixedOffsetFrame<ChainOffset1{}, Distance::zero(), TWO_KM, Distance::zero()>;

static_assert(IsFixedOffsetFrame<ChainOffset1>);
static_assert(IsFixedOffsetFrame<ChainOffset2>);
static_assert(IsDerivedFrame<ChainOffset1>);

// get_offset_from_root_frame accumulates both offsets
TEST_F(FixedOffsetFrameTest, SpatialChainRootOffsetAccumulatesX)
{
    const auto off = get_offset_from_root_frame<ChainOffset2{}>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, SpatialChainRootOffsetAccumulatesY)
{
    const auto off = get_offset_from_root_frame<ChainOffset2{}>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, SpatialChainRootOffsetZIsZero)
{
    const auto off = get_offset_from_root_frame<ChainOffset2{}>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 0.0);
}

// Pure angular chain: Rx(pi/2) then Rz(pi/2).
// Composed from root = Rx(pi/2) * Rz(pi/2):
//   [[0, -1,  0],
//    [0,  0, -1],
//    [1,  0,  0]]
using ChainAngular1 = FixedOffsetFrame<frames::earth::icrf, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ>;
using ChainAngular2 = FixedOffsetFrame<ChainAngular1{}, Angle::zero(), Angle::zero(), HALF_PI_RAD, RotationSequence::XYZ>;

static_assert(IsFixedOffsetFrame<ChainAngular1>);
static_assert(IsFixedOffsetFrame<ChainAngular2>);

TEST_F(FixedOffsetFrameTest, AngularChainRootDcmComposesFirstRow)
{
    const auto dcm = get_dcm_from_root_frame<ChainAngular2{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, AngularChainRootDcmComposesSecondRow)
{
    const auto dcm = get_dcm_from_root_frame<ChainAngular2{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, AngularChainRootDcmComposesThirdRow)
{
    const auto dcm = get_dcm_from_root_frame<ChainAngular2{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// A pure-offset child of a rotated parent has no angular contribution of its own —
// get_dcm_from_root_frame should propagate the parent's DCM unchanged.
TEST_F(FixedOffsetFrameTest, SpatialChildOfAngularParentPreserversParentDcmFirstRow)
{
    // ChainOffset2 has no angular misalignment; its parent ChainAngular1 is Rx(pi/2).
    // get_dcm_from_root_frame<ChainOffset2 derived from ChainAngular1> is not defined
    // because ChainOffset2 must be derived from ChainAngular1 to test this.
    // Use an explicit type: spatial offset child of ChainAngular1.
    using OffsetChildOfAngular = FixedOffsetFrame<ChainAngular1{}, Distance::zero(), TWO_KM, Distance::zero()>;
    const auto dcm             = get_dcm_from_root_frame<OffsetChildOfAngular{}>();
    // No own rotation → DCM is that of ChainAngular1 = Rx(pi/2)
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
}

// Combined offset+misalignment frame derived from another combined frame.
// Parent (ChainCombined1): 1 km in X, Rx(pi/2)
// Child  (ChainCombined2): 2 km in Y (relative to parent), Rz(pi/2)
//
// Accumulated offset from root = (1, 2, 0) km (both offsets summed numerically)
// Composed DCM from root       = Rx(pi/2) * Rz(pi/2) = [[0,-1,0],[0,0,-1],[1,0,0]]
using ChainCombined1 =
    FixedOffsetFrame<frames::earth::icrf, ONE_KM, Distance::zero(), Distance::zero(), HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ>;
using ChainCombined2 =
    FixedOffsetFrame<ChainCombined1{}, Distance::zero(), TWO_KM, Distance::zero(), Angle::zero(), Angle::zero(), HALF_PI_RAD, RotationSequence::XYZ>;

static_assert(IsFixedOffsetFrame<ChainCombined1>);
static_assert(IsFixedOffsetFrame<ChainCombined2>);
static_assert(HasSpatialOffset<ChainCombined1>);
static_assert(HasAngularOffset<ChainCombined1>);
static_assert(HasSpatialOffset<ChainCombined2>);
static_assert(HasAngularOffset<ChainCombined2>);

TEST_F(FixedOffsetFrameTest, CombinedChainRootOffsetAccumulatesX)
{
    const auto off = get_offset_from_root_frame<ChainCombined2{}>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootOffsetAccumulatesY)
{
    const auto off = get_offset_from_root_frame<ChainCombined2{}>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootOffsetZIsZero)
{
    const auto off = get_offset_from_root_frame<ChainCombined2{}>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootDcmComposesFirstRow)
{
    const auto dcm = get_dcm_from_root_frame<ChainCombined2{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootDcmComposesSecondRow)
{
    const auto dcm = get_dcm_from_root_frame<ChainCombined2{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootDcmComposesThirdRow)
{
    const auto dcm = get_dcm_from_root_frame<ChainCombined2{}>();
    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}
