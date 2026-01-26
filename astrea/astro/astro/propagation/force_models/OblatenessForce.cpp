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
    _P.resize(degree + 1);
    _normalizingCoefficients.resize(degree + 1);
    for (std::size_t n = 0; n < degree + 1; ++n) {
        _C[n].resize(order + 1);
        _S[n].resize(order + 1);
        _P[n].resize(order + 1);
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
            Unitless factorialCoefficient = 1.0 * astrea::detail::unitless;
            for (std::size_t ii = n - m + 1; ii <= n + m; ++ii) {
                factorialCoefficient *= ii;
            }
            // TODO: This will cause big slowdowns for m ~ n >> 1. need a smarter way to do these factorials.
            // Should be a way to do this recursively using previous values from earlier n and m calculations.

            // sqrt( (2 - delta_m0) * (2n + 1) * (n - m)! / (n + m)! )
            // delta = 1 if m = 0, else 0
            const unsigned int delta       = (m == 0) ? 1 : 0;
            _normalizingCoefficients[n][m] = sqrt((2 - delta) * (2 * n + 1) / factorialCoefficient);

            // Normalize coefficients if needed
            if (centerId == CelestialBodyId::MARS) {
                _C[n][m] /= _normalizingCoefficients[n][m];
                _S[n][m] /= _normalizingCoefficients[n][m];
            }
        }
    }
}


void LegendreCache::assign_legendre(const std::size_t& degree, const std::size_t& order, const Unitless& x)
{
    for (std::size_t n = 2; n < degree + 1; ++n) {
        for (std::size_t m = 0; m < order + 1; ++m) {
            _P[n][m] = _normalizingCoefficients[n][m] * assoc_legendre(n, m, x);
        }
    }
}


Unitless LegendreCache::get_legendre_polynomial(const std::size_t& n, const std::size_t& m, const Unitless& x) const
{
    return _normalizingCoefficients[n][m] * assoc_legendre(n, m, x);
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
    const auto [latitude, longitude, altitude] = convert_earth_fixed_to_geodetic(rEcef, equitorialR, polarR);

    // Precomput common terms
    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];
    const Distance& zEcef = rEcef[2];

    const quantity oneOverR = 1.0 / rEci.norm();

    const Unitless equitorialROverR = equitorialR * oneOverR;

    const Unitless sinLat = sin(latitude);
    const Unitless cosLat = cos(latitude);

    // Calculate serivative of gravitational potential field with respect to
    Unitless dVdr_   = 0.0 * astrea::detail::unitless; // radius
    Unitless dVdlat_ = 0.0 * astrea::detail::unitless; // geocentric latitude
    Unitless dVdlon_ = 0.0 * astrea::detail::unitless; // longitude
    for (std::size_t n = 2; n < _degree + 1; ++n) {
        const Unitless nn = static_cast<double>(n) * astrea::detail::unitless;

        // Reset inner sums
        Unitless dVdrInnerSum   = 0.0 * astrea::detail::unitless;
        Unitless dVdlatInnerSum = 0.0 * astrea::detail::unitless;
        Unitless dVdlonInnerSum = 0.0 * astrea::detail::unitless;
        for (std::size_t m = 0; m < std::min(n, _order) + 1; ++m) {
            const Unitless mm = static_cast<double>(m) * astrea::detail::unitless;

            // Precalculate common terms
            const Unitless Pnm = _legendreCache.get_legendre_polynomial(n, m, sinLat);
            const Unitless Cnm = _legendreCache.get_cosine_coefficient(n, m);
            const Unitless Snm = _legendreCache.get_sine_coefficient(n, m);

            const Unitless cosMLon      = cos(mm * longitude);
            const Unitless sinMLon      = sin(mm * longitude);
            const Unitless cCosPlusSSin = (Cnm * cosMLon + Snm * sinMLon);

            // dVdr
            dVdrInnerSum += cCosPlusSSin * Pnm;

            // dVdlat
            Unitless dPnmdLat = mm * sinLat * Pnm;
            if (m < n) {
                const Unitless Pnmp1 = _legendreCache.get_legendre_polynomial(n, m + 1, sinLat);
                dPnmdLat += cosLat * sqrt((nn - mm) * (nn + mm + 1.0)) * Pnmp1;
            }
            dVdlatInnerSum += cCosPlusSSin * dPnmdLat;

            // dVdlon
            dVdlonInnerSum += mm * Pnm * (Snm * cosMLon - Cnm * sinMLon);
        }

        // Precalculate common terms
        const Unitless rRatio = astrea::math::pow(equitorialROverR, nn);

        /*
            V      =  mu/r   * sum(n=0->N) (Re/r)^n        * sum(m=0->min(n,M))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))

            dVdr   = -mu/r^2 * sum(n=0->N) (n + 1)(Re/r)^n * sum(m=0->min(n,M))       Pnm(sin(lat)) * (Cnm*cos(m*lon) + Snm*sin(m*lon))
            dVdlat =  mu/r   * sum(n=0->N) (Re/r)^n        * sum(m=0->min(n,M)) dPnm(sin(lat))/dlat * (Cnm*cos(m*lon) + Snm*sin(m*lon))
            dVdlon =  mu/r   * sum(n=0->N) (Re/r)^n        * sum(m=0->min(n,M))   m * Pnm(sin(lat)) * (Snm*cos(m*lon) - Cnm*sin(m*lon))
        */

        dVdr_ += rRatio * (nn + 1.0) * dVdrInnerSum;
        dVdlat_ += rRatio * dVdlatInnerSum;
        dVdlon_ += rRatio * dVdlonInnerSum;
    }

    // Correct
    const quantity muOverR = mu * oneOverR; // km^2/s^2

    const Acceleration dVdr = -dVdr_ * (muOverR * oneOverR); // km/s^2
    const quantity dVdlat   = dVdlat_ * muOverR;             // km^2/s^2
    const quantity dVdlon   = dVdlon_ * muOverR; // TODO: Investigate: My notes say this: dVdlon_ * (muOverR *
                                                 // oneOverR) but units imply what's uncommented -> km^2/s^2

    // Calculate partials of radius, geocentric latitude, and longitude with respect to radius in Ecef frame
    const Distance planarR = sqrt(xEcef * xEcef + yEcef * yEcef); // km

    const quantity term1 = oneOverR * (dVdr - zEcef * oneOverR / planarR * dVdlat);
    const quantity term2 = dVdlon / (planarR * planarR);

    // Calculate accel in ECEF (not with respect to ECEF)
    AccelerationVector<frames::earth::earth_fixed> accelOblatenessEcef = {
        term1 * xEcef - term2 * yEcef,                          //
        term1 * yEcef + term2 * xEcef,                          //
        oneOverR * (dVdr * zEcef + oneOverR * planarR * dVdlat) //
    };

    // Rotate back into inertial coordinates (no accel conversions required)
    const AccelerationVector<frames::earth::icrf> accelOblatenessIcrf = accelOblatenessEcef.in_frame<frames::earth::icrf>(date);
    static bool compare = true;
    if (compare) { // TODO: Remove this
        const AccelerationVector<frames::earth::icrf> gravity = -mu / pow<3>(rEci.norm()) * rEci;
        AccelerationVector<frames::earth::icrf> expected      = { 5.51387371235876 * m / (s * s),
                                                                  -1.22700119262805 * m / (s * s),
                                                                  -6.62056474851441 * m / (s * s) };
        expected -= gravity;

        const AccelerationVector<frames::earth::icrf> diff = accelOblatenessIcrf - expected;

        std::cout << "Expected Accel: " << expected << " (" << expected.norm() << ")" << std::endl;
        std::cout << "Computed Accel: " << accelOblatenessIcrf << " (" << accelOblatenessIcrf.norm() << ")" << std::endl;
        std::cout << "Difference: " << diff << " (" << diff.norm() << ")" << std::endl;
        std::cout << "% Diff: [" << diff[0] / expected[0] * 100.0 << " %, " << diff[1] / expected[1] * 100.0 << " %, "
                  << diff[2] / expected[2] * 100.0 << " %] (" << diff.norm() / expected.norm() * 100.0 << " %)" << std::endl;

        compare = false;
    }
    return accelOblatenessIcrf;
}

} // namespace astro
} // namespace astrea