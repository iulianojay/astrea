/**
 * @file Nrlmsise00.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Nrlmsise00 class.
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

#include <mp-units/systems/si.h>
#include <nrlmsise00/Nrlmsise00.hpp>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Calculate the local solar time for a given state.
 * @param state The current state of the satellite.
 * @return The local solar time.
 */
Time calculate_local_solar_time(const State& state);

class Nrlmsise00Atmosphere {
  public:
    /**
     * @brief Deleted constructor — use static factory or find_atmospheric_density directly.
     */
    Nrlmsise00Atmosphere() = delete;

    /**
     * @brief Find the atmospheric density at a given state and solar/geomagnetic conditions.
     * @param state The current state of the satellite.
     * @param f107a The 81-day average of the F10.7 solar flux.
     * @param f107 The daily F10.7 solar flux.
     * @param ap The array of geomagnetic indices.
     * @param flags The array of flags to set the model switches.
     * @param ignoreLowAltitudes If true, the model will ignore low altitudes and return a density of 0.0 for altitudes below 80 km.
     * @return The atmospheric density.

     * \parblock
     * @note The magnetic index array contains:
     * Array containing the following magnetic values:
     * - 0: daily AP
     * - 1: 3 hr AP index for current time
     * - 2: 3 hr AP index for 3 hrs before current time
     * - 3: 3 hr AP index for 6 hrs before current time
     * - 4: 3 hr AP index for 9 hrs before current time
     * - 5: Average of eight 3 hr AP indicies from 12 to 33 hrs prior to current time
     * - 6: Average of eight 3 hr AP indicies from 36 to 57 hrs prior to current time
     * \endparblock
     * \parblock
     * @note f107 and f107A values used to generate the model correspond
     *       to the 10.7 cm radio flux at the actual distance of the Earth
     *       from the Sun rather than the radio flux at 1 AU.
     * \endparblock
     * \parblock
     * @note f107, f107A, and ap effects are neither large nor well
     *       established below 80 km and these parameters should be set to
     *       150., 150., and 4. respectively.
     */
    static Density find_atmospheric_density(
        const State& state,
        const SolarFlux& f107a,
        const SolarFlux& f107,
        const std::array<Unitless, 8>& ap,
        const std::array<int, 24>& flags = get_default_flags(),
        const bool ignoreLowAltitudes    = true
    );

  private:
    /**
     * @brief Get the default flags for the Nrlmsise00 model.
     * @return The default flags for the Nrlmsise00 model.
     */
    static std::array<int, 24> get_default_flags();
};

} // namespace astro
} // namespace astrea
