#include "OblatenessForce.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "math_c.hpp"

OblatenessForce::OblatenessForce(const AstrodynamicsSystem& sys, const size_t& _N, const size_t& _M) : N(_N), M(_M), center(sys.get_center()) {
    // Open coefficients file
    std::string filename;
    std::string path;
    path = "./data/gravity_models/";

    if (center.planetId() == 2) { // Venus
        filename = path + "shgj120p.txt"; // Normalized?
    }
    else if (center.planetId() == 3 && center.moonId() == 0) { // Earth
        filename = path + "EGM2008_to2190_ZeroTide_mod.txt"; // Normalized
    }
    else if (center.planetId() == 3 && center.moonId() == 1) { // Moon
        filename = path + "jgl165p1.txt"; // Normalized?
    }
    else if (center.planetId() == 3) { // Mars
        filename = path + "%sgmm3120.txt"; // Do not appear to be normalized
    }
    std::ifstream file(filename);

    // Size arrays (size Legendre array now so it only happens once)
    C.resize(N + 1);
    S.resize(N + 1);
    P.resize(N + 1);
    for (size_t n = 0; n < N+1; ++n) {
        C[n].resize(M + 1);
        S[n].resize(M + 1);
        P[n].resize(M + 1);
    }

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
        if (center.planetId() == 4) {
            for (size_t m = 0; m < N+1; ++m) {
                double nPlusMFactorial = 1;
                double nMinusMFactorial = 1;
                for (size_t ii = n + m; ii > 0; --ii) {
                    nPlusMFactorial *= ii;
                    if (ii <= n-m) {
                        nMinusMFactorial *= double(ii);
                    }
                }

                double Nnm = (m == 0) ?
                    sqrt(nMinusMFactorial*(2*n + 1)/nPlusMFactorial) :
                        sqrt(nMinusMFactorial*(2*n + 1)*2/nPlusMFactorial);

                C[n][m] /= Nnm;
                S[n][m] /= Nnm;
            }
        }

        if (n >= N && m >= M) { break; }
    }
    file.close();
}

basis_array OblatenessForce::compute_force(const double& julianDate, const OrbitalElements& state, const Spacecraft& vehicle, const AstrodynamicsSystem& sys) const {

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    // Central body properties
    const double& mu = center.mu();
    const double& equitorialR = center.eqR();
    const double& bodyRotationRate = center.rotRate();

    /*
        To clarify this logic: Use J2 if
            1) NxM Oblateness is not selected
            2) N = 2 and M = 0, which is J2
            3) The central body is not Venus, Earth, the Moon, or Mars
            4) If Mars is the planet id, the moon id must be 0 to ensure the central body is not phobos or deimos
    */
    basis_array accelOblateness = {0.0, 0.0, 0.0};
    if ((N == 2 && M == 0) || (center.planetId() != 2 && center.planetId() != 3 && !(center.planetId() == 4 && center.moonId() == 0))) { // J2 oblateness only
        // Variables to reduce calculations
        const double& J2 = center.j2();
        const double tempA = -1.5*J2*mu*equitorialR*equitorialR/pow(R,5);
        const double tempB = z*z/(R*R);

        // accel due to oblateness
        accelOblateness[0] = tempA*(1.0 - 5.0*tempB)*x;
        accelOblateness[1] = tempA*(1.0 - 5.0*tempB)*y;
        accelOblateness[2] = tempA*(1.0 - 3.0*tempB)*z;
    }
    else { // Any NxM gravitational field
        // Find lat and long
        basis_array radius = {x, y, z};
        basis_array rBCBF;
        conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);

        const double& xBCBF = rBCBF[0];
        const double& yBCBF = rBCBF[1];

        const double longitude = atan2(yBCBF,xBCBF);
        const double latitude = asin(z/R);

        const double cosLat = math_c::cos(latitude);
        const double sinLat = math_c::sin(latitude);
        const double tanLat = sinLat/cosLat;

        // Populate Legendre polynomial array
        assign_legendre(latitude);

        // Calculate serivative of gravitational potential field with respect to
        double dVdr = 0.0;       // radius
        double dVdlat = 0.0;     // geocentric latitude
        double dVdlong = 0.0;    // longitude
        for (size_t n = 2; n < N+1; ++n) {
            const double nn = (double)n;

            // Reset inner sums
            double dVdrInnerSum = 0.0;
            double dVdlatInnerSum = 0.0;
            double dVdlongInnerSum = 0.0;

            for (size_t m = 0; m < std::min(n, M)+1; ++m) {
                const double mm = (double) m;

                // Precalculate common terms
                const double cosLongM = math_c::cos(mm*longitude);
                const double sinLongM = math_c::sin(mm*longitude);

                // dVdr
                dVdrInnerSum += (C[n][m]*cosLongM + S[n][m]*sinLongM)*P[n][m];

                //dVdlat
                const double gamma = (m == 0) ? sqrt((nn - mm)*(nn + mm + 1.0)*0.5) : sqrt((nn - mm)*(nn + mm + 1.0));
                dVdlatInnerSum += (C[n][m]*cosLongM + S[n][m]*sinLongM)*(gamma*P[n][m+1] - mm*tanLat*P[n][m]);

                // dVdlong
                dVdlongInnerSum += mm*(S[n][m]*cosLongM - C[n][m]*sinLongM)*P[n][m];
            }
            // Precalculate common terms
            const double rRatio = pow(equitorialR/R, nn);

            // dVdr
            dVdr += rRatio*(nn + 1.0)*dVdrInnerSum;

            // dVdlat
            dVdlat += rRatio*dVdlatInnerSum;

            // dVdlong
            dVdlong += rRatio*dVdlongInnerSum;
        }

        // Correct
        double tempA = mu/R;
        dVdr *= tempA/R;
        dVdlat *= tempA;
        dVdlong *= tempA/R;

        // Calculate partials of radius, geocentric latitude, and longitude with respect to BCBF frame
        const double drdrBCBF[3] = {
            xBCBF/R,
            yBCBF/R,
            z/R
        };

        tempA = 1/sqrt(xBCBF*xBCBF + yBCBF*yBCBF);
        double tempB = z/(R*R);
        const double dlatdrBCBF[3] = {
            -tempA*xBCBF*tempB,
            -tempA*yBCBF*tempB,
             tempA*(1 - z*tempB)
        };

        tempA *= tempA;
        const double dlongdrBCBF[3] = {
            -tempA*yBCBF,
             tempA*xBCBF,
             0.0
        };

        // Calculate accel in BCBF (not with respect to BCBF)
        basis_array accelOblatenessBCBF = {
            dVdr*drdrBCBF[0] + dVdlat*dlatdrBCBF[0] + dVdlong*dlongdrBCBF[0],
            dVdr*drdrBCBF[1] + dVdlat*dlatdrBCBF[1] + dVdlong*dlongdrBCBF[1],
            dVdr*drdrBCBF[2] + dVdlat*dlatdrBCBF[2]
        };

        // Rotate back into inertial coordinates
        conversions::bcbf_to_bci(accelOblatenessBCBF, julianDate, bodyRotationRate, accelOblateness);
    }

    return accelOblateness;
}

void OblatenessForce::assign_legendre(const double& latitude) const {
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
            P[n][n] = sqrt(2.0*(2.0*nn + 1.0)*tau)*pow(cosLat, nn);
        }

        for (int n = 1; n < N+1; ++n) { // n = m + 1
            nn = (double)n;
            P[n][n-1] = sqrt(2.0*(nn - 1.0) + 3.0)*sinLat*P[n-1][n-1];
        }

        Developers Note: Fuck this function
    */
    const double cosLat = math_c::cos(latitude);
    const double sinLat = math_c::sin(latitude);
    for (size_t n = 0; n < N+1; ++n) {
        const double nn = (double)n;

        for (size_t m = 0; m < M+1; ++m) {
            const double mm = (double)m;

            if (n == m) {
                if (n == 0) {
                    P[n][m] = 1;
                }
                else {
                    double tau = 1.0;
                    for (int ii = 2*n - 1; ii > 0; ii -= 2) {
                        tau *= (double)ii/((double)ii + 1.0);
                    }
                    P[n][m] = sqrt(2.0*(2.0*nn + 1.0)*tau)*pow(cosLat, nn);
                }
            }
            else if (n == m + 1) {
                P[n][m] = sqrt(2.0*mm + 3.0)*sinLat*P[m][m];
            }
            else if (n >= m + 2) {
                const double alpha = sqrt((2.0*nn + 1.0)*(2.0*nn - 1.0)/((nn - mm)*(nn + mm)));
                const double beta = sqrt((2.0*nn + 1.0)*(nn + mm - 1.0)*(nn - mm - 1.0)/((2.0*nn - 3.0)*(nn - mm)*(nn + mm)));

                P[n][m] = alpha*sinLat*P[n-1][m] + beta*P[n-2][m];
            }
            else {
                P[n][m] = 0.0;
            }
        }
    }
}