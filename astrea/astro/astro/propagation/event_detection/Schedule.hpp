/**
 * @file Schedule.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a Schedule in the astrea astro library.
 * @date 2026-03-14
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

#include <vector>

#include <gtl/btree.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a Schedule in the astrea astro library.
 * The Schedule is responsible for scheduling and managing Events that are set to trigger at specific Dates during propagation.
 */
class Schedule {
  public:
    /**
     * @brief Default constructor for the Schedule class.
     */
    Schedule() = default;

    /**
     * @brief Schedules an Event to trigger at a specific Date.
     *
     * @param date The Date at which the Event should trigger.
     * @param event The Event to be scheduled.
     */
    void schedule_event(const Date& date, const Event& event);

    /**
     * @brief Schedules an Event to trigger at multiple Dates.
     *
     * @param dates A vector of Dates at which the Event should trigger.
     * @param event The Event to be scheduled.
     */
    void schedule_event(const std::vector<Date>& dates, const Event& event);

    /**
     * @brief Retrieves the Events scheduled to trigger at a specific Date.
     *
     * @param date The Date for which to retrieve the scheduled Events.
     * @return std::vector<Event> A vector of Events scheduled to trigger at the specified Date.
     */
    std::vector<Event> get_events_at(const Date& date) const;

    /**
     * @brief Retrieves all the Dates that have Events scheduled.
     *
     * @return std::vector<Date> A vector of Dates that have Events scheduled.
     */
    std::vector<Date> get_scheduled_dates() const;

    /**
     * @brief Clears all scheduled Events and their associated Dates from the Schedule.
     */
    void clear();

    /**
     * @brief Removes all Events scheduled to trigger at a specific Date.
     *
     * @param date The Date for which to remove the scheduled Events.
     */
    void remove_events_at(const Date& date);

    /**
     * @brief Removes all Events scheduled to trigger between two Dates (inclusive).
     *
     * @param startDate The start Date of the range for which to remove the scheduled Events.
     * @param endDate The end Date of the range for which to remove the scheduled Events.
     */
    void remove_events_between(const Date& startDate, const Date& endDate);

    /**
     * @brief Triggers all Events scheduled to trigger at a specific Date.
     *
     * @param date The Date at which to trigger the scheduled Events.
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The Vehicle to trigger the Events on.
     */
    void trigger_scheduled_events(const Date& date, const Time& time, State& state, Vehicle& vehicle) const;

  private:
    gtl::btree_map<Date, std::vector<std::size_t>> _schedule; //!< A schedule of events
    gtl::btree_map<std::size_t, Event> _events;               //!< A map of event IDs to their corresponding Events
};

} // namespace astro
} // namespace astrea