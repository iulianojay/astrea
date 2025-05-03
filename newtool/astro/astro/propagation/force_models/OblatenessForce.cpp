#include <astro/propagation/force_models/OblatenessForce.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;
using namespace mp_units::iau::unit_symbols;

namespace astro {

OblatenessForce::OblatenessForce(const AstrodynamicsSystem& sys, const size_t& _N, const size_t& _M) :
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
    for (size_t n = 0; n < N + 1; ++n) {
        const quantity nn = (double)n * one;

        for (size_t m = 0; m < M + 1; ++m) {
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

void OblatenessForce::size_vectors(const size_t& N, const size_t& M)
{
    C.resize(N + 1);
    S.resize(N + 1);
    P.resize(N + 1);
    alpha.resize(N + 1);
    beta.resize(N + 1);
    gamma.resize(N + 1);
    Pbase.resize(N + 1);
    for (size_t n = 0; n < N + 1; ++n) {
        C[n].resize(M + 1);
        S[n].resize(M + 1);
        P[n].resize(M + 1);
        alpha[n].resize(M + 1);
        beta[n].resize(M + 1);
        gamma[n].resize(M + 1);
        Pbase[n].resize(M + 1);
    }
}


void OblatenessForce::ingest_legendre_coefficient_file(const size_t& N, const size_t& M)
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

    size_t n = 0, m = 0;
    while (file) {
        // Read line from stream
        std::getline(file, line);
        std::stringstream lineStream(line);
        std::vector<double> lineData;
        while (std::getline(lineStream, cell, ',')) {
            lineData.push_back(std::atof(cell.c_str()));
        }

        n = (size_t)lineData[0];
        m = (size_t)lineData[1];

        C[n][m] = lineData[2];
        S[n][m] = lineData[3];

        // Normalize coefficients if needed
        if (centerName == "Mars") {
            for (size_t m = 0; m < N + 1; ++m) {
                quantity nPlusMFactorial  = 1.0 * one;
                quantity nMinusMFactorial = 1.0 * one;
                for (size_t ii = n + m; ii > 0; --ii) {
                    nPlusMFactorial *= ii;
                    if (ii <= n - m) { nMinusMFactorial *= double(ii) * one; }
                }

                quantity Nnm = (m == 0 * one) ? sqrt(nMinusMFactorial * (2 * n + 1) / nPlusMFactorial) :
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
    OblatenessForce::compute_force(const JulianDate& julianDate, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    // Extract
    const Distance& x       = state.get_x();
    const Distance& y       = state.get_y();
    const Distance& z       = state.get_z();
    const Distance R        = sqrt(x * x + y * y + z * z);
    const quantity oneOverR = 1.0 / R;

    // Central body properties
    static const GravParam& mu                 = center->get_mu();
    static const Distance& equitorialR         = center->get_equitorial_radius();
    static const AngularRate& bodyRotationRate = center->get_rotation_rate();

    // Find lat and long
    RadiusVector radius = { x, y, z };
    RadiusVector rBCBF;
    conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);

    const quantity& xBCBF = rBCBF[0];
    const quantity& yBCBF = rBCBF[1];

    const quantity longitude = atan2(yBCBF, xBCBF);
    const quantity latitude  = asin(z * oneOverR);

    const quantity cosLat = cos(latitude);
    const quantity sinLat = sin(latitude);
    const quantity tanLat = sinLat / cosLat;

    // Populate Legendre polynomial array
    assign_legendre(latitude);

    // Calculate serivative of gravitational potential field with respect to
    quantity dVdr    = 0.0 * one; // radius
    quantity dVdlat  = 0.0 * one; // geocentric latitude
    quantity dVdlong = 0.0 * one; // longitude
    for (size_t n = 2; n < N + 1; ++n) {
        const quantity nn = (double)n * one;

        // Reset inner sums
        quantity dVdrInnerSum    = 0.0 * one;
        quantity dVdlatInnerSum  = 0.0 * one;
        quantity dVdlongInnerSum = 0.0 * one;

        for (size_t m = 0; m < std::min(n, M) + 1; ++m) {
            const quantity mm = (double)m * one;

            // Precalculate common terms
            const quantity cosLongM = cos(mm * longitude);
            const quantity sinLongM = sin(mm * longitude);
            const quantity temp     = (C[n][m] * cosLongM + S[n][m] * sinLongM);

            // dVdr
            dVdrInnerSum += temp * P[n][m];

            // dVdlat
            dVdlatInnerSum += temp * (gamma[n][m] * P[n][m + 1] - mm * tanLat * P[n][m]);

            // dVdlong
            dVdlongInnerSum += mm * (S[n][m] * cosLongM - C[n][m] * sinLongM) * P[n][m];
        }
        // Precalculate common terms
        const quantity rRatio = pow(equitorialR * oneOverR, n);

        // dVdr
        dVdr += rRatio * (nn + 1.0) * dVdrInnerSum;

        // dVdlat
        dVdlat += rRatio * dVdlatInnerSum;

        // dVdlong
        dVdlong += rRatio * dVdlongInnerSum;
    }

    // Correct
    const quantity muOverR = mu * oneOverR;
    dVdr *= muOverR * oneOverR;
    dVdlat *= muOverR;
    dVdlong *= muOverR * oneOverR;

    // Calculate partials of radius, geocentric latitude, and longitude with respect to BCBF frame
    const quantity drdrBCBF[3] = { xBCBF * oneOverR, yBCBF * oneOverR, z * oneOverR };

    const quantity oneOverBcbfR = 1 / sqrt(xBCBF * xBCBF + yBCBF * yBCBF);
    const quantity zOverR2      = z / (R * R);
    const quantity dlatdrBCBF[3] = { -oneOverBcbfR * xBCBF * zOverR2, -oneOverBcbfR * yBCBF * zOverR2, oneOverBcbfR * (1 - z * zOverR2) };

    const quantity muOverR2       = muOverR * muOverR;
    const quantity dlongdrBCBF[3] = { -muOverR2 * yBCBF, muOverR2 * xBCBF, 0.0 };

    // Calculate accel in BCBF (not with respect to BCBF)
    AccelerationVector accelOblatenessBCBF = { dVdr * drdrBCBF[0] + dVdlat * dlatdrBCBF[0] + dVdlong * dlongdrBCBF[0],
                                               dVdr * drdrBCBF[1] + dVdlat * dlatdrBCBF[1] + dVdlong * dlongdrBCBF[1],
                                               dVdr * drdrBCBF[2] + dVdlat * dlatdrBCBF[2] };

    // Rotate back into inertial coordinates
    AccelerationVector accelOblateness;
    conversions::bcbf_to_bci(accelOblatenessBCBF, julianDate, bodyRotationRate, accelOblateness);

    return accelOblateness;
}

void OblatenessForce::assign_legendre(const quantity<km>& latitude) const
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
    const quantity cosLat = cos(latitude);
    const quantity sinLat = sin(latitude);
    for (size_t n = 0; n < N + 1; ++n) {
        const quantity costLatPowN = pow(cosLat, n);
        for (size_t m = 0; m < M + 1; ++m) {
            if (n == m) {
                if (n == 0) { P[n][m] = 1; }
                else {
                    P[n][m] = Pbase[n][m] * costLatPowN;
                }
            }
            else if (n == m + 1) {
                P[n][m] = Pbase[n][m] * sinLat * P[m][m];
            }
            else if (n >= m + 2) {
                P[n][m] = alpha[n][m] * sinLat * P[n - 1][m] + beta[n][m] * P[n - 2][m];
            }
            else {
                P[n][m] = 0.0;
            }
        }
    }
}

} // namespace astro