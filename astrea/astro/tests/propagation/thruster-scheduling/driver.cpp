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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/equations_of_motion/instances/TwoBody.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/Schedule.hpp>
#include <astro/propagation/event_detection/events/TurnThrustersOff.hpp>
#include <astro/propagation/event_detection/events/TurnThrustersOn.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class ThrusterSchedulingRegressionTest : public testing::Test {
  public:
    ThrusterSchedulingRegressionTest() :
        sys(),
        mu(sys.get_mu()),
        thrusterForce(2.0 * N),
        epoch(J2000),
        integrator(),
        eom(),
        forces()
    {
        // Setup spacecraft with thruster
        ThrusterParameters thrusterParams(thrusterForce);
        spacecraft.attach_payload(thrusterParams);
        vehicle = Vehicle(spacecraft);

        // Setup initial LEO orbit
        initialElements = Keplerian::LEO(); // ~500 km circular orbit
        initialState    = State(initialElements, epoch, sys);

        // Calculate orbital period for scheduling
        orbitalPeriod = initialElements.get_orbital_period(mu);
    }

  protected:
    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;
    const Unitless ABS_TOL = 1.0e-10;

    AstrodynamicsSystem sys;
    GravParam mu;
    Force thrusterForce;
    Date epoch;
    Integrator integrator;
    TwoBody eom;
    ForceModel forces;

    Spacecraft spacecraft;
    Vehicle vehicle;
    Keplerian initialElements;
    State initialState;
    Time orbitalPeriod;
    Schedule schedule;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(ThrusterSchedulingRegressionTest, ScheduledThrusterBurnIncreasesSemimajorAxis)
{
    // Schedule thruster to turn on after 0.5 orbital periods
    // and turn off after 3 orbital periods of thrust
    const Time thrusterStartTime = orbitalPeriod * 0.5;
    const Time thrusterDuration  = orbitalPeriod * 3.0; // 3 orbital periods of thrust
    const Time thrusterEndTime   = thrusterStartTime + thrusterDuration;
    const Time totalPropTime     = orbitalPeriod * 5.0; // Propagate for 5 orbital periods total

    // Create events
    Event turnOnEvent{ TurnThrustersOn() };
    Event turnOffEvent{ TurnThrustersOff() };

    // Schedule events
    schedule.schedule_event(epoch + thrusterStartTime, turnOnEvent);
    schedule.schedule_event(epoch + thrusterEndTime, turnOffEvent);

    // Verify initial thruster state (should be off)
    const Spacecraft* spacecraftPtr = vehicle.extract<Spacecraft>();
    ASSERT_NE(spacecraftPtr, nullptr);

    const auto& thrusters = spacecraftPtr->get_payloads();
    ASSERT_FALSE(thrusters.empty());

    for (const auto& thruster : thrusters) {
        ASSERT_FALSE(thruster.is_on()) << "Thruster should start in OFF state";
    }

    // Store initial semimajor axis
    const Distance initialSemimajorAxis = initialElements.get_semimajor();

    // Propagate with manual event triggering
    State currentState = initialState;
    Time currentTime   = 0.0 * s;
    Date currentDate   = epoch;

    const Time timeStep = orbitalPeriod / 100.0;
    integrator.switch_fixed_timestep(true, timeStep);
    const int numSteps = static_cast<int>((totalPropTime / timeStep).numerical_value_in(one));

    Distance maxSemimajorAxis = initialSemimajorAxis;
    bool thrusterWasActivated = false;

    for (int ii = 0; ii < numSteps; ++ii) {
        currentTime = ii * timeStep;
        currentDate = epoch + currentTime;

        // Check and trigger scheduled events
        auto scheduledEvents = schedule.get_events_at(currentDate);
        if (!scheduledEvents.empty()) {
            schedule.trigger_scheduled_events(currentDate, currentTime, currentState, vehicle);

            // Check thruster state after event
            const auto& currentThrusters = spacecraftPtr->get_payloads();
            for (const auto& thruster : currentThrusters) {
                if (thruster.is_on()) { thrusterWasActivated = true; }
            }
        }

        // Propagate one time step
        const auto stateHistory = integrator.propagate(currentState, timeStep, eom, vehicle, false, {});
        if (!stateHistory.empty()) {
            currentState = stateHistory.last(); // Get final state

            // Track maximum semimajor axis reached
            const Keplerian currentElements     = currentState.in_element_set<Keplerian>();
            const Distance currentSemimajorAxis = currentElements.get_semimajor();

            if (currentSemimajorAxis > maxSemimajorAxis) { maxSemimajorAxis = currentSemimajorAxis; }
        }
    }

    // Get final orbital elements
    const Keplerian finalElements     = currentState.in_element_set<Keplerian>();
    const Distance finalSemimajorAxis = finalElements.get_semimajor();

    // Verify that thruster was actually activated during the test
    ASSERT_TRUE(thrusterWasActivated) << "Thruster should have been activated during the test";

    // The thruster should increase the orbit energy, resulting in larger semimajor axis
    const Distance semiMajorAxisIncrease = finalSemimajorAxis - initialSemimajorAxis;
    ASSERT_GT(semiMajorAxisIncrease, 0.0 * km) << "Thruster should have a positive effect on semimajor axis";

    // Verify the increase is significant (at least 1 meter for our 200N thruster over 3 orbital periods)
    ASSERT_GT(semiMajorAxisIncrease, 1.0 * m) << "Semimajor axis increase should be measurable (> 1 meter)";
}

TEST_F(ThrusterSchedulingRegressionTest, NoThrusterSemimajorAxisUnchanged)
{
    // Control test: Propagate same orbit without thruster activation
    const Time totalPropTime = orbitalPeriod * 5.0;

    // Store initial semimajor axis
    const Distance initialSemimajorAxis = initialElements.get_semimajor();

    // Propagate without any thruster activation
    const auto stateHistory = integrator.propagate(initialState, totalPropTime, eom, vehicle, false, {});

    // Get final orbital elements
    const State finalState            = stateHistory.last();
    const Keplerian finalElements     = finalState.in_element_set<Keplerian>();
    const Distance finalSemimajorAxis = finalElements.get_semimajor();

    // Verify semimajor axis remains essentially unchanged (within numerical precision)
    const Distance semiMajorAxisChange = finalSemimajorAxis - initialSemimajorAxis;

    ASSERT_LT(abs(semiMajorAxisChange), 1.0 * m)
        << "Without thruster, semimajor axis should remain essentially unchanged";
}

TEST_F(ThrusterSchedulingRegressionTest, MultipleScheduledBurnsCumulativeEffect)
{
    // Test multiple short burns scheduled throughout several orbital periods
    const Time burnDuration  = orbitalPeriod * 0.1; // Short 0.1 period burns
    const int numBurns       = 5;
    const Time totalPropTime = orbitalPeriod * 10.0;

    // Schedule multiple on/off cycles
    for (int ii = 0; ii < numBurns; ++ii) {
        const Time burnStartTime = orbitalPeriod * (1.0 + 1.5 * ii);
        const Time burnEndTime   = burnStartTime + burnDuration;

        Event turnOnEvent{ TurnThrustersOn() };
        Event turnOffEvent{ TurnThrustersOff() };

        schedule.schedule_event(epoch + burnStartTime, turnOnEvent);
        schedule.schedule_event(epoch + burnEndTime, turnOffEvent);
    }

    // Store initial semimajor axis
    const Distance initialSemimajorAxis = initialElements.get_semimajor();

    // Propagate with manual event triggering (similar to first test)
    State currentState = initialState;
    Time currentTime   = 0.0 * s;
    Date currentDate   = epoch;

    const Time timeStep = orbitalPeriod / 200.0; // Smaller time steps for more burns
    const int numSteps  = static_cast<int>((totalPropTime / timeStep).numerical_value_in(one));

    int burnsActivated = 0;

    for (int ii = 0; ii < numSteps; ++ii) {
        currentTime = ii * timeStep;
        currentDate = epoch + currentTime;

        // Check and trigger scheduled events
        auto scheduledEvents = schedule.get_events_at(currentDate);
        if (!scheduledEvents.empty()) {
            schedule.trigger_scheduled_events(currentDate, currentTime, currentState, vehicle);

            // Count thruster activations
            const auto& currentThrusters = vehicle.extract<Spacecraft>()->get_payloads();
            for (const auto& thruster : currentThrusters) {
                if (thruster.is_on()) {
                    burnsActivated++;
                    break; // Only count once per activation
                }
            }

            // Propagate one time step
            const auto stateHistory = integrator.propagate(currentState, timeStep, eom, vehicle, false, {});
            if (!stateHistory.empty()) { currentState = stateHistory.last(); }
        }

        // Get final orbital elements
        const Keplerian finalElements     = currentState.in_element_set<Keplerian>();
        const Distance finalSemimajorAxis = finalElements.get_semimajor();

        // Verify cumulative positive effect
        const Distance totalIncrease = finalSemimajorAxis - initialSemimajorAxis;
        std::cout << "Total semimajor axis increase: " << totalIncrease << std::endl;

        if (!scheduledEvents.empty()) {
            ASSERT_GT(burnsActivated, 0) << "At least some burns should have been activated";
            ASSERT_GT(totalIncrease, 0.0 * km)
                << "Multiple burns should have positive cumulative effect on semimajor axis";
        }
    }
}