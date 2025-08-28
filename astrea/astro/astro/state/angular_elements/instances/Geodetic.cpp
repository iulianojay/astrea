#include <astro/state/angular_elements/instances/Geodetic.hpp>

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

Geodetic::Geodetic(const RadiusVector<ECI>& rEci, const Date& date, const CelestialBody* parent)
{
    *this = Geodetic(rEci.in_frame<ECEF>(date), parent);
}

Geodetic::Geodetic(const RadiusVector<ECEF>& rEcef, const CelestialBody* parent)
{
    std::tie(_latitude, _longitude, _altitude) =
        convert_earth_fixed_to_geodetic(rEcef, parent->get_equitorial_radius(), parent->get_polar_radius());
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

RadiusVector<ECEF> Geodetic::get_position(const CelestialBody* parent) const
{
    return convert_geodetic_to_earth_fixed(_latitude, _longitude, _altitude, parent->get_equitorial_radius(), parent->get_polar_radius());
}

RadiusVector<ECI> Geodetic::get_position(const Date& date, const CelestialBody* parent) const
{
    return get_position(parent).in_frame<ECI>(date);
}

std::ostream& operator<<(std::ostream& os, Geodetic const& elements)
{
    os << "[";
    os << elements.get_latitude() << ", ";
    os << elements.get_longitude() << ", ";
    os << elements.get_altitude();
    os << "] (Geodetic)";
    return os;
}

std::tuple<Angle, Angle, Distance>
    convert_earth_fixed_to_geodetic(const RadiusVector<EarthCenteredEarthFixed>& rEcef, const Distance& rEquitorial, const Distance& rPolar)
{
    static const unsigned MAX_ITER  = 1e3;
    static const Distance MAX_ERROR = 1.0e-9 * km;

    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];
    const Distance& zEcef = rEcef[2];

    const Unitless f   = (rEquitorial - rPolar) / rEquitorial;
    const Unitless eSq = (2.0 - f) * f;

    const auto xSqYSq = xEcef * xEcef + yEcef * yEcef;

    Distance dz  = eSq * zEcef;
    Distance err = 1.0 * km;
    Distance N   = 0.0 * km;
    unsigned ii  = 0;
    while (err > MAX_ERROR && ii < MAX_ITER) {
        const Unitless s = (zEcef + dz) / sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz));
        N                = rEquitorial / sqrt(1 - eSq * s * s);
        err              = abs(dz - N * eSq * s);
        dz               = N * eSq * s;
        ++ii;
    }

    if (ii >= MAX_ITER - 1) { throw std::runtime_error("Conversion from ECEF to LLA failed to converge."); }

    const Angle longitude = atan2(yEcef, xEcef);
    const Angle latitude  = atan2(zEcef + dz, sqrt(xSqYSq)); // geodetic
    // _latitude = atan((1.0 - f) * (1.0 - f) * tan(lat)); // geocentric
    Distance altitude = sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz)) - N;
    if (altitude < 0.0 * km) { altitude = 0.0 * km; }

    return { latitude, longitude, altitude };
}

RadiusVector<EarthCenteredEarthFixed>
    convert_geodetic_to_earth_fixed(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar)
{
    const quantity sinLat = sin(lat);
    const quantity cosLat = cos(lat);

    const Unitless f   = (rEquitorial - rPolar) / rEquitorial;
    const Unitless eSq = (2.0 - f) * f;
    const Distance N   = rEquitorial / sqrt(1.0 - eSq * sinLat * sinLat);

    // Ecef coordinates
    return { (N + alt) * cosLat * cos(lon), (N + alt) * cosLat * sin(lon), ((1.0 - eSq) * N + alt) * sinLat };
}

} // namespace astro
} // namespace astrea