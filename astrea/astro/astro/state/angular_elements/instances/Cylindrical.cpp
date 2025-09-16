#include <astro/state/angular_elements/instances/Cylindrical.hpp>

#include <iomanip>
#include <iostream>

// mp-units
#include <mp-units/math.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

Cylindrical::Cylindrical(const RadiusVector<ECI>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Cylindrical(rEci.in_frame<ECEF>(date), parent);
}

Cylindrical::Cylindrical(const RadiusVector<ECEF>& rEcef, const CelestialBody* parent)
{
    std::tie(_range, _azimuth, _elevation) = convert_earth_fixed_to_cylindrical(rEcef);
}

// Copy constructor
Cylindrical::Cylindrical(const Cylindrical& other) :
    _range(other._range),
    _azimuth(other._azimuth),
    _elevation(other._elevation)
{
}

// Move constructor
Cylindrical::Cylindrical(Cylindrical&& other) noexcept :
    _range(std::move(other._range)),
    _azimuth(std::move(other._azimuth)),
    _elevation(std::move(other._elevation))
{
}

// Move assignment operator
Cylindrical& Cylindrical::operator=(Cylindrical&& other) noexcept
{
    if (this != &other) {
        _range     = std::move(other._range);
        _azimuth   = std::move(other._azimuth);
        _elevation = std::move(other._elevation);
    }
    return *this;
}

// Copy assignment operator
Cylindrical& Cylindrical::operator=(const Cylindrical& other) { return *this = Cylindrical(other); }

// Comparitors operators
bool Cylindrical::operator==(const Cylindrical& other) const
{
    return (_range == other._range && _azimuth == other._azimuth && _elevation == other._elevation);
}

bool Cylindrical::operator!=(const Cylindrical& other) const { return !(*this == other); }


// Mathmatical operators
Cylindrical Cylindrical::operator+(const Cylindrical& other) const
{
    return Cylindrical(_range + other._range, _azimuth + other._azimuth, _elevation + other._elevation);
}
Cylindrical& Cylindrical::operator+=(const Cylindrical& other)
{
    _range += other._range;
    _azimuth += other._azimuth;
    _elevation += other._elevation;
    return *this;
}

Cylindrical Cylindrical::operator-(const Cylindrical& other) const
{
    return Cylindrical(_range - other._range, _azimuth - other._azimuth, _elevation - other._elevation);
}
Cylindrical& Cylindrical::operator-=(const Cylindrical& other)
{
    _range -= other._range;
    _azimuth -= other._azimuth;
    _elevation -= other._elevation;
    return *this;
}

Cylindrical Cylindrical::operator*(const Unitless& multiplier) const
{
    return Cylindrical(_range * multiplier, _azimuth * multiplier, _elevation * multiplier);
}
Cylindrical& Cylindrical::operator*=(const Unitless& multiplier)
{
    _range *= multiplier;
    _azimuth *= multiplier;
    _elevation *= multiplier;
    return *this;
}

std::vector<Unitless> Cylindrical::operator/(const Cylindrical& other) const
{
    return { _range / other._range, _azimuth / other._azimuth, _elevation / other._elevation };
}

Cylindrical Cylindrical::operator/(const Unitless& divisor) const
{
    return Cylindrical(_range / divisor, _azimuth / divisor, _elevation / divisor);
}
Cylindrical& Cylindrical::operator/=(const Unitless& divisor)
{
    _range /= divisor;
    _azimuth /= divisor;
    _elevation /= divisor;
    return *this;
}

Cylindrical Cylindrical::interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical& other, const Time& targetTime) const
{
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);
    const Distance interpElev =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _elevation, other.get_elevation() }, targetTime);

    return Cylindrical(interpRange, interpAzimuth, interpElev);
}

RadiusVector<ECEF> Cylindrical::get_position(const CelestialBody* parent) const
{
    return convert_cylindrical_to_earth_fixed(_range, _azimuth, _elevation);
}

RadiusVector<ECI> Cylindrical::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<ECI>(date);
}

std::ostream& operator<<(std::ostream& os, Cylindrical const& elements)
{
    os << "[";
    os << elements.get_range() << ", ";
    os << elements.get_azimuth() << ", ";
    os << elements.get_elevation();
    os << "] (Cylindrical)";
    return os;
}


std::tuple<Distance, Angle, Distance> convert_earth_fixed_to_cylindrical(const RadiusVector<EarthCenteredEarthFixed>& rEcef)
{
    const Distance range     = rEcef.norm();
    const Distance elevation = rEcef.get_z();
    Angle azimuth = acos(rEcef.get_x() / sqrt(rEcef.get_x() * rEcef.get_x() + rEcef.get_y() * rEcef.get_y()));
    if (rEcef.get_y() < 0 * km) { azimuth = -azimuth; }
    return { range, azimuth, elevation };
}


RadiusVector<EarthCenteredEarthFixed>
    convert_cylindrical_to_earth_fixed(const Distance& range, const Angle& azimuth, const Distance& elevation)
{
    const auto x = range * cos(azimuth);
    const auto y = range * sin(azimuth);
    const auto z = elevation;
    return RadiusVector<ECEF>(x, y, z);
}

} // namespace astro
} // namespace astrea