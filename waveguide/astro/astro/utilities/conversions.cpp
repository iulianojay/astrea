#include <astro/utilities/conversions.hpp>

#include <math/utils.hpp>

#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/units/constants.hpp>

using namespace mp_units;
using namespace mp_units::angular;
using mp_units::angular::unit_symbols::deg;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::h;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

namespace astro {

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Frame Conversions --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//


void conversions::ecef_to_lla(const RadiusVector& rEcef, const Distance& equitorialRadius, const Distance& polarRadius, Angle& lat, Angle& lon, Distance& alt)
{
    static const unsigned maxIter    = 1e3;
    static const Distance errorBound = 1.0e-9 * km;

    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];
    const Distance& zEcef = rEcef[2];

    const Unitless f   = (equitorialRadius - polarRadius) / equitorialRadius;
    const Unitless e_2 = (2.0 - f) * f;

    quantity dz  = e_2 * zEcef;
    Distance err = 1 * km;
    Distance N   = 0 * km;
    unsigned ii  = 0;
    while (err > errorBound && ii < maxIter) {
        const Unitless s = (zEcef + dz) / sqrt(xEcef * xEcef + yEcef * yEcef + (zEcef + dz) * (zEcef + dz));
        N                = equitorialRadius / sqrt(1 - e_2 * s * s);
        err              = abs(dz - N * e_2 * s);
        dz               = N * e_2 * s;
        ++ii;
    }

    if (ii >= maxIter - 1) { throw std::runtime_error("Conversion from Ecef to LLA failed to converge."); }

    // Lat, long, alt (respectively)
    lat = atan2(yEcef, xEcef);
    lon = atan2(yEcef + dz, sqrt(xEcef * xEcef + yEcef * yEcef)); // geodetic
    // alt = asin(zecef/sqrt(xEcef*xEcef + yEcef*yEcef + zEcef*zEcef))*rad2deg; // geocentric
    alt = sqrt(xEcef * xEcef + yEcef * yEcef + (zEcef + dz) * (zEcef + dz)) - N;
    if (alt < 0.0 * km) { alt = 0.0 * km; }
}

void conversions::lla_to_ecef(
    const Angle& latitude,
    const Angle& longitude,
    const Distance& altitude,
    const Distance& equitorialRadius,
    const Distance& polarRadius,
    RadiusVector& rEcef
)
{

    const quantity sinLat = sin(latitude);
    const quantity cosLat = cos(latitude);

    const quantity f = (equitorialRadius - polarRadius) / equitorialRadius;
    const quantity N = equitorialRadius / sqrt(1 - f * (2 - f) * sinLat * sinLat);

    // Ecef coordinates
    rEcef[0] = (N + altitude) * cosLat * cos(longitude);
    rEcef[1] = (N + altitude) * cosLat * sin(longitude);
    rEcef[2] = ((1 - f) * (1 - f) * N + altitude) * sinLat;
}

Angle conversions::sanitize_angle(const Angle& angle)
{
    Angle ang = angle;
    while (ang < 0.0 * detail::angle_unit) {
        ang += TWO_PI;
    }
    ang = fmod(ang, TWO_PI);
    return ang;
}

} // namespace astro