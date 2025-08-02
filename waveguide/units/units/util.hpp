
#pragma once

#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace waveguide {

template <auto R, typename Rep>
[[nodiscard]] constexpr bool nearly_equal(const mp_units::quantity<R, Rep>& x, const mp_units::quantity<R, Rep>& y, const mp_units::quantity<mp_units::one>& relTol) noexcept
{
    const auto a = x.in(x.unit);
    const auto b = y.in(x.unit);
    if (a != 0.0 * R && abs((a - b) / a) > relTol) { return false; }
    else if (b != 0.0 * R && abs((a - b) / b) > relTol) {
        return false;
    }
    return true;
}

} // namespace waveguide