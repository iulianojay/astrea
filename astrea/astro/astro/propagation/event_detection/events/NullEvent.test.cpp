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

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/EventDetector.hpp>
#include <astro/propagation/event_detection/events/NullEvent.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

using namespace astrea;
using namespace astro;

class NullEventTest : public testing::Test {
  public:
    NullEventTest() = default;
    void SetUp() override
    {
        event   = NullEvent();
        time    = Time(0.0 * mp_units::si::unit_symbols::s);
        state   = State();
        vehicle = Vehicle();
    }
    NullEvent event;
    Time time;
    State state;
    Vehicle vehicle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(NullEventTest, GetName) { ASSERT_EQ(event.get_name(), "NullEvent"); }

TEST_F(NullEventTest, MeasureEvent)
{
    Unitless result = event.measure_event(time, state, vehicle);
    ASSERT_EQ(result, 1.0 * mp_units::one);
}

TEST_F(NullEventTest, IsTerminal) { ASSERT_FALSE(event.is_terminal()); }
