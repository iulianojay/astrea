/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
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

#include <astro/frames/definitions/RadialInTrackCrossTrack.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>
#include <astro/state/State.hpp>
#include <astro/state/framework/OrbitalElements.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/systems/system_utilities.hpp>

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

class ImpulsiveBurnTest : public testing::Test {
  public:
    ImpulsiveBurnTest() = default;
    void SetUp() override
    {
        // Set up a basic state and vehicle for testing
        time = Time(0.0 * s);

        // Create a circular orbit
        const Distance semiMajorAxis = 7000.0 * km;
        const Unitless eccentricity  = 0.0 * one;
        const Angle inclination      = 0.0 * rad;
        const Angle raan             = 0.0 * rad;
        const Angle argPe            = 0.0 * rad;
        const Angle trueAnomaly      = 0.0 * rad;

        Keplerian<frames::earth::icrf> keplerian(semiMajorAxis, eccentricity, inclination, raan, argPe, trueAnomaly);
        state   = State(keplerian, Date());
        vehicle = Vehicle(spacecraft);

        // Set up a standard burn direction (radial)
        burnDirection = Direction<frames::dynamic::ric>(1.0, 0.0, 0.0);
    }

    const Unitless REL_TOL = 1.0e-6 * one;

    Time time;
    State state;
    Vehicle vehicle;
    Spacecraft spacecraft;
    Direction<frames::dynamic::ric> burnDirection;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(ImpulsiveBurnTest, TriggerAtTrueAnomalyConstructor)
{
    const Angle triggerAnomaly = 90.0 * deg;
    ASSERT_NO_THROW(ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_true_anomaly(triggerAnomaly, burnDirection, 1));
}

TEST_F(ImpulsiveBurnTest, TriggerAtMeanAnomalyConstructor)
{
    const Angle triggerAnomaly = 90.0 * deg;
    ASSERT_NO_THROW(ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_mean_anomaly(triggerAnomaly, burnDirection, 1));
}

TEST_F(ImpulsiveBurnTest, TriggerAtAltitudeConstructor)
{
    const Distance triggerAltitude = 400.0 * km;
    ASSERT_NO_THROW(ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_altitude(triggerAltitude, burnDirection, 1));
}

TEST_F(ImpulsiveBurnTest, TriggerAtEpochConstructor)
{
    const Date epoch = Date();
    ASSERT_NO_THROW(ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_epoch(epoch, burnDirection, 1));
}

TEST_F(ImpulsiveBurnTest, GetName)
{
    ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_true_anomaly(0.0 * rad, burnDirection);
    ASSERT_EQ(burn.get_name(), "Impulsive Burn");
}

TEST_F(ImpulsiveBurnTest, IsTerminal)
{
    ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_true_anomaly(0.0 * rad, burnDirection);
    ASSERT_FALSE(burn.is_terminal());
}

TEST_F(ImpulsiveBurnTest, MeasureEventTrueAnomaly)
{
    // Create a burn that triggers at 0 degrees true anomaly
    ImpulsiveBurn burn = ImpulsiveBurn::trigger_at_true_anomaly(0.0 * rad, burnDirection);

    // Our test state is already at 0 degrees true anomaly
    Unitless result = burn.measure_event(time, state, vehicle);

    ASSERT_TRUE(math::nearly_equal(result, Unitless(0.0 * one), REL_TOL));
}

TEST_F(ImpulsiveBurnTest, MeasureEventAltitude)
{
    // Create a burn that triggers at a lower altitude than current
    const Distance triggerAltitude = 500.0 * km;
    ImpulsiveBurn burn             = ImpulsiveBurn::trigger_at_altitude(triggerAltitude, burnDirection);

    Unitless result = burn.measure_event(time, state, vehicle);

    // Since current altitude should be higher than trigger altitude, result should be positive
    ASSERT_GT(result, Unitless(0.0 * one));
}

TEST_F(ImpulsiveBurnTest, MeasureEventEpoch)
{
    // Create a burn that triggers at current epoch
    const Date triggerEpoch = state.get_epoch();
    ImpulsiveBurn burn      = ImpulsiveBurn::trigger_at_epoch(triggerEpoch, burnDirection);

    Unitless result = burn.measure_event(time, state, vehicle);

    // At the trigger epoch, the result should be 0 or very small
    ASSERT_TRUE(math::nearly_equal(result, Unitless(0.0 * one), REL_TOL));
}