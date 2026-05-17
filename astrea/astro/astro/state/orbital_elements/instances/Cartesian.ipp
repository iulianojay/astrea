/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
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
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>
#include <math/interpolation.hpp>

namespace {
using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;
} // namespace

namespace astrea {
namespace astro {

template <IsFrame auto frame>
Cartesian<frame>::Cartesian(const Keplerian<frame>& elements, const GravParam& mu)
{
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
    const quantity cosTheta = cos(theta);
    const quantity sinTheta = sin(theta);

    const quantity cosW = cos(w);
    const quantity sinW = sin(w);

    const quantity cosRaan = cos(raan);
    const quantity sinRaan = sin(raan);

    const quantity cosInc = cos(inc);
    const quantity sinInc = sin(inc);

    const quantity h = sqrt(mu * a * (1.0 - ecc * ecc));
    const quantity A = h * h / mu / (1.0 + ecc * cosTheta);
    const quantity B = mu / h;

    // Perifocal Coordinates
    const quantity xPeri = A * cosTheta;
    const quantity yPeri = A * sinTheta;

    const quantity vxPeri = -B * sinTheta;
    const quantity vyPeri = B * (ecc + cosTheta);

    // Preallocate Dcm values for speed
    const quantity DcmPeri2Eci11 = (cosW * cosRaan - sinW * cosInc * sinRaan);
    const quantity DcmPeri2Eci12 = (-sinW * cosRaan - cosW * cosInc * sinRaan);

    const quantity DcmPeri2Eci21 = (cosW * sinRaan + sinW * cosInc * cosRaan);
    const quantity DcmPeri2Eci22 = (-sinW * sinRaan + cosW * cosInc * cosRaan);

    const quantity DcmPeri2Eci31 = sinInc * sinW;
    const quantity DcmPeri2Eci32 = sinInc * cosW;

    // Inertial position and _velocity
    _r[0] = DcmPeri2Eci11 * xPeri + DcmPeri2Eci12 * yPeri;
    _r[1] = DcmPeri2Eci21 * xPeri + DcmPeri2Eci22 * yPeri;
    _r[2] = DcmPeri2Eci31 * xPeri + DcmPeri2Eci32 * yPeri;

    _v[0] = DcmPeri2Eci11 * vxPeri + DcmPeri2Eci12 * vyPeri;
    _v[1] = DcmPeri2Eci21 * vxPeri + DcmPeri2Eci22 * vyPeri;
    _v[2] = DcmPeri2Eci31 * vxPeri + DcmPeri2Eci32 * vyPeri;
}

template <IsFrame auto frame>
Cartesian<frame>::Cartesian(const Equinoctial<frame>& elements, const GravParam& mu)
{
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

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::LEO(const GravParam& mu)
{
    return Cartesian<frame>(Keplerian<frame>::LEO(), mu);
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::LMEO(const GravParam& mu)
{
    return Cartesian<frame>(Keplerian<frame>::LMEO(), mu);
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::GPS(const GravParam& mu)
{
    return Cartesian<frame>(Keplerian<frame>::GPS(), mu);
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::HMEO(const GravParam& mu)
{
    return Cartesian<frame>(Keplerian<frame>::HMEO(), mu);
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::GEO(const GravParam& mu)
{
    return Cartesian<frame>(Keplerian<frame>::GEO(), mu);
}

template <IsFrame auto frame>
Cartesian<frame>::Cartesian(Cartesian<frame>&& other) noexcept :
    _r(std::move(other._r)),
    _v(std::move(other._v))
{
}

template <IsFrame auto frame>
Cartesian<frame>::Cartesian(const Cartesian<frame>& other) :
    _r(other._r),
    _v(other._v)
{
}


// Move assignment operator
template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator=(Cartesian<frame>&& other) noexcept
{
    if (this != &other) {
        _r = std::move(other._r);
        _v = std::move(other._v);
    }
    return *this;
}

// Copy assignment operator
template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator=(const Cartesian<frame>& other)
{
    return *this = Cartesian(other);
}

// Comparitor operators
template <IsFrame auto frame>
bool Cartesian<frame>::operator==(const Cartesian<frame>& other) const
{
    return (_r == other._r && _v == other._v);
}

template <IsFrame auto frame>
bool Cartesian<frame>::operator!=(const Cartesian<frame>& other) const
{
    return !(*this == other);
}


// Mathematical operators
template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator+(const Cartesian<frame>& other) const
{
    return Cartesian(_r + other._r, _v + other._v);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator+=(const Cartesian<frame>& other)
{
    _r += other._r;
    _v += other._v;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator+(const RadiusVector<frame>& r) const
{
    return Cartesian(_r + r, _v);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator+=(const RadiusVector<frame>& r)
{
    _r += r;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator+(const VelocityVector<frame>& v) const
{
    return Cartesian(_r, _v + v);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator+=(const VelocityVector<frame>& v)
{
    _v += v;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator-(const Cartesian<frame>& other) const
{
    return Cartesian(_r - other._r, _v - other._v);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator-=(const Cartesian<frame>& other)
{
    _r -= other._r;
    _v -= other._v;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator-(const RadiusVector<frame>& r) const
{
    return Cartesian(_r - r, _v);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator-=(const RadiusVector<frame>& r)
{
    _r -= r;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator-(const VelocityVector<frame>& v) const
{
    return Cartesian(_r, _v - v);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator-=(const VelocityVector<frame>& v)
{
    _v -= v;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator*(const Unitless& multiplier) const
{
    return Cartesian(_r * multiplier, _v * multiplier);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator*=(const Unitless& multiplier)
{
    _r *= multiplier;
    _v *= multiplier;
    return *this;
}

template <IsFrame auto frame>
CartesianPartial<frame> Cartesian<frame>::operator/(const Time& time) const
{
    return CartesianPartial<frame>(_r / time, _v / time);
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::operator/(const Unitless& divisor) const
{
    return Cartesian<frame>(_r / divisor, _v / divisor);
}

template <IsFrame auto frame>
Cartesian<frame>& Cartesian<frame>::operator/=(const Unitless& divisor)
{
    _r /= divisor;
    _v /= divisor;
    return *this;
}

template <IsFrame auto frame>
Cartesian<frame>
    Cartesian<frame>::interpolate(const Time& thisTime, const Time& otherTime, const Cartesian<frame>& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpX          = math::fast_interpolate<Time, Distance>(times, { _r[0], other._r[0] }, targetTime);
    const Distance interpY          = math::fast_interpolate<Time, Distance>(times, { _r[1], other._r[1] }, targetTime);
    const Distance interpZ          = math::fast_interpolate<Time, Distance>(times, { _r[2], other._r[2] }, targetTime);
    const Velocity interpVx         = math::fast_interpolate<Time, Velocity>(times, { _v[0], other._v[0] }, targetTime);
    const Velocity interpVy         = math::fast_interpolate<Time, Velocity>(times, { _v[1], other._v[1] }, targetTime);
    const Velocity interpVz         = math::fast_interpolate<Time, Velocity>(times, { _v[2], other._v[2] }, targetTime);

    return Cartesian<frame>(interpX, interpY, interpZ, interpVx, interpVy, interpVz);
}

template <IsFrame auto frame>
std::vector<Unitless> Cartesian<frame>::force_to_vector() const
{
    return { _r[0] / _r[0].unit, _r[1] / _r[1].unit, _r[2] / _r[2].unit,
             _v[0] / _v[0].unit, _v[1] / _v[1].unit, _v[2] / _v[2].unit };
}

template <IsFrame auto frame>
Cartesian<frame> Cartesian<frame>::from_vector(const std::vector<Unitless>& vec)
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

template <IsFrame auto frame>
Cartesian<frame> CartesianPartial<frame>::operator*(const Time& time) const
{
    return Cartesian<frame>(_v * time, _a * time);
}

template <IsFrame auto frame>
std::vector<Unitless> CartesianPartial<frame>::force_to_vector() const
{
    return { _v[0] / _v[0].unit, _v[1] / _v[1].unit, _v[2] / _v[2].unit,
             _a[0] / _a[0].unit, _a[1] / _a[1].unit, _a[2] / _a[2].unit };
}

template <IsFrame auto frame>
std::ostream& operator<<(std::ostream& os, Cartesian<frame> const& elements)
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

template <IsFrame auto frame>
std::ostream& operator<<(std::ostream& os, CartesianPartial<frame> const& elements)
{
    os << "[";
    os << elements._v[0] << ", ";
    os << elements._v[1] << ", ";
    os << elements._v[2] << ", ";
    os << elements._a[0] << ", ";
    os << elements._a[1] << ", ";
    os << elements._a[2];
    os << "] (CartesianPartial)";
    return os;
}

} // namespace astro
} // namespace astrea
