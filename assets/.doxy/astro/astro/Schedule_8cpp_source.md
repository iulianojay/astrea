

# File Schedule.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**Schedule.cpp**](Schedule_8cpp.md)

[Go to the documentation of this file](Schedule_8cpp.md)


```C++
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

#include <astro/propagation/event_detection/Schedule.hpp>

namespace astrea {
namespace astro {

void Schedule::schedule_event(const Date& date, const Event& event)
{
    const std::size_t eventId = _events.size();
    _events[eventId]          = event;
    _schedule[date].push_back(eventId);
}

void Schedule::schedule_event(const std::vector<Date>& dates, const Event& event)
{
    // This could end up with a lot of copies if the Event is large. Might need a redesign to store pointers to Events instead.
    for (const Date& date : dates) {
        schedule_event(date, event);
    }
}

std::vector<Event> Schedule::get_events_at(const Date& date) const
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

std::vector<Date> Schedule::get_scheduled_dates() const
{
    std::vector<Date> dates;
    for (const auto& [date, eventIds] : _schedule) {
        dates.push_back(date);
    }
    return dates;
}

void Schedule::clear()
{
    _schedule.clear();
    _events.clear();
}

void Schedule::remove_events_at(const Date& date)
{
    const auto it = _schedule.find(date);
    if (it != _schedule.end()) {
        for (const std::size_t eventId : it->second) {
            _events.erase(eventId);
        }
        _schedule.erase(it);
    }
}

void Schedule::remove_events_between(const Date& startDate, const Date& endDate)
{
    auto it = _schedule.lower_bound(startDate);
    while (it != _schedule.end() && it->first <= endDate) {
        for (const std::size_t eventId : it->second) {
            _events.erase(eventId);
        }
        it = _schedule.erase(it);
    }
}

void Schedule::trigger_scheduled_events(const Date& date, const Time& time, State& state, Vehicle& vehicle) const
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
```


