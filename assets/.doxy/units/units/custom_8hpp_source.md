

# File custom.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**custom.hpp**](custom_8hpp.md)

[Go to the documentation of this file](custom_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace units {

inline constexpr struct julian_century final
    : mp_units::named_unit<"Julian Century", mp_units::mag<36525> * mp_units::non_si::day> {
} julian_century;

inline constexpr struct earth_radii final
    : mp_units::named_unit<"Earth Radii", mp_units::mag<6378> * mp_units::si::unit_symbols::km> {
} earth_radii;

inline constexpr struct solar_flux_units final
    : mp_units::named_unit<"Solar Flux Units", mp_units::mag_power<10, -22> * mp_units::si::unit_symbols::W / (pow<2>(mp_units::si::unit_symbols::m) * mp_units::si::unit_symbols::Hz)> {
} solar_flux_units;

inline constexpr struct revolution final : mp_units::named_unit<"rev", mp_units::mag<360> * mp_units::si::unit_symbols::deg> {
} revolution;


namespace unit_symbols {

inline constexpr auto jc  = julian_century;
inline constexpr auto re  = earth_radii;
inline constexpr auto sfu = solar_flux_units;
inline constexpr auto rev = revolution;

} // namespace unit_symbols

} // namespace units
} // namespace astrea
```


