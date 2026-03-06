

# File StateHistory.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**StateHistory.cpp**](StateHistory_8cpp.md)

[Go to the documentation of this file](StateHistory_8cpp.md)


```C++
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

namespace astrea {
namespace astro {


State& StateHistory::operator[](const Date& date) { return _states[date]; }
const State& StateHistory::at(const Date& date) const { return _states.at(date); }

void StateHistory::insert(const State& state) { _states.insert({ state.get_epoch(), state }); }
std::size_t StateHistory::size() const { return _states.size(); }
void StateHistory::clear() { _states.clear(); }

const State& StateHistory::get_closest_state(const Date& date) const
{
    // If exact, return
    if (_states.contains(date)) { return _states.at(date); }

    // Check if input date is out of bounds
    auto iter = _states.lower_bound(date);
    if (iter == _states.begin()) { return first(); }
    else if (iter == _states.end()) {
        return last();
    }

    // Compare date before and after index
    const Time upperDiff = abs((iter)->first - date);
    const Time lowerDiff = abs(std::prev(iter)->first - date);

    // Return closest
    if (lowerDiff < upperDiff) { return std::prev(iter)->second; }
    else {
        return (iter)->second;
    }
}

State StateHistory::get_state_at(const Date& date) const
{
    if (_states.size() == 0) { throw std::runtime_error("No states stored in StateHistory to extrapolate from."); }

    // If exact, return
    if (_states.contains(date)) { return _states.at(date); }

    // Check if input date is out of bounds
    auto iter = _states.lower_bound(date);
    if (iter == _states.begin()) {
        std::ostringstream oss;
        oss << "Cannot extrapolate to date (" << date << ") before first state (" << _states.begin()->first
            << "). Try repropagating to include all desired dates.";
        throw std::runtime_error(oss.str());
    }
    else if (iter == _states.end()) {
        std::ostringstream oss;
        oss << "Cannot extrapolate to date (" << date << ") after last state (" << _states.rbegin()->first
            << "). Try repropagating to include all desired dates.";
        throw std::runtime_error(oss.str());
    }

    // Interpolate
    const Date& postDate                = iter->first;
    const OrbitalElements& postElements = (iter->second).get_elements();

    const Date& preDate                = std::prev(iter)->first;
    const State& preState              = std::prev(iter)->second;
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

} // namespace astro
} // namespace astrea
```


