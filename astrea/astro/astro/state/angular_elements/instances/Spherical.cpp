#include <astro/state/angular_elements/instances/Spherical.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
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

Spherical::Spherical(const RadiusVector<ECI>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Spherical(rEci.in_frame<ECEF>(date), parent);
}

Spherical::Spherical(const RadiusVector<ECEF>& rEcef, const CelestialBody* parent)
{
    _range       = rEcef.norm();
    _inclination = acos(rEcef.get_z() / _range);
    _azimuth     = acos(rEcef.get_x() / sqrt(rEcef.get_x() * rEcef.get_x() + rEcef.get_y() * rEcef.get_y()));
    if (rEcef.get_y() < 0 * km) { _azimuth = -_azimuth; }
}

// Copy constructor
Spherical::Spherical(const Spherical& other) :
    _azimuth(other._azimuth),
    _inclination(other._inclination),
    _range(other._range)
{
}

// Move constructor
Spherical::Spherical(Spherical&& other) noexcept :
    _azimuth(std::move(other._azimuth)),
    _inclination(std::move(other._inclination)),
    _range(std::move(other._range))
{
}

// Move assignment operator
Spherical& Spherical::operator=(Spherical&& other) noexcept
{
    if (this != &other) {
        _azimuth     = std::move(other._azimuth);
        _inclination = std::move(other._inclination);
        _range       = std::move(other._range);
    }
    return *this;
}

// Copy assignment operator
Spherical& Spherical::operator=(const Spherical& other) { return *this = Spherical(other); }

// Comparitors operators
bool Spherical::operator==(const Spherical& other) const
{
    return (_azimuth == other._azimuth && _inclination == other._inclination && _range == other._range);
}

bool Spherical::operator!=(const Spherical& other) const { return !(*this == other); }


// Mathmatical operators
Spherical Spherical::operator+(const Spherical& other) const
{
    return Spherical(_azimuth + other._azimuth, _inclination + other._inclination, _range + other._range);
}
Spherical& Spherical::operator+=(const Spherical& other)
{
    _azimuth += other._azimuth;
    _inclination += other._inclination;
    _range += other._range;
    return *this;
}

Spherical Spherical::operator-(const Spherical& other) const
{
    return Spherical(_azimuth - other._azimuth, _inclination - other._inclination, _range - other._range);
}
Spherical& Spherical::operator-=(const Spherical& other)
{
    _azimuth -= other._azimuth;
    _inclination -= other._inclination;
    _range -= other._range;
    return *this;
}

Spherical Spherical::operator*(const Unitless& multiplier) const
{
    return Spherical(_azimuth * multiplier, _inclination * multiplier, _range * multiplier);
}
Spherical& Spherical::operator*=(const Unitless& multiplier)
{
    _azimuth *= multiplier;
    _inclination *= multiplier;
    _range *= multiplier;
    return *this;
}

Spherical Spherical::operator/(const Unitless& divisor) const
{
    return Spherical(_azimuth / divisor, _inclination / divisor, _range / divisor);
}
Spherical& Spherical::operator/=(const Unitless& divisor)
{
    _azimuth /= divisor;
    _inclination /= divisor;
    _range /= divisor;
    return *this;
}

Spherical Spherical::interpolate(const Time& thisTime, const Time& otherTime, const Spherical& other, const Time& targetTime) const
{
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);
    const Angle interpInc =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _inclination, other.get_inclination() }, targetTime);
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);

    return Spherical(interpAzimuth, interpInc, interpRange);
}

RadiusVector<ECEF> Spherical::get_position(const CelestialBody* parent) const
{
    const auto x = _range * sin(_inclination) * cos(_azimuth);
    const auto y = _range * sin(_inclination) * sin(_azimuth);
    const auto z = _range * cos(_inclination);
    return RadiusVector<ECEF>(x, y, z);
}

RadiusVector<ECI> Spherical::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<ECI>(date);
}

std::ostream& operator<<(std::ostream& os, Spherical const& elements)
{
    os << "[";
    os << elements.get_azimuth() << ", ";
    os << elements.get_inclination() << ", ";
    os << elements.get_range();
    os << "] (Spherical)";
    return os;
}

} // namespace astro
} // namespace astrea