

# File HarrisPriester.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Earth**](dir_0d926747df7aa4605536658442a7f1d2.md) **>** [**atmosphere**](dir_52ad4357f9588f54fe1e3d5cf2b75c1b.md) **>** [**HarrisPriester.hpp**](HarrisPriester_8hpp.md)

[Go to the documentation of this file](HarrisPriester_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {
namespace planets {

class HarrisPriesterAtmosphere {
  public:
    HarrisPriesterAtmosphere() = delete;

    static Density find_atmospheric_density(const State& state);
};

} // namespace planets
} // namespace astro
} // namespace astrea
```


