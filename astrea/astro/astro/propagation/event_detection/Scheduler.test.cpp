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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/Scheduler.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::s;

struct TestSchedulerEvent {
    TestSchedulerEvent() = default;
    std::string get_name() const { return "Test Scheduler Event"; }
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

struct TestSchedulerEvent2 {
    TestSchedulerEvent2() = default;
    std::string get_name() const { return "Test Scheduler Event 2"; }
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
    {
        return 2.0 * mp_units::one;
    }
    bool is_terminal() const { return true; }
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const { triggered = true; }
    mutable bool triggered = false;
};

class SchedulerTest : public testing::Test {
  public:
    SchedulerTest() :
        time(0.0 * s),
        date1(Date()),
        date2(Date() + days(1)),
        date3(Date() + days(2))
    {
    }
    void SetUp() override {}

    Scheduler scheduler;
    Event testEvent1{ TestSchedulerEvent() };
    Event testEvent2{ TestSchedulerEvent2() };
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

TEST_F(SchedulerTest, DefaultConstructor) { ASSERT_NO_THROW(Scheduler scheduler); }

TEST_F(SchedulerTest, ScheduleSingleEvent)
{
    ASSERT_NO_THROW(scheduler.schedule_event(date1, testEvent1));

    // Verify the event was scheduled
    auto events = scheduler.get_events_at(date1);
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0].get_name(), "Test Scheduler Event");
}

TEST_F(SchedulerTest, ScheduleMultipleEventsAtSameDate)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date1, testEvent2);

    auto events = scheduler.get_events_at(date1);
    ASSERT_EQ(events.size(), 2);

    // Events should be returned in the order they were scheduled
    ASSERT_EQ(events[0].get_name(), "Test Scheduler Event");
    ASSERT_EQ(events[1].get_name(), "Test Scheduler Event 2");
}

TEST_F(SchedulerTest, ScheduleEventsAtMultipleDates)
{
    std::vector<Date> dates = { date1, date2, date3 };
    scheduler.schedule_event(dates, testEvent1);

    // Verify events are scheduled at all dates
    for (const auto& date : dates) {
        auto events = scheduler.get_events_at(date);
        ASSERT_EQ(events.size(), 1);
        ASSERT_EQ(events[0].get_name(), "Test Scheduler Event");
    }
}

TEST_F(SchedulerTest, GetEventsAtNonExistentDate)
{
    Date nonExistentDate = Date() + seconds(999999.0);
    auto events          = scheduler.get_events_at(nonExistentDate);
    ASSERT_TRUE(events.empty());
}

TEST_F(SchedulerTest, GetScheduledDates)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date2, testEvent2);
    scheduler.schedule_event(date3, testEvent1);

    auto scheduledDates = scheduler.get_scheduled_dates();
    ASSERT_EQ(scheduledDates.size(), 3);

    // Dates should be returned in sorted order
    ASSERT_EQ(scheduledDates[0], date1);
    ASSERT_EQ(scheduledDates[1], date2);
    ASSERT_EQ(scheduledDates[2], date3);
}

TEST_F(SchedulerTest, GetScheduledDatesEmpty)
{
    auto scheduledDates = scheduler.get_scheduled_dates();
    ASSERT_TRUE(scheduledDates.empty());
}

TEST_F(SchedulerTest, ClearSchedule)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date2, testEvent2);

    scheduler.clear_schedule();

    auto scheduledDates = scheduler.get_scheduled_dates();
    ASSERT_TRUE(scheduledDates.empty());

    auto events = scheduler.get_events_at(date1);
    ASSERT_TRUE(events.empty());
}

TEST_F(SchedulerTest, RemoveEventsAt)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date1, testEvent2);
    scheduler.schedule_event(date2, testEvent1);

    scheduler.remove_events_at(date1);

    // Events at date1 should be removed
    auto eventsAtDate1 = scheduler.get_events_at(date1);
    ASSERT_TRUE(eventsAtDate1.empty());

    // Events at date2 should remain
    auto eventsAtDate2 = scheduler.get_events_at(date2);
    ASSERT_EQ(eventsAtDate2.size(), 1);

    // Scheduled dates should only contain date2
    auto scheduledDates = scheduler.get_scheduled_dates();
    ASSERT_EQ(scheduledDates.size(), 1);
    ASSERT_EQ(scheduledDates[0], date2);
}

TEST_F(SchedulerTest, RemoveEventsAtNonExistentDate)
{
    scheduler.schedule_event(date1, testEvent1);

    Date nonExistentDate = Date() + seconds(999999.0);
    ASSERT_NO_THROW(scheduler.remove_events_at(nonExistentDate));

    // Original events should remain unchanged
    auto events = scheduler.get_events_at(date1);
    ASSERT_EQ(events.size(), 1);
}

TEST_F(SchedulerTest, RemoveEventsBetween)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date2, testEvent2);
    scheduler.schedule_event(date3, testEvent1);

    // Remove events between date1 and date2 (inclusive)
    scheduler.remove_events_between(date1, date2);

    // Events at date1 and date2 should be removed
    auto eventsAtDate1 = scheduler.get_events_at(date1);
    ASSERT_TRUE(eventsAtDate1.empty());

    auto eventsAtDate2 = scheduler.get_events_at(date2);
    ASSERT_TRUE(eventsAtDate2.empty());

    // Events at date3 should remain
    auto eventsAtDate3 = scheduler.get_events_at(date3);
    ASSERT_EQ(eventsAtDate3.size(), 1);

    auto scheduledDates = scheduler.get_scheduled_dates();
    ASSERT_EQ(scheduledDates.size(), 1);
    ASSERT_EQ(scheduledDates[0], date3);
}

TEST_F(SchedulerTest, RemoveEventsBetweenSingleDate)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date2, testEvent2);

    // Remove events between date1 and date1 (just date1)
    scheduler.remove_events_between(date1, date1);

    auto eventsAtDate1 = scheduler.get_events_at(date1);
    ASSERT_TRUE(eventsAtDate1.empty());

    auto eventsAtDate2 = scheduler.get_events_at(date2);
    ASSERT_EQ(eventsAtDate2.size(), 1);
}

TEST_F(SchedulerTest, TriggerScheduledEvents)
{
    scheduler.schedule_event(date1, testEvent1);
    scheduler.schedule_event(date1, testEvent2);

    scheduler.trigger_scheduled_events(date1, time, state, vehicle);

    const auto& events = scheduler.get_events_at(date1);
    ASSERT_EQ(events.size(), 2);

    const TestSchedulerEvent* testEventImpl1  = events[0].extract<TestSchedulerEvent>();
    const TestSchedulerEvent2* testEventImpl2 = events[1].extract<TestSchedulerEvent2>();

    // Both events should have been triggered
    ASSERT_TRUE(testEventImpl1->triggered);
    ASSERT_TRUE(testEventImpl2->triggered);
}

TEST_F(SchedulerTest, TriggerScheduledEventsAtNonExistentDate)
{
    scheduler.schedule_event(date1, testEvent1);

    Date nonExistentDate = Date() + seconds(999999.0);
    ASSERT_NO_THROW(scheduler.trigger_scheduled_events(nonExistentDate, time, state, vehicle));

    const auto& events                       = scheduler.get_events_at(date1);
    const TestSchedulerEvent* testEventImpl1 = events[0].extract<TestSchedulerEvent>();

    // Event should not have been triggered
    ASSERT_FALSE(testEventImpl1->triggered);
}

TEST_F(SchedulerTest, TriggerScheduledEventsEmptySchedule)
{
    ASSERT_NO_THROW(scheduler.trigger_scheduled_events(date1, time, state, vehicle));
}