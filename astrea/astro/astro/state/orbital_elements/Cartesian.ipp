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

// Perifocal Coordinates- we have to use this definition to avoid a log circular dependency issue
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
        get_x()  = 0.0 * km;
        get_y()  = 0.0 * km;
        get_z()  = 0.0 * km;
        get_vx() = 0.0 * km / s;
        get_vy() = 0.0 * km / s;
        get_vz() = 0.0 * km / s;
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
    const auto r = dcmPeri2Eci * rPeri;
    const auto v = dcmPeri2Eci * vPeri;

    get_x()  = r.get_x();
    get_y()  = r.get_y();
    get_z()  = r.get_z();
    get_vx() = v.get_x();
    get_vy() = v.get_y();
    get_vz() = v.get_z();
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
        get_x()  = 0.0 * km;
        get_y()  = 0.0 * km;
        get_z()  = 0.0 * km;
        get_vx() = 0.0 * km / s;
        get_vy() = 0.0 * km / s;
        get_vz() = 0.0 * km / s;
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
    get_x() = rOverSSq * (cosL * (1.0 + alphaSq) + twoHK * sinL);
    get_y() = rOverSSq * (sinL * (1.0 - alphaSq) + twoHK * cosL);
    get_z() = 2.0 * rOverSSq * (h * sinL - k * cosL);

    // Velocity
    get_vx() = -gamma * (sinL * (1.0 + alphaSq) - twoHK * (cosL + f) + g * (1.0 + alphaSq));
    get_vy() = -gamma * (cosL * (-1.0 + alphaSq) + twoHK * (sinL + g) + f * (-1.0 + alphaSq));
    get_vz() = 2.0 * gamma * (h * cosL + k * sinL + f * h + g * k);
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
    _elements(other._elements)
{
}


// Move assignment operator
template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator=(Cartesian<_frame_>&& other) noexcept
{
    if (this != &other) { _elements = std::move(other._elements); }
    return *this;
}

// Copy assignment operator
template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator=(const Cartesian<_frame_>& other)
{
    return *this = Cartesian(other);
}


// Mathematical operators
template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator+(const RadiusVector<_frame_>& r) const
{
    return Cartesian(get_x() + r[0], get_y() + r[1], get_z() + r[2], get_vx(), get_vy(), get_vz());
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator+=(const RadiusVector<_frame_>& r)
{
    get_x() += r[0];
    get_y() += r[1];
    get_z() += r[2];
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator+(const VelocityVector<_frame_>& v) const
{
    return Cartesian(get_x(), get_y(), get_z(), get_vx() + v[0], get_vy() + v[1], get_vz() + v[2]);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator+=(const VelocityVector<_frame_>& v)
{
    get_vx() += v[0];
    get_vy() += v[1];
    get_vz() += v[2];
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator-(const RadiusVector<_frame_>& r) const
{
    return Cartesian(get_x() - r[0], get_y() - r[1], get_z() - r[2], get_vx(), get_vy(), get_vz());
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator-=(const RadiusVector<_frame_>& r)
{
    get_x() -= r[0];
    get_y() -= r[1];
    get_z() -= r[2];
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_> Cartesian<_frame_>::operator-(const VelocityVector<_frame_>& v) const
{
    return Cartesian(get_x(), get_y(), get_z(), get_vx() - v[0], get_vy() - v[1], get_vz() - v[2]);
}

template <IsFrame auto _frame_>
Cartesian<_frame_>& Cartesian<_frame_>::operator-=(const VelocityVector<_frame_>& v)
{
    get_vx() -= v[0];
    get_vy() -= v[1];
    get_vz() -= v[2];
    return *this;
}

template <IsFrame auto _frame_>
Cartesian<_frame_>
    Cartesian<_frame_>::interpolate(const Time& thisTime, const Time& otherTime, const Cartesian<_frame_>& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpX  = math::fast_interpolate<Time, Distance>(times, { get_x(), other.get_x() }, targetTime);
    const Distance interpY  = math::fast_interpolate<Time, Distance>(times, { get_y(), other.get_y() }, targetTime);
    const Distance interpZ  = math::fast_interpolate<Time, Distance>(times, { get_z(), other.get_z() }, targetTime);
    const Velocity interpVx = math::fast_interpolate<Time, Velocity>(times, { get_vx(), other.get_vx() }, targetTime);
    const Velocity interpVy = math::fast_interpolate<Time, Velocity>(times, { get_vy(), other.get_vy() }, targetTime);
    const Velocity interpVz = math::fast_interpolate<Time, Velocity>(times, { get_vz(), other.get_vz() }, targetTime);

    return Cartesian<_frame_>(interpX, interpY, interpZ, interpVx, interpVy, interpVz);
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

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, CartesianPartial<_frame_> const& elements)
{
    os << "[";
    os << elements.get_vx() << ", ";
    os << elements.get_vy() << ", ";
    os << elements.get_vz() << ", ";
    os << elements.get_ax() << ", ";
    os << elements.get_ay() << ", ";
    os << elements.get_az();
    os << "] (CartesianPartial)";
    return os;
}

} // namespace astro
} // namespace astrea
