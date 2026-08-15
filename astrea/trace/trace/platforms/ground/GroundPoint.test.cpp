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

#include <astro/astro.hpp>

#include <trace/trace.hpp>

using namespace astrea;
using namespace astro;
using namespace trace;

class GroundPointTest : public testing::Test {
  public:
    GroundPointTest() = default;

    void SetUp() override
    {
        latitude  = 0.5 * mp_units::si::unit_symbols::rad;
        longitude = 1.0 * mp_units::si::unit_symbols::rad;
        altitude  = 0.1 * mp_units::si::unit_symbols::km;
        point     = GroundPoint<astro::planets::Earth>(latitude, longitude, altitude);
    }

    Angle latitude;
    Angle longitude;
    Distance altitude;
    GroundPoint<astro::planets::Earth> point;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GroundPointTest, DefaultConstructor) { ASSERT_NO_THROW(GroundPoint<astro::planets::Earth>()); }

TEST_F(GroundPointTest, Constructor)
{
    ASSERT_NO_THROW(GroundPoint<astro::planets::Earth>(latitude, longitude, altitude));
}

TEST_F(GroundPointTest, GetLatitude) { ASSERT_EQ(point.get_latitude(), latitude); }

TEST_F(GroundPointTest, GetLongitude) { ASSERT_EQ(point.get_longitude(), longitude); }

TEST_F(GroundPointTest, GetAltitude) { ASSERT_EQ(point.get_altitude(), altitude); }

TEST_F(GroundPointTest, GetParent) { ASSERT_TRUE(GroundPoint<astro::planets::Earth>::body == astro::planets::Earth); }

TEST_F(GroundPointTest, GetId)
{
    const auto ground1 = GroundPoint<astro::planets::Earth>(latitude, longitude, altitude);
    const auto ground2 = GroundPoint<astro::planets::Earth>(latitude, longitude, altitude);
    ASSERT_EQ(ground1.get_id() + 1, ground2.get_id());
}
