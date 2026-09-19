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
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/event_detection/events/TurnThrustersOn.hpp>
#include <astro/state/State.hpp>
#include <astro/systems/system_utilities.hpp>

using namespace astrea;
using namespace astro;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class TurnThrustersOnTest : public testing::Test {
  public:
    TurnThrustersOnTest() = default;
    void SetUp() override
    {
        event = TurnThrustersOn();
        time  = Time(0.0 * s);
        state = State();

        // Set up spacecraft with thrusters
        ThrusterParameters thrusterParams(100.0 * N);
        spacecraft.attach_payload(thrusterParams);
        spacecraft.attach_payload(thrusterParams);
        vehicle = Vehicle(spacecraft);

        // Non-spacecraft vehicle for testing error cases
        emptyVehicle = Vehicle();
    }

    TurnThrustersOn event;
    Time time;
    State state;
    Spacecraft spacecraft;
    Vehicle vehicle;
    Vehicle emptyVehicle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(TurnThrustersOnTest, GetName) { ASSERT_EQ(event.get_name(), "TurnThrustersOn"); }

TEST_F(TurnThrustersOnTest, MeasureEvent)
{
    // This event is only meant to be scheduled, so should return 1.0
    Unitless result = event.measure_event(time, state, vehicle);
    ASSERT_EQ(result, 1.0 * mp_units::one);
}

TEST_F(TurnThrustersOnTest, IsTerminal) { ASSERT_FALSE(event.is_terminal()); }

TEST_F(TurnThrustersOnTest, TriggerActionSuccess)
{
    // Ensure thrusters are initially off
    auto* spacecraftPtr = vehicle.extract_mutable_reference<Spacecraft>();
    ASSERT_NE(spacecraftPtr, nullptr);
    for (auto& thruster : spacecraftPtr->get_payloads()) {
        thruster.switch_off();
    }

    // Verify thrusters are off
    for (const auto& thruster : spacecraftPtr->get_payloads()) {
        ASSERT_FALSE(thruster.is_on());
    }

    // Trigger the action
    ASSERT_NO_THROW(event.trigger_action(time, state, vehicle));

    // Verify thrusters are now on
    for (const auto& thruster : spacecraftPtr->get_payloads()) {
        ASSERT_TRUE(thruster.is_on());
    }
}

TEST_F(TurnThrustersOnTest, TriggerActionWithNonSpacecraftVehicle)
{
    // Should throw an exception when trying to extract as Spacecraft from empty vehicle
    ASSERT_THROW(event.trigger_action(time, state, emptyVehicle), std::runtime_error);
}