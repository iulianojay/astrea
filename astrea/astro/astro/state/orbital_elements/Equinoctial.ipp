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

#include <iomanip>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <math/interpolation.hpp>

#include <astro/frames/definitions/transformations.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::LEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::LEO(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::LMEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::LMEO(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::GPS(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::GPS(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::HMEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::HMEO(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::GEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::GEO(), mu);
}

template <IsFrame auto _frame_>
Equinoctial<_frame_>::Equinoctial(const Keplerian<_frame_>& elements, const GravParam& mu)
{
    using namespace mp_units;
    using namespace mp_units::si;
    using namespace mp_units::si;

    // Get r and v
    const auto& a      = elements.get_semimajor();
    const auto& ecc    = elements.get_eccentricity();
    const auto& inc    = elements.get_inclination();
    const auto& raan   = elements.get_right_ascension();
    const auto& argPer = elements.get_argument_of_perigee();
    const auto& theta  = elements.get_true_anomaly();

    // Semilatus rectum
    _semilatus = a * (1 - ecc * ecc);

    // Non-dimensionalized parameters
    _f = ecc * cos(argPer + raan);
    _g = ecc * sin(argPer + raan);
    _h = tan(inc / 2.0) * cos(raan);
    _k = tan(inc / 2.0) * sin(raan);

    // True longitude
    _trueLongitude = wrap_angle(raan + argPer + theta);
}

// Copy constructor
template <IsFrame auto _frame_>
Equinoctial<_frame_>::Equinoctial(const Equinoctial<_frame_>& other) :
    _semilatus(other._semilatus),
    _f(other._f),
    _g(other._g),
    _h(other._h),
    _k(other._k),
    _trueLongitude(other._trueLongitude)
{
}

// Move constructor
template <IsFrame auto _frame_>
Equinoctial<_frame_>::Equinoctial(Equinoctial<_frame_>&& other) noexcept :
    _semilatus(std::move(other._semilatus)),
    _f(std::move(other._f)),
    _g(std::move(other._g)),
    _h(std::move(other._h)),
    _k(std::move(other._k)),
    _trueLongitude(std::move(other._trueLongitude))
{
}

// Move assignment operator
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator=(Equinoctial<_frame_>&& other) noexcept
{
    if (this != &other) {
        _semilatus     = std::move(other._semilatus);
        _f             = std::move(other._f);
        _g             = std::move(other._g);
        _h             = std::move(other._h);
        _k             = std::move(other._k);
        _trueLongitude = std::move(other._trueLongitude);
    }
    return *this;
}

// Copy assignment operator
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator=(const Equinoctial<_frame_>& other)
{
    return *this = Equinoctial(other);
}

// Comparitors operators
template <IsFrame auto _frame_>
bool Equinoctial<_frame_>::operator==(const Equinoctial<_frame_>& other) const
{
    return (
        _semilatus == other._semilatus && _f == other._f && _g == other._g && _h == other._h && _k == other._k &&
        _trueLongitude == other._trueLongitude
    );
}

template <IsFrame auto _frame_>
bool Equinoctial<_frame_>::operator!=(const Equinoctial<_frame_>& other) const
{
    return !(*this == other);
}


// Mathmatical operators
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::operator+(const Equinoctial<_frame_>& other) const
{
    return Equinoctial(
        _semilatus + other._semilatus,
        _f + other._f,
        _g + other._g,
        _h + other._h,
        _k + other._k,
        _trueLongitude + other._trueLongitude
    );
}
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator+=(const Equinoctial<_frame_>& other)
{
    _semilatus += other._semilatus;
    _f += other._f;
    _g += other._g;
    _h += other._h;
    _k += other._k;
    _trueLongitude += other._trueLongitude;
    return *this;
}

template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::operator-(const Equinoctial<_frame_>& other) const
{
    return Equinoctial(
        _semilatus - other._semilatus,
        _f - other._f,
        _g - other._g,
        _h - other._h,
        _k - other._k,
        _trueLongitude - other._trueLongitude
    );
}
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator-=(const Equinoctial<_frame_>& other)
{
    _semilatus -= other._semilatus;
    _f -= other._f;
    _g -= other._g;
    _h -= other._h;
    _k -= other._k;
    _trueLongitude -= other._trueLongitude;
    return *this;
}

template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::operator*(const Unitless& multiplier) const
{
    return Equinoctial(_semilatus * multiplier, _f * multiplier, _g * multiplier, _h * multiplier, _k * multiplier, _trueLongitude * multiplier);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator*=(const Unitless& multiplier)
{
    _semilatus *= multiplier;
    _f *= multiplier;
    _g *= multiplier;
    _h *= multiplier;
    _k *= multiplier;
    _trueLongitude *= multiplier;
    return *this;
}

template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::operator/(const Unitless& divisor) const
{
    return Equinoctial(_semilatus / divisor, _f / divisor, _g / divisor, _h / divisor, _k / divisor, _trueLongitude / divisor);
}

template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator/=(const Unitless& divisor)
{
    _semilatus /= divisor;
    _f /= divisor;
    _g /= divisor;
    _h /= divisor;
    _k /= divisor;
    _trueLongitude /= divisor;
    return *this;
}


template <IsFrame auto _frame_>
Equinoctial<_frame_>
    Equinoctial<_frame_>::interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial<_frame_>& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpSemimajor =
        math::fast_interpolate<Time, Distance>(times, { _semilatus, other.get_semilatus() }, targetTime);
    const Unitless interpEcc    = math::fast_interpolate<Time, Unitless>(times, { _f, other.get_f() }, targetTime);
    const Unitless interpInc    = math::fast_interpolate<Time, Unitless>(times, { _g, other.get_g() }, targetTime);
    const Unitless interpRaan   = math::fast_interpolate<Time, Unitless>(times, { _h, other.get_h() }, targetTime);
    const Unitless interpArgPer = math::fast_interpolate<Time, Unitless>(times, { _k, other.get_k() }, targetTime);
    const Angle interpTheta = math::fast_interpolate<Time, Angle>(times, { _trueLongitude, other.get_true_longitude() }, targetTime);

    return Equinoctial(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);
}

template <IsFrame auto _frame_>
std::vector<double> Equinoctial<_frame_>::force_to_double_vector() const
{
    return { _semilatus.numerical_value_in(_semilatus.unit),
             _f.numerical_value_in(_f.unit),
             _g.numerical_value_in(_g.unit),
             _h.numerical_value_in(_h.unit),
             _k.numerical_value_in(_k.unit),
             _trueLongitude.numerical_value_in(_trueLongitude.unit) };
}

template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::from_double_vector(const std::vector<double>& vec)
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    if (vec.size() != 6) {
        throw std::runtime_error("Input vector must have exactly 6 elements to convert to Equinoctial.");
    }
    return Equinoctial(vec[0] * km, vec[1], vec[2], vec[3], vec[4], vec[5] * rad);
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, Equinoctial<_frame_> const& elements)
{
    os << "[";
    os << elements.get_semilatus() << ", ";
    os << elements.get_f() << ", ";
    os << elements.get_g() << ", ";
    os << elements.get_h() << ", ";
    os << elements.get_k() << ", ";
    os << elements.get_true_longitude();
    os << "] (Equinoctial)";
    return os;
}

template <IsFrame auto _frame_>
template <IsFrame auto target_frame>
Equinoctial<target_frame> Equinoctial<_frame_>::in_frame(const Date& epoch, const GravParam& mu) const
{
    if constexpr (equivalent(frame, target_frame)) { return *this; }
    return Equinoctial<target_frame>(Cartesian<_frame_>(*this, mu).template in_frame<target_frame>(epoch), mu);
}

} // namespace astro
} // namespace astrea