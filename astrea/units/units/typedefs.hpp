/**
 * @file typedefs.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Type definitions for astrea units
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

#include <stdint.h>

#include <mp-units/core.h>

#include <units/custom.hpp>
#include <units/detail.hpp>

namespace astrea {

/**
 * @brief Definition for a distance quantity.
 */
using Distance = mp_units::quantity<detail::distance_unit>;

/**
 * @brief Definition for an angle quantity.
 */
using Angle = mp_units::quantity<detail::angle_unit>;

/**
 * @brief Definition for a unitless quantity.
 */
using Unitless = mp_units::quantity<detail::unitless>;

/**
 * @brief Definition for a mass quantity.
 */
using Mass = mp_units::quantity<detail::mass_unit>;

/**
 * @brief Definition for a time quantity.
 */
using Time = mp_units::quantity<detail::time_unit>;

/**
 * @brief Definition for a length quantity.
 */
using Length = mp_units::quantity<detail::distance_unit>;

/**
 * @brief Definition for a velocity quantity.
 */
using Velocity = mp_units::quantity<detail::distance_unit / detail::time_unit>;

/**
 * @brief Definition for a force quantity.
 */
using Force = mp_units::quantity<detail::force_unit>;

/**
 * @brief Definition for a specific angular momentum quantity.
 */
using SpecificAngularMomentum = mp_units::quantity<detail::distance_unit * detail::distance_unit / detail::time_unit>;

/**
 * @brief Definition for a unitless per time quantity.
 */
using UnitlessPerTime = mp_units::quantity<detail::unitless / detail::time_unit>;

/**
 * @brief Definition for an angular rate quantity.
 */
using AngularVelocity = mp_units::quantity<detail::angle_unit / detail::time_unit>;

/**
 * @brief Definition for an angular acceleration quantity.
 */
using AngularAcceleration = mp_units::quantity<detail::angle_unit / (detail::time_unit * detail::time_unit)>;

/**
 * @brief Definition for a interplanetary distance quantity.
 */
using InterplanetaryDistance = mp_units::quantity<mp_units::iau::unit_symbols::au>;

/**
 * @brief Definition for a body-related velocity.
 */
using InterplanetaryVelocity = mp_units::quantity<mp_units::iau::unit_symbols::au / astrea::units::unit_symbols::jc>;

/**
 * @brief Definition for a body-related unitless per time.
 */
using BodyUnitlessPerTime = mp_units::quantity<detail::unitless / astrea::units::unit_symbols::jc>;

/**
 * @brief Definition for a body-related angular rate.
 */
using BodyAngularVelocity = mp_units::quantity<detail::angle_unit / astrea::units::unit_symbols::jc>;

/**
 * @brief Definition for an acceleration quantity.
 */
using Acceleration = mp_units::quantity<detail::distance_unit / (detail::time_unit * detail::time_unit)>;

/**
 * @brief Definition for a surface area quantity.
 */
using SurfaceArea = mp_units::quantity<detail::distance_unit * detail::distance_unit>;

/**
 * @brief Definition for a gravitational parameter quantity.
 */
using GravParam =
    mp_units::quantity<(detail::distance_unit * detail::distance_unit * detail::distance_unit) / (detail::time_unit * detail::time_unit)>;

/**
 * @brief Definition for a mean motion quantity.
 */
using MeanMotion = mp_units::quantity<mp_units::one / mp_units::non_si::day>;

/**
 * @brief Definition for a mean motion 1st derivative quantity.
 */
using MeanMotion1stDer = mp_units::quantity<mp_units::one / (mp_units::non_si::day * mp_units::non_si::day)>;

/**
 * @brief Definition for a mean motion 2nd derivative quantity.
 */
using MeanMotion2ndDer =
    mp_units::quantity<mp_units::one / (mp_units::non_si::day * mp_units::non_si::day * mp_units::non_si::day)>;

/**
 * @brief Definition for a ballistic coefficient quantity.
 */
using BallisticCoefficient = mp_units::quantity<mp_units::one / astrea::units::unit_symbols::re>;

/**
 * @brief Definition for a density quantity.
 */
using Density = mp_units::quantity<detail::mass_unit / (detail::distance_unit * detail::distance_unit * detail::distance_unit)>;

/**
 * @brief Definition for an altitude quantity.
 */
using Altitude = mp_units::quantity<detail::distance_unit>;

/**
 * @brief Definition for a gain quantity.
 */
using Gain = mp_units::quantity<detail::unitless>;

/**
 * @brief Definition for a signal-to-noise ratio quantity.
 */
using SNR = mp_units::quantity<detail::unitless>;

/**
 * @brief Definition for a carrier-to-noise ratio quantity.
 */
using CNR = mp_units::quantity<detail::unitless>;

/**
 * @brief Definition for a frequency quantity.
 */
using Frequency = mp_units::quantity<mp_units::one / detail::time_unit>;

/**
 * @brief Definition for a power quantity.
 */
using Power = mp_units::quantity<detail::power_unit>;

/**
 * @brief Definition for a power flux density quantity.
 */
using PowerFluxDensity = mp_units::quantity<detail::power_unit / (detail::distance_unit * detail::distance_unit)>;

/**
 * @brief Definition for a temperature quantity.
 */
using Temperature = mp_units::quantity_point<detail::temperature_unit>;

/**
 * @brief Definition for a pressure quantity.
 */
using Pressure = mp_units::quantity<detail::pressure_unit>;

/**
 * @brief Definition for a moment quantity.
 */
using Moment = mp_units::quantity<detail::force_unit * detail::distance_unit>;

/**
 * @brief Definition for a moment of inertia quantity.
 */
using MomentOfInertia = mp_units::quantity<detail::mass_unit * detail::distance_unit * detail::distance_unit>;

/**
 * @brief Definition for a solar flux quantity.
 */
using SolarFlux = mp_units::quantity<astrea::units::unit_symbols::sfu>;

/**
 * @brief Definition for a chirp quantity, representing the rate of change of frequency.
 */
using Chirp = mp_units::quantity<mp_units::one / (detail::time_unit * detail::time_unit)>;

} // namespace astrea