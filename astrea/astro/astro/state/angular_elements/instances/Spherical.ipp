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

#include <iomanip>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <math/interpolation.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/transformations.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>


namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_>
template <auto _frame_>
    requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
Spherical<_body_>::Spherical(const RadiusVector<_frame_>& rIcrf, const Date& date)
{
    *this = Spherical<_body_>(rIcrf.template in_frame<_fixed_frame_>(date));
}

template <IsCelestialBody auto _body_>
Spherical<_body_>::Spherical(const RadiusVector<_fixed_frame_>& rFixed)
{
    std::tie(_range, _inclination, _azimuth) = convert_body_fixed_to_spherical(rFixed);
}

// Copy constructor
template <IsCelestialBody auto _body_>
Spherical<_body_>::Spherical(const Spherical<_body_>& other) :
    _range(other._range),
    _inclination(other._inclination),
    _azimuth(other._azimuth)
{
}

// Move constructor
template <IsCelestialBody auto _body_>
Spherical<_body_>::Spherical(Spherical<_body_>&& other) noexcept :
    _range(std::move(other._range)),
    _inclination(std::move(other._inclination)),
    _azimuth(std::move(other._azimuth))
{
}

// Move assignment operator
template <IsCelestialBody auto _body_>
Spherical<_body_>& Spherical<_body_>::operator=(Spherical<_body_>&& other) noexcept
{
    if (this != &other) {
        _range       = std::move(other._range);
        _inclination = std::move(other._inclination);
        _azimuth     = std::move(other._azimuth);
    }
    return *this;
}

// Copy assignment operator
template <IsCelestialBody auto _body_>
Spherical<_body_>& Spherical<_body_>::operator=(const Spherical<_body_>& other)
{
    return *this = Spherical<_body_>(other);
}

// Comparison operators
template <IsCelestialBody auto _body_>
bool Spherical<_body_>::operator==(const Spherical<_body_>& other) const
{
    return (_range == other._range && _inclination == other._inclination && _azimuth == other._azimuth);
}

template <IsCelestialBody auto _body_>
bool Spherical<_body_>::operator!=(const Spherical<_body_>& other) const
{
    return !(*this == other);
}

// Mathematical operators
template <IsCelestialBody auto _body_>
Spherical<_body_> Spherical<_body_>::operator+(const Spherical<_body_>& other) const
{
    return Spherical<_body_>(_range + other._range, _inclination + other._inclination, _azimuth + other._azimuth);
}

template <IsCelestialBody auto _body_>
Spherical<_body_>& Spherical<_body_>::operator+=(const Spherical<_body_>& other)
{
    _range += other._range;
    _inclination += other._inclination;
    _azimuth += other._azimuth;
    return *this;
}

template <IsCelestialBody auto _body_>
Spherical<_body_> Spherical<_body_>::operator-(const Spherical<_body_>& other) const
{
    return Spherical<_body_>(_range - other._range, _inclination - other._inclination, _azimuth - other._azimuth);
}

template <IsCelestialBody auto _body_>
Spherical<_body_>& Spherical<_body_>::operator-=(const Spherical<_body_>& other)
{
    _range -= other._range;
    _inclination -= other._inclination;
    _azimuth -= other._azimuth;
    return *this;
}

template <IsCelestialBody auto _body_>
Spherical<_body_> Spherical<_body_>::operator*(const Unitless& multiplier) const
{
    return Spherical<_body_>(_range * multiplier, _inclination * multiplier, _azimuth * multiplier);
}

template <IsCelestialBody auto _body_>
Spherical<_body_>& Spherical<_body_>::operator*=(const Unitless& multiplier)
{
    _range *= multiplier;
    _inclination *= multiplier;
    _azimuth *= multiplier;
    return *this;
}

template <IsCelestialBody auto _body_>
std::vector<Unitless> Spherical<_body_>::operator/(const Spherical<_body_>& other) const
{
    return { _range / other._range, _inclination / other._inclination, _azimuth / other._azimuth };
}

template <IsCelestialBody auto _body_>
Spherical<_body_> Spherical<_body_>::operator/(const Unitless& divisor) const
{
    return Spherical<_body_>(_range / divisor, _inclination / divisor, _azimuth / divisor);
}

template <IsCelestialBody auto _body_>
Spherical<_body_>& Spherical<_body_>::operator/=(const Unitless& divisor)
{
    _range /= divisor;
    _inclination /= divisor;
    _azimuth /= divisor;
    return *this;
}

template <IsCelestialBody auto _body_>
Spherical<_body_>
    Spherical<_body_>::interpolate(const Time& thisTime, const Time& otherTime, const Spherical<_body_>& other, const Time& targetTime) const
{
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);
    const Angle interpInc =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _inclination, other.get_inclination() }, targetTime);
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);

    return Spherical<_body_>(interpRange, interpInc, interpAzimuth);
}

template <IsCelestialBody auto _body_>
RadiusVector<Spherical<_body_>::_fixed_frame_> Spherical<_body_>::get_position() const
{
    return convert_spherical_to_body_fixed<_fixed_frame_>(_range, _inclination, _azimuth);
}

template <IsCelestialBody auto _body_>
RadiusVector<Spherical<_body_>::_icrf_frame_> Spherical<_body_>::get_position(const Date& date) const
{
    return get_position().template in_frame<_icrf_frame_>(date);
}

template <IsCelestialBody auto _body_>
std::ostream& operator<<(std::ostream& os, Spherical<_body_> const& elements)
{
    os << "[";
    os << elements.get_range() << ", ";
    os << elements.get_inclination() << ", ";
    os << elements.get_azimuth();
    os << "] (Spherical)";
    return os;
}

} // namespace astro
} // namespace astrea
