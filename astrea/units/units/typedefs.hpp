/**
 * @file typedefs.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Type definitions for astrea units
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <array>
#include <stdint.h>

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

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
using Length = mp_units::quantity<detail::minor_distance_unit>;

/**
 * @brief Definition for a velocity quantity.
 */
using Velocity = mp_units::quantity<detail::distance_unit / detail::time_unit>;

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
using AngularRate = mp_units::quantity<detail::angle_unit / detail::time_unit>;

/**
 * @brief Definition for a body-related velocity.
 */
using BodyVelocity = mp_units::quantity<detail::distance_unit / JulianCentury>;

/**
 * @brief Definition for a body-related unitless per time.
 */
using BodyUnitlessPerTime = mp_units::quantity<detail::unitless / JulianCentury>;

/**
 * @brief Definition for a body-related angular rate.
 */
using BodyAngularRate = mp_units::quantity<detail::angle_unit / JulianCentury>;

/**
 * @brief Definition for an acceleration quantity.
 */
using Acceleration = mp_units::quantity<detail::distance_unit / mp_units::pow<2>(detail::time_unit)>;

/**
 * @brief Definition for a surface area quantity.
 */
using SurfaceArea = mp_units::quantity<mp_units::pow<2>(detail::minor_distance_unit)>;

/**
 * @brief Definition for a gravitational parameter quantity.
 */
using GravParam = mp_units::quantity<mp_units::pow<3>(detail::distance_unit) / mp_units::pow<2>(detail::time_unit)>;

/**
 * @brief Definition for a mean motion quantity.
 */
using MeanMotion           = mp_units::quantity<mp_units::one / mp_units::non_si::day>;

/**
 * @brief Definition for a mean motion 1st derivative quantity.
 */
using MeanMotion1stDer     = mp_units::quantity<mp_units::one / mp_units::pow<2>(mp_units::non_si::day)>;

/**
 * @brief Definition for a mean motion 2nd derivative quantity.
 */
using MeanMotion2ndDer     = mp_units::quantity<mp_units::one / mp_units::pow<3>(mp_units::non_si::day)>;

/**
 * @brief Definition for a ballistic coefficient quantity.
 */
using BallisticCoefficient = mp_units::quantity<mp_units::one / EarthRadii>;

/**
 * @brief Definition for a density quantity.
 */
using Density = mp_units::quantity<detail::mass_unit / (mp_units::pow<3>(detail::minor_distance_unit))>;

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
using Frequency = mp_units::quantity<detail::frequency_unit>;

/**
 * @brief Definition for a power quantity.
 */
using Power = mp_units::quantity<detail::power_unit>;

/**
 * @brief Definition for a power flux density quantity.
 */
using PowerFluxDensity = mp_units::quantity<detail::power_unit / mp_units::pow<2>(detail::minor_distance_unit)>;

/**
 * @brief Definition for a temperature quantity.
 */
using Temperature = mp_units::quantity<detail::temperature_unit>;

} // namespace astrea