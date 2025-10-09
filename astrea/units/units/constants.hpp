/**
 * @file constants.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains definitions for constant values used in astrea.
 * @version 0.1
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
#include <mp-units/systems/si.h>

#include <units/detail.hpp>
#include <units/typedefs.hpp>

namespace astrea {

constexpr Velocity speed_of_light_in_vacuum = 1.0 * mp_units::si::si2019::speed_of_light_in_vacuum;
constexpr auto boltzmann_constant           = 1.0 * mp_units::si::si2019::boltzmann_constant;

constexpr Angle PI     = 1.0 * (mp_units::mag<mp_units::pi> * detail::angle_unit);
constexpr Angle TWO_PI = 2.0 * (mp_units::mag<mp_units::pi> * detail::angle_unit);

constexpr mp_units::quantity<mp_units::mag<mp_units::pi> * detail::angle_unit> n_pi(const double& mag)
{
    return mag * (mp_units::mag<mp_units::pi> * detail::angle_unit);
}

constexpr mp_units::quantity<detail::unitless> n_pi_mag(const double& mag)
{
    return mag * (mp_units::mag<mp_units::pi> * detail::unitless);
}

} // namespace astrea