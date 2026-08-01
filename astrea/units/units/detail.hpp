/**
 * @file detail.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains detail namespace with unit definitions for astrea project.
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

#include <array>

// mp-units
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace detail {

inline constexpr auto time_unit        = mp_units::si::unit_symbols::s;
inline constexpr auto distance_unit    = mp_units::si::unit_symbols::km;
inline constexpr auto angle_unit       = mp_units::si::unit_symbols::rad;
inline constexpr auto mass_unit        = mp_units::si::unit_symbols::kg;
inline constexpr auto unitless         = mp_units::one;
inline constexpr auto power_unit       = mp_units::si::unit_symbols::W;
inline constexpr auto frequency_unit   = mp_units::si::unit_symbols::Hz;
inline constexpr auto temperature_unit = mp_units::si::unit_symbols::K;
inline constexpr auto force_unit       = (mass_unit * distance_unit) / (time_unit * time_unit);
inline constexpr auto pressure_unit    = force_unit / (distance_unit * distance_unit);

} // namespace detail
} // namespace astrea