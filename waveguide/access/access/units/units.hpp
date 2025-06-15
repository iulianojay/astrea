#pragma once

// mp-units
#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace accesslib {

namespace detail {

inline constexpr auto power_unit     = mp_units::si::unit_symbols::W;
inline constexpr auto frequency_unit = mp_units::si::unit_symbols::Hz;

} // namespace detail

} // namespace accesslib
