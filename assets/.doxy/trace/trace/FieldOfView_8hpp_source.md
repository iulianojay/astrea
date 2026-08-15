

# File FieldOfView.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**platforms**](dir_4dbda61db413396ce1d3b920f98dbf93.md) **>** [**sensors**](dir_4c34a36d272c54a3547c6d2c18e9dea2.md) **>** [**fov**](dir_303a66b90134ad3dff734d202c421315.md) **>** [**FieldOfView.hpp**](FieldOfView_8hpp.md)

[Go to the documentation of this file](FieldOfView_8hpp.md)


```C++

#pragma once

#include <numbers>
#include <unordered_map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>

namespace astrea {
namespace trace {

Angle calculate_angle_between_vectors(
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& vector1,
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& vector2
);

class FieldOfView {
  public:
    FieldOfView() = default;

    ~FieldOfView() = default;

    virtual bool contains(
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& boresight,
        const astro::CartesianVector<Distance, astro::frames::earth::icrf>& target
    ) const = 0;

    virtual Angle max_half_angle() const { return std::numbers::pi / 2.0 * mp_units::si::unit_symbols::rad; }
};

} // namespace trace
} // namespace astrea
```


