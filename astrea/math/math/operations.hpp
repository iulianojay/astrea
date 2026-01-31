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
    return mp_units::quantity{ max(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
}

template <auto R, typename Rep>
    requires requires(Rep v) { min(v, v); } || requires(Rep v) { std::min(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> min(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::min;
    return mp_units::quantity{ min(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { pow(v, v); } || requires(Rep v) { std::pow(v, v); }
[[nodiscard]] inline mp_units::quantity<mp_units::one, Rep>
    pow(const mp_units::quantity<R, Rep>& q, const mp_units::quantity<R, Rep>& n) noexcept
{
    using std::pow;
    return mp_units::quantity{ pow(q.numerical_value_in(mp_units::one), n.numerical_value_in(mp_units::one)), mp_units::one };
}

} // namespace math
} // namespace astrea