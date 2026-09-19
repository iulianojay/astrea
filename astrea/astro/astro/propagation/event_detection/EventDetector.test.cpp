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
#include <astro/state/State.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::s;

struct TestEvent {

    std::string get_name() const { return "Test Event"; }

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        static int sign = -1;
        sign *= -1;
        return sign * mp_units::one;
    }

    bool is_terminal() const { return false; }
};

struct TerminalTestEvent : public TestEvent {

    std::string get_name() const { return "Terminal Test Event"; }

    bool is_terminal() const { return true; }
};

class EventDetectorTest : public testing::Test {
  public:
    EventDetectorTest() {}

    void SetUp() override {}

    EventDetector detector;
    Event event{ TestEvent() };
    Event terminalEvent{ TerminalTestEvent() };
    Vehicle vehicle{ Spacecraft() };
    State state{};
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(EventDetectorTest, GetEvents) { ASSERT_EQ(detector.get_events().size(), 0); }

TEST_F(EventDetectorTest, SetEvents)
{
    ASSERT_EQ(detector.get_events().size(), 0);
    detector.add_event(event);
    ASSERT_EQ(detector.get_events().size(), 1);
}

TEST_F(EventDetectorTest, DetectNonTerminalEvents)
{
    detector.add_event(event);
    for (int ii = 0; ii < 10; ++ii) {
        const bool isTerminal = detector.detect_events(Time(ii * s), state, vehicle);
        ASSERT_EQ(isTerminal, false);
    }
}

TEST_F(EventDetectorTest, DetectTerminalEvents)
{
    detector.add_event(terminalEvent);
    for (int ii = 0; ii < 10; ++ii) {
        const bool isTerminal = detector.detect_events(Time(ii * s), state, vehicle);
        ASSERT_EQ(isTerminal, bool(ii > 0));
    }
}
