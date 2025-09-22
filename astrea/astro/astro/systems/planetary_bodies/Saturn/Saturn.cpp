#include <astro/systems/planetary_bodies/Earth/Earth.hpp>

#include <map>

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS
#include <ephemeris/Saturn/ephemeris/SaturnEphemerisTable.hpp>
#include <math/chebyshev_utils.hpp>
#endif // ASTREA_BUILD_SATURN_EPHEMERIS

namespace astrea {
namespace astro {
namespace planetary_bodies {

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

Cartesian Saturn::get_ephemeris_at(const Date& date) const override
{
    //! Number of days covered by each set of polynomial coefficients
    static constexpr Time timePerCoefficient = SaturnEphemerisTable::TIME_PER_COEFFICIENT;

    // Extract components
    const std::size_t ind = get_index(date, timePerCoefficient);
    const auto& xInterp   = SaturnEphemerisTable::X_INTERP[ind];
    const auto& yInterp   = SaturnEphemerisTable::Y_INTERP[ind];
    const auto& zInterp   = SaturnEphemerisTable::Z_INTERP[ind];

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

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea