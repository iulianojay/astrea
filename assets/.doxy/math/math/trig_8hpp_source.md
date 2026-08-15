

# File trig.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**math**](dir_450de47f4bf9646ba641743528a4ea64.md) **>** [**math**](dir_b2ecf34ed687fe8e79818a2ecae6cd69.md) **>** [**trig.hpp**](trig_8hpp.md)

[Go to the documentation of this file](trig_8hpp.md)


```C++

#pragma once

#include <cmath>
#include <numbers>

#include <gcem.hpp>
#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>

namespace astrea {
namespace math {

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { sin(v); } || requires(Rep v) { gcem::sin(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto sin(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::sin;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(sin(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ sin(value_cast<rep>(q).numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ sin(q.numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { cos(v); } || requires(Rep v) { gcem::cos(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto cos(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::cos;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(cos(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ cos(value_cast<rep>(q).numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ cos(q.numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { tan(v); } || requires(Rep v) { gcem::tan(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto tan(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::tan;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(tan(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ tan(value_cast<rep>(q).numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ tan(q.numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { asin(v); } || requires(Rep v) { gcem::asin(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto
    asin(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::asin;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(asin(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ asin(value_cast<rep>(q).numerical_value_in(mp_units::dimensionless)), mp_units::si::radian };
    }
    else {
        return mp_units::quantity{ asin(q.numerical_value_in(mp_units::dimensionless)), mp_units::si::radian };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { acos(v); } || requires(Rep v) { gcem::acos(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto
    acos(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::acos;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(acos(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ acos(value_cast<rep>(q).numerical_value_in(mp_units::dimensionless)), mp_units::si::radian };
    }
    else {
        return mp_units::quantity{ acos(q.numerical_value_in(mp_units::dimensionless)), mp_units::si::radian };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { atan(v); } || requires(Rep v) { gcem::atan(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto
    atan(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::atan;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(atan(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ atan(value_cast<rep>(q).numerical_value_in(mp_units::dimensionless)), mp_units::si::radian };
    }
    else {
        return mp_units::quantity{ atan(q.numerical_value_in(mp_units::dimensionless)), mp_units::si::radian };
    }
}

template <mp_units::Quantity auto R, typename Rep>
    requires requires(Rep v, Rep w) { atan2(v, w); } || requires(Rep v, Rep w) { gcem::atan2(v, w); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto
    atan2(const mp_units::quantity<R, Rep>& y, const mp_units::quantity<R, Rep>& x) noexcept
{
    using gcem::atan2;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(atan2(y.force_numerical_value_in(y.unit), x.force_numerical_value_in(x.unit)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ atan2(value_cast<rep>(y).numerical_value_in(y.unit), value_cast<rep>(x).numerical_value_in(x.unit)),
                                   mp_units::si::radian };
    }
    else {
        return mp_units::quantity{ atan2(y.numerical_value_in(y.unit), x.numerical_value_in(x.unit)), mp_units::si::radian };
    }
}

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { sin(v); } || requires(Rep v) { gcem::sin(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto sinc(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::sin;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(sin(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ sin(value_cast<rep>(q).numerical_value_in(mp_units::si::radian)) /
                                       value_cast<rep>(q).numerical_value_in(mp_units::si::radian),
                                   mp_units::one };
    }
    else {
        return mp_units::quantity{ sin(q.numerical_value_in(mp_units::si::radian)) / q.numerical_value_in(mp_units::si::radian),
                                   mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { cosh(v); } || requires(Rep v) { gcem::cosh(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto cosh(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::cosh;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(cosh(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ cosh(value_cast<rep>(q).numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ cosh(q.numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { sinh(v); } || requires(Rep v) { gcem::sinh(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto sinh(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::sinh;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(sinh(q.force_numerical_value_in(mp_units::si::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ sinh(value_cast<rep>(q).numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ sinh(q.numerical_value_in(mp_units::si::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { std::cyl_bessel_j(static_cast<Rep>(0.0), v); }
[[nodiscard]] constexpr mp_units::quantity<mp_units::one, Rep> cyl_bessel_j(const Rep& nu, const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::cyl_bessel_j;
    return { static_cast<Rep>(cyl_bessel_j(nu, q.numerical_value_ref_in(q.unit))), mp_units::one };
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { std::assoc_legendre(0, 0, v); }
[[nodiscard]] constexpr mp_units::quantity<mp_units::one, Rep>
    assoc_legendre(const unsigned int& n, const unsigned int& m, const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::assoc_legendre;
    return { static_cast<Rep>(assoc_legendre(n, m, q.numerical_value_ref_in(q.unit))), mp_units::one };
}

template <mp_units::ReferenceOf<mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
    requires requires(Rep v) { sin(v); } || requires(Rep v) { gcem::sin(v); }
[[nodiscard]] inline constexpr auto sin_cos_pack(const mp_units::quantity<R, Rep>& q) noexcept
{
    return std::make_pair(math::sin(q), math::cos(q));
}

// TODO: Make this mp-units compatible
template <typename T>
T atan3(T y, T x)
{
    T sy{}, sx{};
    if (y >= 0) { sy = 1; }
    else {
        sy = -1;
    }
    if (x >= 0) { sx = 1; }
    else {
        sx = -1;
    }

    static constexpr T PI_T = static_cast<T>(std::numbers::pi);
    if (std::abs(y) < 1e-10) { return (1 - sx) * PI_T / 2.0; }
    else if (std::abs(x) < 1e-10) {
        return (2.0 - sy) * PI_T / 2.0;
    }
    else {
        return (2.0 - sy) * PI_T / 2 + sy * sx * (std::abs(std::atan(y / x)) - PI_T / 2.0);
    }
}

} // namespace math
} // namespace astrea
```


