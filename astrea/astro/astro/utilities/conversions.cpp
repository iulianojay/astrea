#include <astro/utilities/conversions.hpp>

#include <units/units.hpp>

#include <astro/element_sets/CartesianVector.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::h;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Frame Conversions --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//


void ecef_to_lla(const RadiusVector<EarthCenteredEarthFixed>& rEcef, const Distance& rEquitorial, const Distance& rPolar, Angle& lat, Angle& lon, Distance& alt)
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

    lon = atan2(yEcef, xEcef);
    lat = atan2(zEcef + dz, sqrt(xSqYSq)); // geodetic
    // lat = atan((1.0 - f) * (1.0 - f) * tan(lat)); // geocentric
    alt = sqrt(xSqYSq + (zEcef + dz) * (zEcef + dz)) - N;
    if (alt < 0.0 * km) { alt = 0.0 * km; }
}

RadiusVector<EarthCenteredEarthFixed>
    lla_to_ecef(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar)
{
    const quantity sinLat = sin(lat);
    const quantity cosLat = cos(lat);

    const Unitless f   = (rEquitorial - rPolar) / rEquitorial;
    const Unitless eSq = (2.0 - f) * f;
    const Distance N   = rEquitorial / sqrt(1.0 - eSq * sinLat * sinLat);

    // Ecef coordinates
    return { (N + alt) * cosLat * cos(lon), (N + alt) * cosLat * sin(lon), ((1.0 - eSq) * N + alt) * sinLat };
}

Angle sanitize_angle(const Angle& angle)
{
    Angle ang = angle;
    while (ang < 0.0 * astrea::detail::angle_unit) {
        ang += TWO_PI;
    }
    return fmod(ang, TWO_PI);
}

} // namespace astro
} // namespace astrea