/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <tests/utilities/comparisons.hpp>

#include <gtest/gtest.h>

#include <math/operations.hpp>

#include <astro/state/orbital_elements/OrbitalElements.hpp>

namespace astrea {

namespace astro {

bool nearly_equal(
    const OrbitalElements& first,
    const OrbitalElements& second,
    const bool& ignoreFastVariable,
    const Unitless& relTol,
    const std::vector<Unitless>& absTol
) noexcept
{
    using mp_units::one;

    if (first.index() != second.index()) { return false; }

    auto firstUnitless  = first.force_to_double_vector();
    auto secondUnitless = second.force_to_double_vector();
    const int maxIdx    = ignoreFastVariable ? 5 : 6;
    for (int ii = 0; ii < maxIdx; ii++) {
        if (!math::nearly_equal(firstUnitless[ii] * one, secondUnitless[ii] * one, relTol, absTol.size() == 1 ? absTol[0] : absTol[ii])) {
            std::cout << "First: " << first << std::endl;
            std::cout << "Second: " << second << std::endl;
            std::cout << "Element " << ii << " differs: " << firstUnitless[ii] << " vs " << secondUnitless[ii] << std::endl;
            return false;
        }
    }
    return true;
}

bool nearly_equal(const OrbitalElementPartials& first, const OrbitalElementPartials& second, const Unitless& relTol, const std::vector<Unitless>& absTol) noexcept
{
    using mp_units::one;

    if (first.index() != second.index()) { return false; }

    const auto firstScaled  = first.force_to_double_vector();
    const auto secondScaled = second.force_to_double_vector();
    for (int ii = 0; ii < 6; ii++) {
        if (!math::nearly_equal(firstScaled[ii] * one, secondScaled[ii] * one, relTol, absTol.size() == 1 ? absTol[0] : absTol[ii])) {
            std::cout << "First: " << first << std::endl;
            std::cout << "Second: " << second << std::endl;
            std::cout << "Element " << ii << " differs: " << firstScaled[ii] << " vs " << secondScaled[ii] << std::endl;
            return false;
        }
    }
    return true;
}

} // namespace astro
} // namespace astrea