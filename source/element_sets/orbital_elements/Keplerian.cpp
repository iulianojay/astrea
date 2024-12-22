#include "Keplerian.hpp"

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>
#include <mp-units/systems/angular/math.h>

#include "AstrodynamicsSystem.hpp"
#include "Cartesian.hpp"


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;


Keplerian::Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys) {

    /*
        Force rounding errors to assume zero values for angles. Assume complex
        results are the result of rounding errors. Flip values near their antipode
        to zero for simplicity. Assume NaN results are from singularities and force
        values to be 0.

        No idea how much of this is just wrong.
    */
    static const quantity<one> tol = 1.0e-10 * one;
    static const quantity piRad = 1.0 * (mag<pi>*rad);
    static const quantity twoPiRad = 2.0 * (mag<pi>*rad);

    // Get mu
    quantity mu = sys.get_center()->get_mu() * km*km*km/(s*s);

    // Get r and v
    const auto& x = elements.get_x();
    const auto& y = elements.get_y();
    const auto& z = elements.get_z();
    const auto& vx = elements.get_vx();
    const auto& vy = elements.get_vy();
    const auto& vz = elements.get_vz();

    quantity R = sqrt(x*x + y*y + z*z);
    quantity V = sqrt(vx*vx + vy*vy + vz*vz);

    // Specific Relative Angular Momentum
    quantity hx = y*vz - z*vy; // h = cross(r, v)
    quantity hy = z*vx - x*vz;
    quantity hz = x*vy - y*vx;

    quantity normH = sqrt(hx*hx + hy*hy + hz*hz);

    // Setup
    quantity Nx = -hy;  // N = cross([0 0 1], h)
    quantity Ny = hx;

    quantity normN = sqrt(Nx*Nx + Ny*Ny);

    // Semimajor Axis
    quantity a = 1.0/(2.0/R - V*V/mu);

    // Eccentricity
    quantity dotRV = x*vx + y*vy + z*vz;

    quantity eccX = (1.0/mu)*((V*V - mu/R)*x - dotRV*vx);
    quantity eccY = (1.0/mu)*((V*V - mu/R)*y - dotRV*vy);
    quantity eccZ = (1.0/mu)*((V*V - mu/R)*z - dotRV*vz);

    quantity ecc = sqrt(eccX*eccX + eccY*eccY + eccZ*eccZ);
    /*
        If the orbit has an inclination of exactly 0, w is ill-defined, the
        eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (abs(ecc) < tol) {
        ecc = 0.0 * one;
    }

    // Inclination (rad)
    quantity<rad> inc = acos(hz/normH);
    if (isnan(inc) || abs(inc - piRad) < tol){
        inc = 0.0 * rad;
    }

    // Right Ascension of Ascending Node (rad)
    quantity<rad> raan{};
    quantity acos_Nx_Nnorm = acos(Nx/normN);
    if (Ny > 0.0 * (km*km/s)) {
        raan = acos_Nx_Nnorm;
    }
    else {
        raan = twoPiRad - acos_Nx_Nnorm;
    }

    if (normN == 0.0 * (km*km/s) || isnan(raan) || abs(raan - twoPiRad) < tol) {
        raan = 0.0 * rad;
    }

    // True Anomaly (rad)
    quantity<rad> theta{};
    if (ecc == 0.0 * one) { // No argument of perigee, use nodal line
        if (inc == 0.0 * rad) { // No nodal line, use true longitude
            if (vx <= 0.0 * km/s) {
                theta = acos(x/R);
            }
            else {
                theta = 2*piRad - acos(x/R);
            }
        }
        else { // Use argument of latitude
            quantity dot_n_r = Nx*x + Ny*y;
            if (z >= 0.0 * km) {
                theta = acos(dot_n_r/(normN*R));
            }
            else {
                theta = 2*piRad - acos(dot_n_r/(normN*R));
            }
        }
    }
    else {
        quantity dot_ecc_r = eccX*x + eccY*y + eccZ*z;
        if (dotRV >= 0.0 * (km*km/s)) {
            theta = acos(dot_ecc_r/(ecc*R));
        }
        else {
            theta = twoPiRad - acos(dot_ecc_r/(ecc*R));
        }
    }

    if (isnan(theta) || abs(theta - twoPiRad) < tol) {
        theta = 0.0 * rad;
    }

    // Argument of Parigee (rad)
    quantity<rad> w{};
    if (ecc == 0.0 * one) { // Ill-defined. Assume zero
        w = 0.0 * rad;
    }
    else if (inc == 0.0 * rad) { // No nodal line, use ecc vec
        if (hz > 0.0 * (km*km/s)) {
            w = atan2(eccY, eccX);
        }
        else {
            w = 2*piRad - atan2(eccY, eccX);
        }
    }
    else {
        quantity dot_ecc_N = eccX*Nx + eccY*Ny;
        if (eccZ < 0.0 * one){
            w = twoPiRad - acos(dot_ecc_N/(ecc*normN));
        }
        else {
            w = acos(dot_ecc_N/(ecc*normN));
        }
    }

    if (normN == 0.0 * (km*km/s) || isnan(w) || abs(w - twoPiRad) < tol) {
        w = 0.0 * rad;
    }

    // Assign to coes
    semimajor = a;
    eccentricity = ecc;
    inclination = inc;
    rightAscension = raan;
    argPerigee = w;
    trueAnomaly = theta;
}