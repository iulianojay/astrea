/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <iomanip>
#include <iostream>

// mp-units
#include <mp-units/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <math/interpolation.hpp>
#include <math/trig.hpp>

#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

namespace {

// Perifocal Coordinates- we have to use this definition to avoid a long circular dependency issue
inline constexpr struct peri : Frame<"fake perifocal frame for this calc only", DynamicOrigin{}, DynamicAxis{}> {
} peri;

} // namespace

template <IsFrame auto _frame_>
Cartesian<_frame_>::Cartesian(const Keplerian<_frame_>& elements, const GravParam& mu)
{
    using namespace mp_units;
    using namespace mp_units::si;
    using namespace mp_units::si;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    // Extract elements
    const auto& a     = elements.get_semimajor();
    const auto& ecc   = elements.get_eccentricity();
    const auto& inc   = elements.get_inclination();
    const auto& raan  = elements.get_right_ascension();
    const auto& w     = elements.get_argument_of_perigee();
    const auto& theta = elements.get_true_anomaly();

    if (a == 0.0 * km) {
        _r = { 0.0 * km, 0.0 * km, 0.0 * km };
        _v = { 0.0 * km / s, 0.0 * km / s, 0.0 * km / s };
        return;
    }

    // Precalculate
    const auto [sinTheta, cosTheta] = math::sin_cos_pack(theta);
    const auto [sinW, cosW]         = math::sin_cos_pack(w);
    const auto [sinRaan, cosRaan]   = math::sin_cos_pack(raan);
    const auto [sinInc, cosInc]     = math::sin_cos_pack(inc);

    const SpecificAngularMomentum h    = elements.get_specific_angular_momentum(mu);
    const Distance radialCoefficient   = pow<2>(h) / mu / (1.0 + ecc * cosTheta);
    const Velocity velocityCoefficient = mu / h;

    const RadiusVector<peri> rPeri{ radialCoefficient * cosTheta, radialCoefficient * sinTheta, Distance::zero() };
    const VelocityVector<peri> vPeri{ -velocityCoefficient * sinTheta, velocityCoefficient * (ecc + cosTheta), Velocity::zero() };

    // Preallocate Dcm values for speed
    const DCM<peri, _frame_> dcmPeri2Eci = {
        { cosW * cosRaan - sinW * cosInc * sinRaan, -sinW * cosRaan - cosW * cosInc * sinRaan, sinInc * sinRaan },
        { cosW * sinRaan + sinW * cosInc * cosRaan, -sinW * sinRaan + cosW * cosInc * cosRaan, -sinInc * cosRaan },
        { sinInc * sinW, sinInc * cosW, cosInc }
    };

    // Inertial position and _velocity
    _r = dcmPeri2Eci * rPeri;
    _v = dcmPeri2Eci * vPeri;
}

template <IsFrame auto _frame_>
Cartesian<_frame_>::Cartesian(const Equinoctial<_frame_>& elements, const GravParam& mu)
{
    using namespace mp_units;
    using namespace mp_units::si;
    using namespace mp_units::si;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    // Extract
    const auto& semilatus     = elements.get_semilatus();
    const auto& f             = elements.get_f();
    const auto& g             = elements.get_g();
    const auto& h             = elements.get_h();
    const auto& k             = elements.get_k();
    const auto& trueLongitude = elements.get_true_longitude();

    // Catch default/nonsense case
    if (semilatus == 0.0 * km) {
        _r[0] = 0.0 * km;
        _r[1] = 0.0 * km;
        _r[2] = 0.0 * km;
        _v[0] = 0.0 * km / s;
        _v[1] = 0.0 * km / s;
        _v[2] = 0.0 * km / s;
        return;
    }

    // Precalculate
    const auto cosL = cos(trueLongitude);
    const auto sinL = sin(trueLongitude);

    const auto alphaSq = h * h - k * k;
    const auto sSq     = 1.0 + h * h + k * k;
    const auto w       = 1.0 + f * cosL + g * sinL;
    const auto r       = semilatus / w;

    const auto rOverSSq = r / sSq;
    const auto twoHK    = 2.0 * h * k;

    const auto gamma = 1.0 / sSq * sqrt(mu / semilatus);

    // Radius
    _r[0] = rOverSSq * (cosL * (1.0 + alphaSq) + twoHK * sinL);
    _r[1] = rOverSSq * (sinL * (1.0 - alphaSq) + twoHK * cosL);
    _r[2] = 2.0 * rOverSSq * (h * sinL - k * cosL);

    // Velocity
    _v[0] = -gamma * (sinL * (1.0 + alphaSq) - twoHK * (cosL + f) + g * (1.0 + alphaSq));
    _v[1] = -gamma * (cosL * (-1.0 + alphaSq) + twoHK * (sinL + g) + f * (-1.0 + alphaSq));
    _v[2] = 2.0 * gamma * (h * cosL + k * sinL + f * h + g * k);
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::LEO(const GravParam& mu)
{
    return Cartesian<_frame_>(Keplerian<_frame_>::LEO(), mu);
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::LMEO(const GravParam& mu)
{
    return Cartesian<_frame_>(Keplerian<_frame_>::LMEO(), mu);
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::GPS(const GravParam& mu)
{
    return Cartesian<_frame_>(Keplerian<_frame_>::GPS(), mu);
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::HMEO(const GravParam& mu)
{
    return Cartesian<_frame_>(Keplerian<_frame_>::HMEO(), mu);
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::GEO(const GravParam& mu)
{
    return Cartesian<_frame_>(Keplerian<_frame_>::GEO(), mu);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>::Cartesian(const Cartesian<_frame_>& other) :
    _r(other._r),
    _v(other._v)
{
}


// Move assignment operator
template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator=(Cartesian<_frame_>&& other) noexcept
{
    if (this != &other) {
        _r = std::move(other._r);
        _v = std::move(other._v);
    }
    return *this;
}

// Copy assignment operator
template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator=(const Cartesian<_frame_>& other)
{
    return *this = Cartesian(other);
}

// Comparitor operators
template <IsFrame auto _frame_>
bool Cartesian<_frame_>::operator==(const Cartesian<_frame_>& other) const
{
    return (_r == other._r && _v == other._v);
}

template <IsFrame auto _frame_>
bool Cartesian<_frame_>::operator!=(const Cartesian<_frame_>& other) const
{
    return !(*this == other);
}


// Mathematical operators
template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator+(const Cartesian<_frame_>& other) const
{
    return Cartesian(_r + other._r, _v + other._v);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator+=(const Cartesian<_frame_>& other)
{
    _r += other._r;
    _v += other._v;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator+(const RadiusVector<_frame_>& r) const
{
    return Cartesian(_r + r, _v);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator+=(const RadiusVector<_frame_>& r)
{
    _r += r;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator+(const VelocityVector<_frame_>& v) const
{
    return Cartesian(_r, _v + v);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator+=(const VelocityVector<_frame_>& v)
{
    _v += v;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator-(const Cartesian<_frame_>& other) const
{
    return Cartesian(_r - other._r, _v - other._v);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator-=(const Cartesian<_frame_>& other)
{
    _r -= other._r;
    _v -= other._v;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator-(const RadiusVector<_frame_>& r) const
{
    return Cartesian(_r - r, _v);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator-=(const RadiusVector<_frame_>& r)
{
    _r -= r;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator-(const VelocityVector<_frame_>& v) const
{
    return Cartesian(_r, _v - v);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator-=(const VelocityVector<_frame_>& v)
{
    _v -= v;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator*(const Unitless& multiplier) const
{
    return Cartesian(_r * multiplier, _v * multiplier);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator*=(const Unitless& multiplier)
{
    _r *= multiplier;
    _v *= multiplier;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator/(const Unitless& divisor) const
{
    return Cartesian<_frame_>(_r / divisor, _v / divisor);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator/=(const Unitless& divisor)
{
    _r /= divisor;
    _v /= divisor;
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_>
    Cartesian<_frame_>::interpolate(const Time& thisTime, const Time& otherTime, const Cartesian<_frame_>& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpX          = math::fast_interpolate<Time, Distance>(times, { _r[0], other._r[0] }, targetTime);
    const Distance interpY          = math::fast_interpolate<Time, Distance>(times, { _r[1], other._r[1] }, targetTime);
    const Distance interpZ          = math::fast_interpolate<Time, Distance>(times, { _r[2], other._r[2] }, targetTime);
    const Velocity interpVx         = math::fast_interpolate<Time, Velocity>(times, { _v[0], other._v[0] }, targetTime);
    const Velocity interpVy         = math::fast_interpolate<Time, Velocity>(times, { _v[1], other._v[1] }, targetTime);
    const Velocity interpVz         = math::fast_interpolate<Time, Velocity>(times, { _v[2], other._v[2] }, targetTime);

    return Cartesian<_frame_>(interpX, interpY, interpZ, interpVx, interpVy, interpVz);
}

template <IsFrame auto _frame_>
std::vector<double> Cartesian<_frame_>::force_to_double_vector() const
{
    return { _r[0].numerical_value_in(_r[0].unit), _r[1].numerical_value_in(_r[1].unit),
             _r[2].numerical_value_in(_r[2].unit), _v[0].numerical_value_in(_v[0].unit),
             _v[1].numerical_value_in(_v[1].unit), _v[2].numerical_value_in(_v[2].unit) };
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::from_double_vector(const std::vector<double>& vec)
{
    if (vec.size() != 6) {
        throw std::runtime_error("Input vector must have exactly 6 elements to convert to Cartesian.");
    }

    return Cartesian(
        vec[0] * astrea::detail::distance_unit,
        vec[1] * astrea::detail::distance_unit,
        vec[2] * astrea::detail::distance_unit,
        vec[3] * astrea::detail::distance_unit / astrea::detail::time_unit,
        vec[4] * astrea::detail::distance_unit / astrea::detail::time_unit,
        vec[5] * astrea::detail::distance_unit / astrea::detail::time_unit
    );
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, Cartesian<_frame_> const& elements)
{
    os << "[";
    os << elements.get_x() << ", ";
    os << elements.get_y() << ", ";
    os << elements.get_z() << ", ";
    os << elements.get_vx() << ", ";
    os << elements.get_vy() << ", ";
    os << elements.get_vz();
    os << "] (Cartesian)";
    return os;
}

} // namespace astro
} // namespace astrea
