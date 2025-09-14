#include <astro/propagation/event_detection/EventDetector.hpp>

#include <mp-units/math.h>

namespace astrea {
namespace astro {

EventDetector::EventDetector(const std::vector<Event>& events) { set_events(events); }

void EventDetector::set_events(const std::vector<Event>& events)
{
    _eventTrackers.clear();
    _eventTrackers.resize(events.size());
    for (std::size_t ii = 0; ii < events.size(); ++ii) {
        _eventTrackers[ii].event            = events[ii];
        _eventTrackers[ii].firstMeasurement = true;
    }
}

std::vector<Event> EventDetector::get_events() const
{
    std::vector<Event> events;
    for (const auto& tracker : _eventTrackers) {
        events.push_back(tracker.event);
    }
    return events;
}

bool EventDetector::detect_events(const Time& time, const OrbitalElements& state, Vehicle& vehicle)
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
            event.trigger_action(vehicle);

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

phmap::btree_map<std::string, std::vector<Date>> EventDetector::get_event_times(const Date& epoch) const
{
    phmap::btree_map<std::string, std::vector<Date>> eventTimes;
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