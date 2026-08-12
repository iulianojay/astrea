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

#include <astro/frames.hpp>
#include <astro/frames/framework/FixedOffsetFrame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/type_traits.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;

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
inline constexpr struct ZeroEarthIcrf final
    : FixedOffsetFrame<frames::earth::icrf, Distance::zero(), Distance::zero(), Distance::zero()> {
} ZeroEarthIcrf;
inline constexpr struct ZeroMarsIcrf final
    : FixedOffsetFrame<frames::mars::icrf, Distance::zero(), Distance::zero(), Distance::zero()> {
} ZeroMarsIcrf;

static_assert(HasSpatialOffset<decltype(ZeroEarthIcrf)>);
static_assert(ZeroEarthIcrf::parent.origin == planets::Earth);
static_assert(HasSpatialOffset<decltype(ZeroMarsIcrf)>);
static_assert(ZeroMarsIcrf::parent.origin == planets::Mars);
static_assert(ZeroEarthIcrf::origin != ZeroMarsIcrf::origin); // share the same origin (FixedOffsetOrigin), but different parents (Earth vs Mars)
static_assert(ZeroEarthIcrf::parent.origin != ZeroMarsIcrf::parent.origin); // different parents (Earth vs Mars)

TEST_F(FixedOffsetFrameTest, DefaultOffsetXIsZero)
{
    EXPECT_DOUBLE_EQ(get_offset_from_frame<ZeroEarthIcrf>().get_x().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, DefaultOffsetYIsZero)
{
    EXPECT_DOUBLE_EQ(get_offset_from_frame<ZeroEarthIcrf>().get_y().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, DefaultOffsetZIsZero)
{
    EXPECT_DOUBLE_EQ(get_offset_from_frame<ZeroEarthIcrf>().get_z().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, OffsetIsConstexprAccessible)
{
    // Verifies offset is a constexpr static member
    constexpr auto off = get_offset_from_frame<ZeroEarthIcrf>();
    (void)off;
    SUCCEED();
}

static_assert(IsFrame<decltype(ZeroEarthIcrf)>);
static_assert(IsStaticFrame<decltype(ZeroEarthIcrf)>);
static_assert(IsInertialFrame<decltype(ZeroEarthIcrf)>);
static_assert(IsFixedOffsetFrame<decltype(ZeroEarthIcrf)>);

static_assert(ZeroEarthIcrf.origin != frames::earth::icrf.origin);
static_assert(ZeroEarthIcrf::parent.origin == frames::earth::icrf.origin);
static_assert(equivalent(ZeroEarthIcrf.origin, frames::earth::icrf.origin));

static_assert(ZeroEarthIcrf.axis == frames::earth::icrf.axis);
static_assert(ZeroEarthIcrf::parent.axis == frames::earth::icrf.axis);
static_assert(equivalent(ZeroEarthIcrf.axis, frames::earth::icrf.axis));

static_assert(ZeroEarthIcrf != frames::earth::icrf);
static_assert(equivalent(ZeroEarthIcrf, frames::earth::icrf));
static_assert(ZeroEarthIcrf::parent == frames::earth::icrf);

inline constexpr struct Also final : FixedOffsetFrame<frames::earth::icrf, Distance::zero(), Distance::zero(), Distance::zero()> {
} Also;
static_assert(ZeroEarthIcrf != Also);           // Type differs, even though all members are the same
static_assert(equivalent(ZeroEarthIcrf, Also)); // Equivalent since they share the same parent and have values
static_assert(ZeroEarthIcrf != ZeroMarsIcrf);


constexpr Angle HALF_PI_RAD = std::numbers::pi / 2.0 * rad;

// Zero-angle angular offset (all defaults explicit)
inline constexpr struct ZeroAngularEarthIcrf final
    : FixedOffsetFrame<frames::earth::icrf, Angle::zero(), Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} ZeroAngularEarthIcrf;

// XYZ sequence (default) — one axis rotated at a time
inline constexpr struct RotXHalfPiXYZ final
    : FixedOffsetFrame<frames::earth::icrf, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} RotXHalfPiXYZ;
inline constexpr struct RotYHalfPiXYZ final
    : FixedOffsetFrame<frames::earth::icrf, Angle::zero(), HALF_PI_RAD, Angle::zero(), RotationSequence::XYZ> {
} RotYHalfPiXYZ;
inline constexpr struct RotZHalfPiXYZ final
    : FixedOffsetFrame<frames::earth::icrf, Angle::zero(), Angle::zero(), HALF_PI_RAD, RotationSequence::XYZ> {
} RotZHalfPiXYZ;
// ZYX sequence — same phi angle, different result
inline constexpr struct RotXHalfPiZYX final
    : FixedOffsetFrame<frames::earth::icrf, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::ZYX> {
} RotXHalfPiZYX;

static_assert(HasAngularOffset<decltype(ZeroAngularEarthIcrf)>);
static_assert(ZeroAngularEarthIcrf::parent.origin == planets::Earth);
static_assert(HasAngularOffset<decltype(RotXHalfPiXYZ)>);
static_assert(RotXHalfPiXYZ::parent.origin == planets::Earth);

static_assert(IsFrame<decltype(ZeroAngularEarthIcrf)>);
static_assert(IsStaticFrame<decltype(ZeroAngularEarthIcrf)>);
static_assert(IsInertialFrame<decltype(ZeroAngularEarthIcrf)>);
static_assert(IsFrame<decltype(RotXHalfPiXYZ)>);
static_assert(IsFrame<decltype(RotXHalfPiZYX)>);

// Angular and positional FixedOffsetFrames are distinct types
static_assert(!std::is_same_v<decltype(ZeroAngularEarthIcrf), decltype(ZeroEarthIcrf)>);
// Same angles, different sequence → different types
static_assert(!std::is_same_v<decltype(RotXHalfPiXYZ), decltype(RotXHalfPiZYX)>);

static constexpr Unitless ANGULAR_TOL = 1.0e-10 * one;

// Zero-angle angular offset → identity misalignment
static constexpr Date epoch;

TEST_F(FixedOffsetFrameTest, ZeroAnglesGivesIdentityMisalignment_Diagonal)
{
    const auto& dcm = get_dcm<ZeroAngularEarthIcrf.parent, ZeroAngularEarthIcrf>(epoch);
    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

TEST_F(FixedOffsetFrameTest, ZeroAnglesGivesIdentityMisalignment_OffDiagonal)
{
    const auto& dcm = get_dcm<ZeroAngularEarthIcrf.parent, ZeroAngularEarthIcrf>(epoch);
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

TEST_F(FixedOffsetFrameTest, XYZHalfPiPhiGivesXRotation)
{
    const auto& dcm = get_dcm<RotXHalfPiXYZ.parent, RotXHalfPiXYZ>(epoch);

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// XYZ(0, pi/2, 0) → pure Y-axis rotation:
//   [[ 0, 0, 1],
//    [ 0, 1, 0],
//    [-1, 0, 0]]

TEST_F(FixedOffsetFrameTest, XYZHalfPiThetaGivesYRotation)
{
    const auto& dcm = get_dcm<RotYHalfPiXYZ.parent, RotYHalfPiXYZ>(epoch);

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 1.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// XYZ(0, 0, pi/2) → pure Z-axis rotation:
//   [[ 0, -1, 0],
//    [ 1,  0, 0],
//    [ 0,  0, 1]]

TEST_F(FixedOffsetFrameTest, XYZHalfPiPsiGivesZRotation)
{
    const auto& dcm = get_dcm<RotZHalfPiXYZ.parent, RotZHalfPiXYZ>(epoch);

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 1.0 * one, ANGULAR_TOL));
}

// ZYX(pi/2, 0, 0) = XYZ(0, 0, pi/2) → Z-axis rotation, confirming rotation sequence is applied.
// This differs from XYZ(pi/2, 0, 0) which is an X-rotation.

TEST_F(FixedOffsetFrameTest, ZYXHalfPiPhiGivesZRotation)
{
    const auto& dcm = get_dcm<RotXHalfPiZYX.parent, RotXHalfPiZYX>(epoch);

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], 0.0 * one, ANGULAR_TOL));

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
inline constexpr struct CombinedEarthIcrf final
    : FixedOffsetFrame<frames::earth::icrf, ONE_KM, TWO_KM, THREE_KM, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} CombinedEarthIcrf;

static_assert(HasSpatialOffset<decltype(CombinedEarthIcrf)>);
static_assert(HasAngularOffset<decltype(CombinedEarthIcrf)>);
static_assert(IsFixedOffsetFrame<decltype(CombinedEarthIcrf)>);

// get_offset_from_frame returns the declared translational offset
TEST_F(FixedOffsetFrameTest, GetOffsetFromFrameReturnsCorrectX)
{
    const auto off = get_offset_from_frame<CombinedEarthIcrf>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromFrameReturnsCorrectY)
{
    const auto off = get_offset_from_frame<CombinedEarthIcrf>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromFrameReturnsCorrectZ)
{
    const auto off = get_offset_from_frame<CombinedEarthIcrf>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 3.0);
}

// get_dcm returns Rx(pi/2) — same result as RotXHalfPiXYZ despite also having an offset
// [[1, 0,  0],
//  [0, 0, -1],
//  [0, 1,  0]]
TEST_F(FixedOffsetFrameTest, GetDcmFromFrame)
{
    const auto dcm = get_dcm<CombinedEarthIcrf.parent, CombinedEarthIcrf>(epoch);

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// get_offset_from_root_frame for a non-derived parent is identical to get_offset_from_frame
TEST_F(FixedOffsetFrameTest, GetOffsetFromRootFrameMatchesFromFrameX)
{
    const auto off = get_offset_from_root_frame<CombinedEarthIcrf>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromRootFrameMatchesFromFrameY)
{
    const auto off = get_offset_from_root_frame<CombinedEarthIcrf>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, GetOffsetFromRootFrameMatchesFromFrameZ)
{
    const auto off = get_offset_from_root_frame<CombinedEarthIcrf>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 3.0);
}

// get_dcm_from_root_frame for a non-derived parent is identical to get_dcm
TEST_F(FixedOffsetFrameTest, GetDcmFromRootFrameMatchesFromFrame)
{
    const auto dcm = get_dcm_from_root_frame<CombinedEarthIcrf>();

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// ==================== Chained frames ====================

// Pure spatial offset chain: 1 km in X, then 2 km in Y from that child frame.
inline constexpr struct ChainOffset1 final : FixedOffsetFrame<frames::earth::icrf, ONE_KM, Distance::zero(), Distance::zero()> {
} ChainOffset1;
inline constexpr struct ChainOffset2 final : FixedOffsetFrame<ChainOffset1, Distance::zero(), TWO_KM, Distance::zero()> {
} ChainOffset2;

static_assert(IsFixedOffsetFrame<decltype(ChainOffset1)>);
static_assert(IsFixedOffsetFrame<decltype(ChainOffset2)>);
static_assert(IsDerivedFrame<decltype(ChainOffset1)>);

// get_offset_from_root_frame accumulates both offsets
TEST_F(FixedOffsetFrameTest, SpatialChainRootOffsetAccumulatesX)
{
    const auto off = get_offset_from_root_frame<ChainOffset2>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, SpatialChainRootOffsetAccumulatesY)
{
    const auto off = get_offset_from_root_frame<ChainOffset2>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, SpatialChainRootOffsetZIsZero)
{
    const auto off = get_offset_from_root_frame<ChainOffset2>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 0.0);
}

// Pure angular chain: Rx(pi/2) then Rz(pi/2).
// Composed from root = Rx(pi/2) * Rz(pi/2):
//   [[0, -1,  0],
//    [0,  0, -1],
//    [1,  0,  0]]
inline constexpr struct ChainAngular1 final
    : FixedOffsetFrame<frames::earth::icrf, HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} ChainAngular1;
inline constexpr struct ChainAngular2 final
    : FixedOffsetFrame<ChainAngular1, Angle::zero(), Angle::zero(), HALF_PI_RAD, RotationSequence::XYZ> {
} ChainAngular2;

static_assert(IsFixedOffsetFrame<decltype(ChainAngular1)>);
static_assert(IsFixedOffsetFrame<decltype(ChainAngular2)>);

TEST_F(FixedOffsetFrameTest, AngularChainRootDcmComposes)
{
    const auto dcm = get_dcm_from_root_frame<ChainAngular2>();

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}

// A pure-offset child of a rotated parent has no angular contribution of its own —
// get_dcm_from_root_frame should propagate the parent's DCM unchanged.
inline constexpr struct OffsetChildOfAngular final : FixedOffsetFrame<ChainAngular1, Distance::zero(), TWO_KM, Distance::zero()> {
} OffsetChildOfAngular;
TEST_F(FixedOffsetFrameTest, SpatialChildOfAngularParentPreserversParentDcm)
{
    // ChainOffset2 has no angular misalignment; its parent ChainAngular1 is Rx(pi/2).
    // get_dcm_from_root_frame<ChainOffset2 derived from ChainAngular1> is not defined
    // because ChainOffset2 must be derived from ChainAngular1 to test this.
    // Use an explicit type: spatial offset child of ChainAngular1.
    const auto dcm = get_dcm_from_root_frame<OffsetChildOfAngular>();
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
inline constexpr struct ChainCombined1 final
    : FixedOffsetFrame<frames::earth::icrf, ONE_KM, Distance::zero(), Distance::zero(), HALF_PI_RAD, Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} ChainCombined1;
inline constexpr struct ChainCombined2 final
    : FixedOffsetFrame<ChainCombined1, Distance::zero(), TWO_KM, Distance::zero(), Angle::zero(), Angle::zero(), HALF_PI_RAD, RotationSequence::XYZ> {
} ChainCombined2;

static_assert(IsFixedOffsetFrame<decltype(ChainCombined1)>);
static_assert(IsFixedOffsetFrame<decltype(ChainCombined2)>);
static_assert(HasSpatialOffset<decltype(ChainCombined1)>);
static_assert(HasAngularOffset<decltype(ChainCombined1)>);
static_assert(HasSpatialOffset<decltype(ChainCombined2)>);
static_assert(HasAngularOffset<decltype(ChainCombined2)>);

TEST_F(FixedOffsetFrameTest, CombinedChainRootOffsetAccumulatesX)
{
    const auto off = get_offset_from_root_frame<ChainCombined2>();
    EXPECT_DOUBLE_EQ(off.get_x().numerical_value_in(km), 1.0);
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootOffsetAccumulatesY)
{
    const auto off = get_offset_from_root_frame<ChainCombined2>();
    EXPECT_DOUBLE_EQ(off.get_y().numerical_value_in(km), 2.0);
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootOffsetZIsZero)
{
    const auto off = get_offset_from_root_frame<ChainCombined2>();
    EXPECT_DOUBLE_EQ(off.get_z().numerical_value_in(km), 0.0);
}

TEST_F(FixedOffsetFrameTest, CombinedChainRootDcmComposes)
{
    const auto dcm = get_dcm_from_root_frame<ChainCombined2>();

    EXPECT_TRUE(math::nearly_equal(dcm[0, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 1], -1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[0, 2], 0.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[1, 0], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[1, 2], -1.0 * one, ANGULAR_TOL));

    EXPECT_TRUE(math::nearly_equal(dcm[2, 0], 1.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 1], 0.0 * one, ANGULAR_TOL));
    EXPECT_TRUE(math::nearly_equal(dcm[2, 2], 0.0 * one, ANGULAR_TOL));
}
