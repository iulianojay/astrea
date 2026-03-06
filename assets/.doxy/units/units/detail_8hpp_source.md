

# File detail.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**detail.hpp**](detail_8hpp.md)

[Go to the documentation of this file](detail_8hpp.md)


```C++

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
inline constexpr auto pressure_unit = mp_units::si::unit_symbols::Pa; // TODO: Make sure this won't cause lots of conversions
inline constexpr auto force_unit = mp_units::si::unit_symbols::N; // TODO: Make sure this won't cause lots of conversions

} // namespace detail
} // namespace astrea
```


