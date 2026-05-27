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

#include <astro/systems/celestial_bodies/JplEphemerisTable.hpp>

// Standard Library Includes
#include <stdexcept>

namespace astrea {
namespace astro {

const Date JplEphemerisTable::START_DATE = Date("1999-12-24 00:00:00");
const Date JplEphemerisTable::STOP_DATE  = Date("2100-01-12 00:00:00");

std::size_t JplEphemerisTable::get_index(const Date& date, const Time& timePerPoly)
{
    if (date < START_DATE || date > STOP_DATE) {
        throw std::out_of_range(
            "JplEphemerisTable::get_index() - Value provided for date is outside of the valid range "
            "for the Chebyshev polynomial coefficients. Valid range: 1/1/2000 12:00:00 to 1/1/2100 "
            "12:00:00."
        );
    }
    return static_cast<std::size_t>(((date - START_DATE) / timePerPoly).numerical_value_in(mp_units::one));
}

} // namespace astro
} // namespace astrea
