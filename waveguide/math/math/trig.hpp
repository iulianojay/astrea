/**
 * @file trig.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Trigonometric functions for Angular and SI units.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cmath>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

namespace waveguide {
namespace math {

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
    requires requires(Rep v) { sin(v); } || requires(Rep v) { std::sin(v); }
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

} // namespace math
} // namespace waveguide