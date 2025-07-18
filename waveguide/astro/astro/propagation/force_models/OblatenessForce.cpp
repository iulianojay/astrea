#include <astro/propagation/force_models/OblatenessForce.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/isq_angle.h>

#include <math/utils.hpp>

#include <astro/utilities/conversions.hpp>

using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using namespace mp_units::si::unit_symbols;
using namespace mp_units::iau::unit_symbols;

namespace astro {

OblatenessForce::OblatenessForce(const AstrodynamicsSystem& sys, const std::size_t& _N, const std::size_t& _M) :
    N(_N),
    M(_M),
    center(sys.get_center())
{

    // Size arrays (size Legendre array now so it only happens once)
    size_vectors(N, M);

    // Read coefficients from file
    ingest_legendre_coefficient_file(N, M);

    // Precompute as much as possible
    const quantity sqrtOneHalf = sqrt(0.5) * one;
    for (std::size_t n = 0; n < N + 1; ++n) {
        const quantity nn = (double)n * one;

        for (std::size_t m = 0; m < M + 1; ++m) {
            const quantity mm = (double)m * one;

            if (n == m) {
                if (n != 0) {
                    quantity tau = 1.0 * one;
                    for (int ii = 2 * n - 1; ii > 0; ii -= 2) {
                        tau *= (double)ii / ((double)ii + 1.0) * one;
                    }
                    Pbase[n][m] = sqrt(2.0 * (2.0 * nn + 1.0) * tau);
                }
            }
            else if (n == m + 1) {
                Pbase[n][m] = sqrt(2.0 * mm + 3.0);
            }
            else if (n >= m + 2) {
                alpha[n][m] = sqrt((2.0 * nn + 1.0) * (2.0 * nn - 1.0) / ((nn - mm) * (nn + mm)));
                beta[n][m] =
                    sqrt((2.0 * nn + 1.0) * (nn + mm - 1.0) * (nn - mm - 1.0) / ((2.0 * nn - 3.0) * (nn - mm) * (nn + mm)));
            }

            gamma[n][m] = sqrt((nn - mm) * (nn + mm + 1.0));
            if (m == 0) { gamma[n][m] *= sqrtOneHalf; }
        }
    }
}

void OblatenessForce::size_vectors(const std::size_t& N, const std::size_t& M)
{
    C.resize(N + 1);
    S.resize(N + 1);
    P.resize(N + 1);
    alpha.resize(N + 1);
    beta.resize(N + 1);
    gamma.resize(N + 1);
    Pbase.resize(N + 1);
    for (std::size_t n = 0; n < N + 1; ++n) {
        C[n].resize(M + 1);
        S[n].resize(M + 1);
        P[n].resize(M + 1);
        alpha[n].resize(M + 1);
        beta[n].resize(M + 1);
        gamma[n].resize(M + 1);
        Pbase[n].resize(M + 1);
    }
}


void OblatenessForce::ingest_legendre_coefficient_file(const std::size_t& N, const std::size_t& M)
{

    // Open coefficients file
    std::string filename;
    std::string path;
    path                   = "./data/gravity_models/";
    std::string centerName = center->get_name();
    if (centerName == "Venus") {          // Venus
        filename = path + "shgj120p.txt"; // Normalized?
    }
    else if (centerName == "Earth") {                        // Earth
        filename = path + "EGM2008_to2190_ZeroTide_mod.txt"; // Normalized
    }
    else if (centerName == "Moon") {      // Moon
        filename = path + "jgl165p1.txt"; // Normalized?
    }
    else if (centerName == "Mars") {       // Mars
        filename = path + "%sgmm3120.txt"; // Do not appear to be normalized
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

        // Normalize coefficients if needed
        if (centerName == "Mars") {
            for (std::size_t m = 0; m < N + 1; ++m) {
                Unitless nPlusMFactorial  = 1.0 * one;
                Unitless nMinusMFactorial = 1.0 * one;
                for (std::size_t ii = n + m; ii > 0; --ii) {
                    nPlusMFactorial *= ii;
                    if (ii <= n - m) { nMinusMFactorial *= double(ii) * one; }
                }

                Unitless Nnm = (m == 0) ? sqrt(nMinusMFactorial * (2 * n + 1) / nPlusMFactorial) :
                                          sqrt(nMinusMFactorial * (2 * n + 1) * 2 / nPlusMFactorial);

                C[n][m] /= Nnm;
                S[n][m] /= Nnm;
            }
        }

        if (n >= N && m >= M) { break; }
    }
    file.close();
}


AccelerationVector
    OblatenessForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();
    const Distance R  = sqrt(x * x + y * y + z * z);

    const quantity<one / detail::distance_unit> oneOverR = 1.0 / R;

    // Central body properties
    static const GravParam& mu         = center->get_mu();
    static const Distance& equitorialR = center->get_equitorial_radius();

    // Find lat and long
    RadiusVector rEcef = eci_to_ecef(state.get_radius(), date);

    const Distance& xEcef = rEcef[0];
    const Distance& yEcef = rEcef[1];

    const Angle longitude = angular::atan2(yEcef, xEcef);
    const Angle latitude  = angular::asin(z * oneOverR);

    const Unitless cosLat = cos(latitude);
    const Unitless sinLat = sin(latitude);
    const Unitless tanLat = sinLat / cosLat;

    // Populate Legendre polynomial array
    assign_legendre(latitude);

    // Calculate serivative of gravitational potential field with respect to
    Unitless dVdr_    = 0.0 * one; // radius
    Unitless dVdlat_  = 0.0 * one; // geocentric latitude
    Unitless dVdlong_ = 0.0 * one; // longitude
    for (std::size_t n = 2; n < N + 1; ++n) {
        const Unitless nn = (double)n * one;

        // Reset inner sums
        Unitless dVdrInnerSum    = 0.0 * one;
        Unitless dVdlatInnerSum  = 0.0 * one;
        Unitless dVdlongInnerSum = 0.0 * one;

        for (std::size_t m = 0; m < std::min(n, M) + 1; ++m) {
            const Unitless mm = (double)m * one;

            // Precalculate common terms
            const Unitless cosLongM = cos(mm * longitude);
            const Unitless sinLongM = sin(mm * longitude);
            const Unitless temp     = (C[n][m] * cosLongM + S[n][m] * sinLongM);

            // dVdr
            dVdrInnerSum += temp * P[n][m];

            // dVdlat
            dVdlatInnerSum += temp * (gamma[n][m] * P[n][m + 1] - mm * tanLat * P[n][m]);

            // dVdlong
            dVdlongInnerSum += mm * (S[n][m] * cosLongM - C[n][m] * sinLongM) * P[n][m];
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

        // dVdlong
        dVdlong_ += rRatio * dVdlongInnerSum;
    }

    // Correct
    const quantity muOverR = mu * oneOverR; // km^2/s^2

    const quantity dVdr    = dVdr_ * (muOverR * oneOverR); // km/s^2
    const quantity dVdlat  = dVdlat_ * muOverR;            // km^2/s^2
    const quantity dVdlong = dVdlong_ * muOverR; // TODO: Investiage: My notes say this: dVdlong_ * (muOverR * oneOverR)
                                                 // but units imply what's uncommented -> km^2/s^2

    // Calculate partials of radius, geocentric latitude, and longitude with respect to radius in Ecef frame
    const quantity oneOverEcefR   = 1.0 / sqrt(xEcef * xEcef + yEcef * yEcef); // 1/km
    const quantity zOverRSquared  = z / pow<2>(R);                             // 1/km
    const quantity muOverRSquared = pow<2>(muOverR);                           // km^4/s^4

    const std::array<Unitless, 3> drdrEcef = { xEcef * oneOverR, yEcef * oneOverR, z * oneOverR }; // dr/dr -> km/km -> one
    const std::array<quantity<one / detail::distance_unit>, 3> dlatdrEcef = {
        -oneOverEcefR * xEcef * zOverRSquared, -oneOverEcefR * yEcef * zOverRSquared, oneOverEcefR * (1.0 * one - z * zOverRSquared)
    }; // dang/dr -> rad/km
    const std::array<quantity<one / detail::distance_unit>, 3> dlongdrEcef = {
        (-muOverRSquared * yEcef) * (pow<4>(detail::time_unit) / pow<6>(detail::distance_unit)), // TODO: Investigate these units.
        (muOverRSquared * xEcef) * (pow<4>(detail::time_unit) / pow<6>(detail::distance_unit)), // I don't think the weird unit multipy should be required
        0.0 * one / km
    }; // dang/dr -> rad/km

    // Calculate accel in Ecef (not with respect to Ecef)
    AccelerationVector accelOblatenessEcef = { dVdr * drdrEcef[0] + dVdlat * dlatdrEcef[0] + dVdlong * dlongdrEcef[0],
                                               dVdr * drdrEcef[1] + dVdlat * dlatdrEcef[1] + dVdlong * dlongdrEcef[1],
                                               dVdr * drdrEcef[2] + dVdlat * dlatdrEcef[2] };

    // Rotate back into inertial coordinates
    AccelerationVector accelOblateness = ecef_to_eci(accelOblatenessEcef, date);

    return accelOblateness;
}

void OblatenessForce::assign_legendre(const Angle& latitude) const
{
    // Populate Legendre polynomial array
    /*
        Pseudocode:

        P[0][0] = 1;
        for (int n = 1; n < N+1; ++n) { // n = m
            nn = (double)n;
            tau = 1.0;
            for (int ii = 2*n - 1; ii  > 0; ii -= 2) {
                tau *= (double) ii/((double) ii + 1.0);
            }
            P[n][n] = sqrt(2.0*(2.0*nn + 1.0)*tau)*std::pow(cosLat, nn);
        }

        for (int n = 1; n < N+1; ++n) { // n = m + 1
            nn = (double)n;
            P[n][n-1] = sqrt(2.0*(nn - 1.0) + 3.0)*sinLat*P[n-1][n-1];
        }

        Developers Note: Fuck this function
    */
    const Unitless cosLat = cos(latitude);
    const Unitless sinLat = sin(latitude);
    for (std::size_t n = 0; n < N + 1; ++n) {
        Unitless cosLatPowN = 1.0 * one;
        for (std::size_t ii = 0; ii < n; ii++) { // TODO: Make this a pow function for unitless only
            cosLatPowN *= cosLat;
        }
        for (std::size_t m = 0; m < M + 1; ++m) {
            if (n == m) {
                if (n == 0) { P[n][m] = 1; }
                else {
                    P[n][m] = Pbase[n][m] * cosLatPowN;
                }
            }
            else if (n == m + 1) {
                P[n][m] = Pbase[n][m] * sinLat * P[m][m];
            }
            else if (n >= m + 2) {
                P[n][m] = alpha[n][m] * sinLat * P[n - 1][m] + beta[n][m] * P[n - 2][m];
            }
            else {
                P[n][m] = 0.0 * one;
            }
        }
    }
}

} // namespace astro