/**
 * @file trig.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Trigonometric functions for Angular and SI units.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <cmath>
#include <numbers>

#include <gcem.hpp>
#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

namespace astrea {
namespace math {

template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
    requires requires(Rep v) { sin(v); } || requires(Rep v) { gcem::sin(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto sin(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::sin;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(sin(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ sin(value_cast<rep>(q).numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ sin(q.numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
    requires requires(Rep v) { cos(v); } || requires(Rep v) { gcem::cos(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto cos(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::cos;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(cos(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ cos(value_cast<rep>(q).numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ cos(q.numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
    requires requires(Rep v) { tan(v); } || requires(Rep v) { gcem::tan(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto tan(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::tan;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(tan(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ tan(value_cast<rep>(q).numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ tan(q.numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { asin(v); } || requires(Rep v) { gcem::asin(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::angular::angle> auto asin(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::asin;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(asin(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ asin(value_cast<rep>(q).numerical_value_in(mp_units::dimensionless)), mp_units::angular::radian };
    }
    else {
        return mp_units::quantity{ asin(q.numerical_value_in(mp_units::dimensionless)), mp_units::angular::radian };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { acos(v); } || requires(Rep v) { gcem::acos(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::angular::angle> auto acos(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::acos;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(acos(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ acos(value_cast<rep>(q).numerical_value_in(mp_units::dimensionless)), mp_units::angular::radian };
    }
    else {
        return mp_units::quantity{ acos(q.numerical_value_in(mp_units::dimensionless)), mp_units::angular::radian };
    }
}

template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { atan(v); } || requires(Rep v) { gcem::atan(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::angular::angle> auto atan(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::atan;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(atan(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ atan(value_cast<rep>(q).numerical_value_in(mp_units::dimensionless)), mp_units::angular::radian };
    }
    else {
        return mp_units::quantity{ atan(q.numerical_value_in(mp_units::dimensionless)), mp_units::angular::radian };
    }
}

template <mp_units::Quantity auto R, typename Rep>
    requires requires(Rep v, Rep w) { atan2(v, w); } || requires(Rep v, Rep w) { gcem::atan2(v, w); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::angular::angle> auto
    atan2(const mp_units::quantity<R, Rep>& y, const mp_units::quantity<R, Rep>& x) noexcept
{
    using gcem::atan2;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(atan2(y.force_numerical_value_in(y.unit), x.force_numerical_value_in(x.unit)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ atan2(value_cast<rep>(y).numerical_value_in(y.unit), value_cast<rep>(x).numerical_value_in(x.unit)),
                                   mp_units::angular::radian };
    }
    else {
        return mp_units::quantity{ atan2(y.numerical_value_in(y.unit), x.numerical_value_in(x.unit)), mp_units::angular::radian };
    }
}

/**
 * @brief Computes the sinc function for a given angle in radians.
 *
 * The sinc function is defined as sin(x)/x, where x is in radians.
 * This function handles both integral and floating-point types.
 *
 * @tparam R The reference type for the angle (e.g., radian).
 * @tparam Rep The representation type (e.g., double, float).
 * @param q The angle in radians.
 * @return The value of the sinc function at the given angle.
 */
template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
    requires requires(Rep v) { sin(v); } || requires(Rep v) { gcem::sin(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto sinc(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::sin;
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

/**
 * @brief Computes the hyperbolic cosine of a given angle in radians.
 *
 * @tparam R The reference type for the angle (e.g., radian).
 * @tparam Rep The representation type (e.g., double, float).
 * @param q The angle in radians.
 * @return The value of the hyperbolic cosine at the given angle.
 */
template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
    requires requires(Rep v) { cosh(v); } || requires(Rep v) { gcem::cosh(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto cosh(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::cosh;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(cosh(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ cosh(value_cast<rep>(q).numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ cosh(q.numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
}

/**
 * @brief Computes the hyperbolic sine of a given angle in radians.
 *
 * @tparam R The reference type for the angle (e.g., radian).
 * @tparam Rep The representation type (e.g., double, float).
 * @param q The angle in radians.
 * @return The value of the hyperbolic sine at the given angle.
 */
template <mp_units::ReferenceOf<mp_units::angular::angle> auto R, typename Rep>
    requires requires(Rep v) { sinh(v); } || requires(Rep v) { gcem::sinh(v); }
[[nodiscard]] inline constexpr mp_units::QuantityOf<mp_units::dimensionless> auto sinh(const mp_units::quantity<R, Rep>& q) noexcept
{
    using gcem::sinh;
    if constexpr (!mp_units::treat_as_floating_point<Rep>) {
        // check what is the return type when called with the integral value
        using rep = decltype(sinh(q.force_numerical_value_in(mp_units::angular::radian)));
        // use this type ahead of calling the function to prevent narrowing if a unit conversion is needed
        return mp_units::quantity{ sinh(value_cast<rep>(q).numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
    else {
        return mp_units::quantity{ sinh(q.numerical_value_in(mp_units::angular::radian)), mp_units::one };
    }
}

/**
 * @brief Computes the Bessel function of the first kind of order zero.
 *
 * This function computes the Bessel function of the first kind of order zero for a given value.
 * It is defined as J_0(x) = (1/π) ∫_0^π cos(x sin(θ)) dθ.
 *
 * @tparam R The reference type for the input value (e.g., dimensionless).
 * @tparam Rep The representation type (e.g., double, float).
 * @param q The input value.
 * @return The value of the Bessel function of the first kind of order zero at the given input.
 */
template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { std::cyl_bessel_j(static_cast<Rep>(0.0), v); }
[[nodiscard]] constexpr mp_units::quantity<mp_units::one, Rep> cyl_bessel_j(const Rep& nu, const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::cyl_bessel_j;
    return { static_cast<Rep>(cyl_bessel_j(nu, q.numerical_value_ref_in(q.unit))), mp_units::one };
}

/**
 * @brief Computes the associated Legendre function of the first kind.
 *
 * This function computes the associated Legendre function P_n^m(x) for given n, m, and x.
 * It is defined as P_n^m(x) = (1/2^n n!) (d/dx)^n ((1 - x^2)^n) P_m^n(x).
 *
 * @tparam R The reference type for the input value (e.g., dimensionless).
 * @tparam Rep The representation type (e.g., double, float).
 * @param n The degree of the polynomial.
 * @param m The order of the polynomial.
 * @param q The input value.
 * @return The value of the associated Legendre function at the given input.
 */
template <mp_units::ReferenceOf<mp_units::dimensionless> auto R, typename Rep>
    requires requires(Rep v) { std::assoc_legendre(0, 0, v); }
[[nodiscard]] constexpr mp_units::quantity<mp_units::one, Rep>
    assoc_legendre(const unsigned int& n, const unsigned int& m, const mp_units::quantity<R, Rep>& q) noexcept
{
    using std::assoc_legendre;
    return { static_cast<Rep>(assoc_legendre(n, m, q.numerical_value_ref_in(q.unit))), mp_units::one };
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