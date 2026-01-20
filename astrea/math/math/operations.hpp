/**
 * @file operations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Mathematical operations for quantities..
 * @date 2025-08-03
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

#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace math {

template <auto R, typename Rep>
    requires requires(Rep v) { max(v, v); } || requires(Rep v) { std::max(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> max(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::max;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(max(q1.force_numerical_value_in(q1.unit), q2.force_numerical_value_in(q1.unit)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{
            max(value_cast<rep>(q1).numerical_value_in(q1.unit), value_cast<rep>(q2).numerical_value_in(q1.unit)), q1.unit
        };
    }
    else {
        return mp_units::quantity{ max(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
    }
}

template <auto R, typename Rep>
    requires requires(Rep v) { min(v, v); } || requires(Rep v) { std::min(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> min(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::min;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(min(q1.force_numerical_value_in(q1.unit), q2.force_numerical_value_in(q1.unit)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{
            min(value_cast<rep>(q1).numerical_value_in(q1.unit), value_cast<rep>(q2).numerical_value_in(q1.unit)), q1.unit
        };
    }
    else {
        return mp_units::quantity{ min(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
    }
}

template <auto R, typename Rep>
    requires requires(Rep v) { abs(v); } || requires(Rep v) { std::abs(v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> abs(const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::abs;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(abs(q.force_numerical_value_in(q.unit)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ abs(value_cast<rep>(q).numerical_value_in(q.unit)), q.unit };
    }
    else {
        return mp_units::quantity{ abs(q.numerical_value_in(q.unit)), q.unit };
    }
}

} // namespace math
} // namespace astrea