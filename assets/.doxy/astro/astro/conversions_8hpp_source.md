

# File conversions.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**utilities**](dir_68b93ce2887c47fc193a24ece16ebbe5.md) **>** [**conversions.hpp**](conversions_8hpp.md)

[Go to the documentation of this file](conversions_8hpp.md)


```C++

#pragma once

#include <numbers>

#include <mp-units/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

Angle convert_mean_anomaly_to_true_anomaly(const Angle& ma, const Unitless ecc);

Angle convert_true_anomaly_to_mean_anomaly(const Angle& ta, const Unitless ecc);

Angle convert_eccentric_anomaly_to_mean_anomaly(const Angle& ea, const Unitless ecc);

Angle convert_mean_anomaly_to_eccentric_anomaly(const Angle& ma, const Unitless ecc);

inline constexpr Angle wrap_angle(const Angle& angle) noexcept
{
    using mp_units::angular::unit_symbols::rad;
    static constexpr Angle twoPi = 2.0 * (std::numbers::pi * rad);

    Angle ang = angle;
    while (ang < 0.0 * rad) {
        ang += twoPi;
    }
    return mp_units::fmod(ang, twoPi);
}

inline constexpr Angle wrap_angle_to_pi(const Angle& angle) noexcept
{
    using mp_units::angular::unit_symbols::rad;
    static constexpr Angle onePi = std::numbers::pi * rad;

    Angle ang = angle;
    while (ang < 0.0 * rad) {
        ang += onePi;
    }
    return mp_units::fmod(ang, onePi);
}

} // namespace astro
} // namespace astrea
```


