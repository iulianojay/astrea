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
    _eventTrackers.push_back({ .id = static_cast<uint_8>(_eventTrackers.size()), .event = event, .firstMeasurement = true });
}

void EventDetector::add_events(const std::vector<Event>& events)
{
    _eventTrackers.resize(events.size());
    for (std::size_t ii = 0; ii < events.size(); ++ii) {
        _eventTrackers[ii].id               = static_cast<uint_8>(ii);
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

EventDetectionResult EventDetector::detect_events(Time& time, State& state, Vehicle& vehicle)
{
    /**
        1. Detect all events
        2. For each event, find exact time
        3. Find first event and trigger it
        3a. If no trigger, just continue until an event has a trigger
        3b. If event is terminal, just exit
        4. Remove first triggered events from next check only
        5. Repeat until no events left
    */

    // Check for events since last time step
    auto& triggeredTrackers = detect_events_impl(time, state, vehicle);

    // If no events were detected, exit
    if (triggeredTrackers.empty()) { return { .isTerminal = false, .eventTriggered = false }; }

    // Sort by latest event detection time
    std::sort(triggeredTrackers.begin(), triggeredTrackers.end(), [](const EventTracker& a, const EventTracker& b) {
        return *a.detectionTimes.rbegin() < *b.detectionTimes.rbegin();
    });

    // Trigger the earliest event
    for (auto& tracker : triggeredTrackers) {
        const Event& event = tracker.event;

        // If the event is terminal, exit
        if (event.is_terminal()) { return { .isTerminal = true, .eventTriggered = false }; }

        // Trigger only the first event with a trigger action and return to the propagation loop to check for events again
        // TODO: This may end up with a lot of sluggish re-integration over the same times. Need to study and see if it's a
        // practical concern
        if (event.has_trigger_action()) {
            // implicit function sets event crossing time/state to previousTime/previousState
            // we overwrite the time/state to the previous time/state so that the trigger action is applied at the event crossing time/state
            time  = tracker.previousTime;
            state = tracker.previousState;
            event.trigger_action(time, state, vehicle);

            // Now we need to overwrite all the previous times and states for all trackers to the current time and state
            // in case this event trigger action changed the state or the vehicle in a way that would affect the other events
            for (auto& otherTracker : _eventTrackers) {
                if (otherTracker.id == tracker.id) { continue; }
                otherTracker.previousTime  = time;
                otherTracker.previousState = state;
                otherTracker.previousValue = otherTracker.event.measure_event(time, state, vehicle);
            }
            break;
        }
    }
    return { .isTerminal = false, .eventTriggered = true };
}

std::vector<EventTracker> EventDetector::detect_events_impl(const Time& time, const State& state, const Vehicle& vehicle)
{
    std::vector<EventTracker> triggeredTrackers;
    bool isTerminal = false;
    for (auto& tracker : _eventTrackers) {
        const Event& event = tracker.event;

        // Measure event
        const Unitless value = event.measure_event(time, state, vehicle);

        // Test for a zero-crossing
        const bool eventDetected = detect_zero_crossing(time, value, tracker);

        if (eventDetected && value != 0.0) {
            // Find exact event time using bisection method
            auto [eventTime, eventState] = find_zero_crossing_time(time, tracker, state, vehicle);

            // Store trigger time
            tracker.detectionTimes.insert(eventTime);

            // Check for termination
            if (event.is_terminal()) { isTerminal = true; }
            triggeredTrackers.push_back(tracker);

            tracker.previousTime  = eventTime;
            tracker.previousValue = 0.0; // Set to exact zero to avoid rounding issues in future checks
            tracker.previousState = eventState;
        }
        else {
            // Update the event tracker with the latest time and vehicle data
            tracker.previousTime  = time;
            tracker.previousValue = value;
            tracker.previousState = state;
        }
    }
    return triggeredTrackers;
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
        if (value != 0.0) { // Previous time was an exact event time and this one isn't -> Not a crossing
            return false;
        }
        else { // Previous time was an exact event time and so is this one -> Assume it's a valid crossing
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

std::tuple<Time, State>
    EventDetector::find_zero_crossing_time(const Time& time, const EventTracker& tracker, const State& state, const Vehicle& vehicle) const
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
            return { midPoint, midState }; // Exact zero found
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

    const Time bestEstimate = (lowerBound + upperBound) / 2.0;
    const State bestState   = previousState.interpolate(previousTime, time, state, bestEstimate);
    return { bestEstimate, bestState }; // Return midpoint as the best estimate of the zero-crossing time
}

} // namespace astro
} // namespace astrea