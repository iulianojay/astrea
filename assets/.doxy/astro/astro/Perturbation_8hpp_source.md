

# File Perturbation.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**Perturbation.hpp**](Perturbation_8hpp.md)

[Go to the documentation of this file](Perturbation_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

struct Perturbation {
    ForceVector<frames::primary> force = { 0.0 * mp_units::si::unit_symbols::N }; 
    TorqueVector<frames::primary> torque = { 0.0 * mp_units::si::unit_symbols::N * mp_units::si::unit_symbols::m }; 
};

} // namespace astro
} // namespace astrea
```


