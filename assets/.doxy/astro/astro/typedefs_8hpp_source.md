

# File typedefs.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**types**](dir_81b398d2ba04cf47420d9ac22d356bcf.md) **>** [**typedefs.hpp**](typedefs_8hpp.md)

[Go to the documentation of this file](typedefs_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

template <typename Frame_T>
using RadiusVector = CartesianVector<Distance, Frame_T>;

template <typename Frame_T>
using VelocityVector = CartesianVector<Velocity, Frame_T>;

template <typename Frame_T>
using AccelerationVector = CartesianVector<Acceleration, Frame_T>;

template <typename Frame_T>
using UnitVector = CartesianVector<Unitless, Frame_T>;

} // namespace astro
} // namespace astrea
```


