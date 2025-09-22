#include <astro/systems/planetary_bodies/Earth/Earth.hpp>

#include <map>

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
#include <ephemeris/Mercury/ephemeris/MercuryEphemerisTable.hpp>
#include <math/chebyshev_utils.hpp>
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

Cartesian Mercury::get_ephemeris_at(const Date& date) const override
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = MercuryEphemerisTable::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = get_index(date, timePerCoefficient);
    const auto& xInterp   = MercuryEphemerisTable::X_INTERP[ind];
    const auto& yInterp   = MercuryEphemerisTable::Y_INTERP[ind];
    const auto& zInterp   = MercuryEphemerisTable::Z_INTERP[ind];

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

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea