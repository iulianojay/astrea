

# File custom.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**custom.hpp**](custom_8hpp.md)

[Go to the documentation of this file](custom_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>

namespace astrea {

inline constexpr struct JulianCentury final : mp_units::named_unit<"JulianCentury", mp_units::mag<36525> * mp_units::non_si::day> {
} JulianCentury;

inline constexpr struct EarthRadii final
    : mp_units::named_unit<"EarthRadii", mp_units::mag<6378> * mp_units::si::unit_symbols::km> {
} EarthRadii;

inline constexpr struct SolarFluxUnits final
    : mp_units::named_unit<"SolarFluxUnits", mp_units::mag_power<10, -22> * mp_units::si::unit_symbols::W / (pow<2>(mp_units::si::unit_symbols::m) * mp_units::si::unit_symbols::Hz)> {
} SolarFluxUnits;

} // namespace astrea
```


