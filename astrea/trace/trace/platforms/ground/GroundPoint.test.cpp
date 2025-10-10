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
        parent    = sys.get(CelestialBodyId::EARTH).get();
        latitude  = 0.5 * mp_units::angular::unit_symbols::rad;
        longitude = 1.0 * mp_units::angular::unit_symbols::rad;
        altitude  = 0.1 * mp_units::si::unit_symbols::km;
        point     = GroundPoint(parent, latitude, longitude, altitude);
    }

    AstrodynamicsSystem sys;
    const CelestialBody* parent;
    Angle latitude;
    Angle longitude;
    Distance altitude;
    GroundPoint point;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GroundPointTest, DefaultConstructor) { ASSERT_NO_THROW(GroundPoint()); }

TEST_F(GroundPointTest, Constructor)
{
    ASSERT_NO_THROW(GroundPoint(sys.get(CelestialBodyId::EARTH).get(), latitude, longitude, altitude));
}

TEST_F(GroundPointTest, GetLatitude) { ASSERT_EQ(point.get_latitude(), latitude); }

TEST_F(GroundPointTest, GetLongitude) { ASSERT_EQ(point.get_longitude(), longitude); }

TEST_F(GroundPointTest, GetAltitude) { ASSERT_EQ(point.get_altitude(), altitude); }

TEST_F(GroundPointTest, GetParent) { ASSERT_EQ(point.get_parent(), sys.get(CelestialBodyId::EARTH).get()); }

TEST_F(GroundPointTest, GetId)
{
    ASSERT_EQ(point.get_id(), GroundPoint(sys.get(CelestialBodyId::EARTH).get(), latitude, longitude, altitude).get_id());
}
