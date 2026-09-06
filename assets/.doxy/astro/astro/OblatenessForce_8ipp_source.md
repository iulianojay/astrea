

# File OblatenessForce.ipp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**OblatenessForce.ipp**](OblatenessForce_8ipp.md)

[Go to the documentation of this file](OblatenessForce_8ipp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version. Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details. You should have received a copy of the GNU General
 * Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <iostream>
#include <string>

#include <mp-units/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <math/operations.hpp>
#include <math/trig.hpp>

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
namespace astro {

/*
For the life of me, I could not get this to match the NASA checkcases. I can't find anything wrong with it. If you figure
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
        //  V      =  mu/r   * sum(n=0->_degree_) (Re/r)^n        * sum(m=0->min(n,M))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //
        //  dVdr   = -mu/r^2 * sum(n=0->_degree_) (n + 1)(Re/r)^n * sum(m=0->min(n,M))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //  dVdlat =  mu/r   * sum(n=0->_degree_) (Re/r)^n        * sum(m=0->min(n,M)) dPnm(sin(lat))/dlat * (Cnm*cos(m*lon) + Snm*sin(m*lon))
        //  dVdlon =  mu/r   * sum(n=0->_degree_) (Re/r)^n        * sum(m=0->min(n,M))   m * Pnm(sin(lat)) * (Snm*cos(m*lon) - Cnm*sin(m*lon))
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
    // Montenbruck & Gill (2000) V and W recurrence relations method
    // Reference: Satellite Orbits: Models, Methods and Applications, O. Montenbruck and E. Gill, Springer, 2000

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
    const Distance r           = rEcef.norm();
    const Unitless xOverR      = x / r;
    const Unitless yOverR      = y / r;
    const Unitless zOverR      = z / r;
    const Unitless rEqOverR    = equitorialR / r;
    const Unitless zREqOverRSq = zOverR * rEqOverR;
    const Unitless rEqOverRSq  = pow<2>(rEqOverR);

    // Initialize V and W as flat 1D arrays (row-major, stride = _order_ + 2)
    // Access element [n][m] as V[n * stride + m], W[n * stride + m]
    static constexpr std::size_t stride = _order_ + 2;
    std::array<Unitless, (_degree_ + 2) * stride> V{};
    std::array<Unitless, (_degree_ + 2) * stride> W{};

    // Compute V and W using recurrence relations (Montenbruck & Gill Eq. 3.33)
    // Base case: V[0][0] = Re/r, W[0][0] = 0
    V[0] = rEqOverR;

    // Combined recursion for V[n][m] and W[n][m]
    for (std::size_t m = 0; m <= _order_; ++m) {
        for (std::size_t n = (m == 0 ? 1 : m); n <= _degree_; ++n) {

            if (m == 0) {
                // First column recursion: V[n][0] and W[n][0]
                V[n * stride] = ((2.0 * n - 1.0) / n) * zREqOverRSq * V[(n - 1) * stride];
                if (n > 1) { V[n * stride] -= ((n - 1.0) / n) * rEqOverRSq * V[(n - 2) * stride]; }
            }
            else if (n == m) {
                // Diagonal recursion: V[m][m] and W[m][m]
                const Unitless factor  = (2.0 * m - 1.0) * rEqOverR;
                const std::size_t idx  = (m - 1) * stride + (m - 1);
                const std::size_t mIdx = m * stride + m;
                V[mIdx]                = factor * (xOverR * V[idx] - yOverR * W[idx]);
                W[mIdx]                = factor * (xOverR * W[idx] + yOverR * V[idx]);
            }
            else {
                // General recursion for n > m
                const Unitless factor1 = zREqOverRSq * (2.0 * n - 1.0) / (n - m);
                const Unitless factor2 = rEqOverRSq * (n + m - 1.0) / (n - m);
                const std::size_t idx1 = (n - 1) * stride + m;
                const std::size_t idx2 = (n - 2) * stride + m;
                const std::size_t mIdx = n * stride + m;

                V[mIdx] = factor1 * V[idx1];
                W[mIdx] = factor1 * W[idx1];

                if (n > 2) {
                    V[mIdx] -= factor2 * V[idx2];
                    W[mIdx] -= factor2 * W[idx2];
                }
            }
        }
    }

    // Compute acceleration components using V and W
    // Following Montenbruck & Gill Eq. 3.35
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
    const Acceleration muOverR2 = mu / pow<2>(equitorialR);
    const AccelerationVector<frames::primary_fixed> accelOblatenessEcef = { ax * muOverR2, ay * muOverR2, az * muOverR2 };

    // Transform back to inertial frame without abberations - original values are in ecef, not w.r.t ecef
    const AccelerationVector<frames::primary> accelOblatenessIcrf =
        frames::rotate_vector_into_frame<frames::primary>(accelOblatenessEcef, date);
    return { .force = (accelOblatenessIcrf * vehicle.get_mass(state)) };
}

} // namespace astro
} // namespace astrea
```


