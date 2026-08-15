/**
 * @file StateHistory.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for StateHistory class
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

#include <gtl/btree.hpp>

#include <astro/state/State.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to manage the history of states for an object over date.
 *
 * This class allows storing, retrieving, and managing the states of an object
 * at different dates, providing functionality to access the closest state
 * to a given date and to convert between different orbital elements.
 */
template <typename State_T>
class StateHistory {

    using EventTimesMap = gtl::btree_map<std::string, std::vector<Date>>;

  public:
    /**
     * @brief Default constructor for StateHistory.
     */
    StateHistory() = default;

    /**
     * @brief Constructor that initializes StateHistory with a specific object ID.
     *
     * @param objectId The ID of the object for which the state history is maintained.
     */
    StateHistory(const std::size_t& objectId) :
        _objectId(objectId)
    {
    }

    /**
     * @brief Destructor for StateHistory.
     */
    ~StateHistory() = default;

    /**
     * @brief Inserts a state at a specific date into the history.
     *
     * @param state The state to be inserted.
     */
    void insert(const State_T& state);

    /**
     * @brief Inserts multiple states from another StateHistory into this history.
     *
     * @param stateHistory The StateHistory containing the states to be inserted.
     */
    void insert(const StateHistory<State_T>& stateHistory);

    /**
     * @brief Appends a state to the end of the history without sorting.
     *
     * This method is faster than insert() but does not maintain sorted order.
     * Use with caution and only when you are sure the states are already sorted.
     *
     * @param state The state to be appended.
     */
    void fast_append(const State_T& state) { _states.push_back(state); }

    /**
     * @brief Prepends a state to the beginning of the history without sorting.
     *
     * This method is faster than insert() but does not maintain sorted order.
     * Use with caution and only when you are sure the states are already sorted.
     *
     * @param state The state to be prepended.
     */
    void fast_prepend(const State_T& state) { _states.insert(_states.begin(), state); }

    /**
     * @brief Get the number of states in the history.
     *
     * @return std::size_t The number of states in the history.
     */
    std::size_t size() const;

    /**
     * @brief Checks if the state history is empty.
     *
     * @return true if the state history is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Clears the state history, removing all stored states.
     */
    void clear();

    /**
     * @brief Retrieves the epoch (first date) of the state history.
     *
     * @return const Date& Reference to the epoch of the state history.
     */
    const Date& epoch() const { return _states.front().get_epoch(); }

    /**
     * @brief Retrieves the first and last states in the history.
     *
     * @return State_T& Reference to the first state.
     */
    State_T& first() { return _states.front(); }

    /**
     * @brief Retrieves the first and last states in the history.
     *
     * @return const State_T& Reference to the first state.
     */
    const State_T& first() const { return _states.front(); }

    /**
     * @brief Retrieves the last state in the history.
     *
     * @return State_T& Reference to the last state.
     */
    State_T& last() { return _states.back(); }

    /**
     * @brief Retrieves the last state in the history.
     *
     * @return const State_T& Reference to the last state.
     */
    const State_T& last() const { return _states.back(); }

    /**
     * @brief Sets the object ID for this state history.
     *
     * @param objectId The ID of the object for which this state history is maintained.
     */
    void set_object_id(const std::size_t& objectId) { _objectId = objectId; }

    /**
     * @brief Gets the object ID for this state history.
     *
     * @return std::size_t The ID of the object for which this state history is maintained.
     */
    std::size_t get_object_id() const { return _objectId; }

    /**
     * @brief Retrieves the closest state to a given date.
     *
     * This function finds the state that is closest to the specified date,
     * either before or after it, and returns it.
     *
     * @param date The date for which the closest state is requested.
     * @return const State_T& Reference to the closest state.
     */
    const State_T& get_closest_state(const Date& date) const;

    /**
     * @brief Retrieves the state at a specific date.
     *
     * This function returns the state at the specified date, or the closest
     * state if no exact match is found and allowApproximation is true, otherwise it interpolates to the given time.
     *
     * @param date The date for which the state is requested.
     * @param allowApproximation Flag indicating whether to allow returning the closest state if an exact match is not found (default is true).
     * @return State_T The state at the specified date.
     *
     * @note Allowing the approximation is generally recommended and will only accept times within a second of any stored points without interpolation.
     */
    State_T get_state_at(const Date& date, const bool allowApproximation = true) const;

    /**
     * @brief Sets the event times recorded during propagation.
     *
     * @param eventTimes A vector of dates representing the event times.
     */
    void set_event_times(const EventTimesMap& eventTimes) { _eventTimes = eventTimes; }

    /**
     * @brief Retrieves the event times recorded during propagation.
     *
     * @return const EventTimesMap& A vector of dates representing the event times.
     */
    const EventTimesMap& get_event_times() const { return _eventTimes; }

    /**
     * @brief Retrieves the event times recorded during propagation.
     *
     * @return const EventTimesMap& A vector of dates representing the event times.
     */
    EventTimesMap& get_event_times() { return _eventTimes; }

    /**
     * @brief Iterator types for iterating over the states in the history.
     */
    using iterator = std::vector<State_T>::iterator;

    /**
     * @brief Constant iterator types for iterating over the states in the history.
     */
    using const_iterator = std::vector<State_T>::const_iterator;

    /**
     * @brief Returns an iterator to the beginning of the state history.
     *
     * @return iterator An iterator to the first state in the history.
     */
    iterator begin() { return _states.begin(); }

    /**
     * @brief Returns an iterator to the end of the state history.
     *
     * @return iterator An iterator to the position after the last state in the history.
     */
    iterator end() { return _states.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the state history.
     *
     * @return const_iterator A constant iterator to the first state in the history.
     */
    const_iterator begin() const { return _states.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the state history.
     *
     * @return const_iterator A constant iterator to the position after the last state in the history.
     */
    const_iterator end() const { return _states.end(); }

    /**
     * @brief Returns a constant iterator to the beginning of the state history.
     *
     * @return const_iterator A constant iterator to the first state in the history.
     */
    const_iterator cbegin() const { return _states.cbegin(); }

    /**
     * @brief Returns a constant iterator to the end of the state history.
     *
     * @return const_iterator A constant iterator to the position after the last state in the history.
     */
    const_iterator cend() const { return _states.cend(); }

    /**
     * @brief Sorts the states in the history by date (epoch).
     *
     * This method should typically not be needed since insert() maintains sorted order,
     * but can be useful if states were modified after insertion.
     */
    void sort();

    /**
     * @brief Converts the orbital elements of all states in the history to a different type.
     *
     * @tparam T The type to convert the orbital elements to.
     */
    template <IsOrbitalElements T>
    void convert_to_set()
    {
        for (auto& state : _states) {
            state.convert_to_set<T>();
        }
    }

  private:
    std::vector<State_T> _states; //!< Vector to store states sorted by date
    EventTimesMap _eventTimes;    //!< Vector to store event times during propagation
    std::size_t _objectId = 0;    //!< ID of the object for which this state history is maintained
};

} // namespace astro
} // namespace astrea