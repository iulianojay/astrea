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

#include <astro/propagation/event_detection/EventDetector.hpp>

#include <mp-units/math.h>

using namespace mp_units;
using mp_units::si::unit_symbols::s;

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

bool EventDetector::detect_events(const Time& time, State& state, Vehicle& vehicle)
{
    bool isTerminal = false;
    // TODO: Give precision control to user? Might need more machinery to handle this properly
    for (auto& tracker : _eventTrackers) {
        const Event& event = tracker.event;

        // Measure event
        const Unitless value = event.measure_event(time, state, vehicle);

        // Test for a zero-crossing
        const bool eventDetected = detect_zero_crossing(time, value, tracker);

        if (eventDetected) {
            // Find exact event time using bisection method
            const Time eventTime = (value == 0.0) ? time : find_zero_crossing_time(time, tracker, state, vehicle);

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
        tracker.previousState = state;
    }
    return isTerminal;
}

bool EventDetector::detect_zero_crossing(const Time& time, const Unitless& value, EventTracker& tracker) const
{
    // Setup
    const EventDirection direction = tracker.event.get_event_direction();
    const bool catchRising         = (direction == EventDirection::RISING || direction == EventDirection::ANY);
    const bool catchFalling        = (direction == EventDirection::FALLING || direction == EventDirection::ANY);

    // Have to ignore first measurement to avoid sign assumptions
    if (tracker.firstMeasurement) {
        tracker.firstMeasurement = false;
        return false;
    }
    else if (tracker.previousValue == 0.0) {
        if (value != 0.0) { // Previous time was an exact event time and this one isn't
            return false;
        }
        else { // Previous time was an exact event time and so is this one
            return true;
        }
    }
    else {
        // Check for zero crossing
        if ((catchFalling && tracker.previousValue > 0.0 && value <= 0.0) ||
            (catchRising && tracker.previousValue < 0.0 && value >= 0.0)) {
            return true;
        }
    }
    return false;
}

Time EventDetector::find_zero_crossing_time(const Time& time, const EventTracker& tracker, State& state, Vehicle& vehicle) const
{
    // Settings. Hard coding is fine
    static const Time ZERO_CROSSING_TOL      = 1.0 * s; //!< The tolerance for detecting zero crossings.
    static const unsigned MAX_BISECTION_ITER = 100;     //!< The maximum number of iterations for the bisection method.

    // Setup
    const Event& event             = tracker.event;
    const State& previousState     = tracker.previousState;
    const Time previousTime        = tracker.previousTime;
    const EventDirection direction = event.get_event_direction();
    const bool catchRising         = (direction == EventDirection::RISING || direction == EventDirection::ANY);
    const bool catchFalling        = (direction == EventDirection::FALLING || direction == EventDirection::ANY);

    // Bisection method to find the zero-crossing time
    Time lowerBound = previousTime;
    Time upperBound = time;
    unsigned iter   = 0;
    while (upperBound - lowerBound > ZERO_CROSSING_TOL && iter < MAX_BISECTION_ITER) {
        const Time midPoint = (lowerBound + upperBound) / 2.0;

        // Interpolate state at midPoint - this should be valid since the integrator is only stepping between states if
        // they're valid to linearize under whatever stepping scheme. It won't be perfect, but it's miles better than
        // iterating directly with the integrator steppers (which would be a nightmare to implement and would be very slow).
        const State midState = previousState.interpolate(previousTime, time, state, midPoint);

        // Measure event at midPoint
        const Unitless midValue = event.measure_event(midPoint, midState, vehicle);

        if (midValue == 0.0) {
            return midPoint; // Exact zero found
        }
        else if ((catchRising && midValue < 0.0) || (catchFalling && midValue > 0.0)) {
            lowerBound = midPoint; // Zero is in the upper half
        }
        else {
            upperBound = midPoint; // Zero is in the lower half
        }
        ++iter;
    }

    if (iter >= MAX_BISECTION_ITER) {
        std::cerr << "Warning: Maximum bisection iterations reached while finding zero-crossing time of "
                  << event.get_name() << ". Returning midpoint as best estimate.\n";
    }

    // Round to seconds to avoid numerical issues
    return round<s>((lowerBound + upperBound) / 2.0); // Return midpoint as the best estimate of the zero-crossing time
}

} // namespace astro
} // namespace astrea