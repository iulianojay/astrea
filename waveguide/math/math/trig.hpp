#pragma once

#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace waveguide {
namespace math {

template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
requires requires(Rep v) { sin(v); } || requires(Rep v)
{
    std::sin(v);
}
[[nodiscard]] inline mp_units::QuantityOf<mp_units::dimensionless> auto sinc(const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::sin;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(sin(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ sin(value_cast<rep>(q).numerical_value_in(mp_units::angular::radian)) /
                                       value_cast<rep>(q).numerical_value_in(mp_units::angular::radian),
                                   mp_units::one };
    }
    else {
        return mp_units::quantity{ sin(q.numerical_value_in(mp_units::angular::radian)) /
                                       q.numerical_value_in(mp_units::angular::radian),
                                   mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
requires requires(Rep v) { std::cyl_bessel_j(static_cast<Rep>(0.0), v); }
[[nodiscard]] constexpr mp_units::quantity<mp_units::one, Rep> cyl_bessel_j(const Rep& nu, const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::cyl_bessel_j;
    return { static_cast<Rep>(cyl_bessel_j(nu, q.numerical_value_ref_in(q.unit))), mp_units::one };
}

} // namespace math
} // namespace waveguide