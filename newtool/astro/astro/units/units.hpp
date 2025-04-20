#pragma once

#include <array>

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace detail {

inline constexpr auto time_unit           = mp_units::si::unit_symbols::s;
inline constexpr auto distance_unit       = mp_units::si::unit_symbols::km;
inline constexpr auto minor_distance_unit = mp_units::si::unit_symbols::m;
inline constexpr auto angle_unit          = mp_units::angular::unit_symbols::rad;
inline constexpr auto mass_unit           = mp_units::si::unit_symbols::kg;
inline constexpr auto unitless            = mp_units::one;

} // namespace detail

using Distance = mp_units::quantity<detail::distance_unit>;
using Angle    = mp_units::quantity<detail::angle_unit>;
using Unitless = mp_units::quantity<detail::unitless>;
using Mass     = mp_units::quantity<detail::mass_unit>;
using Time     = mp_units::quantity<detail::time_unit>;

using Velocity        = mp_units::quantity<detail::distance_unit / detail::time_unit>;
using UnitlessPerTime = mp_units::quantity<detail::unitless / detail::time_unit>;
using AngularRate     = mp_units::quantity<detail::angle_unit / detail::time_unit>;

using Acceleration = mp_units::quantity<detail::distance_unit / mp_units::pow<2>(detail::time_unit)>;

using SurfaceArea = mp_units::quantity<mp_units::pow<2>(detail::minor_distance_unit)>;
using GravParam   = mp_units::quantity<mp_units::pow<3>(detail::distance_unit) / mp_units::pow<2>(detail::time_unit)>;

using Density  = mp_units::quantity<detail::mass_unit / (mp_units::pow<3>(detail::minor_distance_unit))>;
using Altitude = mp_units::quantity<detail::distance_unit>;

using RadiusVector       = std::array<Distance, 3>;
using VelocityVector     = std::array<Velocity, 3>;
using AccelerationVector = std::array<Acceleration, 3>;