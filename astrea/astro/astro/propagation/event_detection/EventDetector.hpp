/**
 * @file EventDetector.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class for detecting events in the astrea astro platform.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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
    gtl::btree_map<std::string, std::vector<Date>> get_event_times(const Date& epoch) const;

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