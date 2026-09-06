

# File constants.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**units**](dir_69ee7df8d286dff8402d348058eb58eb.md) **>** [**units**](dir_8ace873b55bc88b2d1a73a241bbdd96b.md) **>** [**constants.hpp**](constants_8hpp.md)

[Go to the documentation of this file](constants_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/si.h>

#include <units/detail.hpp>
#include <units/typedefs.hpp>

namespace astrea {

constexpr Velocity speed_of_light_in_vacuum = 1.0 * mp_units::si::si2019::speed_of_light_in_vacuum;
constexpr auto boltzmann_constant           = 1.0 * mp_units::si::si2019::boltzmann_constant;

} // namespace astrea
```


