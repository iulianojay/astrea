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

#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>


namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_>
Cylindrical<_body_>::Cylindrical(const RadiusVector<_icrf_frame_>& rIcrf, const Date& date)
{
    *this = Cylindrical<_body_>(rIcrf.template in_frame<_fixed_frame_>(date));
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_>::Cylindrical(const RadiusVector<_fixed_frame_>& rFixed)
{
    std::tie(_range, _azimuth, _elevation) = convert_body_fixed_to_cylindrical(rFixed);
}

// Copy constructor
template <IsCelestialBody auto _body_>
Cylindrical<_body_>::Cylindrical(const Cylindrical<_body_>& other) :
    _range(other._range),
    _azimuth(other._azimuth),
    _elevation(other._elevation)
{
}

// Move constructor
template <IsCelestialBody auto _body_>
Cylindrical<_body_>::Cylindrical(Cylindrical<_body_>&& other) noexcept :
    _range(std::move(other._range)),
    _azimuth(std::move(other._azimuth)),
    _elevation(std::move(other._elevation))
{
}

// Move assignment operator
template <IsCelestialBody auto _body_>
Cylindrical<_body_>& Cylindrical<_body_>::operator=(Cylindrical<_body_>&& other) noexcept
{
    if (this != &other) {
        _range     = std::move(other._range);
        _azimuth   = std::move(other._azimuth);
        _elevation = std::move(other._elevation);
    }
    return *this;
}

// Copy assignment operator
template <IsCelestialBody auto _body_>
Cylindrical<_body_>& Cylindrical<_body_>::operator=(const Cylindrical<_body_>& other)
{
    return *this = Cylindrical<_body_>(other);
}

// Comparison operators
template <IsCelestialBody auto _body_>
bool Cylindrical<_body_>::operator==(const Cylindrical<_body_>& other) const
{
    return (_range == other._range && _azimuth == other._azimuth && _elevation == other._elevation);
}

template <IsCelestialBody auto _body_>
bool Cylindrical<_body_>::operator!=(const Cylindrical<_body_>& other) const
{
    return !(*this == other);
}

// Mathematical operators
template <IsCelestialBody auto _body_>
Cylindrical<_body_> Cylindrical<_body_>::operator+(const Cylindrical<_body_>& other) const
{
    return Cylindrical<_body_>(_range + other._range, _azimuth + other._azimuth, _elevation + other._elevation);
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_>& Cylindrical<_body_>::operator+=(const Cylindrical<_body_>& other)
{
    _range += other._range;
    _azimuth += other._azimuth;
    _elevation += other._elevation;
    return *this;
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_> Cylindrical<_body_>::operator-(const Cylindrical<_body_>& other) const
{
    return Cylindrical<_body_>(_range - other._range, _azimuth - other._azimuth, _elevation - other._elevation);
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_>& Cylindrical<_body_>::operator-=(const Cylindrical<_body_>& other)
{
    _range -= other._range;
    _azimuth -= other._azimuth;
    _elevation -= other._elevation;
    return *this;
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_> Cylindrical<_body_>::operator*(const Unitless& multiplier) const
{
    return Cylindrical<_body_>(_range * multiplier, _azimuth * multiplier, _elevation * multiplier);
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_>& Cylindrical<_body_>::operator*=(const Unitless& multiplier)
{
    _range *= multiplier;
    _azimuth *= multiplier;
    _elevation *= multiplier;
    return *this;
}

template <IsCelestialBody auto _body_>
std::vector<Unitless> Cylindrical<_body_>::operator/(const Cylindrical<_body_>& other) const
{
    return { _range / other._range, _azimuth / other._azimuth, _elevation / other._elevation };
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_> Cylindrical<_body_>::operator/(const Unitless& divisor) const
{
    return Cylindrical<_body_>(_range / divisor, _azimuth / divisor, _elevation / divisor);
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_>& Cylindrical<_body_>::operator/=(const Unitless& divisor)
{
    _range /= divisor;
    _azimuth /= divisor;
    _elevation /= divisor;
    return *this;
}

template <IsCelestialBody auto _body_>
Cylindrical<_body_>
    Cylindrical<_body_>::interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical<_body_>& other, const Time& targetTime) const
{
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);
    const Distance interpElev =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _elevation, other.get_elevation() }, targetTime);

    return Cylindrical<_body_>(interpRange, interpAzimuth, interpElev);
}

template <IsCelestialBody auto _body_>
RadiusVector<Cylindrical<_body_>::_fixed_frame_> Cylindrical<_body_>::get_position() const
{
    return convert_cylindrical_to_body_fixed<_fixed_frame_>(_range, _azimuth, _elevation);
}

template <IsCelestialBody auto _body_>
RadiusVector<Cylindrical<_body_>::_icrf_frame_> Cylindrical<_body_>::get_position(const Date& date) const
{
    return get_position().template in_frame<_icrf_frame_>(date);
}

template <IsCelestialBody auto _body_>
std::ostream& operator<<(std::ostream& os, Cylindrical<_body_> const& elements)
{
    os << "[";
    os << elements.get_range() << ", ";
    os << elements.get_azimuth() << ", ";
    os << elements.get_elevation();
    os << "] (Cylindrical)";
    return os;
}

} // namespace astro
} // namespace astrea
