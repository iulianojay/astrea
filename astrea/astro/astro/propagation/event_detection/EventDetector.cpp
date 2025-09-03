#include <astro/propagation/event_detection/EventDetector.hpp>

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

bool EventDetector::detect_events(const Time& time, const OrbitalElements& state, Vehicle& vehicle)
{
    bool isTerminal = false;
    for (auto& tracker : _eventTrackers) {
        const Event& event = tracker.event;

        // Measure event
        const Unitless value = event.measure_event(time, state, vehicle);

        // Test for a zero-crossing
        const bool eventDetected = detect_event(time, value, tracker);

        // Trigger action
        if (eventDetected) { event.trigger_action(vehicle); }

        // Check for termination
        if (eventDetected && event.is_terminal()) { isTerminal = true; }

        // Update the event tracker with the latest time and vehicle data
        tracker.previousTime  = time;
        tracker.previousValue = value;
    }
    return isTerminal;
}

bool EventDetector::detect_event(const Time& time, const Unitless& value, EventTracker& tracker) const
{
    // Have to ignore first measurement to avoid sign assumptions
    if (tracker.firstMeasurement) {
        tracker.firstMeasurement = false;
        return false;
    }
    else if (tracker.previousValue == 0.0 * mp_units::one) {
        if (value != 0.0 * mp_units::one) { // Previous time was an exact event time so this one can't be
            return false;
        }
        else { // Previous time was an exact event time and so is this one
            return true;
        }
    }
    else {
        // Check for zero crossing
        if ((tracker.previousValue > 0.0 * mp_units::one && value <= 0.0 * mp_units::one) ||
            (tracker.previousValue < 0.0 * mp_units::one && value >= 0.0 * mp_units::one)) {
            return true;
        }
    }
    return false;
}

} // namespace astro
} // namespace astrea