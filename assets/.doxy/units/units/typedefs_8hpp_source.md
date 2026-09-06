

# File typedefs.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**typedefs.hpp**](typedefs_8hpp.md)

[Go to the documentation of this file](typedefs_8hpp.md)


```C++

#pragma once

#include <stdint.h>

#include <mp-units/core.h>

#include <units/custom.hpp>
#include <units/detail.hpp>

namespace astrea {

using Distance = mp_units::quantity<detail::distance_unit>;

using Angle = mp_units::quantity<detail::angle_unit>;

using Unitless = mp_units::quantity<detail::unitless>;

using Mass = mp_units::quantity<detail::mass_unit>;

using Time = mp_units::quantity<detail::time_unit>;

using Length = mp_units::quantity<detail::distance_unit>;

using Velocity = mp_units::quantity<detail::distance_unit / detail::time_unit>;

using Force = mp_units::quantity<detail::force_unit>;

using SpecificAngularMomentum = mp_units::quantity<detail::distance_unit * detail::distance_unit / detail::time_unit>;

using UnitlessPerTime = mp_units::quantity<detail::unitless / detail::time_unit>;

using AngularVelocity = mp_units::quantity<detail::angle_unit / detail::time_unit>;

using AngularAcceleration = mp_units::quantity<detail::angle_unit / (detail::time_unit * detail::time_unit)>;

using InterplanetaryDistance = mp_units::quantity<mp_units::iau::unit_symbols::au>;

using InterplanetaryVelocity = mp_units::quantity<mp_units::iau::unit_symbols::au / astrea::units::unit_symbols::jc>;

using BodyUnitlessPerTime = mp_units::quantity<detail::unitless / astrea::units::unit_symbols::jc>;

using BodyAngularVelocity = mp_units::quantity<detail::angle_unit / astrea::units::unit_symbols::jc>;

using Acceleration = mp_units::quantity<detail::distance_unit / (detail::time_unit * detail::time_unit)>;

using SurfaceArea = mp_units::quantity<detail::distance_unit * detail::distance_unit>;

using GravParam =
    mp_units::quantity<(detail::distance_unit * detail::distance_unit * detail::distance_unit) / (detail::time_unit * detail::time_unit)>;

using MeanMotion = mp_units::quantity<mp_units::one / mp_units::non_si::day>;

using MeanMotion1stDer = mp_units::quantity<mp_units::one / (mp_units::non_si::day * mp_units::non_si::day)>;

using MeanMotion2ndDer =
    mp_units::quantity<mp_units::one / (mp_units::non_si::day * mp_units::non_si::day * mp_units::non_si::day)>;

using BallisticCoefficient = mp_units::quantity<mp_units::one / astrea::units::unit_symbols::re>;

using Density = mp_units::quantity<detail::mass_unit / (detail::distance_unit * detail::distance_unit * detail::distance_unit)>;

using Altitude = mp_units::quantity<detail::distance_unit>;

using Gain = mp_units::quantity<detail::unitless>;

using SNR = mp_units::quantity<detail::unitless>;

using CNR = mp_units::quantity<detail::unitless>;

using Frequency = mp_units::quantity<mp_units::one / detail::time_unit>;

using Power = mp_units::quantity<detail::power_unit>;

using PowerFluxDensity = mp_units::quantity<detail::power_unit / (detail::distance_unit * detail::distance_unit)>;

using Temperature = mp_units::quantity_point<detail::temperature_unit>;

using Pressure = mp_units::quantity<detail::pressure_unit>;

using Moment = mp_units::quantity<detail::force_unit * detail::distance_unit>;

using MomentOfInertia = mp_units::quantity<detail::mass_unit * detail::distance_unit * detail::distance_unit>;

using SolarFlux = mp_units::quantity<astrea::units::unit_symbols::sfu>;

using Chirp = mp_units::quantity<mp_units::one / (detail::time_unit * detail::time_unit)>;

} // namespace astrea
```


