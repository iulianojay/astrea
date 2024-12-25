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
    const quantity mu = sys.get_center()->get_mu() * km*km*km/(s*s);

    // Get r and v
    const auto& x = elements.get_x();
    const auto& y = elements.get_y();
    const auto& z = elements.get_z();
    const auto& vx = elements.get_vx();
    const auto& vy = elements.get_vy();
    const auto& vz = elements.get_vz();

    const quantity R = sqrt(x*x + y*y + z*z);
    const quantity V = sqrt(vx*vx + vy*vy + vz*vz);

    // Specific Relative Angular Momentum
    const quantity hx = y*vz - z*vy; // h = cross(r, v)
    const quantity hy = z*vx - x*vz;
    const quantity hz = x*vy - y*vx;

    const quantity normH = sqrt(hx*hx + hy*hy + hz*hz);

    // Setup
    const quantity Nx = -hy;  // N = cross([0 0 1], h)
    const quantity Ny = hx;

    const quantity normN = sqrt(Nx*Nx + Ny*Ny);

    // Semimajor Axis
    semimajor = 1.0/(2.0/R - V*V/mu);

    // Eccentricity
    const quantity dotRV = x*vx + y*vy + z*vz;
    const quantity oneOverMu = (1.0/mu);
    const quantity vSquaredMinuMuTimesR = (V*V - mu/R);

    const quantity eccX = oneOverMu*(vSquaredMinuMuTimesR*x - dotRV*vx);
    const quantity eccY = oneOverMu*(vSquaredMinuMuTimesR*y - dotRV*vy);
    const quantity eccZ = oneOverMu*(vSquaredMinuMuTimesR*z - dotRV*vz);

    eccentricity = sqrt(eccX*eccX + eccY*eccY + eccZ*eccZ);

    /*
        If the orbit has an inclination of exactly 0, w is ill-defined, the
        eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (eccentricity < tol) {
        eccentricity = 0.0 * one;
    }

    // Inclination (rad)
    inclination = acos(hz/normH);
    if (abs(inclination - piRad) < tol){
        inclination = 0.0 * rad;
    }

    // Right Ascension of Ascending Node (rad)
    if (inclination == 0.0 * rad) { // No nodal line
        rightAscension = 0.0 * rad;
    }
    else {
        if (Ny > 0.0 * (km*km/s)) {
            rightAscension = acos(Nx/normN);
        }
        else {
            rightAscension = twoPiRad - acos(Nx/normN);
        }

        if (abs(rightAscension - twoPiRad) < tol) {
            rightAscension = 0.0 * rad;
        }
    }

    // True Anomaly (rad)
    if (eccentricity == 0.0 * one) { // No argument of perigee, use nodal line
        if (inclination == 0.0 * rad) { // No nodal line, use true longitude
            if (vx <= 0.0 * km/s) {
                trueAnomaly = acos(x/R);
            }
            else {
                trueAnomaly = 2*piRad - acos(x/R);
            }
        }
        else { // Use argument of latitude
            const quantity nDotR = Nx*x + Ny*y;
            if (z >= 0.0 * km) {
                trueAnomaly = acos(nDotR/(normN*R));
            }
            else {
                trueAnomaly = 2*piRad - acos(nDotR/(normN*R));
            }
        }
    }
    else {
        const quantity eccDotR = eccX*x + eccY*y + eccZ*z;
        if (dotRV >= 0.0 * (km*km/s)) {
            trueAnomaly = acos(eccDotR/(eccentricity*R));
        }
        else {
            trueAnomaly = twoPiRad - acos(eccDotR/(eccentricity*R));
        }
    }

    // Argument of Parigee (rad)
    if (eccentricity == 0.0 * one) { // Ill-defined. Assume zero
        argPerigee = 0.0 * rad;
    }
    else if (inclination == 0.0 * rad) { // No nodal line, use ecc vec
        if (hz > 0.0 * (km*km/s)) {
            argPerigee = atan2(eccY, eccX);
        }
        else {
            argPerigee = 2*piRad - atan2(eccY, eccX);
        }
    }
    else {
        const quantity eccDotN = eccX*Nx + eccY*Ny;
        if (eccZ < 0.0 * one){
            argPerigee = twoPiRad - acos(eccDotN/(eccentricity*normN));
        }
        else {
            argPerigee = acos(eccDotN/(eccentricity*normN));
        }
    }

    // Catch garbage
    if (normN == 0.0 * (km*km/s) || abs(argPerigee - twoPiRad) < tol) {
        trueAnomaly += argPerigee;
        argPerigee = 0.0 * rad;
    }

    if (abs(trueAnomaly - twoPiRad) < tol) {
        trueAnomaly = 0.0 * rad;
    }
}



std::ostream &operator<<(std::ostream& os, Keplerian const& elements) {
    os << "[";
    os << elements.get_semimajor() << ", ";
    os << elements.get_eccentricity() << ", ";
    os << elements.get_inclination() << ", ";
    os << elements.get_right_ascension() << ", ";
    os << elements.get_argument_of_perigee() << ", ";
    os << elements.get_true_anomaly();
    os << "] (Keplerian)";
    return os;
}