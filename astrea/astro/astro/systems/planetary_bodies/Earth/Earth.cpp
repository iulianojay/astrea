#include <astro/systems/planetary_bodies/Earth/Earth.hpp>

#include <map>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemeris/Earth/ephemeris/EarthEphemerisTable.hpp>
#include <math/chebyshev_utils.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::non_si::day;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<
    Altitude,
    std::tuple<
        Altitude,
        Density,
        Altitude>>
    earthAtmosphere = { // km, (km, kg/m^3, km)
        { 25.0 * km, { 0.0 * km, 1.225 * kg / (pow<3>(m)), 7.249 * km } },
        { 30.0 * km, { 25.0 * km, 3.899e-2 * kg / (pow<3>(m)), 6.349 * km } },
        { 40.0 * km, { 30.0 * km, 1.774e-2 * kg / (pow<3>(m)), 6.682 * km } },
        { 50.0 * km, { 40.0 * km, 3.972e-3 * kg / (pow<3>(m)), 7.554 * km } },
        { 60.0 * km, { 50.0 * km, 1.057e-3 * kg / (pow<3>(m)), 8.382 * km } },
        { 70.0 * km, { 60.0 * km, 3.206e-4 * kg / (pow<3>(m)), 7.714 * km } },
        { 80.0 * km, { 70.0 * km, 8.770e-5 * kg / (pow<3>(m)), 6.549 * km } },
        { 90.0 * km, { 80.0 * km, 1.905e-5 * kg / (pow<3>(m)), 5.799 * km } },
        { 100.0 * km, { 90.0 * km, 3.396e-6 * kg / (pow<3>(m)), 5.382 * km } },
        { 110.0 * km, { 100.0 * km, 5.297e-7 * kg / (pow<3>(m)), 5.877 * km } },
        { 120.0 * km, { 110.0 * km, 9.661e-8 * kg / (pow<3>(m)), 7.263 * km } },
        { 130.0 * km, { 120.0 * km, 2.438e-8 * kg / (pow<3>(m)), 9.473 * km } },
        { 140.0 * km, { 130.0 * km, 8.484e-9 * kg / (pow<3>(m)), 12.636 * km } },
        { 150.0 * km, { 140.0 * km, 3.845e-9 * kg / (pow<3>(m)), 16.149 * km } },
        { 180.0 * km, { 150.0 * km, 2.070e-9 * kg / (pow<3>(m)), 22.523 * km } },
        { 200.0 * km, { 180.0 * km, 5.464e-10 * kg / (pow<3>(m)), 29.740 * km } },
        { 250.0 * km, { 200.0 * km, 2.789e-10 * kg / (pow<3>(m)), 37.105 * km } },
        { 300.0 * km, { 250.0 * km, 7.248e-11 * kg / (pow<3>(m)), 45.546 * km } },
        { 350.0 * km, { 300.0 * km, 2.418e-11 * kg / (pow<3>(m)), 53.628 * km } },
        { 400.0 * km, { 350.0 * km, 9.158e-12 * kg / (pow<3>(m)), 53.298 * km } },
        { 450.0 * km, { 400.0 * km, 3.725e-12 * kg / (pow<3>(m)), 58.515 * km } },
        { 500.0 * km, { 450.0 * km, 1.585e-12 * kg / (pow<3>(m)), 60.828 * km } },
        { 600.0 * km, { 500.0 * km, 6.967e-13 * kg / (pow<3>(m)), 63.822 * km } },
        { 700.0 * km, { 600.0 * km, 1.454e-13 * kg / (pow<3>(m)), 71.835 * km } },
        { 800.0 * km, { 700.0 * km, 3.614e-14 * kg / (pow<3>(m)), 88.667 * km } },
        { 900.0 * km, { 800.0 * km, 1.170e-14 * kg / (pow<3>(m)), 124.64 * km } },
        { 1000.0 * km, { 900.0 * km, 5.245e-15 * kg / (pow<3>(m)), 181.05 * km } },
        { 1100.0 * km, { 1000.0 * km, 2.019e-15 * kg / (pow<3>(m)), 268.00 * km } }
    };

Density Earth::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    Distance referenceAltitude;
    Density referenceDensity;
    Distance scaleHeight;

    const auto iter = earthAtmosphere.upper_bound(altitude);
    if (iter != earthAtmosphere.end()) {
        const auto atmo   = iter->second;
        referenceAltitude = std::get<0>(atmo);
        referenceDensity  = std::get<1>(atmo);
        scaleHeight       = std::get<2>(atmo);
    }
    else {
        referenceAltitude = 1100.0 * km;
        referenceDensity  = 0.0 * kg / (m * m * m);
        scaleHeight       = 1.0 * km;
    }

    return referenceDensity * exp((referenceAltitude - altitude) / scaleHeight);
}

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

Cartesian Earth::get_ephemeris_at(const Date& date) const override
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = EarthEphemerisTable::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = get_index(date, timePerCoefficient);
    const auto& xInterp   = EarthEphemerisTable::X_INTERP[ind];
    const auto& yInterp   = EarthEphemerisTable::Y_INTERP[ind];
    const auto& zInterp   = EarthEphemerisTable::Z_INTERP[ind];

    // Evaluate Chebyshev polynomials
    const auto mjd                      = date.mjd();
    static const double coeffZeroFactor = 1.0;

    Distance x = evaluate_chebyshev_polynomial(mjd, xInterp, coeffZeroFactor) * km;
    Distance y = evaluate_chebyshev_polynomial(mjd, yInterp, coeffZeroFactor) * km;
    Distance z = evaluate_chebyshev_polynomial(mjd, zInterp, coeffZeroFactor) * km;

    Velocity vx = evaluate_chebyshev_derivative(mjd, xInterp, coeffZeroFactor) * km / day;
    Velocity vy = evaluate_chebyshev_derivative(mjd, yInterp, coeffZeroFactor) * km / day;
    Velocity vz = evaluate_chebyshev_derivative(mjd, zInterp, coeffZeroFactor) * km / day;

    return Cartesian{ x, y, z, vx, vy, vz };
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea