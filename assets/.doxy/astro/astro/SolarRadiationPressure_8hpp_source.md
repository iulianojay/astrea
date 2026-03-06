

# File SolarRadiationPressure.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**SolarRadiationPressure.hpp**](SolarRadiationPressure_8hpp.md)

[Go to the documentation of this file](SolarRadiationPressure_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Force.hpp>

namespace astrea {
namespace astro {

class SolarRadiationPressure : public Force {
  public:
    SolarRadiationPressure() = default;

    ~SolarRadiationPressure() = default;

    CartesianVector<Acceleration, frames::earth::icrf> compute_force(const State& state, const Vehicle& vehicle) const override;

  private:
};

} // namespace astro
} // namespace astrea
```


