

# File Nrlmsise00.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**space\_weather**](dir_ba92a5bb4647772267966b3cef944594.md) **>** [**atmosphere**](dir_3bfcc16c8bbdb2d74b81ce33c082ff6e.md) **>** [**Nrlmsise00.hpp**](Nrlmsise00_8hpp.md)

[Go to the documentation of this file](Nrlmsise00_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/si.h>
#include <nrlmsise00/Nrlmsise00.hpp>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

Time calculate_local_solar_time(const State& state);

class Nrlmsise00Atmosphere {
  public:
    Nrlmsise00Atmosphere() = delete;

    static Density find_atmospheric_density(
        const State& state,
        const SolarFlux& f107a,
        const SolarFlux& f107,
        const std::array<Unitless, 8>& ap,
        const std::array<int, 24>& flags = get_default_flags(),
        const bool ignoreLowAltitudes    = true
    );

  private:
    static std::array<int, 24> get_default_flags();
};

} // namespace astro
} // namespace astrea
```


