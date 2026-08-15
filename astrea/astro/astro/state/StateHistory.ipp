/**
 * @file StateHistory.ipp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Implementation file for StateHistory class
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
 */
#pragma once

#include <iostream>

#include <mp-units/math.h>

using namespace mp_units;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

template <typename State_T>
void StateHistory<State_T>::insert(const State_T& state)
{
    auto iter = std::lower_bound(_states.begin(), _states.end(), state.get_epoch(), [](const State& existingState, const Date& date) {
        return existingState.get_epoch() < date;
    });

    // If state with same epoch exists, replace it
    if (iter != _states.end() && iter->get_epoch() == state.get_epoch()) { *iter = state; }
    else {
        // Insert at the correct position to maintain sorted order
        _states.insert(iter, state);
    }
}

template <typename State_T>
void StateHistory<State_T>::insert(const StateHistory<State_T>& stateHistory)
{
    for (const auto& state : stateHistory._states) {
        insert(state);
    }
}

template <typename State_T>
std::size_t StateHistory<State_T>::size() const
{
    return _states.size();
}
template <typename State_T>
bool StateHistory<State_T>::empty() const
{
    return _states.empty();
}
template <typename State_T>
void StateHistory<State_T>::clear()
{
    _states.clear();
}

template <typename State_T>
const State_T& StateHistory<State_T>::get_closest_state(const Date& date) const
{
    if (_states.empty()) { throw std::runtime_error("No states stored in StateHistory."); }

    // Find the first state with epoch >= date
    auto iter = std::lower_bound(_states.begin(), _states.end(), date, [](const State& state, const Date& target_date) {
        return state.get_epoch() < target_date;
    });

    // If exact match, return it
    if (iter != _states.end() && iter->get_epoch() == date) { return *iter; }

    // Check if input date is out of bounds
    if (iter == _states.begin()) { return first(); }
    else if (iter == _states.end()) {
        return last();
    }

    // Compare date before and after index
    const Time upperDiff = abs(iter->get_epoch() - date);
    const Time lowerDiff = abs(std::prev(iter)->get_epoch() - date);

    // Return closest
    if (lowerDiff < upperDiff) { return *std::prev(iter); }
    else {
        return *iter;
    }
}

template <typename State_T>
State_T StateHistory<State_T>::get_state_at(const Date& date, const bool allowApproximation) const
{
    if (_states.size() == 0) { throw std::runtime_error("No states stored in StateHistory to extrapolate from."); }

    // Find the first state with epoch >= date
    auto iter = std::lower_bound(_states.begin(), _states.end(), date, [](const State& state, const Date& target_date) {
        return state.get_epoch() < target_date;
    });

    // If within a second, return it
    static constexpr auto allowableTimeError = 0.5 * s;
    if (iter != _states.end() &&
        (allowApproximation ? abs(iter->get_epoch() - date) <= allowableTimeError : iter->get_epoch() == date)) {
        return *iter;
    }

    // Check if input date is out of bounds
    if (iter == _states.begin()) {
        std::ostringstream oss;
        oss << "Cannot extrapolate to date (" << date << ") before first state (" << _states.begin()->get_epoch()
            << "). Try repropagating to include all desired dates.";
        throw std::runtime_error(oss.str());
    }
    else if (iter == _states.end()) {
        std::ostringstream oss;
        oss << "Cannot extrapolate to date (" << date << ") after last state (" << _states.rbegin()->get_epoch()
            << "). Try repropagating to include all desired dates.";
        throw std::runtime_error(oss.str());
    }

    // Interpolate
    const Date& postDate                = iter->get_epoch();
    const OrbitalElements& postElements = iter->get_elements();

    const Date& preDate                = std::prev(iter)->get_epoch();
    const State& preState              = *std::prev(iter);
    const OrbitalElements& preElements = preState.get_elements();

    const auto& mu = get_mu<frames::earth::icrf.origin>();

    // Normalize to initial date for simplicity
    const Time time0 = 0.0 * astrea::detail::time_unit;
    const Time timef = postDate - preDate;
    const Time time  = date - preDate;

    const OrbitalElements interpolatedElements = preElements.interpolate(time0, timef, postElements, mu, time);
    return State({ interpolatedElements, date });

    // // Insert if we want this to store
    // _states[date] = interpolatedState;

    // return _states.at(date);
}

template <typename State_T>
void StateHistory<State_T>::sort()
{
    std::sort(_states.begin(), _states.end(), [](const State& a, const State& b) {
        return a.get_epoch() < b.get_epoch();
    });
}

} // namespace astro
} // namespace astrea