/**
 * @file custom.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Custom units for astrea project
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

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace astrea {

/**
 * @brief Definition for a Julian Century as 36525 days.
 */
inline constexpr struct JulianCentury final : mp_units::named_unit<"JulianCentury", mp_units::mag<36525> * mp_units::non_si::day> {
} JulianCentury;

/**
 * @brief Definition for Earth Radii as 6378 km.
 */
inline constexpr struct EarthRadii final
    : mp_units::named_unit<"EarthRadii", mp_units::mag<6378> * mp_units::si::unit_symbols::km> {
} EarthRadii;

} // namespace astrea