/**
 * @file custom.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Custom units for astrea project
 * @date 2025-08-02
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

#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace units {

/**
 * @brief Definition for a Julian Century as 36525 days.
 */
inline constexpr struct julian_century final
    : mp_units::named_unit<"Julian Century", mp_units::mag<36525> * mp_units::non_si::day> {
} julian_century;

/**
 * @brief Definition for Earth Radii as 6378 km.
 */
inline constexpr struct earth_radii final
    : mp_units::named_unit<"Earth Radii", mp_units::mag<6378> * mp_units::si::unit_symbols::km> {
} earth_radii;

/**
 * @brief Definition for Solar Flux Units as 1e-22 W / (m^2 * Hz).
 */
inline constexpr struct solar_flux_units final
    : mp_units::named_unit<"Solar Flux Units", mp_units::mag_power<10, -22> * mp_units::si::unit_symbols::W / (pow<2>(mp_units::si::unit_symbols::m) * mp_units::si::unit_symbols::Hz)> {
} solar_flux_units;

/**
 * @brief Definition for a revolution as 360 degrees.
 */
inline constexpr struct revolution final : mp_units::named_unit<"rev", mp_units::mag<360> * mp_units::si::unit_symbols::deg> {
} revolution;


namespace unit_symbols {

inline constexpr auto jc  = julian_century;
inline constexpr auto re  = earth_radii;
inline constexpr auto sfu = solar_flux_units;
inline constexpr auto rev = revolution;

} // namespace unit_symbols

} // namespace units
} // namespace astrea