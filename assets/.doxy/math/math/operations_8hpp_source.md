

# File operations.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**math**](dir_450de47f4bf9646ba641743528a4ea64.md) **>** [**math**](dir_b2ecf34ed687fe8e79818a2ecae6cd69.md) **>** [**operations.hpp**](operations_8hpp.md)

[Go to the documentation of this file](operations_8hpp.md)


```C++

#pragma once

#include <cmath>
#include <algorithm>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace math {


template <auto R1, auto R2, typename Rep>
[[nodiscard]] constexpr bool nearly_equal(
    const mp_units::quantity<R1, Rep>& x,
    const mp_units::quantity<R2, Rep>& y,
    const mp_units::quantity<mp_units::one, Rep>& relTol = 0.0 * mp_units::one,
    const mp_units::quantity<mp_units::one, Rep>& absTol = 0.0 * mp_units::one
) noexcept
{
    // Bring both to the same unit for comparison
    const auto a = x.in(x.unit);
    const auto b = y.in(x.unit);

    // Check rel tol
    if (relTol != 0.0 * mp_units::one) {
        if (a != 0.0 * R1 && b != 0.0 * R1) {
            if (abs((a - b) / a) > relTol) { return false; }
        }
    }

    // Check abs tol
    if (absTol != 0.0 * mp_units::one) {
        if (abs(a - b) > absTol * R1) { return false; }
    }

    return true;
}

template <auto R, typename Rep>
    requires requires(Rep v) { max(v, v); } || requires(Rep v) { std::max(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> max(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::max;
    return mp_units::quantity{ max(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
}

template <auto R, typename Rep>
    requires requires(Rep v) { min(v, v); } || requires(Rep v) { std::min(v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep> min(const mp_units::quantity<R, Rep>& q1, const mp_units::quantity<R, Rep>& q2) noexcept
{
    using std::min;
    return mp_units::quantity{ min(q1.numerical_value_in(q1.unit), q2.numerical_value_in(q1.unit)), q1.unit };
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R1, mp_units::ReferenceOf<mp_units::dimensionless> auto R2, typename Rep1, typename Rep2>
    requires requires(Rep1 v1, Rep2 v2) { pow(v1, v2); } || requires(Rep1 v1, Rep2 v2) { std::pow(v1, v2); }
[[nodiscard]] inline mp_units::quantity<mp_units::one, Rep1>
    pow(const mp_units::quantity<R1, Rep1>& q, const mp_units::quantity<R2, Rep2>& n) noexcept
{
    using std::pow;
    return mp_units::quantity{ pow(q.numerical_value_in(mp_units::one), n.numerical_value_in(mp_units::one)), mp_units::one };
}

template <auto R, typename Rep>
    requires requires(Rep v) { clamp(v, v, v); } || requires(Rep v) { std::clamp(v, v, v); }
[[nodiscard]] inline mp_units::quantity<R, Rep>
    clamp(const mp_units::quantity<R, Rep>& q, const mp_units::quantity<R, Rep>& low, const mp_units::quantity<R, Rep>& high) noexcept
{
    using std::clamp;
    return mp_units::quantity{ clamp(q.numerical_value_in(q.unit), low.numerical_value_in(q.unit), high.numerical_value_in(q.unit)),
                               q.unit };
}


} // namespace math
} // namespace astrea
```


