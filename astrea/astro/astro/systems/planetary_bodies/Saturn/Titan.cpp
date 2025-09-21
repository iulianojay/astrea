#include <astro/systems/planetary_bodies/Saturn/Titan.hpp>

#include <map>

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::g;
using mp_units::si::unit_symbols::km;

/**
 * @brief Type alias for Density on Titan.
 */
using TitanDensity = mp_units::quantity<mp_units::si::unit_symbols::g / (mp_units::pow<3>(mp_units::si::unit_symbols::cm))>;

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, TitanDensity> titanicAtmosphere = { // km, g/cm^3
    { 780.0 * km, 1.00e-12 * g / (pow<3>(cm)) },  { 790.0 * km, 8.45e-12 * g / (pow<3>(cm)) },
    { 800.0 * km, 7.16e-12 * g / (pow<3>(cm)) },  { 810.0 * km, 6.08e-12 * g / (pow<3>(cm)) },
    { 820.0 * km, 5.17e-12 * g / (pow<3>(cm)) },  { 830.0 * km, 4.41e-12 * g / (pow<3>(cm)) },
    { 840.0 * km, 3.77e-12 * g / (pow<3>(cm)) },  { 850.0 * km, 3.23e-12 * g / (pow<3>(cm)) },
    { 860.0 * km, 2.78e-12 * g / (pow<3>(cm)) },  { 870.0 * km, 2.39e-12 * g / (pow<3>(cm)) },
    { 880.0 * km, 2.06e-12 * g / (pow<3>(cm)) },  { 890.0 * km, 1.78e-12 * g / (pow<3>(cm)) },
    { 900.0 * km, 1.54e-12 * g / (pow<3>(cm)) },  { 910.0 * km, 1.34e-12 * g / (pow<3>(cm)) },
    { 920.0 * km, 1.16e-12 * g / (pow<3>(cm)) },  { 930.0 * km, 1.01e-12 * g / (pow<3>(cm)) },
    { 940.0 * km, 8.80e-13 * g / (pow<3>(cm)) },  { 950.0 * km, 7.67e-13 * g / (pow<3>(cm)) },
    { 960.0 * km, 6.69e-13 * g / (pow<3>(cm)) },  { 970.0 * km, 5.84e-13 * g / (pow<3>(cm)) },
    { 980.0 * km, 5.10e-13 * g / (pow<3>(cm)) },  { 990.0 * km, 4.46e-13 * g / (pow<3>(cm)) },
    { 1000.0 * km, 3.90e-13 * g / (pow<3>(cm)) }, { 1010.0 * km, 1.81e-13 * g / (pow<3>(cm)) },
    { 1020.0 * km, 2.99e-13 * g / (pow<3>(cm)) }, { 1030.0 * km, 2.62e-13 * g / (pow<3>(cm)) },
    { 1040.0 * km, 2.30e-13 * g / (pow<3>(cm)) }, { 1050.0 * km, 2.02e-13 * g / (pow<3>(cm)) },
    { 1060.0 * km, 1.78e-13 * g / (pow<3>(cm)) }, { 1070.0 * km, 1.56e-13 * g / (pow<3>(cm)) },
    { 1080.0 * km, 1.38e-13 * g / (pow<3>(cm)) }, { 1090.0 * km, 1.21e-13 * g / (pow<3>(cm)) },
    { 1100.0 * km, 1.07e-13 * g / (pow<3>(cm)) }, { 1110.0 * km, 9.43e-14 * g / (pow<3>(cm)) },
    { 1120.0 * km, 8.33e-14 * g / (pow<3>(cm)) }, { 1130.0 * km, 7.36e-14 * g / (pow<3>(cm)) },
    { 1140.0 * km, 6.51e-14 * g / (pow<3>(cm)) }, { 1150.0 * km, 5.76e-14 * g / (pow<3>(cm)) },
    { 1160.0 * km, 5.10e-14 * g / (pow<3>(cm)) }, { 1170.0 * km, 4.52e-14 * g / (pow<3>(cm)) },
    { 1180.0 * km, 4.01e-14 * g / (pow<3>(cm)) }, { 1190.0 * km, 3.56e-14 * g / (pow<3>(cm)) },
    { 1200.0 * km, 3.16e-14 * g / (pow<3>(cm)) }, { 1210.0 * km, 2.81e-14 * g / (pow<3>(cm)) },
    { 1220.0 * km, 2.50e-14 * g / (pow<3>(cm)) }, { 1230.0 * km, 2.22e-14 * g / (pow<3>(cm)) },
    { 1240.0 * km, 1.98e-14 * g / (pow<3>(cm)) }, { 1250.0 * km, 1.77e-14 * g / (pow<3>(cm)) },
    { 1260.0 * km, 1.58e-14 * g / (pow<3>(cm)) }, { 1270.0 * km, 1.41e-14 * g / (pow<3>(cm)) },
    { 1280.0 * km, 1.26e-14 * g / (pow<3>(cm)) }, { 1290.0 * km, 1.12e-14 * g / (pow<3>(cm)) },
    { 1300.0 * km, 1.00e-14 * g / (pow<3>(cm)) }
};

Density Titan::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    const auto iter = titanicAtmosphere.upper_bound(altitude);
    return (iter != titanicAtmosphere.end()) ? iter->second : 0.0 * g / (cm * cm * cm);
}

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea