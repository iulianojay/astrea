#include <astro/systems/planetary_bodies/Venus/Venus.hpp>

#include <map>

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS
#include <ephemeris/Venus/ephemeris/VenusEphemerisTable.hpp>
#include <math/chebyshev_utils.hpp>
#endif // ASTREA_BUILD_VENUS_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, Density> venutianAtmosphere = { // km, kg/m^3
    { 3.0 * km, 5.53e1 * kg / (pow<3>(m)) },    { 6.0 * km, 4.75e1 * kg / (pow<3>(m)) },
    { 9.0 * km, 4.02e1 * kg / (pow<3>(m)) },    { 12.0 * km, 3.44e1 * kg / (pow<3>(m)) },
    { 15.0 * km, 2.91e1 * kg / (pow<3>(m)) },   { 18.0 * km, 2.46e1 * kg / (pow<3>(m)) },
    { 21.0 * km, 2.06e1 * kg / (pow<3>(m)) },   { 24.0 * km, 1.70e1 * kg / (pow<3>(m)) },
    { 27.0 * km, 1.405e1 * kg / (pow<3>(m)) },  { 30.0 * km, 1.115e1 * kg / (pow<3>(m)) },
    { 33.0 * km, 9.0 * kg / (pow<3>(m)) },      { 36.0 * km, 7.15 * kg / (pow<3>(m)) },
    { 39.0 * km, 5.15 * kg / (pow<3>(m)) },     { 42.0 * km, 4.34 * kg / (pow<3>(m)) },
    { 45.0 * km, 3.30 * kg / (pow<3>(m)) },     { 48.0 * km, 2.39 * kg / (pow<3>(m)) },
    { 51.0 * km, 1.88 * kg / (pow<3>(m)) },     { 54.0 * km, 1.38 * kg / (pow<3>(m)) },
    { 57.0 * km, 9.6e-1 * kg / (pow<3>(m)) },   { 60.0 * km, 6.2e-1 * kg / (pow<3>(m)) },
    { 70.0 * km, 1.2e-1 * kg / (pow<3>(m)) },   { 80.0 * km, 1.8e-2 * kg / (pow<3>(m)) },
    { 90.0 * km, 2.3e-3 * kg / (pow<3>(m)) },   { 100.0 * km, 3.1e-4 * kg / (pow<3>(m)) },
    { 110.0 * km, 4.4e-5 * kg / (pow<3>(m)) },  { 120.0 * km, 7.2e-6 * kg / (pow<3>(m)) },
    { 130.0 * km, 1.4e-6 * kg / (pow<3>(m)) },  { 140.0 * km, 3.0e-7 * kg / (pow<3>(m)) },
    { 150.0 * km, 8.0e-8 * kg / (pow<3>(m)) },  { 160.0 * km, 2.6e-8 * kg / (pow<3>(m)) },
    { 170.0 * km, 9.5e-9 * kg / (pow<3>(m)) },  { 180.0 * km, 4.0e-9 * kg / (pow<3>(m)) },
    { 190.0 * km, 1.9e-9 * kg / (pow<3>(m)) },  { 200.0 * km, 9.4e-10 * kg / (pow<3>(m)) },
    { 210.0 * km, 4.9e-10 * kg / (pow<3>(m)) }, { 220.0 * km, 2.6e-10 * kg / (pow<3>(m)) },
    { 230.0 * km, 1.4e-10 * kg / (pow<3>(m)) }, { 240.0 * km, 7.5e-11 * kg / (pow<3>(m)) },
    { 250.0 * km, 5.5e-11 * kg / (pow<3>(m)) }, { 260.0 * km, 4.1e-11 * kg / (pow<3>(m)) },
    { 270.0 * km, 2.2e-11 * kg / (pow<3>(m)) }, { 280.0 * km, 1.2e-11 * kg / (pow<3>(m)) },
    { 290.0 * km, 6.5e-12 * kg / (pow<3>(m)) }, { 300.0 * km, 3.5e-12 * kg / (pow<3>(m)) }
};

Density Venus::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    const auto iter = venutianAtmosphere.upper_bound(altitude);
    return (iter != venutianAtmosphere.end()) ? iter->second : 0.0 * kg / (m * m * m);
}

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS

Cartesian Venus::get_ephemeris_at(const Date& date) const override
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = VenusEphemerisTable::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = get_index(date, timePerCoefficient);
    const auto& xInterp   = VenusEphemerisTable::X_INTERP[ind];
    const auto& yInterp   = VenusEphemerisTable::Y_INTERP[ind];
    const auto& zInterp   = VenusEphemerisTable::Z_INTERP[ind];

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

#endif // ASTREA_BUILD_VENUS_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea