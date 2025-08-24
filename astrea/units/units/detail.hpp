/**
 * @file detail.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains detail namespace with unit definitions for astrea project.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <array>

// mp-units
#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace detail {

inline constexpr auto time_unit           = mp_units::si::unit_symbols::s;
inline constexpr auto distance_unit       = mp_units::si::unit_symbols::km;
inline constexpr auto minor_distance_unit = mp_units::si::unit_symbols::m;
inline constexpr auto angle_unit          = mp_units::angular::unit_symbols::rad;
inline constexpr auto mass_unit           = mp_units::si::unit_symbols::kg;
inline constexpr auto unitless            = mp_units::one;
inline constexpr auto power_unit          = mp_units::si::unit_symbols::W;
inline constexpr auto frequency_unit      = mp_units::si::unit_symbols::Hz;
inline constexpr auto temperature_unit    = mp_units::si::unit_symbols::K;

} // namespace detail
} // namespace astrea