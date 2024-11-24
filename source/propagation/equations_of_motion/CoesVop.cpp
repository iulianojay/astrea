#include "CoesVop.hpp"

#include "math_c.hpp"

OrbitalElements CoesVop::operator()(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const {

    if (state.get_set() != ElementSet::COE) {
        throw std::runtime_error("The COEs VoP dynamics evaluator requires that the incoming Orbital Element set is in COE coordinates.");
    }

    // Extract
    const double& a = state[0];
    // const double& raan = state[3];
    const double& w = state[4];
    const double& theta = state[5];

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    const double& ecc = (state[1] < checkTol) ? checkTol : state[1];
    const double& inc = (state[2] < checkTol) ? checkTol : state[2];

    if (ecc == checkTol || inc == checkTol) {
        checkflag = true;
    }

    // h and mu
    const double h = std::sqrt(mu*a*(1 - ecc));

    // conversions COEs to r and v
    const auto cartesianState = conversions::convert(state, ElementSet::COE, ElementSet::CARTESIAN, system);

    const double& x = cartesianState[0];
    const double& y = cartesianState[1];
    const double& z = cartesianState[2];
    const double R = std::sqrt(x*x + y*y + z*z);

    const double& vx = cartesianState[3];
    const double& vy = cartesianState[4];
    const double& vz = cartesianState[5];

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    const double Rhat[3] = {
        x/R,
        y/R,
        z/R
    };

    const double Nhat[3] = {
        (y*vz - z*vy)/h,
        (z*vx - x*vz)/h,
        (x*vy - y*vx)/h
    };

    const double Tv[3] = {
        Nhat[1]*Rhat[2] - Nhat[2]*Rhat[1],
        Nhat[2]*Rhat[0] - Nhat[0]*Rhat[2],
        Nhat[0]*Rhat[1] - Nhat[1]*Rhat[0]
    };
    const double normTv = std::sqrt(Tv[0]*Tv[0] + Tv[1]*Tv[1] + Tv[2]*Tv[2]);

    const double That[3] = {
        Tv[0]/normTv,
        Tv[1]/normTv,
        Tv[2]/normTv
    };

    // Function for finding accel caused by perturbations
    auto julianDate = spacecraft.get_epoch().julian_day() + time.count<days>();
    basis_array accelPerts = forces.compute_forces(julianDate, cartesianState, spacecraft, system);

    // Calculate R, N, and T
    const double radialPert     = accelPerts[0]*Rhat[0] + accelPerts[1]*Rhat[1] + accelPerts[2]*Rhat[2];
    const double normalPert     = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];
    const double tangentialPert = accelPerts[0]*That[0] + accelPerts[1]*That[1] + accelPerts[2]*That[2];

    // Argument of latitude
    const double u = w + theta;

    // Precalculate
    const double cosTA = math_c::cos(theta);
    const double sinTA = math_c::sin(theta);
    const double cosU = math_c::cos(u);
    const double sinU = math_c::sin(u);
    const double h_2 = h*h;
    const double hOverR_2 = h/(R*R);

    // Calculate the derivatives of the COEs - from the notes
    const double dhdt     = R*tangentialPert;
    const double _deccdt   = h/mu*sinTA*radialPert + 1/(mu*h)*((h_2 + mu*R)*cosTA + mu*ecc*R)*tangentialPert;
    const double _dincdt   = R/h*cosU*normalPert;
    const double dthetadt = hOverR_2 + (1/(ecc*h))*((h_2/mu)*cosTA*radialPert - (h_2/mu + R)*sinTA*tangentialPert);
    const double draandt  = R*sinU/(h*math_c::sin(inc))*normalPert;
    const double dwdt     = -dthetadt + (hOverR_2 - draandt*math_c::cos(inc));

    // Check to prevent crashes due to circular and zero inclination orbits.
    // Will cause innaccuracies
    double deccdt = _deccdt;
    if (ecc == checkTol && deccdt <= checkTol) {
        deccdt = 0.0;
        checkflag = true;
    }
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