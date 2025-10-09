/**
 * @file jpl_ephemeris/celestial_bodies/JplEphemerisTable.hpp
 * @brief Base class for any JPL Celestial-Body (CB) table
 *
 * @note Resource: https://www.celestialprogramming.com/jpl-ephemeris-format/jpl-ephemeris-format.html
 * @note Adapted from https://github.com/mschmit6/jpl_ephemeris.git
 * @author Matt Schmit
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
 */

#pragma once

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for any JPL CelestialBody table.
 */
struct JplEphemerisTable {

  protected:
    JplEphemerisTable()  = delete; // Prevent construction
    ~JplEphemerisTable() = delete;

    /**
     * @brief Get the index corresponding to the Chebyshev polynomial coefficients
     *
     * @param date Date for which the index is to be computed
     * @param timePerPoly Amount of time each set of polynomial coefficients covers
     *
     * @return Table lookup index
     */
    static std::size_t get_index(const Date& date, const Time& timePerPoly);

    //! Lower bound on MJD J2K in the TDB time system
    static const Date START_DATE;

    //! Upper bound on MJD J2K in the TDB time system
    static const Date STOP_DATE;
};

} // namespace astro
} // namespace astrea
