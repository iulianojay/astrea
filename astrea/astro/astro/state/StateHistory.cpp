/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/state/StateHistory.hpp>

#include <iostream>

#include <mp-units/math.h>

using namespace mp_units;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

void StateHistory::insert(const State& state)
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

void StateHistory::insert(const StateHistory& stateHistory)
{
    for (const auto& state : stateHistory._states) {
        insert(state);
    }
}

std::size_t StateHistory::size() const { return _states.size(); }
bool StateHistory::empty() const { return _states.empty(); }
void StateHistory::clear() { _states.clear(); }

const State& StateHistory::get_closest_state(const Date& date) const
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

State StateHistory::get_state_at(const Date& date, const bool allowApproximation) const
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

    const AstrodynamicsSystem& system = preState.get_system();
    const auto& mu                    = system.get_mu();

    // Normalize to initial date for simplicity
    const Time time0 = 0.0 * astrea::detail::time_unit;
    const Time timef = postDate - preDate;
    const Time time  = date - preDate;

    const OrbitalElements interpolatedElements = preElements.interpolate(time0, timef, postElements, mu, time);
    return State({ interpolatedElements, date, system });

    // // Insert if we want this to store
    // _states[date] = interpolatedState;

    // return _states.at(date);
}

void StateHistory::sort()
{
    std::sort(_states.begin(), _states.end(), [](const State& a, const State& b) {
        return a.get_epoch() < b.get_epoch();
    });
}

} // namespace astro
} // namespace astrea