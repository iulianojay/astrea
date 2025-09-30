#include <astro/state/angular_elements/instances/Spherical.hpp>

#include <iomanip>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
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

Spherical::Spherical(const RadiusVector<frames::earth::icrf>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Spherical(rEci.in_frame<frames::earth::earth_fixed>(date), parent);
}

Spherical::Spherical(const RadiusVector<frames::earth::earth_fixed>& rEcef, const CelestialBody* parent)
{
    std::tie(_range, _inclination, _azimuth) = convert_earth_fixed_to_spherical(rEcef);
}

// Copy constructor
Spherical::Spherical(const Spherical& other) :
    _range(other._range),
    _inclination(other._inclination),
    _azimuth(other._azimuth)
{
}

// Move constructor
Spherical::Spherical(Spherical&& other) noexcept :
    _range(std::move(other._range)),
    _inclination(std::move(other._inclination)),
    _azimuth(std::move(other._azimuth))
{
}

// Move assignment operator
Spherical& Spherical::operator=(Spherical&& other) noexcept
{
    if (this != &other) {
        _range       = std::move(other._range);
        _inclination = std::move(other._inclination);
        _azimuth     = std::move(other._azimuth);
    }
    return *this;
}

// Copy assignment operator
Spherical& Spherical::operator=(const Spherical& other) { return *this = Spherical(other); }

// Comparitors operators
bool Spherical::operator==(const Spherical& other) const
{
    return (_range == other._range && _inclination == other._inclination && _azimuth == other._azimuth);
}

bool Spherical::operator!=(const Spherical& other) const { return !(*this == other); }


// Mathmatical operators
Spherical Spherical::operator+(const Spherical& other) const
{
    return Spherical(_range + other._range, _inclination + other._inclination, _azimuth + other._azimuth);
}
Spherical& Spherical::operator+=(const Spherical& other)
{
    _range += other._range;
    _inclination += other._inclination;
    _azimuth += other._azimuth;
    return *this;
}

Spherical Spherical::operator-(const Spherical& other) const
{
    return Spherical(_range - other._range, _inclination - other._inclination, _azimuth - other._azimuth);
}
Spherical& Spherical::operator-=(const Spherical& other)
{
    _range -= other._range;
    _inclination -= other._inclination;
    _azimuth -= other._azimuth;
    return *this;
}

Spherical Spherical::operator*(const Unitless& multiplier) const
{
    return Spherical(_range * multiplier, _inclination * multiplier, _azimuth * multiplier);
}
Spherical& Spherical::operator*=(const Unitless& multiplier)
{
    _range *= multiplier;
    _inclination *= multiplier;
    _azimuth *= multiplier;
    return *this;
}

std::vector<Unitless> Spherical::operator/(const Spherical& other) const
{
    return { _range / other._range, _inclination / other._inclination, _azimuth / other._azimuth };
}

Spherical Spherical::operator/(const Unitless& divisor) const
{
    return Spherical(_range / divisor, _inclination / divisor, _azimuth / divisor);
}
Spherical& Spherical::operator/=(const Unitless& divisor)
{
    _range /= divisor;
    _inclination /= divisor;
    _azimuth /= divisor;
    return *this;
}

Spherical Spherical::interpolate(const Time& thisTime, const Time& otherTime, const Spherical& other, const Time& targetTime) const
{
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);
    const Angle interpInc =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _inclination, other.get_inclination() }, targetTime);
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);

    return Spherical(interpRange, interpInc, interpAzimuth);
}

RadiusVector<frames::earth::earth_fixed> Spherical::get_position(const CelestialBody* parent) const
{
    return convert_spherical_to_earth_fixed(_range, _inclination, _azimuth);
}

RadiusVector<frames::earth::icrf> Spherical::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<frames::earth::icrf>(date);
}

std::ostream& operator<<(std::ostream& os, Spherical const& elements)
{
    os << "[";
    os << elements.get_range() << ", ";
    os << elements.get_inclination() << ", ";
    os << elements.get_azimuth();
    os << "] (Spherical)";
    return os;
}


std::tuple<Distance, Angle, Angle> convert_earth_fixed_to_spherical(const RadiusVector<frames::earth::earth_fixed>& rEcef)
{
    const Distance range    = rEcef.norm();
    const Angle inclination = acos(rEcef.get_z() / range);

    const Distance& x = rEcef.get_x();
    const Distance& y = rEcef.get_y();

    Angle azimuth;
    if (x == 0.0 * km && y == 0.0 * km) { azimuth = 0.0 * rad; }
    else {
        azimuth = acos(x / sqrt(x * x + y * y));
        if (y < 0.0 * km) { azimuth = -azimuth; }
    }
    return std::make_tuple(range, inclination, azimuth);
}


RadiusVector<frames::earth::earth_fixed>
    convert_spherical_to_earth_fixed(const Distance& range, const Angle& inclination, const Angle& azimuth)
{
    const auto x = range * sin(inclination) * cos(azimuth);
    const auto y = range * sin(inclination) * sin(azimuth);
    const auto z = range * cos(inclination);
    return RadiusVector<frames::earth::earth_fixed>(x, y, z);
}

} // namespace astro
} // namespace astrea