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

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/events/Deorbit.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/systems/system_utilities.hpp>

using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class DeorbitTest : public testing::Test {
  public:
    DeorbitTest() = default;
    void SetUp() override
    {
        // Set up a basic state and vehicle for testing
        time    = Time(0.0 * s);
        vehicle = Vehicle(spacecraft);

        // Create a position just above Earth's surface for testing
        const RadiusVector<frames::earth::icrf> position{ 6400.0 * km, 0.0 * km, 0.0 * km };
        const VelocityVector<frames::earth::icrf> velocity{ 0.0 * km / s, 7.8 * km / s, 0.0 * km / s };

        cartesian = Cartesian<frames::earth::icrf>(position, velocity);
        state     = State(cartesian, epoch);
    }

    Time time;
    Date epoch;
    Cartesian<frames::earth::icrf> cartesian;
    State state;
    Spacecraft spacecraft;
    Vehicle vehicle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(DeorbitTest, DefaultConstructor)
{
    Deorbit event;
    ASSERT_EQ(event.get_name(), "Deorbit");
}

TEST_F(DeorbitTest, ConstructorWithAltitude)
{
    const Distance triggerAltitude = 100.0 * km;
    Deorbit event(triggerAltitude);
    ASSERT_EQ(event.get_name(), "Deorbit");
}

TEST_F(DeorbitTest, GetName)
{
    Deorbit event;
    ASSERT_EQ(event.get_name(), "Deorbit");
}

TEST_F(DeorbitTest, IsTerminal)
{
    Deorbit event;
    ASSERT_TRUE(event.is_terminal());
}

TEST_F(DeorbitTest, MeasureEventDefaultAltitude)
{
    Deorbit event; // Default altitude of 0 km
    Unitless result = event.measure_event(time, state, vehicle);

    const Distance altitude    = Geodetic<planets::Earth>(cartesian.get_position(), epoch).get_altitude();
    const Distance crashRadius = get_crash_radius<planets::Earth>();
    Unitless expected          = (altitude - crashRadius) / (1.0 * km);

    ASSERT_TRUE(math::nearly_equal(result, expected, 1.0e-6 * one));
}

TEST_F(DeorbitTest, MeasureEventWithCustomAltitude)
{
    const Distance triggerAltitude = 50.0 * km;
    Deorbit event(triggerAltitude);
    Unitless result = event.measure_event(time, state, vehicle);

    const Distance altitude = Geodetic<planets::Earth>(cartesian.get_position(), epoch).get_altitude();
    Unitless expected       = (altitude - triggerAltitude) / (1.0 * km);

    ASSERT_TRUE(math::nearly_equal(result, expected, 1.0e-6 * one));
}