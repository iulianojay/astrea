/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/force_models/OblatenessForce.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>

#include <math/operations.hpp>
#include <math/trig.hpp>

#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/utilities/conversions.hpp>


namespace astrea {

using math::assoc_legendre;

namespace astro {

using namespace mp_units;
using namespace mp_units::angular;

using mp_units::pow;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;


LegendreCache::LegendreCache(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order)
{
    // Size arrays (size Legendre array now so it only happens once)
    size_vectors(degree, order);

    // Read coefficients from file
    ingest_legendre_coefficient_file(sys, degree, order);
}


void LegendreCache::size_vectors(const std::size_t& degree, const std::size_t& order)
{
    _C.resize(degree + 1);
    _S.resize(degree + 1);
    _normalizingCoefficients.resize(degree + 1);
    for (std::size_t n = 0; n < degree + 1; ++n) {
        _C[n].resize(order + 1);
        _S[n].resize(order + 1);
        _normalizingCoefficients[n].resize(order + 1);
    }
}


void LegendreCache::ingest_legendre_coefficient_file(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order)
{
    // Open coefficients file
    // TODO: Attach these files to the CelestialBody class
    // TODO: Change to binary files cause boy are these big
    std::filesystem::path path = std::string(std::getenv("ASTREA_ROOT")) + "/astrea/astro/data/gravity_models/";
    std::filesystem::path filename;
    const CelestialBodyId centerId =
        sys.get_central_body_id(); // TODO: This forces the oblatness to only consider the system central body
    switch (centerId) {
        case CelestialBodyId::MERCURY:
            // https://pds-geosciences.wustl.edu/messenger/mess-h-rss_mla-5-sdp-v1/messrs_1001/data/shadr/
            filename = path / "Mercury" / "jgmess_160a_sha.tab"; // Normalized
            break;

        case CelestialBodyId::VENUS:
            // https://pds-geosciences.wustl.edu/mgn/mgn-v-rss-5-gravity-l2-v1/mg_5201/gravity/
            filename = path / "Venus" / "shgj180u.a01"; // Normalized?
            break;

        case CelestialBodyId::EARTH:
            filename = path / "Earth" / "EGM2008_to2190_ZeroTide_mod.txt"; // Normalized
            // filename = path / "Earth" / "WGS84"; // Normalized
            // filename = path / "Earth" / "NASA_6DoF"; // Normalized - only goes to 8x8
            break;

        case CelestialBodyId::MOON:
            // https://pds-geosciences.wustl.edu/grail/grail-l-lgrs-5-rdr-v1/grail_1001/shadr/
            filename = path / "Moon" / "jggrx_0420a_sha.tab"; // Normalized?
            break;

        case CelestialBodyId::MARS:
            // https://pds-geosciences.wustl.edu/mro/mro-m-rss-5-sdp-v1/mrors_1xxx/data/shadr/
            filename = path / "Mars" / "jgmro_120f_sha.tab"; // Normalized?
            break;

        default: throw std::runtime_error("Legendre coefficient file for central body not found.");
    }
    std::ifstream file(filename);
    if (file.fail()) { throw std::runtime_error("Failed to open Legendre coefficient file: " + filename.string()); }

    // Read coefficients from file
    std::string line;
    std::string cell;

    std::size_t n = 0, m = 0;
    while (file) {
        // Read line from stream
        std::getline(file, line);
        std::stringstream lineStream(line);
        std::vector<double> lineData;
        while (std::getline(lineStream, cell, ',')) {
            lineData.push_back(std::atof(cell.c_str()));
        }

        n = (std::size_t)lineData[0];
        m = (std::size_t)lineData[1];

        _C[n][m] = lineData[2];
        _S[n][m] = lineData[3];

        if (n >= degree && m >= order) { break; }
    }
    file.close();

    // Calculate normalization coefficients after reading all coefficients
    for (std::size_t n = 0; n <= degree; ++n) {
        for (std::size_t m = 0; m <= std::min(n, order); ++m) {
            // Calculate (n + m)!/(n - m)! = (n - m + 1)(n - m + 2)...(n + m)
            Unitless factorialCoefficient = 1.0 * one;
            for (std::size_t ii = n - m + 1; ii <= n + m; ++ii) {
                factorialCoefficient *= ii;
            }
            // TODO: This will cause big slowdowns for m ~ n >> 1. need a smarter way to do these factorials.
            // Should be a way to do this recursively using previous values from earlier n and m calculations.

            // sqrt( (2 - delta_m0) * (2n + 1) * (n - m)! / (n + m)! )
            // delta = 1 if m = 0, else 0
            const unsigned int delta = (m == 0) ? 1 : 0;
            _normalizingCoefficients[n][m] = sqrt(static_cast<double>((2 - delta) * (2 * n + 1)) / factorialCoefficient);

            // Normalize coefficients if needed
            if (centerId == CelestialBodyId::MARS) {
                _C[n][m] /= _normalizingCoefficients[n][m];
                _S[n][m] /= _normalizingCoefficients[n][m];
            }
        }
    }
}


// std::vector<std::vector<Unitless>>
//     LegendreCache::get_legendre_coefficients(const std::size_t& degree, const std::size_t& order, const Unitless& x) const
// {
//     std::vector<std::vector<Unitless>> P(degree + 1);
//     for (std::size_t n = 0; n < degree + 1; ++n) {
//         P[n].resize(order + 1, 0.0 * one);
//     }

//     const Unitless sqrtOneMinusX2 = sqrt(1.0 * one - x * x);

//     // Compute diagonal terms P_m^m using recursion
//     Unitless Pmm = 1.0 * one; // P_0^0 = 1
//     for (std::size_t m = 0; m <= std::min(degree, order); ++m) {
//         if (m > 0) {
//             // P_m^m = (2m-1) * sqrt(1-x^2) * P_{m-1}^{m-1}
//             Pmm *= (2.0 * m - 1.0) * sqrtOneMinusX2;
//         }

//         if (m >= 2) { P[m][m] = _normalizingCoefficients[m][m] * Pmm; }

//         // Compute P_{m+1}^m if m+1 <= degree
//         if (m + 1 <= degree) {
//             // P_{m+1}^m = x * (2m+1) * P_m^m
//             const Unitless Pmp1m = x * (2.0 * m + 1.0) * Pmm;
//             if (m + 1 >= 2) { P[m + 1][m] = _normalizingCoefficients[m + 1][m] * Pmp1m; }

//             // Compute P_n^m for n > m+1 using three-term recursion
//             // (n-m)*P_n^m = x*(2n-1)*P_{n-1}^m - (n+m-1)*P_{n-2}^m
//             Unitless Pnm2 = Pmm;   // P_{n-2}^m
//             Unitless Pnm1 = Pmp1m; // P_{n-1}^m

//             for (std::size_t n = m + 2; n <= degree; ++n) {
//                 const Unitless Pnm = (x * (2.0 * n - 1.0) * Pnm1 - (n + m - 1.0) * Pnm2) / (n - m);

//                 if (n >= 2) { P[n][m] = _normalizingCoefficients[n][m] * Pnm; }

//                 // Shift for next iteration
//                 Pnm2 = Pnm1;
//                 Pnm1 = Pnm;
//             }
//         }
//     }

//     return P;
// }


Unitless LegendreCache::get_normalizing_coefficient(const std::size_t& n, const std::size_t& m) const
{
    return _normalizingCoefficients[n][m];
}


Unitless LegendreCache::get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const { return _C[n][m]; }


Unitless LegendreCache::get_sine_coefficient(const std::size_t& n, const std::size_t& m) const { return _S[n][m]; }


OblatenessForce::OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order) :
    _degree(degree),
    _order(order),
    _sys(&sys),
    _legendreCache(sys, degree, order)
{
}

/*
For the life of me, I could not get this to match the NASA checkcases. I can't find anything wrong with it. If you figure
it out, let me know.

AccelerationVector<frames::earth::icrf>
    OblatenessForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    // Central body properties
    const GravParam& mu         = _sys->get_mu();
    const Distance& equitorialR = _sys->get_central_body()->get_equitorial_radius();
    const Distance& polarR      = _sys->get_central_body()->get_polar_radius();

    // Find lat and lon
    const RadiusVector<frames::earth::icrf> rEci = state.get_position();
    const RadiusVector<frames::earth::earth_fixed> rEcef = state.get_position().in_frame<frames::earth::earth_fixed>(date);
    const auto [latitude, longitude, altitude] = convert_earth_fixed_to_geocentric(rEcef, equitorialR, polarR);

    // Precomput common terms
    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];
    const Distance& zEcef = rEcef[2];

    const Distance rho              = sqrt(xEcef * xEcef + yEcef * yEcef);
    const auto oneOverR             = 1.0 / rEci.norm();
    const Unitless equitorialROverR = equitorialR * oneOverR;

    const Unitless sinLat = sin(latitude);
    const Unitless cosLat = cos(latitude);
    const Unitless tanLat = tan(latitude);

    // Get Legendre polynomial coefficients
    const auto P = _legendreCache.get_legendre_coefficients(_degree, _order, sinLat);

    // Calculate serivative of gravitational potential field with respect to
    Unitless dVdrOuterSum   = 0.0 * one; // radius
    Unitless dVdlatOuterSum = 0.0 * one; // geocentric latitude
    Unitless dVdlonOuterSum = 0.0 * one; // longitude
    for (std::size_t n = 2; n < _degree + 1; ++n) {
        const Unitless nn = static_cast<double>(n) * one;

        // Reset inner sums
        Unitless dVdrInnerSum   = 0.0 * one;
        Unitless dVdlatInnerSum = 0.0 * one;
        Unitless dVdlonInnerSum = 0.0 * one;
        for (std::size_t m = 0; m < std::min(n, _order) + 1; ++m) {
            const Unitless mm = static_cast<double>(m) * one;

            // Precalculate common terms
            const Unitless Pnm = P[n][m];
            const Unitless Cnm = _legendreCache.get_cosine_coefficient(n, m);
            const Unitless Snm = _legendreCache.get_sine_coefficient(n, m);

            const Unitless cosMLon      = cos(mm * longitude);
            const Unitless sinMLon      = sin(mm * longitude);
            const Unitless cCosPlusSSin = (Cnm * cosMLon + Snm * sinMLon);

            // dVdr
            dVdrInnerSum += cCosPlusSSin * Pnm;

            // dVdlat
            Unitless dPnmdLat = mm * tanLat * Pnm;
            if (m < n) { dPnmdLat += sqrt((nn - mm) * (nn + mm + 1.0)) * P[n][m + 1] * cosLat; }
            dVdlatInnerSum += cCosPlusSSin * dPnmdLat;

            // dVdlon
            dVdlonInnerSum += mm * Pnm * (Snm * cosMLon - Cnm * sinMLon);
        }

        // Precalculate common terms
        const Unitless rRatio = astrea::math::pow(equitorialROverR, nn);

        //
        //  V      =  mu/r   * sum(n=0->N) (Re/r)^n        * sum(m=0->min(n,M))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //
        //  dVdr   = -mu/r^2 * sum(n=0->N) (n + 1)(Re/r)^n * sum(m=0->min(n,M))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //  dVdlat =  mu/r   * sum(n=0->N) (Re/r)^n        * sum(m=0->min(n,M)) dPnm(sin(lat))/dlat * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //  dVdlon =  mu/r   * sum(n=0->N) (Re/r)^n        * sum(m=0->min(n,M))   m * Pnm(sin(lat)) * (Snm*cos(m*lon) - Cnm*sin(m*lon))
        //

        dVdrOuterSum += rRatio * (nn + 1.0) * dVdrInnerSum;
        dVdlatOuterSum += rRatio * dVdlatInnerSum;
        dVdlonOuterSum += rRatio * dVdlonInnerSum;
    }

    // Correct
    const auto muOverR = mu * oneOverR; // km^2/s^2

    const auto dVdr   = -dVdrOuterSum * (muOverR * oneOverR); // km/s^2
    const auto dVdlat = dVdlatOuterSum * muOverR;             // km^2/s^2
    const auto dVdlon = dVdlonOuterSum * muOverR;             // km^2/s^2

    // Calculate partials of radius, geocentric latitude, and longitude with respect to radius in Ecef frame
    const auto term1 = oneOverR * (dVdr - zEcef * oneOverR / rho * dVdlat);
    const auto term2 = dVdlon / (rho * rho);

    // Calculate accel in ECEF (not with respect to ECEF)
    const AccelerationVector<frames::earth::earth_fixed> accelOblatenessEcef = {
        term1 * xEcef - term2 * yEcef,                      //
        term1 * yEcef + term2 * xEcef,                      //
        oneOverR * (dVdr * zEcef + oneOverR * rho * dVdlat) //
    };

    // Rotate back into inertial coordinates (no accel conversions required)
    return accelOblatenessEcef.in_frame<frames::earth::icrf>(date);
}
*/

AccelerationVector<frames::earth::icrf>
    OblatenessForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    // Montenbruck & Gill (2000) V and W recurrence relations method
    // Reference: Satellite Orbits: Models, Methods and Applications, O. Montenbruck and E. Gill, Springer, 2000

    // Central body properties
    const GravParam& mu         = _sys->get_mu();
    const Distance& equitorialR = _sys->get_central_body()->get_equitorial_radius();

    // Transform position to body-fixed frame
    const RadiusVector<frames::earth::icrf> rEci = state.get_position();
    const RadiusVector<frames::earth::earth_fixed> rEcef = state.get_position().in_frame<frames::earth::earth_fixed>(date);

    // Position components in ECEF
    const Distance& x = rEcef[0];
    const Distance& y = rEcef[1];
    const Distance& z = rEcef[2];

    // Compute derived quantities
    const Distance r          = rEci.norm();
    const Unitless xOverR     = x / r;
    const Unitless yOverR     = y / r;
    const Unitless zOverR     = z / r;
    const Unitless rEqOverR   = equitorialR / r;
    const Unitless rEqOverRSq = pow<2>(rEqOverR);

    // Initialize V and W matrices
    // V[n][m] and W[n][m] for n=0 to degree, m=0 to order
    std::vector<std::vector<Unitless>> V(_degree + 2);
    std::vector<std::vector<Unitless>> W(_degree + 2);

    for (std::size_t n = 0; n <= _degree + 1; ++n) {
        V[n].resize(_order + 2, 0.0 * one);
        W[n].resize(_order + 2, 0.0 * one);
    }

    // Compute V and W using recurrence relations (Montenbruck & Gill Eq. 3.33)
    // Base case: V[0][0] = Re/r, W[0][0] = 0
    V[0][0] = rEqOverR;

    // Combined recursion for V[n][m] and W[n][m]
    for (std::size_t m = 0; m <= _order + 1; ++m) {
        const Unitless mm = static_cast<double>(m) * one;

        for (std::size_t n = (m == 0 ? 1 : m); n <= _degree + 1; ++n) {
            const Unitless nn = static_cast<double>(n) * one;

            if (m == 0) {
                // First column recursion: V[n][0] and W[n][0]
                V[n][0] = ((2.0 * nn - 1.0) / nn) * zOverR * rEqOverR * V[n - 1][0];
                if (n > 1) { V[n][0] -= ((nn - 1.0) / nn) * rEqOverRSq * V[n - 2][0]; }
            }
            else if (n == m) {
                // Diagonal recursion: V[m][m] and W[m][m]
                V[m][m] = (2.0 * mm - 1.0) * rEqOverR * (xOverR * V[m - 1][m - 1] - yOverR * W[m - 1][m - 1]);
                W[m][m] = (2.0 * mm - 1.0) * rEqOverR * (xOverR * W[m - 1][m - 1] + yOverR * V[m - 1][m - 1]);
            }
            else {
                // General recursion for n > m
                const Unitless factor1 = rEqOverR * zOverR * (2.0 * nn - 1.0) / (nn - mm);
                const Unitless factor2 = rEqOverRSq * (nn + mm - 1.0) / (nn - mm);

                V[n][m] = factor1 * V[n - 1][m];
                W[n][m] = factor1 * W[n - 1][m];

                if (n > 2) {
                    V[n][m] -= factor2 * V[n - 2][m];
                    W[n][m] -= factor2 * W[n - 2][m];
                }
            }
        }
    }

    // Compute acceleration components using V and W
    // Following Montenbruck & Gill Eq. 3.35
    Unitless ax = 0.0 * one;
    Unitless ay = 0.0 * one;
    Unitless az = 0.0 * one;
    for (std::size_t m = 0; m <= _order; ++m) {
        const Unitless mm = static_cast<double>(m) * one;

        for (std::size_t n = m; n <= _degree; ++n) {
            const Unitless nn = static_cast<double>(n) * one;

            const Unitless Nnm = _legendreCache.get_normalizing_coefficient(n, m);
            const Unitless Cnm = _legendreCache.get_cosine_coefficient(n, m) * Nnm;
            const Unitless Snm = _legendreCache.get_sine_coefficient(n, m) * Nnm;

            if (m == 0) {
                // Special case for m = 0 (zonal harmonics)
                ax += -Cnm * V[n + 1][1];
                ay += -Cnm * W[n + 1][1];
            }
            else {
                // Sectoral and tesseral harmonics (m > 0)
                const Unitless nmFactor = (nn - mm + 2.0) * (nn - mm + 1.0);

                // ax component
                ax += 0.5 * ((-Cnm * V[n + 1][m + 1] - Snm * W[n + 1][m + 1]) +
                             nmFactor * (Cnm * V[n + 1][m - 1] + Snm * W[n + 1][m - 1]));

                // ay component
                ay += 0.5 * ((-Cnm * W[n + 1][m + 1] + Snm * V[n + 1][m + 1]) +
                             nmFactor * (-Cnm * W[n + 1][m - 1] + Snm * V[n + 1][m - 1]));
            }

            // az component
            az += (nn - mm + 1.0) * (-Cnm * V[n + 1][m] - Snm * W[n + 1][m]);
        }
    }

    // Scale by mu/r^2
    const Acceleration muOverR2 = mu / (equitorialR * equitorialR);
    const AccelerationVector<frames::earth::earth_fixed> accelOblatenessEcef = { ax * muOverR2, ay * muOverR2, az * muOverR2 };

    // Transform back to inertial frame - original values are in ecef, not w.r.t ecef
    return accelOblatenessEcef.in_frame<frames::earth::icrf>(date);
}

} // namespace astro
} // namespace astrea