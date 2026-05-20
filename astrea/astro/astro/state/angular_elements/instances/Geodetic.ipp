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
Geodetic<body>::Geodetic(const RadiusVector<_icrf_frame_>& rIcrf, const Date& date)
{
    *this = Geodetic<body>(rIcrf.template in_frame<_fixed_frame_>(date));
}

template <IsCelestialBody auto body>
Geodetic<body>::Geodetic(const RadiusVector<_fixed_frame_>& rFixed)
{
    std::tie(_latitude, _longitude, _altitude) =
        convertbodyfixed_to_geodetic(rFixed, get_equitorial_radius<body>(), get_polar_radius<body>());
}

// Copy constructor
template <IsCelestialBody auto body>
Geodetic<body>::Geodetic(const Geodetic<body>& other) :
    _latitude(other._latitude),
    _longitude(other._longitude),
    _altitude(other._altitude)
{
}

// Move constructor
template <IsCelestialBody auto body>
Geodetic<body>::Geodetic(Geodetic<body>&& other) noexcept :
    _latitude(std::move(other._latitude)),
    _longitude(std::move(other._longitude)),
    _altitude(std::move(other._altitude))
{
}

// Move assignment operator
template <IsCelestialBody auto body>
Geodetic<body>& Geodetic<body>::operator=(Geodetic<body>&& other) noexcept
{
    if (this != &other) {
        _latitude  = std::move(other._latitude);
        _longitude = std::move(other._longitude);
        _altitude  = std::move(other._altitude);
    }
    return *this;
}

// Copy assignment operator
template <IsCelestialBody auto body>
Geodetic<body>& Geodetic<body>::operator=(const Geodetic<body>& other)
{
    return *this = Geodetic<body>(other);
}

// Comparison operators
template <IsCelestialBody auto body>
bool Geodetic<body>::operator==(const Geodetic<body>& other) const
{
    return (_latitude == other._latitude && _longitude == other._longitude && _altitude == other._altitude);
}

template <IsCelestialBody auto body>
bool Geodetic<body>::operator!=(const Geodetic<body>& other) const
{
    return !(*this == other);
}

// Mathematical operators
template <IsCelestialBody auto body>
Geodetic<body> Geodetic<body>::operator+(const Geodetic<body>& other) const
{
    return Geodetic<body>(_latitude + other._latitude, _longitude + other._longitude, _altitude + other._altitude);
}

template <IsCelestialBody auto body>
Geodetic<body>& Geodetic<body>::operator+=(const Geodetic<body>& other)
{
    _latitude += other._latitude;
    _longitude += other._longitude;
    _altitude += other._altitude;
    return *this;
}

template <IsCelestialBody auto body>
Geodetic<body> Geodetic<body>::operator-(const Geodetic<body>& other) const
{
    return Geodetic<body>(_latitude - other._latitude, _longitude - other._longitude, _altitude - other._altitude);
}

template <IsCelestialBody auto body>
Geodetic<body>& Geodetic<body>::operator-=(const Geodetic<body>& other)
{
    _latitude -= other._latitude;
    _longitude -= other._longitude;
    _altitude -= other._altitude;
    return *this;
}

template <IsCelestialBody auto body>
Geodetic<body> Geodetic<body>::operator*(const Unitless& multiplier) const
{
    return Geodetic<body>(_latitude * multiplier, _longitude * multiplier, _altitude * multiplier);
}

template <IsCelestialBody auto body>
Geodetic<body>& Geodetic<body>::operator*=(const Unitless& multiplier)
{
    _latitude *= multiplier;
    _longitude *= multiplier;
    _altitude *= multiplier;
    return *this;
}

template <IsCelestialBody auto body>
std::vector<Unitless> Geodetic<body>::operator/(const Geodetic<body>& other) const
{
    return { _latitude / other._latitude, _longitude / other._longitude, _altitude / other._altitude };
}

template <IsCelestialBody auto body>
Geodetic<body> Geodetic<body>::operator/(const Unitless& divisor) const
{
    return Geodetic<body>(_latitude / divisor, _longitude / divisor, _altitude / divisor);
}

template <IsCelestialBody auto body>
Geodetic<body>& Geodetic<body>::operator/=(const Unitless& divisor)
{
    _latitude /= divisor;
    _longitude /= divisor;
    _altitude /= divisor;
    return *this;
}

template <IsCelestialBody auto body>
Geodetic<body>
    Geodetic<body>::interpolate(const Time& thisTime, const Time& otherTime, const Geodetic<body>& other, const Time& targetTime) const
{
    const Angle interpLat = math::interpolate<Time, Angle>({ thisTime, otherTime }, { _latitude, other.get_latitude() }, targetTime);
    const Angle interpLon =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _longitude, other.get_longitude() }, targetTime);
    const Distance interpAlt =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _altitude, other.get_altitude() }, targetTime);

    return Geodetic<body>(interpLat, interpLon, interpAlt);
}

template <IsCelestialBody auto body>
RadiusVector<Geodetic<body>::_fixed_frame_> Geodetic<body>::get_position() const
{
    return convert_geodetic_to_body_fixed<_fixed_frame_>(_latitude, _longitude, _altitude, get_equitorial_radius<body>(), get_polar_radius<body>());
}

template <IsCelestialBody auto body>
RadiusVector<Geodetic<body>::_icrf_frame_> Geodetic<body>::get_position(const Date& date) const
{
    return get_position().template in_frame<_icrf_frame_>(date);
}

template <IsCelestialBody auto body>
std::ostream& operator<<(std::ostream& os, Geodetic<body> const& elements)
{
    using mp_units::angular::unit_symbols::deg;
    using mp_units::si::unit_symbols::km;
    os << "[";
    os << elements.get_latitude().in(deg) << ", ";
    os << elements.get_longitude().in(deg);
    if (elements.get_altitude() != 0.0 * km) { os << ", " << elements.get_altitude(); }
    os << "] (Geodetic)";
    return os;
}

} // namespace astro
} // namespace astrea
