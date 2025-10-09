/*
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

class GroundStationTest : public testing::Test {
  public:
    GroundStationTest() = default;

    void SetUp() override
    {
        latitude  = 0.5 * mp_units::angular::unit_symbols::rad;
        longitude = 1.0 * mp_units::angular::unit_symbols::rad;
        altitude  = 0.1 * mp_units::si::unit_symbols::km;
        name      = "TestStation";
        sensors   = {};
        station = new GroundStation(sys.get(CelestialBodyId::EARTH).get(), latitude, longitude, altitude, name, sensors);
    }

    void TearDown() override { delete station; }

    AstrodynamicsSystem sys;
    Angle latitude;
    Angle longitude;
    Distance altitude;
    std::string name;
    std::vector<SensorParameters> sensors;
    GroundStation* station;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GroundStationTest, Constructor)
{
    ASSERT_EQ(station->get_name(), name);
    ASSERT_EQ(
        station->get_id(),
        GroundStation(sys.get(CelestialBodyId::EARTH).get(), latitude, longitude, altitude, name, sensors).get_id()
    );
}

TEST_F(GroundStationTest, GetName) { ASSERT_EQ(station->get_name(), name); }

TEST_F(GroundStationTest, GetId) { ASSERT_NO_THROW(station->get_id()); }

TEST_F(GroundStationTest, GetInertialPosition) { ASSERT_NO_THROW(auto pos = station->get_inertial_position(Date())); }

TEST_F(GroundStationTest, GetInertialVelocity) { ASSERT_NO_THROW(auto vel = station->get_inertial_velocity(Date())); }
