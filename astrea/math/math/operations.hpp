/**
 * @file operations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Mathematical operations for quantities..
 * @date 2025-08-03
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

#include <algorithm>
#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace math {


/**
 * @brief Check if two quantities of the same unit are nearly equal within a relative and absolute tolerance.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param x First quantity to compare.
 * @param y Second quantity to compare.
 * @param relTol Relative tolerance for comparison. Default is 0, which means relative differences are not considered.
 * @param absTol Absolute tolerance for comparison. Default is 0, which means absolute differences are not considered.
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

/**
 * @brief Returns the maximum of two quantities of the same unit.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param q1 First quantity to compare.
 * @param q2 Second quantity to compare.
 * @return The maximum of the two quantities.
 */
template <auto R, typename Rep>
    requires requires(Rep v) { max(v, v); } || requires(Rep v) { std::max(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> max(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::max;
    return mp_units::quantity{ max(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
}

/**
 * @brief Returns the minimum of two quantities of the same unit.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param q1 First quantity to compare.
 * @param q2 Second quantity to compare.
 * @return The minimum of the two quantities.
 */
template <auto R, typename Rep>
    requires requires(Rep v) { min(v, v); } || requires(Rep v) { std::min(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> min(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::min;
    return mp_units::quantity{ min(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
}

/**
 * @brief Returns the result of raising a dimensionless quantity to the power of another dimensionless quantity.
 *
 * @tparam R The unit type (must be dimensionless).
 * @tparam Rep The representation type (e.g., double).
 * @param q The quantity to be raised to a power.
 * @param n The exponent quantity.
 * @return The result of raising q to the power of n, with the same unit as q (which is dimensionless).
 */
template <mp_units::ReferenceOf<mp_units::dimensionless> auto R1, mp_units::ReferenceOf<mp_units::dimensionless> auto R2, typename Rep1, typename Rep2>
    requires requires(Rep1 v1, Rep2 v2) { pow(v1, v2); } || requires(Rep1 v1, Rep2 v2) { std::pow(v1, v2); }
[[nodiscard]] inline mp_units::quantity<mp_units::one, Rep1>
    pow(const mp_units::quantity<R1, Rep1>& q, const mp_units::quantity<R2, Rep2>& n) noexcept
{
    using std::pow;
    return mp_units::quantity{ pow(q.numerical_value_in(mp_units::one), n.numerical_value_in(mp_units::one)), mp_units::one };
}

/**
 * @brief Clamps a quantity within a specified range.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param q The quantity to be clamped.
 * @param low The lower bound for the quantity.
 * @param high The upper bound for the quantity.
 * @return The clamped quantity, ensuring it lies within the specified range.
 */
template <auto R, typename Rep>
    requires requires(Rep v) { clamp(v, v, v); } || requires(Rep v) { std::clamp(v, v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep>
    clamp(const mp_units::quantity<R, Rep>& q, const mp_units::quantity<R, Rep>& low, const mp_units::quantity<R, Rep>& high) noexcept
{
    using std::clamp;
    return mp_units::quantity{ clamp(q.numerical_value_in(q.unit), low.numerical_value_in(q.unit), high.numerical_value_in(q.unit)),
                               q.unit };
}

/**
 * @brief Bounds a quantity within a specified range, accounting for floating-point errors.
 *
 * This function checks if the given quantity `q` is within the specified `high` and `low` bounds.
 * If `q` is outside the bounds but within a small tolerance (2.0e-8) of the bounds, it will be clamped to the nearest
 * bound. If it is beyond the tolerance, it will be returned as is.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param q The quantity to be bounded.
 * @param high The upper bound for the quantity.
 * @param low The lower bound for the quantity.
 * @return The bounded quantity, adjusted for floating-point errors if necessary.
 */
template <auto R, typename Rep>
    requires requires(Rep v) { abs(v); } || requires(Rep v) { std::abs(v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> clamp_within_floating_point_error(
    const mp_units::quantity<R, Rep>& q,
    const mp_units::quantity<R, Rep>& low,
    const mp_units::quantity<R, Rep>& high
) noexcept
{
    static const mp_units::quantity<R, Rep> tolerance = 2.0e-8 * q.unit; // Tolerance for floating-point comparison

    if (q > high + tolerance) { return high; }
    else if (q < low - tolerance) {
        return low;
    }
    return q;
}


} // namespace math
} // namespace astrea