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
    _semimajor = 1.0/(2.0/R - V*V/mu);

    // Eccentricity
    const quantity dotRV = x*vx + y*vy + z*vz;
    const quantity oneOverMu = (1.0/mu);
    const quantity vSquaredMinuMuTimesR = (V*V - mu/R);

    const quantity eccX = oneOverMu*(vSquaredMinuMuTimesR*x - dotRV*vx);
    const quantity eccY = oneOverMu*(vSquaredMinuMuTimesR*y - dotRV*vy);
    const quantity eccZ = oneOverMu*(vSquaredMinuMuTimesR*z - dotRV*vz);

    _eccentricity = sqrt(eccX*eccX + eccY*eccY + eccZ*eccZ);

    /*
        If the orbit has an _inclination of exactly 0, w is ill-defined, the
        _eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        _eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (_eccentricity < tol) {
        _eccentricity = 0.0 * one;
    }

    // Inclination (rad)
    _inclination = acos(hz/normH);
    if (abs(_inclination - piRad) < tol){
        _inclination = 0.0 * rad;
    }

    // Right Ascension of Ascending Node (rad)
    if (_inclination == 0.0 * rad) { // No nodal line
        _rightAscension = 0.0 * rad;
    }
    else {
        if (Ny > 0.0 * (km*km/s)) {
            _rightAscension = acos(Nx/normN);
        }
        else {
            _rightAscension = twoPiRad - acos(Nx/normN);
        }

        if (abs(_rightAscension - twoPiRad) < tol) {
            _rightAscension = 0.0 * rad;
        }
    }

    // True Anomaly (rad)
    if (_eccentricity == 0.0 * one) { // No argument of perigee, use nodal line
        if (_inclination == 0.0 * rad) { // No nodal line, use true longitude
            if (vx <= 0.0 * km/s) {
                _trueAnomaly = acos(x/R);
            }
            else {
                _trueAnomaly = 2*piRad - acos(x/R);
            }
        }
        else { // Use argument of latitude
            const quantity nDotR = Nx*x + Ny*y;
            if (z >= 0.0 * km) {
                _trueAnomaly = acos(nDotR/(normN*R));
            }
            else {
                _trueAnomaly = 2*piRad - acos(nDotR/(normN*R));
            }
        }
    }
    else {
        const quantity eccDotR = eccX*x + eccY*y + eccZ*z;
        if (dotRV >= 0.0 * (km*km/s)) {
            _trueAnomaly = acos(eccDotR/(_eccentricity*R));
        }
        else {
            _trueAnomaly = twoPiRad - acos(eccDotR/(_eccentricity*R));
        }
    }

    // Argument of Parigee (rad)
    if (_eccentricity == 0.0 * one) { // Ill-defined. Assume zero
        _argPerigee = 0.0 * rad;
    }
    else if (_inclination == 0.0 * rad) { // No nodal line, use ecc vec
        if (hz > 0.0 * (km*km/s)) {
            _argPerigee = atan2(eccY, eccX);
        }
        else {
            _argPerigee = 2*piRad - atan2(eccY, eccX);
        }
    }
    else {
        const quantity eccDotN = eccX*Nx + eccY*Ny;
        if (eccZ < 0.0 * one){
            _argPerigee = twoPiRad - acos(eccDotN/(_eccentricity*normN));
        }
        else {
            _argPerigee = acos(eccDotN/(_eccentricity*normN));
        }
    }

    // Catch garbage
    if (normN == 0.0 * (km*km/s) || abs(_argPerigee - twoPiRad) < tol) {
        _trueAnomaly += _argPerigee;
        _argPerigee = 0.0 * rad;
    }

    if (abs(_trueAnomaly - twoPiRad) < tol) {
        _trueAnomaly = 0.0 * rad;
    }
}

// Copy constructor
Keplerian::Keplerian(const Keplerian& other) :
    _semimajor(other._semimajor),
    _eccentricity(other._eccentricity),
    _inclination(other._inclination),
    _rightAscension(other._rightAscension),
    _argPerigee(other._argPerigee),
    _trueAnomaly(other._trueAnomaly)
{}

// Move constructor
Keplerian::Keplerian(Keplerian&& other) noexcept :
    _semimajor(std::move(other._semimajor)),
    _eccentricity(std::move(other._eccentricity)),
    _inclination(std::move(other._inclination)),
    _rightAscension(std::move(other._rightAscension)),
    _argPerigee(std::move(other._argPerigee)),
    _trueAnomaly(std::move(other._trueAnomaly))
{}

// Move assignment operator
Keplerian& Keplerian::operator=(Keplerian&& other) noexcept {
    if (this != &other) {
        _semimajor = std::move(other._semimajor);
        _eccentricity = std::move(other._eccentricity);
        _inclination = std::move(other._inclination);
        _rightAscension = std::move(other._rightAscension);
        _argPerigee = std::move(other._argPerigee);
        _trueAnomaly = std::move(other._trueAnomaly);
    }
    return *this;
}

// Copy assignment operator
Keplerian& Keplerian::operator=(const Keplerian& other) {
    return *this = Keplerian(other);
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