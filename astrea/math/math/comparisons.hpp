/**
 * @file comparisons.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Mathematical comparisons for quantities..
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free sotware: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Sotware Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <cmath>

#include <mp-units/core.h>
#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <math/operations.hpp>

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
 * @brief Return the unit in the last place (ULP) of a floating-point value, which is the distance to the next representable value.
 *
 * @tparam T The floating-point type (e.g., float, double).
 * @param x The floating-point value for which to calculate the ULP.
 * @return The ULP of the value.
 */
template <typename T>
    requires(std::is_floating_point_v<T>)
[[nodiscard]] inline constexpr T ulp(T x) noexcept
{
    if (x > 0) { return std::nexttoward(x, std::numeric_limits<T>::infinity()) - x; }
    else {
        return x - std::nexttoward(x, -std::numeric_limits<T>::infinity());
    }
}

/**
 * @brief Calculate the difference between two floating-point values in terms of ULPs.
 *
 * @tparam T The floating-point type (e.g., float, double).
 * @param x First floating-point value.
 * @param y Second floating-point value.
 * @return The difference between x and y in terms of ULPs.
 */
template <typename T>
    requires(std::is_floating_point_v<T>)
[[nodiscard]] inline constexpr int calculate_ulp_difference(T x, T y) noexcept
{
    const T minUlp          = std::min(ulp(x), ulp(y));
    const unsigned nUlpDiff = std::ceil(std::abs(x - y) / minUlp);
    if (nUlpDiff == 0) { return 0; }     // Handle the case where x and y are exactly equal
    return (int)log10((double)nUlpDiff); // Convert to number of ULPs
}


/**
 * @brief Returns the unit in the last place (ULP) of a quantity, which is the distance to the next representable value.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param q The quantity for which to calculate the ULP.
 * @return The ULP of the quantity, with the same unit as q.
 */
template <auto R, typename Rep>
    requires(std::is_floating_point_v<Rep>)
[[nodiscard]] inline constexpr mp_units::quantity<R, Rep> ulp(const mp_units::quantity<R, Rep>& q) noexcept
{
    return mp_units::quantity{ ulp(q.numerical_value_in(q.unit)), q.unit };
}

/**
 * @brief Calculate the difference between two quantities in terms of ULPs.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param x First quantity.
 * @param y Second quantity.
 * @return The difference between x and y in terms of ULPs, with the same unit as x and y.
 */
template <auto R1, auto R2, typename Rep>
    requires(std::is_floating_point_v<Rep>)
[[nodiscard]] inline constexpr int
    calculate_ulp_difference(const mp_units::quantity<R1, Rep>& x, const mp_units::quantity<R2, Rep>& y) noexcept
{
    return calculate_ulp_difference(x.numerical_value_in(x.unit), y.numerical_value_in(x.unit));
}

/**
 * @brief Check if two quantities of the same unit are nearly equal within a specified number of ULPs.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param x First quantity to compare.
 * @param y Second quantity to compare.
 * @param maxUlps Maximum number of ULPs for the quantities to be considered nearly equal.
 * @return true if the two quantities are nearly equal within the specified number of ULPs.
 * @return false if they are not nearly equal.
 */
template <auto R1, auto R2, typename Rep>
    requires(std::is_floating_point_v<Rep>)
[[nodiscard]] constexpr bool
    nearly_equal_by_ulp(const mp_units::quantity<R1, Rep>& x, const mp_units::quantity<R2, Rep>& y, const double maxUlps = 1.0) noexcept
{
    // Bring both to the same unit for comparison
    // TODO: Do we want this to be the smaller unit?
    const auto a = x.in(x.unit);
    const auto b = y.in(x.unit);

    const auto maxDiff = max(ulp(a), ulp(b)) * maxUlps;

    return abs(a - b) <= maxDiff;
}

} // namespace math
} // namespace astrea