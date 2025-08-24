/**
 * @file util.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Utility functions for unit comparisons in the astrea project.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace astrea {

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
template <auto R, typename Rep>
[[nodiscard]] constexpr bool
    nearly_equal(const mp_units::quantity<R, Rep>& x, const mp_units::quantity<R, Rep>& y, const mp_units::quantity<mp_units::one>& relTol) noexcept
{
    const auto a = x.in(x.unit);
    const auto b = y.in(x.unit);
    if (a != 0.0 * R && abs((a - b) / a) > relTol) { return false; }
    else if (b != 0.0 * R && abs((a - b) / b) > relTol) {
        return false;
    }
    return true;
}

} // namespace astrea