

# File typedefs.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**typedefs.hpp**](typedefs_8hpp.md)

[Go to the documentation of this file](typedefs_8hpp.md)


```C++

#pragma once

#include <array>
#include <stdint.h>

#include <mp-units/ext/format.h>

#include <units/custom.hpp>
#include <units/detail.hpp>

namespace astrea {

using Distance = mp_units::quantity<detail::distance_unit>;

using Angle = mp_units::quantity<detail::angle_unit>;

using Unitless = mp_units::quantity<detail::unitless>;

using Mass = mp_units::quantity<detail::mass_unit>;

using Time = mp_units::quantity<detail::time_unit>;

using Length = mp_units::quantity<detail::minor_distance_unit>;

using Velocity = mp_units::quantity<detail::distance_unit / detail::time_unit>;

using Thrust = mp_units::quantity<detail::mass_unit * detail::distance_unit / mp_units::pow<2>(detail::time_unit)>;

using SpecificAngularMomentum = mp_units::quantity<detail::distance_unit * detail::distance_unit / detail::time_unit>;

using UnitlessPerTime = mp_units::quantity<detail::unitless / detail::time_unit>;

using AngularRate = mp_units::quantity<detail::angle_unit / detail::time_unit>;

using InterplanetaryDistance = mp_units::quantity<mp_units::iau::unit_symbols::au>;

using InterplanetaryVelocity = mp_units::quantity<mp_units::iau::unit_symbols::au / JulianCentury>;

using BodyUnitlessPerTime = mp_units::quantity<detail::unitless / JulianCentury>;

using BodyAngularRate = mp_units::quantity<detail::angle_unit / JulianCentury>;

using Acceleration = mp_units::quantity<detail::distance_unit / mp_units::pow<2>(detail::time_unit)>;

using SurfaceArea = mp_units::quantity<mp_units::pow<2>(detail::minor_distance_unit)>;

using GravParam = mp_units::quantity<mp_units::pow<3>(detail::distance_unit) / mp_units::pow<2>(detail::time_unit)>;

using MeanMotion = mp_units::quantity<mp_units::one / mp_units::non_si::day>;

using MeanMotion1stDer = mp_units::quantity<mp_units::one / mp_units::pow<2>(mp_units::non_si::day)>;

using MeanMotion2ndDer = mp_units::quantity<mp_units::one / mp_units::pow<3>(mp_units::non_si::day)>;

using BallisticCoefficient = mp_units::quantity<mp_units::one / EarthRadii>;

using Density = mp_units::quantity<detail::mass_unit / (mp_units::pow<3>(detail::minor_distance_unit))>;

using Altitude = mp_units::quantity<detail::distance_unit>;

using Gain = mp_units::quantity<detail::unitless>;

using SNR = mp_units::quantity<detail::unitless>;

using CNR = mp_units::quantity<detail::unitless>;

using Frequency = mp_units::quantity<detail::frequency_unit>;

using Power = mp_units::quantity<detail::power_unit>;

using PowerFluxDensity = mp_units::quantity<detail::power_unit / mp_units::pow<2>(detail::minor_distance_unit)>;

using Temperature = mp_units::quantity_point<detail::temperature_unit>;

using Pressure = mp_units::quantity<detail::pressure_unit>;

using Moment = mp_units::quantity<detail::force_unit * detail::minor_distance_unit>;

} // namespace astrea
```


