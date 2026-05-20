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

template <IsCelestialBody auto body>
Spherical<body>::Spherical(const RadiusVector<_icrf_frame_>& rIcrf, const Date& date)
{
    *this = Spherical<body>(rIcrf.template in_frame<_fixed_frame_>(date));
}

template <IsCelestialBody auto body>
Spherical<body>::Spherical(const RadiusVector<_fixed_frame_>& rFixed)
{
    std::tie(_range, _inclination, _azimuth) = convertbodyfixed_to_spherical(rFixed);
}

// Copy constructor
template <IsCelestialBody auto body>
Spherical<body>::Spherical(const Spherical<body>& other) :
    _range(other._range),
    _inclination(other._inclination),
    _azimuth(other._azimuth)
{
}

// Move constructor
template <IsCelestialBody auto body>
Spherical<body>::Spherical(Spherical<body>&& other) noexcept :
    _range(std::move(other._range)),
    _inclination(std::move(other._inclination)),
    _azimuth(std::move(other._azimuth))
{
}

// Move assignment operator
template <IsCelestialBody auto body>
Spherical<body>& Spherical<body>::operator=(Spherical<body>&& other) noexcept
{
    if (this != &other) {
        _range       = std::move(other._range);
        _inclination = std::move(other._inclination);
        _azimuth     = std::move(other._azimuth);
    }
    return *this;
}

// Copy assignment operator
template <IsCelestialBody auto body>
Spherical<body>& Spherical<body>::operator=(const Spherical<body>& other)
{
    return *this = Spherical<body>(other);
}

// Comparison operators
template <IsCelestialBody auto body>
bool Spherical<body>::operator==(const Spherical<body>& other) const
{
    return (_range == other._range && _inclination == other._inclination && _azimuth == other._azimuth);
}

template <IsCelestialBody auto body>
bool Spherical<body>::operator!=(const Spherical<body>& other) const
{
    return !(*this == other);
}

// Mathematical operators
template <IsCelestialBody auto body>
Spherical<body> Spherical<body>::operator+(const Spherical<body>& other) const
{
    return Spherical<body>(_range + other._range, _inclination + other._inclination, _azimuth + other._azimuth);
}

template <IsCelestialBody auto body>
Spherical<body>& Spherical<body>::operator+=(const Spherical<body>& other)
{
    _range += other._range;
    _inclination += other._inclination;
    _azimuth += other._azimuth;
    return *this;
}

template <IsCelestialBody auto body>
Spherical<body> Spherical<body>::operator-(const Spherical<body>& other) const
{
    return Spherical<body>(_range - other._range, _inclination - other._inclination, _azimuth - other._azimuth);
}

template <IsCelestialBody auto body>
Spherical<body>& Spherical<body>::operator-=(const Spherical<body>& other)
{
    _range -= other._range;
    _inclination -= other._inclination;
    _azimuth -= other._azimuth;
    return *this;
}

template <IsCelestialBody auto body>
Spherical<body> Spherical<body>::operator*(const Unitless& multiplier) const
{
    return Spherical<body>(_range * multiplier, _inclination * multiplier, _azimuth * multiplier);
}

template <IsCelestialBody auto body>
Spherical<body>& Spherical<body>::operator*=(const Unitless& multiplier)
{
    _range *= multiplier;
    _inclination *= multiplier;
    _azimuth *= multiplier;
    return *this;
}

template <IsCelestialBody auto body>
std::vector<Unitless> Spherical<body>::operator/(const Spherical<body>& other) const
{
    return { _range / other._range, _inclination / other._inclination, _azimuth / other._azimuth };
}

template <IsCelestialBody auto body>
Spherical<body> Spherical<body>::operator/(const Unitless& divisor) const
{
    return Spherical<body>(_range / divisor, _inclination / divisor, _azimuth / divisor);
}

template <IsCelestialBody auto body>
Spherical<body>& Spherical<body>::operator/=(const Unitless& divisor)
{
    _range /= divisor;
    _inclination /= divisor;
    _azimuth /= divisor;
    return *this;
}

template <IsCelestialBody auto body>
Spherical<body>
    Spherical<body>::interpolate(const Time& thisTime, const Time& otherTime, const Spherical<body>& other, const Time& targetTime) const
{
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);
    const Angle interpInc =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _inclination, other.get_inclination() }, targetTime);
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);

    return Spherical<body>(interpRange, interpInc, interpAzimuth);
}

template <IsCelestialBody auto body>
RadiusVector<Spherical<body>::_fixed_frame_> Spherical<body>::get_position() const
{
    return convert_spherical_tobodyfixed<_fixed_frame_>(_range, _inclination, _azimuth);
}

template <IsCelestialBody auto body>
RadiusVector<Spherical<body>::_icrf_frame_> Spherical<body>::get_position(const Date& date) const
{
    return get_position().template in_frame<_icrf_frame_>(date);
}

template <IsCelestialBody auto body>
std::ostream& operator<<(std::ostream& os, Spherical<body> const& elements)
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
