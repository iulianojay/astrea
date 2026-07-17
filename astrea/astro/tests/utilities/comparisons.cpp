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

#include <tests/utilities/comparisons.hpp>

#include <gtest/gtest.h>

#include <math/operations.hpp>

#include <astro/state/framework/element_matrix_concepts.hpp>

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
    if (first.index() != second.index()) { return false; }

    auto firstUnitless  = first.force_to_vector();
    auto secondUnitless = second.force_to_vector();
    const int maxIdx    = ignoreFastVariable ? 5 : 6;
    for (int ii = 0; ii < maxIdx; ii++) {
        if (!math::nearly_equal(firstUnitless[ii], secondUnitless[ii], relTol, absTol.size() == 1 ? absTol[0] : absTol[ii])) {
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
    if (first.index() != second.index()) { return false; }

    // arbitrary normalization. shouldn't affect relative size
    const Time scale                         = 1.0 * mp_units::si::unit_symbols::s;
    const std::vector<Unitless> firstScaled  = (first * scale).force_to_vector();
    const std::vector<Unitless> secondScaled = (second * scale).force_to_vector();
    for (int ii = 0; ii < 6; ii++) {
        if (!math::nearly_equal(firstScaled[ii], secondScaled[ii], relTol, absTol.size() == 1 ? absTol[0] : absTol[ii])) {
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