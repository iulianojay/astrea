

# File CircularFieldOfView.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**fov**](dir_303a66b90134ad3dff734d202c421315.md) **>** [**CircularFieldOfView.hpp**](CircularFieldOfView_8hpp.md)

[Go to the documentation of this file](CircularFieldOfView_8hpp.md)


```C++

#pragma once

#include <numbers>
#include <unordered_map>

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <units/units.hpp>

#include <trace/platforms/sensors/fov/FieldOfView.hpp>

namespace astrea {
namespace trace {

class CircularFieldOfView : public FieldOfView {
  public:
    CircularFieldOfView(const Angle& halfConeAngle = std::numbers::pi / 4.0 * mp_units::si::unit_symbols::rad);

    ~CircularFieldOfView() = default;

    bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const;

    Angle max_half_angle() const override { return _halfConeAngle; }

  private:
    Angle _halfConeAngle;       // Half-cone angle defining the circular field of view
    Unitless _cosHalfConeAngle; // cos(_halfConeAngle), pre-computed for fast containment checks
};

} // namespace trace
} // namespace astrea
```


