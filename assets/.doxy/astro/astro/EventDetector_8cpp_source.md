

# File EventDetector.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**EventDetector.cpp**](EventDetector_8cpp.md)

[Go to the documentation of this file](EventDetector_8cpp.md)


```C++
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

#include <astro/propagation/event_detection/EventDetector.hpp>

#include <mp-units/math.h>

namespace astrea {
namespace astro {

EventDetector::EventDetector(const std::vector<Event>& events) { add_events(events); }

void EventDetector::add_event(const Event& event)
{
    _eventTrackers.push_back({ .event = event, .firstMeasurement = true });
}

void EventDetector::add_events(const std::vector<Event>& events)
{
    _eventTrackers.resize(events.size());
    for (std::size_t ii = 0; ii < events.size(); ++ii) {
        _eventTrackers[ii].event            = events[ii];
        _eventTrackers[ii].firstMeasurement = true;
    }
}

void EventDetector::clear_events() { _eventTrackers.clear(); }

std::vector<Event> EventDetector::get_events() const
{
    std::vector<Event> events;
    for (const auto& tracker : _eventTrackers) {
        events.push_back(tracker.event);
    }
    return events;
}

bool EventDetector::detect_events(const Time& time, State& state, Vehicle& vehicle)
{
    bool isTerminal = false;
    const Time eventTime = mp_units::round<mp_units::si::unit_symbols::s>(time); // Round to seconds to avoid numerical issues
    // TODO: Give precision control to user? Might need more machinery to handle this properly
    for (auto& tracker : _eventTrackers) {
        const Event& event = tracker.event;

        // Measure event
        const Unitless value = event.measure_event(eventTime, state, vehicle);

        // Test for a zero-crossing
        const bool eventDetected = detect_event(eventTime, value, tracker);

        if (eventDetected) {
            // Store trigger time
            tracker.detectionTimes.insert(eventTime);

            // Trigger action
            event.trigger_action(eventTime, state, vehicle);

            // Check for termination
            if (event.is_terminal()) { isTerminal = true; }
        }

        // Update the event tracker with the latest time and vehicle data
        tracker.previousTime  = eventTime;
        tracker.previousValue = value;
    }
    return isTerminal;
}

bool EventDetector::detect_event(const Time& time, const Unitless& value, EventTracker& tracker) const
{
    // Have to ignore first measurement to avoid sign assumptions
    static const Unitless zero = 0.0 * mp_units::one;
    if (tracker.firstMeasurement) {
        tracker.firstMeasurement = false;
        return false;
    }
    else if (tracker.previousValue == zero) {
        if (value != zero) { // Previous time was an exact event time so this one can't be
            return false;
        }
        else { // Previous time was an exact event time and so is this one
            return true;
        }
    }
    else {
        // Check for zero crossing
        if ((tracker.previousValue > zero && value <= zero) || (tracker.previousValue < zero && value >= zero)) {
            return true;
        }
    }
    return false;
}

gtl::btree_map<std::string, std::vector<Date>> EventDetector::get_event_times(const Date& epoch) const
{
    gtl::btree_map<std::string, std::vector<Date>> eventTimes;
    for (const auto& tracker : _eventTrackers) {
        std::vector<Date> dates;
        for (const auto& time : tracker.detectionTimes) {
            dates.push_back(epoch + time);
        }
        eventTimes[tracker.event.get_name()] = dates;
    }
    return eventTimes;
}

} // namespace astro
} // namespace astrea
```


