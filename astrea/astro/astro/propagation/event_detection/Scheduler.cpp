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

#include <astro/propagation/event_detection/Scheduler.hpp>

namespace astrea {
namespace astro {

void Scheduler::schedule_event(const Date& date, const Event& event)
{
    const std::size_t eventId = _events.size();
    _events[eventId]          = event;
    _schedule[date].push_back(eventId);
}

void Scheduler::schedule_event(const std::vector<Date>& dates, const Event& event)
{
    // This could end up with a lot of copies if the Event is large. Might need a redesign to store pointers to Events instead.
    for (const Date& date : dates) {
        schedule_event(date, event);
    }
}

std::vector<Event> Scheduler::get_events_at(const Date& date) const
{
    std::vector<Event> eventsAtDate;
    const auto it = _schedule.find(date);
    if (it != _schedule.end()) {
        for (const std::size_t eventId : it->second) {
            eventsAtDate.push_back(_events.at(eventId));
        }
    }
    return eventsAtDate;
}

std::vector<Date> Scheduler::get_scheduled_dates() const
{
    std::vector<Date> dates;
    for (const auto& [date, eventIds] : _schedule) {
        dates.push_back(date);
    }
    return dates;
}

void Scheduler::clear_schedule()
{
    _schedule.clear();
    _events.clear();
}

void Scheduler::remove_events_at(const Date& date)
{
    const auto it = _schedule.find(date);
    if (it != _schedule.end()) {
        for (const std::size_t eventId : it->second) {
            _events.erase(eventId);
        }
        _schedule.erase(it);
    }
}

void Scheduler::remove_events_between(const Date& startDate, const Date& endDate)
{
    auto it = _schedule.lower_bound(startDate);
    while (it != _schedule.end() && it->first <= endDate) {
        for (const std::size_t eventId : it->second) {
            _events.erase(eventId);
        }
        it = _schedule.erase(it);
    }
}

void Scheduler::trigger_scheduled_events(const Date& date, const Time& time, State& state, Vehicle& vehicle)
{
    const auto it = _schedule.find(date);
    if (it != _schedule.end()) {
        for (const std::size_t eventId : it->second) {
            _events.at(eventId).trigger_action(time, state, vehicle);
        }
    }
}

} // namespace astro
} // namespace astrea