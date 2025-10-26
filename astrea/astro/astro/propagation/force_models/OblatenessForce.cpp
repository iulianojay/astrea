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
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;


LegendreCache::LegendreCache(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order)
{
    // Size arrays (size Legendre array now so it only happens once)
    size_vectors(degree, order);

    // Read coefficients from file
    ingest_legendre_coefficient_file(degree, order, sys.get_central_body());
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


void LegendreCache::ingest_legendre_coefficient_file(const std::size_t& degree, const std::size_t& order, const std::unique_ptr<CelestialBody>& center)
{
    // Open coefficients file
    // TODO: Attach these files to the CelestialBody class
    std::filesystem::path path = std::string(std::getenv("ASTREA_ROOT")) + "astrea/astro/data/gravity_models/";
    std::filesystem::path filename;
    std::string centerName = center->get_name();
    if (centerName == "Venus") {          // Venus
        filename = path / "shgj120p.txt"; // Normalized?
    }
    else if (centerName == "Earth") {                        // Earth
        filename = path / "EGM2008_to2190_ZeroTide_mod.txt"; // Normalized
    }
    else if (centerName == "Moon") {      // Moon
        filename = path / "jgl165p1.txt"; // Normalized?
    }
    else if (centerName == "Mars") {       // Mars
        filename = path / "%sgmm3120.txt"; // Do not appear to be normalized
    }
    std::ifstream file(filename);

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
        for (std::size_t m = 0; m < degree + 1; ++m) {
            Unitless factorialCoefficient = 1.0 * one; // !(n + m)/!(n - m)
            for (std::size_t ii = n + m; ii > n - m; --ii) {
                factorialCoefficient *= ii;
            }
            // TODO: This will cause MASSIVE slowdowns for m ~ n >> 1. need a smarter way to do these factorials

            const auto delta               = (m == 0) ? 1 : 2;
            _normalizingCoefficients[n][m] = sqrt(delta * (2 * n + 1) / factorialCoefficient);

            // Normalize coefficients if needed
            if (centerName == "Mars") {
                _C[n][m] /= _normalizingCoefficients[n][m];
                _S[n][m] /= _normalizingCoefficients[n][m];
            }
        }

        if (n >= degree && m >= order) { break; }
    }
    file.close();
}


void LegendreCache::assign_legendre(const std::size_t& degree, const std::size_t& order, const Unitless& x)
{
    for (std::size_t n = 2; n < degree + 1; ++n) {
        for (std::size_t m = 0; m < order + 1; ++m) {
            _P[n][m] = _normalizingCoefficients[n][m] * math::assoc_legendre(n, m, x);
        }
    }
}


Unitless LegendreCache::get_legendre_polynomial(const std::size_t& n, const std::size_t& m, const Unitless& x) const
{
    return _normalizingCoefficients[n][m] * math::assoc_legendre(n, m, x);
}


Unitless LegendreCache::get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const { return _C[n][m]; }


Unitless LegendreCache::get_sine_coefficient(const std::size_t& n, const std::size_t& m) const { return _S[n][m]; }


OblatenessForce::OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& degree, const std::size_t& order) :
    _degree(degree),
    _order(order),
    _center(sys.get_central_body()),
    _legendreCache(sys, degree, order)
{
}


AccelerationVector<frames::earth::icrf>
    OblatenessForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();

    const quantity<one / astrea::detail::distance_unit> oneOverR = 1.0 / sqrt(x * x + y * y + z * z);

    // Central body properties
    const GravParam& mu         = _center->get_mu();
    const Distance& equitorialR = _center->get_equitorial_radius();
    const Distance& polarR      = _center->get_polar_radius();

    // Find lat and long
    const RadiusVector<frames::earth::earth_fixed> rEcef = state.get_position().in_frame<frames::earth::earth_fixed>(date);
    const auto [latitude, longitude, altitude] = convert_earth_fixed_to_geodetic(rEcef, equitorialR, polarR);

    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];

    const Unitless sinLat = sin(latitude);
    const Unitless tanLat = tan(latitude);

    // // Populate Legendre polynomial array
    // assign_legendre(sinLat);

    // Calculate serivative of gravitational potential field with respect to
    Unitless dVdr_   = 0.0 * one; // radius
    Unitless dVdlat_ = 0.0 * one; // geocentric latitude
    Unitless dVdlon_ = 0.0 * one; // longitude
    for (std::size_t n = 2; n < _degree + 1; ++n) {
        const Unitless nn = (double)n * one;

        /*
            V(r, lat, lon) = mu/r * sum(n=0->N) (Re/r)^n * sum(m=0->min(n,M)) (Cnm*cos(m*lon) + Snm*sin(m*lon)) * Pnm(sin(lat))
            dVdr = -mu/r^2 * sum(n=0->N) (n + 1)(Re/r)^n * sum(m=0->min(n,M)) (Cnm*cos(m*lon) + Snm*sin(m*lon)) * Pnm(sin(lat))
            dVdlat = mu/r * sum(n=0->N) (Re/r)^n * sum(m=0->min(n,M)) (Cnm*cos(m*lon) + Snm*sin(m*lon)) * dPnm(sin(lat))/dlat
            dVdlon = mu/r * sum(n=0->N) (Re/r)^n * sum(m=0->min(n,M)) m * Pnm(sin(lat)) * (Snm*cos(m*lon) - Cnm*sin(m*lon))
        */

        // Reset inner sums
        Unitless dVdrInnerSum   = 0.0 * one;
        Unitless dVdlatInnerSum = 0.0 * one;
        Unitless dVdlonInnerSum = 0.0 * one;
        for (std::size_t m = 0; m < std::min(n, _order) + 1; ++m) {
            const Unitless mm = (double)m * one;

            // Precalculate common terms
            const Unitless Pnm   = _legendreCache.get_legendre_polynomial(n, m, sinLat);
            const Unitless Pnmp1 = _legendreCache.get_legendre_polynomial(n, m + 1, sinLat);
            const Unitless Cnm   = _legendreCache.get_cosine_coefficient(n, m);
            const Unitless Snm   = _legendreCache.get_sine_coefficient(n, m);

            const Unitless cosMLon      = cos(mm * longitude);
            const Unitless sinMLon      = sin(mm * longitude);
            const Unitless cCosPlusSSin = (Cnm * cosMLon + Snm * sinMLon);

            // dVdr
            dVdrInnerSum += cCosPlusSSin * Pnm;

            // dVdlat
            dVdlatInnerSum += cCosPlusSSin * (Pnmp1 - mm * tanLat * Pnm);

            // dVdlon
            dVdlonInnerSum += mm * Pnm * (Snm * cosMLon - Cnm * sinMLon);
        }
        // Precalculate common terms
        Unitless rRatio                 = 1.0 * one;
        const quantity equitorialROverR = equitorialR * oneOverR;
        for (std::size_t ii = 0; ii < n; ii++) { // TODO: Make this a pow function for unitless only
            rRatio *= equitorialROverR;
        }

        // dVdr
        dVdr_ += rRatio * (nn + 1.0) * dVdrInnerSum;

        // dVdlat
        dVdlat_ += rRatio * dVdlatInnerSum;

        // dVdlon
        dVdlon_ += rRatio * dVdlonInnerSum;
    }

    // Correct
    const quantity muOverR = mu * oneOverR; // km^2/s^2

    const quantity dVdr   = -dVdr_ * (muOverR * oneOverR); // km/s^2
    const quantity dVdlat = dVdlat_ * muOverR;             // km^2/s^2
    const quantity dVdlon = dVdlon_ * muOverR;             // TODO: Investigate: My notes say this: dVdlon_ * (muOverR *
                                                           // oneOverR) but units imply what's uncommented -> km^2/s^2

    // Calculate partials of radius, geocentric latitude, and longitude with respect to radius in Ecef frame
    const Distance planarR = sqrt(xEcef * xEcef + yEcef * yEcef); // km

    const quantity term1 = oneOverR * (dVdr - z * oneOverR / planarR * dVdlat);
    const quantity term2 = dVdlon / (planarR * planarR);

    // Calculate accel in Ecef (not with respect to Ecef)
    AccelerationVector<frames::earth::earth_fixed> accelOblatenessEcef = {
        term1 * xEcef - term2 * yEcef, term1 * yEcef + term2 * xEcef, oneOverR * (dVdr * z + oneOverR * planarR * dVdlat)
    };

    // Rotate back into inertial coordinates (no accel conversions required)
    return accelOblatenessEcef.in_frame<frames::earth::icrf>(date);
}

} // namespace astro
} // namespace astrea