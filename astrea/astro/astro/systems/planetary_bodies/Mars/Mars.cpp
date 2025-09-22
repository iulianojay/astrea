#include <astro/systems/planetary_bodies/Mars/Mars.hpp>

#include <map>

#ifdef ASTREA_BUILD_MARS_EPHEMERIS
#include <ephemeris/Mars/ephemeris/MarsEphemerisTable.hpp>
#include <math/chebyshev_utils.hpp>
#endif // ASTREA_BUILD_MARS_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, Density> martianAtmosphere = { // km, kg/m^3
    { 2.0 * km, 1.19e-1 * kg / (pow<3>(m)) },  { 4.0 * km, 1.10e-1 * kg / (pow<3>(m)) },
    { 6.0 * km, 1.02e-1 * kg / (pow<3>(m)) },  { 8.0 * km, 9.39e-2 * kg / (pow<3>(m)) },
    { 10.0 * km, 8.64e-2 * kg / (pow<3>(m)) }, { 12.0 * km, 7.93e-2 * kg / (pow<3>(m)) },
    { 14.0 * km, 7.25e-2 * kg / (pow<3>(m)) }, { 16.0 * km, 6.61e-2 * kg / (pow<3>(m)) },
    { 18.0 * km, 6.00e-2 * kg / (pow<3>(m)) }, { 20.0 * km, 5.43e-2 * kg / (pow<3>(m)) },
    { 22.0 * km, 4.89e-2 * kg / (pow<3>(m)) }, { 24.0 * km, 3.91e-2 * kg / (pow<3>(m)) },
    { 26.0 * km, 3.32e-2 * kg / (pow<3>(m)) }, { 28.0 * km, 2.82e-2 * kg / (pow<3>(m)) },
    { 30.0 * km, 2.40e-2 * kg / (pow<3>(m)) }, { 32.0 * km, 2.04e-2 * kg / (pow<3>(m)) },
    { 34.0 * km, 1.73e-2 * kg / (pow<3>(m)) }, { 36.0 * km, 1.47e-2 * kg / (pow<3>(m)) },
    { 38.0 * km, 1.25e-2 * kg / (pow<3>(m)) }, { 40.0 * km, 1.06e-2 * kg / (pow<3>(m)) },
    { 45.0 * km, 7.03e-3 * kg / (pow<3>(m)) }, { 50.0 * km, 4.67e-3 * kg / (pow<3>(m)) },
    { 55.0 * km, 3.10e-3 * kg / (pow<3>(m)) }, { 60.0 * km, 2.06e-3 * kg / (pow<3>(m)) },
    { 65.0 * km, 1.36e-3 * kg / (pow<3>(m)) }, { 70.0 * km, 9.11e-4 * kg / (pow<3>(m)) },
    { 75.0 * km, 6.05e-4 * kg / (pow<3>(m)) }, { 80.0 * km, 4.02e-4 * kg / (pow<3>(m)) }
};

Density Mars::find_atmospheric_density(const Date& date, const Distance& altitude) const
{
    // The values up to 80 km are almost definitely wrong.I can't find any
    // sources that contradict them though.Please fix them(and the
    // associated crash radius of Mars) if you can find better numbers.
    Unitless altitudeValue = altitude / astrea::detail::distance_unit;
    if (altitude <= 80.0 * km) {
        const auto iter = martianAtmosphere.upper_bound(altitude);
        return (iter != martianAtmosphere.end()) ? iter->second : 0.0 * kg / (m * m * m);
    }
    else if (altitude < 200.0 * km) {
        return exp(-2.55314e-10 * pow<5>(altitudeValue) + 2.31927e-7 * pow<4>(altitudeValue) -
                   8.33206e-5 * pow<3>(altitudeValue) + 0.0151947 * pow<2>(altitudeValue) - 1.52799 * altitudeValue + 48.69659) *
               kg / (m * m * m);
    }
    else if (altitude < 300.0 * km) {
        return exp(2.65472e-11 * pow<5>(altitudeValue) - 2.45558e-8 * pow<4>(altitudeValue) + 6.31410e-6 * pow<3>(altitudeValue) +
                   4.73359e-4 * pow<2>(altitudeValue) - 0.443712 * altitudeValue + 23.79408) *
               kg / (m * m * m);
    }
    else {
        return 0.0 * kg / (m * m * m);
    }
}

#ifdef ASTREA_BUILD_MARS_EPHEMERIS

Cartesian Jupiter::get_ephemeris_at(const Date& date) const override
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = MarsEphemerisTable::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = get_index(date, timePerCoefficient);
    const auto& xInterp   = MarsEphemerisTable::X_INTERP[ind];
    const auto& yInterp   = MarsEphemerisTable::Y_INTERP[ind];
    const auto& zInterp   = MarsEphemerisTable::Z_INTERP[ind];

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

#endif // ASTREA_BUILD_MARS_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea