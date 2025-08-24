/**
 * @file constants.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains definitions for constant values used in astrea.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
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