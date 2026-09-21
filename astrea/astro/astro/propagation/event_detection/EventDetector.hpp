/**
 * @file EventDetector.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class for detecting events in the astrea astro platform.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <set>
#include <vector>

#include <gtl/btree.hpp>

#include <units/units.hpp>

#include <astro/propagation/event_detection/Event.hpp>

namespace astrea {
namespace astro {

struct EventDetectionResult {
    bool isTerminal;     //!< Indicates if a terminal event was detected
    bool eventTriggered; //!< Indicates if any event was triggered
};

/**
 * @brief A class for detecting events in the astrea astro platform.
 */
class EventDetector {

    /**
     * @brief A struct for tracking events.
     */
    struct EventTracker {
        uint_8 id;                     //!< The unique identifier for the Event.
        Event event;                   //!< The Event being tracked.
        bool firstMeasurement;         //!< Whether this is the first measurement for the Event.
        Time previousTime;             //!< The previous time the Event was measured.
        Unitless previousValue;        //!< The previous value the Event was measured at.
        State previousState;           //!< The previous state of the Vehicle when the Event was measured.
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
     * @brief Adds an Event to the list of Events to track.
     *
     * @param event The Event to add.
     */
    void add_event(const Event& event);

    /**
     * @brief Sets the list of Events to track.
     *
     * @param events The list of Events to track.
     */
    void add_events(const std::vector<Event>& events);

    /**
     * @brief Clears all Events from the list of Events to track.
     */
    void clear_events();

    /**
     * @brief Get events being tracked.
     *
     * @return const std::vector<Event>& A const reference to the list of Events being tracked.
     */
    std::vector<Event> get_events() const;

    /**
     * @brief Detects events for a given time and vehicle.
     *
     * @param time The current time.
     * @param state The current state.
     * @param vehicle The Vehicle to check for events.
     * @return EventDetectionResult An object indicating whether a terminal event was detected and whether any event was triggered.
     */
    EventDetectionResult detect_events(Time& time, State& state, Vehicle& vehicle);

    /**
     * @brief Retrieves the event times recorded during propagation.
     *
     * @param epoch The epoch to which the event times are relative.
     * @return const std::vector<Date>& A vector of dates representing the event times.
     */
    gtl::btree_map<std::string, std::vector<Date>> get_event_times(const Date& epoch) const;

  private:
    std::vector<EventTracker> _eventTrackers; //!< The list of Event trackers.

    /**
     * @brief Detects an event zero-crossing for a given time and value.
     *
     * @param time The current time.
     * @param value The current value.
     * @param tracker The Event tracker to update.
     * @return true If the event was detected.
     * @return false If the event was not detected.
     */
    bool detect_zero_crossing(const Time& time, const Unitless& value, EventTracker& tracker) const;

    /**
     * @brief Finds the zero-crossing time for an event using the bisection method.
     *
     * @param time The current time.
     * @param tracker The Event tracker containing the previous state and time.
     * @param state The current state.
     * @param vehicle The Vehicle to check for events.
     * @return std::tuple<Time, State> The estimated zero-crossing time and the corresponding state.
     */
    std::tuple<Time, State>
        find_zero_crossing_time(const Time& time, const EventTracker& tracker, const State& state, const Vehicle& vehicle) const;
};

} // namespace astro
} // namespace astrea