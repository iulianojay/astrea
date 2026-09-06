

# File NullVehicle.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**vehicles**](dir_6209fec1d31cfd277683fcd634983a45.md) **>** [**NullVehicle.hpp**](NullVehicle_8hpp.md)

[Go to the documentation of this file](NullVehicle_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

class NullVehicle {

  public:
    NullVehicle(const Mass& mass = 1.0 * mp_units::si::unit_symbols::kg);

    NullVehicle* clone() const;

    Mass get_mass(const State& state) const;

    std::string get_name() const;

  private:
    Mass _mass; // Mass of the vehicle
};

} // namespace astro
} // namespace astrea
```


