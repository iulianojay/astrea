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


/**
 * @brief Check if two quantities of the same unit are nearly equal within a relative tolerance.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param x First quantity to compare.
 * @param y Second quantity to compare.
 * @param relTol Relative tolerance for comparison.
 * @return true if the two quantities are nearly equal within the specified tolerance.
 * @return false if they are not nearly equal.
 */
template <auto R1, auto R2, typename Rep>
[[nodiscard]] constexpr bool nearly_equal(
    const mp_units::quantity<R1, Rep>& x,
    const mp_units::quantity<R2, Rep>& y,
    const mp_units::quantity<mp_units::one, Rep>& relTol = 0.0 * mp_units::one,
    const mp_units::quantity<mp_units::one, Rep>& absTol = 0.0 * mp_units::one
) noexcept
{
    // Bring both to the same unit for comparison
    const auto a = x.in(x.unit);
    const auto b = y.in(x.unit);

    // Check rel tol
    if (relTol != 0.0 * mp_units::one) {
        if (a != 0.0 * R1 && b != 0.0 * R1) {
            if (abs((a - b) / a) > relTol) { return false; }
        }
    }

    // Check abs tol
    if (absTol != 0.0 * mp_units::one) {
        if (abs(a - b) > absTol * R1) { return false; }
    }

    return true;
}

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

template <auto R, typename Rep>
    requires requires(Rep v) { clamp(v, v, v); } || requires(Rep v) { std::clamp(v, v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep>
    clamp(const mp_units::quantity<R, Rep>& q, const mp_units::quantity<R, Rep>& low, const mp_units::quantity<R, Rep>& high) noexcept
{
    using std::clamp;
    return mp_units::quantity{ clamp(q.numerical_value_in(q.unit), low.numerical_value_in(q.unit), high.numerical_value_in(q.unit)),
                               q.unit };
}


} // namespace math
} // namespace astrea