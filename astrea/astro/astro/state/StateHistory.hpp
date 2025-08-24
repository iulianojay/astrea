/**
 * @file StateHistory.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for StateHistory class
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <parallel_hashmap/btree.h>

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
class StateHistory {
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
     * @brief Accesses the state at a specific date.
     *
     * @param date The date at which the state is requested.
     * @return State& Reference to the state at the specified date.
     */
    State& operator[](const Date& date);

    /**
     * @brief Retrieves the state at a specific date.
     *
     * @param date The date at which the state is requested.
     * @return const State& Reference to the state at the specified date.
     */
    const State& at(const Date& date) const;

    /**
     * @brief Inserts a state at a specific date into the history.
     *
     * @param date The date at which the state is recorded.
     * @param state The state to be inserted.
     */
    void insert(const Date& date, const State& state);

    /**
     * @brief Get the number of states in the history.
     *
     * @return std::size_t The number of states in the history.
     */
    std::size_t size() const;

    /**
     * @brief Clears the state history, removing all stored states.
     */
    void clear();

    /**
     * @brief Retrieves the first and last states in the history.
     *
     * @return const State& Reference to the first state.
     */
    const State& first() const { return _states.begin()->second; }

    /**
     * @brief Retrieves the last state in the history.
     *
     * @return const State& Reference to the last state.
     */
    const State& last() const { return _states.rbegin()->second; }

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
     * @return const State& Reference to the closest state.
     */
    const State& get_closest_state(const Date& date) const;

    /**
     * @brief Retrieves the state at a specific date.
     *
     * This function returns the state at the specified date, or the closest
     * state if no exact match is found.
     *
     * @param date The date for which the state is requested.
     * @return State The state at the specified date.
     */
    State get_state_at(const Date& date) const;

    /**
     * @brief Iterator types for iterating over the states in the history.
     */
    using iterator = phmap::btree_map<Date, State>::iterator;

    /**
     * @brief Constant iterator types for iterating over the states in the history.
     */
    using const_iterator = phmap::btree_map<Date, State>::const_iterator;

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

  private:
    phmap::btree_map<Date, State> _states; //!< Map to store states indexed by date
    std::size_t _objectId = 0;             //!< ID of the object for which this state history is maintained
};

} // namespace astro
} // namespace astrea