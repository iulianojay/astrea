

# File JacchiaRoberts.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**space\_weather**](dir_ba92a5bb4647772267966b3cef944594.md) **>** [**atmosphere**](dir_3bfcc16c8bbdb2d74b81ce33c082ff6e.md) **>** [**JacchiaRoberts.hpp**](JacchiaRoberts_8hpp.md)

[Go to the documentation of this file](JacchiaRoberts_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

class JacchiaRobertsAtmosphere {
  public:
    JacchiaRobertsAtmosphere() = delete;

    static Density find_atmospheric_density(const State& state, const Distance equitorialRadius, const Distance polarRadius);
};

} // namespace astro
} // namespace astrea
```


