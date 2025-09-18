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

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/angular_coordinates.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/utilities/conversions.hpp>


namespace astrea {
namespace astro {

using namespace mp_units;
using namespace mp_units::angular;

OblatenessForce::OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& _N, const std::size_t& _M) :
    N(_N),
    M(_M),
    center(sys.get_center())
{
    // Size arrays (size Legendre array now so it only happens once)
    size_vectors(N, M);

    // Read coefficients from file
    ingest_legendre_coefficient_file(N, M);
}

void OblatenessForce::size_vectors(const std::size_t& N, const std::size_t& M)
{
    C.resize(N + 1);
    S.resize(N + 1);
    P.resize(N + 1);
    normalizingCoefficients.resize(N + 1);
    for (std::size_t n = 0; n < N + 1; ++n) {
        C[n].resize(M + 1);
        S[n].resize(M + 1);
        P[n].resize(M + 1);
        normalizingCoefficients[n].resize(M + 1);
    }
}


void OblatenessForce::ingest_legendre_coefficient_file(const std::size_t& N, const std::size_t& M)
{

    // Open coefficients file
    std::filesystem::path path = std::string(std::getenv("ASTREA_ROOT")) + "/data/gravity_models/";
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

        C[n][m] = lineData[2];
        S[n][m] = lineData[3];
        for (std::size_t m = 0; m < N + 1; ++m) {
            Unitless factorialCoefficient = 1.0 * one; // !(n + m)/!(n - m)
            for (std::size_t ii = n + m; ii > n - m; --ii) {
                factorialCoefficient *= ii;
            }
            // TODO: This will cause MASSIVE slowdowns for m ~ n >> 1. need a smarter way to do these factorials

            const auto delta              = (m == 0) ? 1 : 2;
            normalizingCoefficients[n][m] = sqrt(delta * (2 * n + 1) / factorialCoefficient);

            // Normalize coefficients if needed
            if (centerName == "Mars") {
                C[n][m] /= normalizingCoefficients[n][m];
                S[n][m] /= normalizingCoefficients[n][m];
            }
        }

        if (n >= N && m >= M) { break; }
    }
    file.close();
}


AccelerationVector<ECI>
    OblatenessForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();

    const quantity<one / astrea::detail::distance_unit> oneOverR = 1.0 / sqrt(x * x + y * y + z * z);

    // Central body properties
    static const GravParam& mu         = center->get_mu();
    static const Distance& equitorialR = center->get_equitorial_radius();
    static const Distance& polarR      = center->get_polar_radius();

    // Find lat and long
    const RadiusVector<ECEF> rEcef             = state.get_position().in_frame<ECEF>(date);
    const auto [latitude, longitude, altitude] = convert_earth_fixed_to_geodetic(rEcef, equitorialR, polarR);

    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];

    const Unitless sinLat = sin(latitude);
    const Unitless tanLat = tan(latitude);

    // Populate Legendre polynomial array
    assign_legendre(sinLat);

    // Calculate serivative of gravitational potential field with respect to
    Unitless dVdr_   = 0.0 * one; // radius
    Unitless dVdlat_ = 0.0 * one; // geocentric latitude
    Unitless dVdlon_ = 0.0 * one; // longitude
    for (std::size_t n = 2; n < N + 1; ++n) {
        const Unitless nn = (double)n * one;

        // Reset inner sums
        Unitless dVdrInnerSum   = 0.0 * one;
        Unitless dVdlatInnerSum = 0.0 * one;
        Unitless dVdlonInnerSum = 0.0 * one;
        for (std::size_t m = 0; m < std::min(n, M) + 1; ++m) {
            const Unitless mm = (double)m * one;

            // Precalculate common terms
            const Unitless cosMLon = cos(mm * longitude);
            const Unitless sinMLon = sin(mm * longitude);
            const Unitless term    = (C[n][m] * cosMLon + S[n][m] * sinMLon);

            // dVdr
            dVdrInnerSum += term * P[n][m];

            // dVdlat
            dVdlatInnerSum += term * (P[n][m + 1] - mm * tanLat * P[n][m]);

            // dVdlon
            dVdlonInnerSum += mm * P[n][m] * (S[n][m] * cosMLon - C[n][m] * sinMLon);
        }
        // Precalculate common terms
        Unitless rRatio = 1.0 * one;
        for (std::size_t ii = 0; ii < n; ii++) { // TODO: Make this a pow function for unitless only
            rRatio *= equitorialR * oneOverR;
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
    AccelerationVector<ECEF> accelOblatenessEcef = { term1 * xEcef - term2 * yEcef,
                                                     term1 * yEcef + term2 * xEcef,
                                                     oneOverR * (dVdr * z + oneOverR * planarR * dVdlat) };

    // Rotate back into inertial coordinates (no accel conversions required)
    return accelOblatenessEcef.in_frame<ECI>(date);
}

void OblatenessForce::assign_legendre(const Unitless& x) const
{
    for (std::size_t n = 0; n < N + 1; ++n) {
        for (std::size_t m = 0; m < M + 1; ++m) {
            P[n][m] = normalizingCoefficients[n][m] * math::assoc_legendre(n, m, x);
        }
    }
}

} // namespace astro
} // namespace astrea