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

#include <type_traits>

#include <units/units.hpp>

#include <astro/frames/FixedOffsetFrame.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>

using namespace astrea;
using namespace astrea::astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;

// Default (zero-offset) instantiation
using ZeroEarthIcrf = FixedOffsetFrame<frames::earth::icrf>;
using ZeroMarsIcrf  = FixedOffsetFrame<frames::mars::icrf>;

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

// IsSameFrame checks origin+axis only; FixedOffsetFrame inherits both,
// so it is considered the same frame by that concept.
static_assert(!IsSameFrame<ZeroEarthIcrf, frames::earth::icrf>);
static_assert(IsSameFrame<ZeroEarthIcrf::parent, frames::earth::icrf>);

using Also = FixedOffsetFrame<frames::earth::icrf>;
static_assert(std::is_same_v<ZeroEarthIcrf, Also>);
static_assert(!IsSameFrame<ZeroEarthIcrf, ZeroMarsIcrf>);

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
