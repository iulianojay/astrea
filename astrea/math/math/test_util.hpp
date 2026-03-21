/**
 * @file util.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Utility functions for unit comparisons in the astrea project.
 * @date 2025-08-02
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

#include <gtest/gtest.h>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <math/operations.hpp>

namespace astrea {

/**
 * @brief Assert that two quantities of the same unit are nearly equal within a relative tolerance.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param x First quantity to compare.
 * @param y Second quantity to compare.
 * @param REL_TOL Relative tolerance for comparison.
 * @param ABS_TOL Absolute tolerance for comparison.
 */
template <auto R1, auto R2, typename Rep>
void ASSERT_EQ_QUANTITY(
    const mp_units::quantity<R1, Rep>& x,
    const mp_units::quantity<R2, Rep>& y,
    const mp_units::quantity<mp_units::one, Rep>& relTol = 0.0 * mp_units::one,
    const mp_units::quantity<mp_units::one, Rep>& absTol = 0.0 * mp_units::one
) noexcept
{
    ASSERT_TRUE(math::nearly_equal(x, y, relTol, absTol))
        << "Comparison had relative differences greater than " << relTol * 100 << "%\n"
        << "or absolute differences greater than " << absTol << "\n"
        << "First Quantity: " << x << "\n"
        << "Second Quantity: " << y << "\n\n";
}

/**
 * @brief Expect that two quantities of the same unit are nearly equal within a relative tolerance.
 *
 * @tparam R The unit type (e.g., distance, time).
 * @tparam Rep The representation type (e.g., double).
 * @param x First quantity to compare.
 * @param y Second quantity to compare.
 * @param REL_TOL Relative tolerance for comparison.
 * @param ABS_TOL Absolute tolerance for comparison.
 */
template <auto R1, auto R2, typename Rep>
void EXPECT_EQ_QUANTITY(
    const mp_units::quantity<R1, Rep>& x,
    const mp_units::quantity<R2, Rep>& y,
    const mp_units::quantity<mp_units::one, Rep>& relTol = 0.0 * mp_units::one,
    const mp_units::quantity<mp_units::one, Rep>& absTol = 0.0 * mp_units::one
) noexcept
{
    EXPECT_TRUE(math::nearly_equal(x, y, relTol, absTol))
        << "Comparison had relative differences greater than " << relTol * 100 << "%\n"
        << "or absolute differences greater than " << absTol << "\n"
        << "First Quantity: " << x << "\n"
        << "Second Quantity: " << y << "\n\n";
}

} // namespace astrea