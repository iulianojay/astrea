

# File Geodetic.ipp

[**File List**](files.md) **>** [**angular\_elements**](dir_8f2f7499654791f4fc4240f01fb9baf6.md) **>** [**Geodetic.ipp**](Geodetic_8ipp.md)

[Go to the documentation of this file](Geodetic_8ipp.md)


```C++
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

#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/transformations.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>


namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_>
template <auto _frame_>
    requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
Geodetic<_body_>::Geodetic(const RadiusVector<_frame_>& rIcrf, const Date& date)
{
    *this = Geodetic<_body_>(rIcrf.template in_frame<_fixed_frame_>(date));
}

template <IsCelestialBody auto _body_>
Geodetic<_body_>::Geodetic(const RadiusVector<_fixed_frame_>& rFixed)
{
    std::tie(_latitude, _longitude, _altitude) = convert_body_fixed_to_geodetic(rFixed);
}

// Copy constructor
template <IsCelestialBody auto _body_>
Geodetic<_body_>::Geodetic(const Geodetic<_body_>& other) :
    _latitude(other._latitude),
    _longitude(other._longitude),
    _altitude(other._altitude)
{
}

// Move constructor
template <IsCelestialBody auto _body_>
Geodetic<_body_>::Geodetic(Geodetic<_body_>&& other) noexcept :
    _latitude(std::move(other._latitude)),
    _longitude(std::move(other._longitude)),
    _altitude(std::move(other._altitude))
{
}

// Move assignment operator
template <IsCelestialBody auto _body_>
Geodetic<_body_>& Geodetic<_body_>::operator=(Geodetic<_body_>&& other) noexcept
{
    if (this != &other) {
        _latitude  = std::move(other._latitude);
        _longitude = std::move(other._longitude);
        _altitude  = std::move(other._altitude);
    }
    return *this;
}

// Copy assignment operator
template <IsCelestialBody auto _body_>
Geodetic<_body_>& Geodetic<_body_>::operator=(const Geodetic<_body_>& other)
{
    return *this = Geodetic<_body_>(other);
}

// Comparison operators
template <IsCelestialBody auto _body_>
bool Geodetic<_body_>::operator==(const Geodetic<_body_>& other) const
{
    return (_latitude == other._latitude && _longitude == other._longitude && _altitude == other._altitude);
}

template <IsCelestialBody auto _body_>
bool Geodetic<_body_>::operator!=(const Geodetic<_body_>& other) const
{
    return !(*this == other);
}

// Mathematical operators
template <IsCelestialBody auto _body_>
Geodetic<_body_> Geodetic<_body_>::operator+(const Geodetic<_body_>& other) const
{
    return Geodetic<_body_>(_latitude + other._latitude, _longitude + other._longitude, _altitude + other._altitude);
}

template <IsCelestialBody auto _body_>
Geodetic<_body_>& Geodetic<_body_>::operator+=(const Geodetic<_body_>& other)
{
    _latitude += other._latitude;
    _longitude += other._longitude;
    _altitude += other._altitude;
    return *this;
}

template <IsCelestialBody auto _body_>
Geodetic<_body_> Geodetic<_body_>::operator-(const Geodetic<_body_>& other) const
{
    return Geodetic<_body_>(_latitude - other._latitude, _longitude - other._longitude, _altitude - other._altitude);
}

template <IsCelestialBody auto _body_>
Geodetic<_body_>& Geodetic<_body_>::operator-=(const Geodetic<_body_>& other)
{
    _latitude -= other._latitude;
    _longitude -= other._longitude;
    _altitude -= other._altitude;
    return *this;
}

template <IsCelestialBody auto _body_>
Geodetic<_body_> Geodetic<_body_>::operator*(const Unitless& multiplier) const
{
    return Geodetic<_body_>(_latitude * multiplier, _longitude * multiplier, _altitude * multiplier);
}

template <IsCelestialBody auto _body_>
Geodetic<_body_>& Geodetic<_body_>::operator*=(const Unitless& multiplier)
{
    _latitude *= multiplier;
    _longitude *= multiplier;
    _altitude *= multiplier;
    return *this;
}

template <IsCelestialBody auto _body_>
std::vector<Unitless> Geodetic<_body_>::operator/(const Geodetic<_body_>& other) const
{
    return { _latitude / other._latitude, _longitude / other._longitude, _altitude / other._altitude };
}

template <IsCelestialBody auto _body_>
Geodetic<_body_> Geodetic<_body_>::operator/(const Unitless& divisor) const
{
    return Geodetic<_body_>(_latitude / divisor, _longitude / divisor, _altitude / divisor);
}

template <IsCelestialBody auto _body_>
Geodetic<_body_>& Geodetic<_body_>::operator/=(const Unitless& divisor)
{
    _latitude /= divisor;
    _longitude /= divisor;
    _altitude /= divisor;
    return *this;
}

template <IsCelestialBody auto _body_>
Geodetic<_body_>
    Geodetic<_body_>::interpolate(const Time& thisTime, const Time& otherTime, const Geodetic<_body_>& other, const Time& targetTime) const
{
    const Angle interpLat = math::interpolate<Time, Angle>({ thisTime, otherTime }, { _latitude, other.get_latitude() }, targetTime);
    const Angle interpLon =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _longitude, other.get_longitude() }, targetTime);
    const Distance interpAlt =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _altitude, other.get_altitude() }, targetTime);

    return Geodetic<_body_>(interpLat, interpLon, interpAlt);
}

template <IsCelestialBody auto _body_>
RadiusVector<Geodetic<_body_>::_fixed_frame_> Geodetic<_body_>::get_position() const
{
    return convert_geodetic_to_body_fixed<_fixed_frame_>(_latitude, _longitude, _altitude);
}

template <IsCelestialBody auto _body_>
RadiusVector<Geodetic<_body_>::_icrf_frame_> Geodetic<_body_>::get_position(const Date& date) const
{
    return get_position().template in_frame<_icrf_frame_>(date);
}

template <IsCelestialBody auto _body_>
std::ostream& operator<<(std::ostream& os, Geodetic<_body_> const& elements)
{
    using mp_units::si::unit_symbols::deg;
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
```


