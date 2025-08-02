#pragma once

#include <array>
#include <stdint.h>

#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <units/detail.hpp>
#include <units/custom.hpp>

namespace waveguide {

using Distance = mp_units::quantity<detail::distance_unit>;
using Angle    = mp_units::quantity<detail::angle_unit>;
using Unitless = mp_units::quantity<detail::unitless>;
using Mass     = mp_units::quantity<detail::mass_unit>;
using Time     = mp_units::quantity<detail::time_unit>;
using Length   = mp_units::quantity<detail::minor_distance_unit>;

using Velocity        = mp_units::quantity<detail::distance_unit / detail::time_unit>;
using UnitlessPerTime = mp_units::quantity<detail::unitless / detail::time_unit>;
using AngularRate     = mp_units::quantity<detail::angle_unit / detail::time_unit>;

using BodyVelocity        = mp_units::quantity<detail::distance_unit / JulianCentury>;
using BodyUnitlessPerTime = mp_units::quantity<detail::unitless / JulianCentury>;
using BodyAngularRate     = mp_units::quantity<detail::angle_unit / JulianCentury>;

using Acceleration = mp_units::quantity<detail::distance_unit / mp_units::pow<2>(detail::time_unit)>;

using SurfaceArea = mp_units::quantity<mp_units::pow<2>(detail::minor_distance_unit)>;
using GravParam   = mp_units::quantity<mp_units::pow<3>(detail::distance_unit) / mp_units::pow<2>(detail::time_unit)>;

using Density  = mp_units::quantity<detail::mass_unit / (mp_units::pow<3>(detail::minor_distance_unit))>;
using Altitude = mp_units::quantity<detail::distance_unit>;

using Gain             = mp_units::quantity<detail::unitless>;
using SNR              = mp_units::quantity<detail::unitless>;
using CNR              = mp_units::quantity<detail::unitless>;
using Frequency        = mp_units::quantity<detail::frequency_unit>;
using Power            = mp_units::quantity<detail::power_unit>;
using PowerFluxDensity = mp_units::quantity<detail::power_unit / mp_units::pow<2>(detail::minor_distance_unit)>;
using Temperature      = mp_units::quantity<detail::temperature_unit>;

// Containers
using RadiusVector       = std::array<Distance, 3>;
using VelocityVector     = std::array<Velocity, 3>;
using AccelerationVector = std::array<Acceleration, 3>;

} // namespace waveguide