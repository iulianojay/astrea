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

#include <astro/state/angular_elements/instances/Geodetic.hpp>

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

Geodetic::Geodetic(const RadiusVector<frames::earth::icrf>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Geodetic(rEci.in_frame<frames::earth::earth_fixed>(date), parent);
}

Geodetic::Geodetic(const RadiusVector<frames::earth::earth_fixed>& rEcef, const CelestialBody* parent)
{
    std::tie(_latitude, _longitude, _altitude) =
        convert_body_fixed_to_geodetic(rEcef, parent->get_equitorial_radius(), parent->get_polar_radius());
}

// Copy constructor
Geodetic::Geodetic(const Geodetic& other) :
    _latitude(other._latitude),
    _longitude(other._longitude),
    _altitude(other._altitude)
{
}

// Move constructor
Geodetic::Geodetic(Geodetic&& other) noexcept :
    _latitude(std::move(other._latitude)),
    _longitude(std::move(other._longitude)),
    _altitude(std::move(other._altitude))
{
}

// Move assignment operator
Geodetic& Geodetic::operator=(Geodetic&& other) noexcept
{
    if (this != &other) {
        _latitude  = std::move(other._latitude);
        _longitude = std::move(other._longitude);
        _altitude  = std::move(other._altitude);
    }
    return *this;
}

// Copy assignment operator
Geodetic& Geodetic::operator=(const Geodetic& other) { return *this = Geodetic(other); }

// Comparitors operators
bool Geodetic::operator==(const Geodetic& other) const
{
    return (_latitude == other._latitude && _longitude == other._longitude && _altitude == other._altitude);
}

bool Geodetic::operator!=(const Geodetic& other) const { return !(*this == other); }


// Mathmatical operators
Geodetic Geodetic::operator+(const Geodetic& other) const
{
    return Geodetic(_latitude + other._latitude, _longitude + other._longitude, _altitude + other._altitude);
}
Geodetic& Geodetic::operator+=(const Geodetic& other)
{
    _latitude += other._latitude;
    _longitude += other._longitude;
    _altitude += other._altitude;
    return *this;
}

Geodetic Geodetic::operator-(const Geodetic& other) const
{
    return Geodetic(_latitude - other._latitude, _longitude - other._longitude, _altitude - other._altitude);
}
Geodetic& Geodetic::operator-=(const Geodetic& other)
{
    _latitude -= other._latitude;
    _longitude -= other._longitude;
    _altitude -= other._altitude;
    return *this;
}

Geodetic Geodetic::operator*(const Unitless& multiplier) const
{
    return Geodetic(_latitude * multiplier, _longitude * multiplier, _altitude * multiplier);
}
Geodetic& Geodetic::operator*=(const Unitless& multiplier)
{
    _latitude *= multiplier;
    _longitude *= multiplier;
    _altitude *= multiplier;
    return *this;
}

std::vector<Unitless> Geodetic::operator/(const Geodetic& other) const
{
    return { _latitude / other._latitude, _longitude / other._longitude, _altitude / other._altitude };
}

Geodetic Geodetic::operator/(const Unitless& divisor) const
{
    return Geodetic(_latitude / divisor, _longitude / divisor, _altitude / divisor);
}
Geodetic& Geodetic::operator/=(const Unitless& divisor)
{
    _latitude /= divisor;
    _longitude /= divisor;
    _altitude /= divisor;
    return *this;
}

Geodetic Geodetic::interpolate(const Time& thisTime, const Time& otherTime, const Geodetic& other, const Time& targetTime) const
{
    const Angle interpLat = math::interpolate<Time, Angle>({ thisTime, otherTime }, { _latitude, other.get_latitude() }, targetTime);
    const Angle interpLon =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _longitude, other.get_longitude() }, targetTime);
    const Distance interpAlt =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _altitude, other.get_altitude() }, targetTime);

    return Geodetic(interpLat, interpLon, interpAlt);
}

RadiusVector<frames::earth::earth_fixed> Geodetic::get_position(const CelestialBody* parent) const
{
    return convert_geodetic_to_body_fixed<frames::earth::earth_fixed>(
        _latitude, _longitude, _altitude, parent->get_equitorial_radius(), parent->get_polar_radius()
    );
}

RadiusVector<frames::earth::icrf> Geodetic::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<frames::earth::icrf>(date);
}

std::ostream& operator<<(std::ostream& os, Geodetic const& elements)
{
    os << "[";
    os << elements.get_latitude().in(deg) << ", ";
    os << elements.get_longitude().in(deg);
    if (elements.get_altitude() != 0.0 * km) { os << ", " << elements.get_altitude(); }
    os << "] (Geodetic)";
    return os;
}

} // namespace astro
} // namespace astrea