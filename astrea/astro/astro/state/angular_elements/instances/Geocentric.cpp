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

#include <astro/state/angular_elements/instances/Geocentric.hpp>

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
#include <astro/systems/system_utilities>
#include <astro/types/typedefs.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::mm;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

Geocentric::Geocentric(const RadiusVector<frames::earth::icrf>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Geocentric(rEci.in_frame<frames::earth::earth_fixed>(date), parent);
}

Geocentric::Geocentric(const RadiusVector<frames::earth::earth_fixed>& rEcef, const CelestialBody* parent)
{
    std::tie(_latitude, _longitude, _altitude) =
        convert_body_fixed_to_geocentric(rEcef, parent->get_equitorial_radius(), parent->get_polar_radius());
}

// Copy constructor
Geocentric::Geocentric(const Geocentric& other) :
    _latitude(other._latitude),
    _longitude(other._longitude),
    _altitude(other._altitude)
{
}

// Move constructor
Geocentric::Geocentric(Geocentric&& other) noexcept :
    _latitude(std::move(other._latitude)),
    _longitude(std::move(other._longitude)),
    _altitude(std::move(other._altitude))
{
}

// Move assignment operator
Geocentric& Geocentric::operator=(Geocentric&& other) noexcept
{
    if (this != &other) {
        _latitude  = std::move(other._latitude);
        _longitude = std::move(other._longitude);
        _altitude  = std::move(other._altitude);
    }
    return *this;
}

// Copy assignment operator
Geocentric& Geocentric::operator=(const Geocentric& other) { return *this = Geocentric(other); }

// Comparitors operators
bool Geocentric::operator==(const Geocentric& other) const
{
    return (_latitude == other._latitude && _longitude == other._longitude && _altitude == other._altitude);
}

bool Geocentric::operator!=(const Geocentric& other) const { return !(*this == other); }


// Mathmatical operators
Geocentric Geocentric::operator+(const Geocentric& other) const
{
    return Geocentric(_latitude + other._latitude, _longitude + other._longitude, _altitude + other._altitude);
}
Geocentric& Geocentric::operator+=(const Geocentric& other)
{
    _latitude += other._latitude;
    _longitude += other._longitude;
    _altitude += other._altitude;
    return *this;
}

Geocentric Geocentric::operator-(const Geocentric& other) const
{
    return Geocentric(_latitude - other._latitude, _longitude - other._longitude, _altitude - other._altitude);
}
Geocentric& Geocentric::operator-=(const Geocentric& other)
{
    _latitude -= other._latitude;
    _longitude -= other._longitude;
    _altitude -= other._altitude;
    return *this;
}

Geocentric Geocentric::operator*(const Unitless& multiplier) const
{
    return Geocentric(_latitude * multiplier, _longitude * multiplier, _altitude * multiplier);
}
Geocentric& Geocentric::operator*=(const Unitless& multiplier)
{
    _latitude *= multiplier;
    _longitude *= multiplier;
    _altitude *= multiplier;
    return *this;
}

std::vector<Unitless> Geocentric::operator/(const Geocentric& other) const
{
    return { _latitude / other._latitude, _longitude / other._longitude, _altitude / other._altitude };
}

Geocentric Geocentric::operator/(const Unitless& divisor) const
{
    return Geocentric(_latitude / divisor, _longitude / divisor, _altitude / divisor);
}
Geocentric& Geocentric::operator/=(const Unitless& divisor)
{
    _latitude /= divisor;
    _longitude /= divisor;
    _altitude /= divisor;
    return *this;
}

Geocentric Geocentric::interpolate(const Time& thisTime, const Time& otherTime, const Geocentric& other, const Time& targetTime) const
{
    const Angle interpLat = math::interpolate<Time, Angle>({ thisTime, otherTime }, { _latitude, other.get_latitude() }, targetTime);
    const Angle interpLon =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _longitude, other.get_longitude() }, targetTime);
    const Distance interpAlt =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _altitude, other.get_altitude() }, targetTime);

    return Geocentric(interpLat, interpLon, interpAlt);
}

RadiusVector<frames::earth::earth_fixed> Geocentric::get_position(const CelestialBody* parent) const
{
    return convert_geocentric_to_body_fixed<frames::earth::earth_fixed>(
        _latitude, _longitude, _altitude, parent->get_equitorial_radius(), parent->get_polar_radius()
    );
}

RadiusVector<frames::earth::icrf> Geocentric::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<frames::earth::icrf>(date);
}

std::ostream& operator<<(std::ostream& os, Geocentric const& elements)
{
    os << "[";
    os << elements.get_latitude().in(deg) << ", ";
    os << elements.get_longitude().in(deg);
    if (elements.get_altitude() != 0.0 * km) { os << ", " << elements.get_altitude(); }
    os << "] (Geocentric)";
    return os;
}

Distance calculate_geocentric_radius(const Angle& lat, const Distance& rEquitorial, const Distance& rPolar)
{
    const Distance& a       = rEquitorial;
    const Distance& b       = rPolar;
    const Unitless cosLatSq = pow<2>(cos(lat));
    const Unitless sinLatSq = pow<2>(sin(lat));
    return sqrt((pow<4>(a) * cosLatSq + pow<4>(b) * sinLatSq) / (pow<2>(a) * cosLatSq + pow<2>(b) * sinLatSq));
}

} // namespace astro
} // namespace astrea