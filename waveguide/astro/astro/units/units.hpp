#pragma once

#include <array>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace astro {

namespace detail {

inline constexpr auto time_unit           = mp_units::si::unit_symbols::s;
inline constexpr auto distance_unit       = mp_units::si::unit_symbols::km;
inline constexpr auto minor_distance_unit = mp_units::si::unit_symbols::m;
inline constexpr auto angle_unit          = mp_units::angular::unit_symbols::rad;
inline constexpr auto mass_unit           = mp_units::si::unit_symbols::kg;
inline constexpr auto unitless            = mp_units::one;

} // namespace detail

inline constexpr struct JulianCentury final : mp_units::named_unit<"JulianCentury", mp_units::mag<36525> * mp_units::non_si::day> {
} JulianCentury;

} // namespace astro