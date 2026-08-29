/**
 * @file NRLMSISE00.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the NRLMSISE00 class.
 * @date 2026-05-01
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>


namespace astrea {
namespace astro {
namespace planets {

/**
 * @brief The NRLMSISE-00 atmospheric model for Earth.
 *
 * Implements the 2001 Naval Research Laboratory Mass Spectrometer and Incoherent Scatter
 * Radar Exosphere (NRLMSISE-00) model. Provides density from the surface to lower exosphere
 * (0 to 1000 km).
 *
 * Space weather inputs required:
 *   - f107a: 81-day average of F10.7 solar flux (centered on day)
 *   - f107:  daily F10.7 solar flux for previous day
 *   - ap[7]: geomagnetic Ap array:
 *       [0] daily Ap
 *       [1] 3-hr ap for current time
 *       [2] 3-hr ap for 3 hrs before current time
 *       [3] 3-hr ap for 6 hrs before current time
 *       [4] 3-hr ap for 9 hrs before current time
 *       [5] average of eight 3-hr ap indices from 12 to 33 hrs prior
 *       [6] average of eight 3-hr ap indices from 36 to 57 hrs prior
 *
 * Switches (indices 1–23, all default to 1):
 *   0 = off, 1 = on, 2 = main effects off but cross terms on.
 *   Switch 9: set to 1 for daily Ap only, -1 to use full ap array.
 *
 * @authors Mike Picone & al (Naval Research Laboratory), 2001: original FORTRAN
 * @authors Dominik Brodowski, 2004: C translation
 * @authors Pascal Parraud, 2016: Java translation (Orekit)
 * @authors Jay Iuliano, 2026: C++ translation (Astrea)
 */
class Nrlmsise00Atmosphere {
  public:
    /**
     * @brief Deleted constructor — use static factory or find_atmospheric_density directly.
     */
    Nrlmsise00Atmosphere() = delete;

    /**
     * @brief Find the atmospheric density at a given state using the NRLMSISE-00 model.
     *
     * Uses all 23 switches set to 1 (standard configuration).
     *
     * @param state The current spacecraft state.
     * @param f107a 81-day average F10.7 solar flux.
     * @param f107 Daily F10.7 solar flux for previous day.
     * @param ap Array of 7 geomagnetic Ap values (see class documentation).
     * @return Density Total mass density (kg/m³) including anomalous oxygen.
     */
    static Density find_atmospheric_density(const State& state, double f107a, double f107, const std::array<double, 7>& ap);
};

} // namespace planets
} // namespace astro
} // namespace astrea
