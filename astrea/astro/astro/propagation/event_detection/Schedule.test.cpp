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

#include <math/comparisons.hpp>
#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/Schedule.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::s;

struct TestScheduleEvent {
    TestScheduleEvent() = default;
    std::string get_name() const { return "Test Schedule Event"; }
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        return 1.0 * mp_units::one;
    }
    bool is_terminal() const { return false; }
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const
    {
        // Record that the event was triggered for testing
        triggered = true;
    }
    mutable bool triggered = false;
};

struct TestScheduleEvent2 {
    TestScheduleEvent2() = default;
    std::string get_name() const { return "Test Schedule Event 2"; }
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        return 2.0 * mp_units::one;
    }
    bool is_terminal() const { return true; }
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const { triggered = true; }
    mutable bool triggered = false;
};

class ScheduleTest : public testing::Test {
  public:
    ScheduleTest() :
        time(0.0 * s),
        date1(Date()),
        date2(Date() + days(1)),
        date3(Date() + days(2))
    {
    }
    void SetUp() override {}

    Schedule schedule;
    Event testEvent1{ TestScheduleEvent() };
    Event testEvent2{ TestScheduleEvent2() };
    Vehicle vehicle;
    Time time;
    State state;
    Date date1, date2, date3;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(ScheduleTest, DefaultConstructor) { ASSERT_NO_THROW(Schedule Schedule); }

TEST_F(ScheduleTest, ScheduleSingleEvent)
{
    ASSERT_NO_THROW(schedule.schedule_event(date1, testEvent1));

    // Verify the event was scheduled
    auto events = schedule.get_events_at(date1);
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0].get_name(), "Test Schedule Event");
}

TEST_F(ScheduleTest, ScheduleMultipleEventsAtSameDate)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date1, testEvent2);

    auto events = schedule.get_events_at(date1);
    ASSERT_EQ(events.size(), 2);

    // Events should be returned in the order they were scheduled
    ASSERT_EQ(events[0].get_name(), "Test Schedule Event");
    ASSERT_EQ(events[1].get_name(), "Test Schedule Event 2");
}

TEST_F(ScheduleTest, ScheduleEventsAtMultipleDates)
{
    std::vector<Date> dates = { date1, date2, date3 };
    schedule.schedule_event(dates, testEvent1);

    // Verify events are scheduled at all dates
    for (const auto& date : dates) {
        auto events = schedule.get_events_at(date);
        ASSERT_EQ(events.size(), 1);
        ASSERT_EQ(events[0].get_name(), "Test Schedule Event");
    }
}

TEST_F(ScheduleTest, GetEventsAtNonExistentDate)
{
    Date nonExistentDate = Date() + seconds(999999.0);
    auto events          = schedule.get_events_at(nonExistentDate);
    ASSERT_TRUE(events.empty());
}

TEST_F(ScheduleTest, GetScheduledDates)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date2, testEvent2);
    schedule.schedule_event(date3, testEvent1);

    auto scheduledDates = schedule.get_scheduled_dates();
    ASSERT_EQ(scheduledDates.size(), 3);

    // Dates should be returned in sorted order
    ASSERT_EQ(scheduledDates[0], date1);
    ASSERT_EQ(scheduledDates[1], date2);
    ASSERT_EQ(scheduledDates[2], date3);
}

TEST_F(ScheduleTest, GetScheduledDatesEmpty)
{
    auto scheduledDates = schedule.get_scheduled_dates();
    ASSERT_TRUE(scheduledDates.empty());
}

TEST_F(ScheduleTest, ClearSchedule)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date2, testEvent2);

    schedule.clear_schedule();

    auto scheduledDates = schedule.get_scheduled_dates();
    ASSERT_TRUE(scheduledDates.empty());

    auto events = schedule.get_events_at(date1);
    ASSERT_TRUE(events.empty());
}

TEST_F(ScheduleTest, RemoveEventsAt)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date1, testEvent2);
    schedule.schedule_event(date2, testEvent1);

    schedule.remove_events_at(date1);

    // Events at date1 should be removed
    auto eventsAtDate1 = schedule.get_events_at(date1);
    ASSERT_TRUE(eventsAtDate1.empty());

    // Events at date2 should remain
    auto eventsAtDate2 = schedule.get_events_at(date2);
    ASSERT_EQ(eventsAtDate2.size(), 1);

    // Scheduled dates should only contain date2
    auto scheduledDates = schedule.get_scheduled_dates();
    ASSERT_EQ(scheduledDates.size(), 1);
    ASSERT_EQ(scheduledDates[0], date2);
}

TEST_F(ScheduleTest, RemoveEventsAtNonExistentDate)
{
    schedule.schedule_event(date1, testEvent1);

    Date nonExistentDate = Date() + seconds(999999.0);
    ASSERT_NO_THROW(schedule.remove_events_at(nonExistentDate));

    // Original events should remain unchanged
    auto events = schedule.get_events_at(date1);
    ASSERT_EQ(events.size(), 1);
}

TEST_F(ScheduleTest, RemoveEventsBetween)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date2, testEvent2);
    schedule.schedule_event(date3, testEvent1);

    // Remove events between date1 and date2 (inclusive)
    schedule.remove_events_between(date1, date2);

    // Events at date1 and date2 should be removed
    auto eventsAtDate1 = schedule.get_events_at(date1);
    ASSERT_TRUE(eventsAtDate1.empty());

    auto eventsAtDate2 = schedule.get_events_at(date2);
    ASSERT_TRUE(eventsAtDate2.empty());

    // Events at date3 should remain
    auto eventsAtDate3 = schedule.get_events_at(date3);
    ASSERT_EQ(eventsAtDate3.size(), 1);

    auto scheduledDates = schedule.get_scheduled_dates();
    ASSERT_EQ(scheduledDates.size(), 1);
    ASSERT_EQ(scheduledDates[0], date3);
}

TEST_F(ScheduleTest, RemoveEventsBetweenSingleDate)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date2, testEvent2);

    // Remove events between date1 and date1 (just date1)
    schedule.remove_events_between(date1, date1);

    auto eventsAtDate1 = schedule.get_events_at(date1);
    ASSERT_TRUE(eventsAtDate1.empty());

    auto eventsAtDate2 = schedule.get_events_at(date2);
    ASSERT_EQ(eventsAtDate2.size(), 1);
}

TEST_F(ScheduleTest, TriggerScheduledEvents)
{
    schedule.schedule_event(date1, testEvent1);
    schedule.schedule_event(date1, testEvent2);

    schedule.trigger_scheduled_events(date1, time, state, vehicle);

    const auto& events = schedule.get_events_at(date1);
    ASSERT_EQ(events.size(), 2);

    const TestScheduleEvent* testEventImpl1  = events[0].extract<TestScheduleEvent>();
    const TestScheduleEvent2* testEventImpl2 = events[1].extract<TestScheduleEvent2>();

    // Both events should have been triggered
    ASSERT_TRUE(testEventImpl1->triggered);
    ASSERT_TRUE(testEventImpl2->triggered);
}

TEST_F(ScheduleTest, TriggerScheduledEventsAtNonExistentDate)
{
    schedule.schedule_event(date1, testEvent1);

    Date nonExistentDate = Date() + seconds(999999.0);
    ASSERT_NO_THROW(schedule.trigger_scheduled_events(nonExistentDate, time, state, vehicle));

    const auto& events                      = schedule.get_events_at(date1);
    const TestScheduleEvent* testEventImpl1 = events[0].extract<TestScheduleEvent>();

    // Event should not have been triggered
    ASSERT_FALSE(testEventImpl1->triggered);
}

TEST_F(ScheduleTest, TriggerScheduledEventsEmptySchedule)
{
    ASSERT_NO_THROW(schedule.trigger_scheduled_events(date1, time, state, vehicle));
}