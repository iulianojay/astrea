/**
 * @file EventDetector.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class for detecting events in the astrea astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <set>
#include <vector>

#include <parallel_hashmap/btree.h>

#include <units/units.hpp>

#include <astro/propagation/event_detection/Event.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class for detecting events in the astrea astro platform.
 */
class EventDetector {

    /**
     * @brief A struct for tracking events.
     */
    struct EventTracker {
        Event event;                   //!< The Event being tracked.
        bool firstMeasurement;         //!< Whether this is the first measurement for the Event.
        Time previousTime;             //!< The previous time the Event was measured.
        Unitless previousValue;        //!< The previous value the Event was measured at.
        std::set<Time> detectionTimes; //!< The times at which the Event was detected.
    };

  public:
    /**
     * @brief Default constructor for EventDetector.
     */
    EventDetector() = default;

    /**
     * @brief Constructs an EventDetector with a given list of Events.
     *
     * @param events The list of Events to track.
     */
    EventDetector(const std::vector<Event>& events);

    /**
     * @brief Destructor for EventDetector.
     */
    ~EventDetector() = default;

    /**
     * @brief Sets the list of Events to track.
     *
     * @param events The list of Events to track.
     */
    void set_events(const std::vector<Event>& events);

    /**
     * @brief Get events being tracked.
     *
     * @return const std::vector<Event>& A const reference to the list of Events being tracked.
     */
    std::vector<Event> get_events() const;

    /**
     * @brief Check if there are any events being tracked.
     *
     * @return true If there are no events being tracked.
     * @return false If there are events being tracked.
     */
    bool empty() const { return _eventTrackers.empty(); }

    /**
     * @brief Detects events for a given time and vehicle.
     *
     * @param time The current time.
     * @param vehicle The Vehicle to check for events.
     * @return true If a terminal event was detected.
     * @return false If no terminal event was detected.
     */
    bool detect_events(const Time& time, const OrbitalElements& state, Vehicle& vehicle);

    /**
     * @brief Retrieves the event times recorded during propagation.
     *
     * @param epoch The epoch to which the event times are relative.
     * @return const std::vector<Date>& A vector of dates representing the event times.
     */
    phmap::btree_map<std::string, std::vector<Date>> get_event_times(const Date& epoch) const;

  private:
    std::vector<EventTracker> _eventTrackers; //!< The list of Event trackers.

    /**
     * @brief Detects an event for a given time and value.
     *
     * @param time The current time.
     * @param value The current value.
     * @param tracker The Event tracker to update.
     * @return true If the event was detected.
     * @return false If the event was not detected.
     */
    bool detect_event(const Time& time, const Unitless& value, EventTracker& tracker) const;
};

} // namespace astro
} // namespace astrea