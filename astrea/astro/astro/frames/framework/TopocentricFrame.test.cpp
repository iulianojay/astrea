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
#include <type_traits>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames.hpp>
#include <astro/frames/definitions/transformations.hpp>
#include <astro/frames/framework/TopocentricFrame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/types/type_traits.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;

class TopocentricFrameTest : public testing::Test {
  public:
    TopocentricFrameTest() {}

    void SetUp() override {}
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

static constexpr Unitless ANGULAR_TOL = 1.0e-10 * one;

// Default (zero-offset) instantiation
inline constexpr struct WashingtonDcWnu final
    : TopocentricFrame<"Washington DC", frames::earth::earth_fixed, 38.895111 * deg, -77.036369 * deg, 0.0 * km> {
} WashingtonDcWnu;

static_assert(HasSpatialOffset<decltype(WashingtonDcWnu)>);
static_assert(HasAngularOffset<decltype(WashingtonDcWnu)>);
static_assert(WashingtonDcWnu::parent.origin == planets::Earth);
static_assert(WashingtonDcWnu::parent == frames::earth::earth_fixed);
static_assert(IsFixedOffsetFrame<decltype(WashingtonDcWnu)>);
static_assert(IsDerivedAxis<decltype(WashingtonDcWnu.axis)>);
static_assert(IsDerivedFrame<decltype(WashingtonDcWnu)>);
static_assert(equivalent(WashingtonDcWnu.axis.parent, WashingtonDcWnu::parent.axis));
static_assert(equivalent(get_root_frame<WashingtonDcWnu>(), frames::earth::earth_fixed));
static_assert(equivalent(WashingtonDcWnu::parent, frames::earth::earth_fixed));
static_assert(equivalent(WashingtonDcWnu::parent.axis, frames::earth::earth_fixed::axis));
static_assert(IsChildOf<decltype(WashingtonDcWnu), decltype(frames::earth::earth_fixed)>);
// static_assert(frames::HasDcm<WashingtonDcWnu::parent, WashingtonDcWnu>);

TEST_F(TopocentricFrameTest, OffsetIsConstexprAccessible)
{
    // Verifies offset is a constexpr static member
    constexpr auto off = get_offset_from_frame<WashingtonDcWnu>();

    const auto expected = convert_geodetic_to_body_fixed<frames::earth::earth_fixed>(38.895111 * deg, -77.036369 * deg, 0.0 * km);

    ASSERT_TRUE(math::nearly_equal(off.get_x(), expected.get_x(), 1e-6 * one));
    ASSERT_TRUE(math::nearly_equal(off.get_y(), expected.get_y(), 1e-6 * one));
    ASSERT_TRUE(math::nearly_equal(off.get_z(), expected.get_z(), 1e-6 * one));
}

TEST_F(TopocentricFrameTest, MisalignmentIsConstexprAccessible)
{
    // Verifies offset is a constexpr static member
    constexpr auto dcm = get_dcm_from_root_frame<WashingtonDcWnu>();
    (void)dcm;
    SUCCEED();
}

TEST_F(TopocentricFrameTest, GetDcm)
{
    constexpr Date epoch;
    const auto& dcm = get_dcm<WashingtonDcWnu.parent, WashingtonDcWnu>(epoch);
    EXPECT_TRUE(math::nearly_equal(dcm.determinant(), 1.0 * one, ANGULAR_TOL));
}

TEST_F(TopocentricFrameTest, ConstexprTransformationToParent)
{
    // Verifies offset is a constexpr static member
    constexpr Date epoch;
    constexpr auto r       = CartesianVector<Distance, WashingtonDcWnu>(1.0 * km, 2.0 * km, 3.0 * km);
    constexpr auto rParent = r.template in_frame<frames::earth::earth_fixed>(epoch);

    const auto rWashingtonDc =
        convert_geodetic_to_body_fixed<frames::earth::earth_fixed>(38.895111 * deg, -77.036369 * deg, 0.0 * km);

    ASSERT_TRUE(math::nearly_equal(rParent.norm(), rWashingtonDc.norm() + r.norm(), 1e-2 * one)) // closeish
        << " rParent.norm() = " << rParent.norm() << ", rWashingtonDc.norm() + r.norm() = " << rWashingtonDc.norm() + r.norm();
}
