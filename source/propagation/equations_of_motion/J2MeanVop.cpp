#include "J2MeanVop.hpp"

#include <cmath>
#include <algorithm>
#include <exception>

#include "astronomical_constants.h"
#include "math_constants.h"
#include "math_c.hpp"
#include "conversions.hpp"

OrbitalElements J2MeanVop::operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const {

    if (state.get_set() != ElementSet::COE) {
        throw std::runtime_error("The Mean J2 dynamics evaluator requires that the incoming Orbital Element set is in COE coordinates.");
    }

    // Extract
    const double& a = state[0];
    const double& ecc = state[1];
    // const double& raan = state[3];
    const double& w = state[4];
    const double& theta = state[5];

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    const double& inc = (state[2] < checkTol) ? checkTol : state[2];
    if (inc == checkTol) {
        checkflag = true;
    }

    // h and mu
    const double h = sqrt(mu*a*(1 - ecc));

    // conversions COEs to r and v
    const auto cartesianState = conversions::convert(state, ElementSet::COE, ElementSet::CARTESIAN, system);

    const double& x = cartesianState[0];
    const double& y = cartesianState[1];
    const double& z = cartesianState[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = cartesianState[3];
    const double& vy = cartesianState[4];
    const double& vz = cartesianState[5];

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
    */
    const double Nhat[3] = {
        (y*vz - z*vy)/h,
        (z*vx - x*vz)/h,
        (x*vy - y*vx)/h
    };

    // Function for finding accel caused by perturbations
    Time julianDate = spacecraft.get_epoch().julian_day() + time;
    basis_array accelPerts = forces.compute_forces(julianDate, cartesianState, spacecraft, system);

    // Calculate R, N, and T
    const double normalPert = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];

    // Calculate the derivatives of the COEs - only raan and w considered
    const double dhdt = 0.0;
    const double deccdt = 0.0;
    const double _dincdt = R/h*cos(w + theta)*normalPert;
    const double dthetadt = h/(R*R);
    const double draandt = R*sin(w + theta)/(h*sin(inc))*normalPert;
    const double dwdt = -draandt*cos(inc);

    // Loop to prevent crashes due to circular and zero inclination orbits.
    // Will cause an error
    double dincdt = _dincdt;
    if (inc == checkTol && dincdt <= checkTol) {
        dincdt = 0.0;
        checkflag = true;
    }

    const OrbitalElements dsdt({
        dhdt,
        deccdt,
        dincdt,
        draandt,
        dwdt,
        dthetadt
    },
    ElementSet::COE);

    return dsdt;
}