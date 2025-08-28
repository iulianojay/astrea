#include <astro/state/angular_elements/instances/Cylindrical.hpp>

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

Cylindrical::Cylindrical(const RadiusVector<ECI>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Cylindrical(rEci.in_frame<ECEF>(date), parent);
}

Cylindrical::Cylindrical(const RadiusVector<ECEF>& rEcef, const CelestialBody* parent)
{
    _range     = rEcef.norm();
    _elevation = rEcef.get_z();
    _azimuth   = acos(rEcef.get_x() / sqrt(rEcef.get_x() * rEcef.get_x() + rEcef.get_y() * rEcef.get_y()));
    if (rEcef.get_y() < 0 * km) { _azimuth = -_azimuth; }
}

// Copy constructor
Cylindrical::Cylindrical(const Cylindrical& other) :
    _azimuth(other._azimuth),
    _elevation(other._elevation),
    _range(other._range)
{
}

// Move constructor
Cylindrical::Cylindrical(Cylindrical&& other) noexcept :
    _azimuth(std::move(other._azimuth)),
    _elevation(std::move(other._elevation)),
    _range(std::move(other._range))
{
}

// Move assignment operator
Cylindrical& Cylindrical::operator=(Cylindrical&& other) noexcept
{
    if (this != &other) {
        _azimuth   = std::move(other._azimuth);
        _elevation = std::move(other._elevation);
        _range     = std::move(other._range);
    }
    return *this;
}

// Copy assignment operator
Cylindrical& Cylindrical::operator=(const Cylindrical& other) { return *this = Cylindrical(other); }

// Comparitors operators
bool Cylindrical::operator==(const Cylindrical& other) const
{
    return (_azimuth == other._azimuth && _elevation == other._elevation && _range == other._range);
}

bool Cylindrical::operator!=(const Cylindrical& other) const { return !(*this == other); }


// Mathmatical operators
Cylindrical Cylindrical::operator+(const Cylindrical& other) const
{
    return Cylindrical(_azimuth + other._azimuth, _elevation + other._elevation, _range + other._range);
}
Cylindrical& Cylindrical::operator+=(const Cylindrical& other)
{
    _azimuth += other._azimuth;
    _elevation += other._elevation;
    _range += other._range;
    return *this;
}

Cylindrical Cylindrical::operator-(const Cylindrical& other) const
{
    return Cylindrical(_azimuth - other._azimuth, _elevation - other._elevation, _range - other._range);
}
Cylindrical& Cylindrical::operator-=(const Cylindrical& other)
{
    _azimuth -= other._azimuth;
    _elevation -= other._elevation;
    _range -= other._range;
    return *this;
}

Cylindrical Cylindrical::operator*(const Unitless& multiplier) const
{
    return Cylindrical(_azimuth * multiplier, _elevation * multiplier, _range * multiplier);
}
Cylindrical& Cylindrical::operator*=(const Unitless& multiplier)
{
    _azimuth *= multiplier;
    _elevation *= multiplier;
    _range *= multiplier;
    return *this;
}

Cylindrical Cylindrical::operator/(const Unitless& divisor) const
{
    return Cylindrical(_azimuth / divisor, _elevation / divisor, _range / divisor);
}
Cylindrical& Cylindrical::operator/=(const Unitless& divisor)
{
    _azimuth /= divisor;
    _elevation /= divisor;
    _range /= divisor;
    return *this;
}

Cylindrical Cylindrical::interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical& other, const Time& targetTime) const
{
    const Angle interpAzimuth =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _azimuth, other.get_azimuth() }, targetTime);
    const Distance interpElev =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _elevation, other.get_elevation() }, targetTime);
    const Distance interpRange =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _range, other.get_range() }, targetTime);

    return Cylindrical(interpAzimuth, interpElev, interpRange);
}

RadiusVector<ECEF> Cylindrical::get_position(const CelestialBody* parent) const
{
    const auto x = _range * cos(_azimuth);
    const auto y = _range * sin(_azimuth);
    const auto z = _elevation;
    return RadiusVector<ECEF>(x, y, z);
}

RadiusVector<ECI> Cylindrical::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<ECI>(date);
}

std::ostream& operator<<(std::ostream& os, Cylindrical const& elements)
{
    os << "[";
    os << elements.get_azimuth() << ", ";
    os << elements.get_elevation() << ", ";
    os << elements.get_range();
    os << "] (Cylindrical)";
    return os;
}

} // namespace astro
} // namespace astrea