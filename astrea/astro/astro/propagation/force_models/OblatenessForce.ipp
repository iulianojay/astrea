/*
 * The G_degree_U Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the G_degree_U Lesser General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version. Astrea is distributed in the hope that it will be useful, but WITHOUT A_degree_Y WARRA_degree_TY;
 * without even the implied warranty of _order_ERCHA_degree_TABILITY or FIT_degree_ESS FOR A PARTICULAR PURPOSE. See the
 * G_degree_U Lesser General Public License for more details. You should have received a copy of the G_degree_U General
 * Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

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

#include <astro/astro.macros.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/transformations.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_utilities.hpp>
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

template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
LegendreCache<_body_, _degree_, _order_>::LegendreCache()
{
    // Open coefficients file
    // TODO: Attach these files to the CelestialBody class
    // TODO: Change to binary files cause boy are these big
    static const std::filesystem::path path = std::string(_ASTRO_ROOT_) + "/data/gravity_models";
    std::filesystem::path filename;
    if constexpr (_body_ == planets::Mercury) {
        // https://pds-geosciences.wustl.edu/messenger/mess-h-rss_mla-5-sdp-v1/messrs_1001/data/shadr/
        filename = path / "Mercury" / "jgmess_160a_sha.tab"; // normalized
    }
    else if constexpr (_body_ == planets::Venus) {
        // https://pds-geosciences.wustl.edu/mgn/mgn-v-rss-5-gravity-l2-v1/mg_5201/gravity/
        filename = path / "Venus" / "shgj180u.a01"; // normalized?
    }
    else if constexpr (_body_ == planets::Earth) {
        filename = path / "Earth" / "EGM2008_to2190_ZeroTide_mod.txt"; // normalized
        // filename = path / "Earth" / "WGS84"; // normalized
        // filename = path / "Earth" / "NASA_6DoF"; // normalized - only goes to 8x8
    }
    else if constexpr (_body_ == moons::Moon) {
        // https://pds-geosciences.wustl.edu/grail/grail-l-lgrs-5-rdr-v1/grail_1001/shadr/
        filename = path / "Moon" / "jggrx_0420a_sha.tab"; // normalized?
    }
    else if constexpr (_body_ == planets::Mars) {
        // https://pds-geosciences.wustl.edu/mro/mro-m-rss-5-sdp-v1/mrors_1xxx/data/shadr/
        filename = path / "Mars" / "jgmro_120f_sha.tab"; // normalized?
    }
    else {
        throw std::runtime_error("Legendre coefficient file for central body, " + decltype(_body_)::name.portable() + ", not found.");
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

        if (n >= _degree_ && m >= _order_) { break; }
    }
    file.close();

    // Calculate normalization coefficients after reading all coefficients
    if (_body_ == planets::Mars) {
        // The Mars file is already normalized, so skip this step for Mars
        return;
    }

    for (std::size_t n = 0; n <= _degree_; ++n) {
        Unitless previousRatio = 0.0 * one;
        for (std::size_t m = 0; m <= std::min(n, _order_); ++m) {
            // Calculate (n + m)!/(n - m)! = (n - m + 1)(n - m + 2)...(n + m)
            const Unitless ratio = (m == 0) ? 1.0 * one : previousRatio * (n + m) * (n - m + 1);
            previousRatio        = ratio;

            // sqrt( (2 - delta_m0) * (2n + 1) * (n - m)! / (n + m)! )
            // delta = 1 if m = 0, else 0
            const unsigned int delta = (m == 0) ? 1 : 0;
            const Unitless Nnm       = sqrt((2 - delta) * (2 * n + 1) / ratio);

            // Pre-normalize coefficients
            _C[n][m] *= Nnm;
            _S[n][m] *= Nnm;
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


template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
Unitless LegendreCache<_body_, _degree_, _order_>::get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const
{
    return _C[n][m];
}


template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
Unitless LegendreCache<_body_, _degree_, _order_>::get_sine_coefficient(const std::size_t& n, const std::size_t& m) const
{
    return _S[n][m];
}

/*
For the life of me, I could not get this to match the _degree_ASA checkcases. I can't find anything wrong with it. If you figure
it out, let me know.

AccelerationVector<frames::primary>
    OblatenessForce::compute_perturbation(const State& state, const Vehicle& vehicle) const
{
    // Central body properties
    const GravParam& mu         = get_mu<frames::primary.origin>();

    // Find lat and lon
    const RadiusVector<frames::primary> rEci = state.get_position();
    const RadiusVector<frames::primary_fixed> rEcef = state.get_position().in_frame<frames::primary_fixed>(date);
    const auto [latitude, longitude, altitude] = convert_body_fixed_to_geocentric(rEcef);

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

            const Unitless cos_order_Lon      = cos(mm * longitude);
            const Unitless sin_order_Lon      = sin(mm * longitude);
            const Unitless cCosPlusSSin = (Cnm * cos_order_Lon + Snm * sin_order_Lon);

            // dVdr
            dVdrInnerSum += cCosPlusSSin * Pnm;

            // dVdlat
            Unitless dPnmdLat = mm * tanLat * Pnm;
            if (m < n) { dPnmdLat += sqrt((nn - mm) * (nn + mm + 1.0)) * P[n][m + 1] * cosLat; }
            dVdlatInnerSum += cCosPlusSSin * dPnmdLat;

            // dVdlon
            dVdlonInnerSum += mm * Pnm * (Snm * cos_order_Lon - Cnm * sin_order_Lon);
        }

        // Precalculate common terms
        const Unitless rRatio = astrea::math::pow(equitorialROverR, nn);

        //
        //  V      =  mu/r   * sum(n=0->_degree_) (Re/r)^n        * sum(m=0->min(n,_order_))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //
        //  dVdr   = -mu/r^2 * sum(n=0->_degree_) (n + 1)(Re/r)^n * sum(m=0->min(n,_order_))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //  dVdlat =  mu/r   * sum(n=0->_degree_) (Re/r)^n        * sum(m=0->min(n,_order_)) dPnm(sin(lat))/dlat * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //  dVdlon =  mu/r   * sum(n=0->_degree_) (Re/r)^n        * sum(m=0->min(n,_order_))   m * Pnm(sin(lat)) * (Snm*cos(m*lon) - Cnm*sin(m*lon))
        //

        dVdrOuterSum += rRatio * (nn + 1.0) * dVdrInnerSum;
        dVdlatOuterSum += rRatio * dVdlatInnerSum;
        dVdlonOuterSum += rRatio * dVdlonInnerSum;
    }

    // Correct
    const GravParam muOverR = mu * oneOverR; // km^2/s^2

    const auto dVdr   = -dVdrOuterSum * (muOverR * oneOverR); // km/s^2
    const auto dVdlat = dVdlatOuterSum * muOverR;             // km^2/s^2
    const auto dVdlon = dVdlonOuterSum * muOverR;             // km^2/s^2

    // Calculate partials of radius, geocentric latitude, and longitude with respect to radius in Ecef frame
    const auto term1 = oneOverR * (dVdr - zEcef * oneOverR / rho * dVdlat);
    const auto term2 = dVdlon / (rho * rho);

    // Calculate accel in ECEF (not with respect to ECEF)
    const AccelerationVector<frames::primary_fixed> accelOblatenessEcef = {
        term1 * xEcef - term2 * yEcef,                      //
        term1 * yEcef + term2 * xEcef,                      //
        oneOverR * (dVdr * zEcef + oneOverR * rho * dVdlat) //
    };

    // Rotate back into inertial coordinates (no accel conversions required)
    const AccelerationVector<frames::primary> accelOblatenessIcrf = accelOblatenessEcef.in_frame<frames::primary>(date);
    static bool compare = true;
    if (compare) { // TODO: Remove this
        const AccelerationVector<frames::primary> gravity = -mu / pow<3>(rEci.norm()) * rEci;
        AccelerationVector<frames::primary> expected      = { 5.51387371235876 * m / (s * s),
                                                                  -1.22700119262805 * m / (s * s),
                                                                  -6.62056474851441 * m / (s * s) };
        expected -= gravity;

        const AccelerationVector<frames::primary> diff = accelOblatenessIcrf - expected;

        std::cout << "Expected Accel: " << expected << " (" << expected.norm() << ")" << std::endl;
        std::cout << "Computed Accel: " << accelOblatenessIcrf << " (" << accelOblatenessIcrf.norm() << ")" << std::endl;
        std::cout << "Difference: " << diff << " (" << diff.norm() << ")" << std::endl;
        std::cout << "% Diff: [" << diff[0] / expected[0] * 100.0 << " %, " << diff[1] / expected[1] * 100.0 << " %, "
                  << diff[2] / expected[2] * 100.0 << " %] (" << diff.norm() / expected.norm() * 100.0 << " %)" << std::endl;

        compare = false;
    }
    return accelOblatenessIcrf;
}
*/

template <IsCelestialBody auto _body_, std::size_t _degree_, std::size_t _order_>
Perturbation OblatenessForce<_body_, _degree_, _order_>::compute_perturbation(const State& state, const Vehicle& vehicle) const
{
    // _order_ontenbruck & Gill (2000) V and W recurrence relations method
    // Reference: Satellite Orbits: _order_odels, _order_ethods and Applications, O. _order_ontenbruck and E. Gill, Springer, 2000

    // Central body properties
    const GravParam& mu         = get_mu<_body_>();
    const Distance& equitorialR = get_equitorial_radius<_body_>();

    // Transform position to body-fixed frame
    const Date date                                 = state.get_epoch();
    const RadiusVector<frames::primary> rEci        = state.get_position();
    const RadiusVector<frames::primary_fixed> rEcef = rEci.in_frame<frames::primary_fixed>(date);

    // Position components in ECEF
    const Distance& x = rEcef[0];
    const Distance& y = rEcef[1];
    const Distance& z = rEcef[2];

    // Compute derived quantities
    const Distance r          = rEcef.norm();
    const Unitless xOverR     = x / r;
    const Unitless yOverR     = y / r;
    const Unitless zOverR     = z / r;
    const Unitless rEqOverR   = equitorialR / r;
    const Unitless rEqOverRSq = pow<2>(rEqOverR);

    // Initialize V and W as flat 1D arrays (row-major, stride = _order_ + 2)
    // Access element [n][m] as V[n * stride + m], W[n * stride + m]
    static constexpr std::size_t stride = _order_ + 2;
    static std::array<Unitless, (_degree_ + 2) * stride> V{};
    static std::array<Unitless, (_degree_ + 2) * stride> W{};

    // Compute V and W using recurrence relations (_order_ontenbruck & Gill Eq. 3.33)
    // Base case: V[0][0] = Re/r, W[0][0] = 0
    V[0] = rEqOverR;

    // Combined recursion for V[n][m] and W[n][m]
    for (std::size_t m = 0; m <= _order_; ++m) {
        for (std::size_t n = (m == 0 ? 1 : m); n <= _degree_; ++n) {

            if (m == 0) {
                // First column recursion: V[n][0] and W[n][0]
                V[n * stride] = ((2.0 * n - 1.0) / n) * zOverR * rEqOverR * V[(n - 1) * stride];
                if (n > 1) { V[n * stride] -= ((n - 1.0) / n) * rEqOverRSq * V[(n - 2) * stride]; }
            }
            else if (n == m) {
                // Diagonal recursion: V[m][m] and W[m][m]
                V[m * stride + m] = (2.0 * m - 1.0) * rEqOverR *
                                    (xOverR * V[(m - 1) * stride + (m - 1)] - yOverR * W[(m - 1) * stride + (m - 1)]);
                W[m * stride + m] = (2.0 * m - 1.0) * rEqOverR *
                                    (xOverR * W[(m - 1) * stride + (m - 1)] + yOverR * V[(m - 1) * stride + (m - 1)]);
            }
            else {
                // General recursion for n > m
                const Unitless factor1 = rEqOverR * zOverR * (2.0 * n - 1.0) / (n - m);
                const Unitless factor2 = rEqOverRSq * (n + m - 1.0) / (n - m);

                V[n * stride + m] = factor1 * V[(n - 1) * stride + m];
                W[n * stride + m] = factor1 * W[(n - 1) * stride + m];

                if (n > 2) {
                    V[n * stride + m] -= factor2 * V[(n - 2) * stride + m];
                    W[n * stride + m] -= factor2 * W[(n - 2) * stride + m];
                }
            }
        }
    }

    // Compute acceleration components using V and W
    // Following _order_ontenbruck & Gill Eq. 3.35
    Unitless ax = 0.0 * one;
    Unitless ay = 0.0 * one;
    Unitless az = 0.0 * one;
    for (std::size_t m = 0; m <= _order_; ++m) {
        for (std::size_t n = m; n <= _degree_; ++n) {

            const Unitless Cnm = _legendreCache.get_cosine_coefficient(n, m);
            const Unitless Snm = _legendreCache.get_sine_coefficient(n, m);

            if (m == 0) {
                // Special case for m = 0 (zonal harmonics)
                ax += -Cnm * V[(n + 1) * stride + 1];
                ay += -Cnm * W[(n + 1) * stride + 1];
            }
            else {
                // Sectoral and tesseral harmonics (m > 0)
                const Unitless nmFactor = (n - m + 2.0) * (n - m + 1.0);

                // ax component
                ax += 0.5 * ((-Cnm * V[(n + 1) * stride + (m + 1)] - Snm * W[(n + 1) * stride + (m + 1)]) +
                             nmFactor * (Cnm * V[(n + 1) * stride + (m - 1)] + Snm * W[(n + 1) * stride + (m - 1)]));

                // ay component
                ay += 0.5 * ((-Cnm * W[(n + 1) * stride + (m + 1)] + Snm * V[(n + 1) * stride + (m + 1)]) +
                             nmFactor * (-Cnm * W[(n + 1) * stride + (m - 1)] + Snm * V[(n + 1) * stride + (m - 1)]));
            }

            // az component
            az += (n - m + 1.0) * (-Cnm * V[(n + 1) * stride + m] - Snm * W[(n + 1) * stride + m]);
        }
    }

    // Scale by mu/r^2
    const Acceleration muOverR2 = mu / (equitorialR * equitorialR);
    const AccelerationVector<frames::primary_fixed> accelOblatenessEcef = { ax * muOverR2, ay * muOverR2, az * muOverR2 };

    // Transform back to inertial frame without abberations - original values are in ecef, not w.r.t ecef
    const AccelerationVector<frames::primary> accelOblatenessIcrf =
        frames::rotate_vector_into_frame<frames::primary>(accelOblatenessEcef, date);
    return { .force = (accelOblatenessIcrf * vehicle.get_mass()) };
}

} // namespace astro
} // namespace astrea