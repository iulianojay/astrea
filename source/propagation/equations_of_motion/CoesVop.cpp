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

    if (doWarn) {
        check_degenerate(ecc, inc);
    }

    // h
    const double h = std::sqrt(mu*a*(1 - ecc*ecc));

    // conversions COEs to r and v
    const OrbitalElements cartesianState = conversions::convert(state, ElementSet::COE, ElementSet::CARTESIAN, system);

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
    const double hSquared = h*h;
    const double hOverRSquared = h/(R*R);

    // Calculate the derivatives of the COEs - from the notes
    const double dhdt     = R*tangentialPert;
    const double deccdt  = h/mu*sinTA*radialPert + 1/(mu*h)*((hSquared + mu*R)*cosTA + mu*ecc*R)*tangentialPert;
    const double dincdt  = R/h*cosU*normalPert;
    const double dthetadt = hOverRSquared + (1/(ecc*h))*((hSquared/mu)*cosTA*radialPert - (hSquared/mu + R)*sinTA*tangentialPert);
    const double draandt  = R*sinU/(h*math_c::sin(inc))*normalPert;
    const double dwdt     = -dthetadt + (hOverRSquared - draandt*math_c::cos(inc));

    const double dadt = (-2*mu/(h*h*h)*dhdt)*(1 - ecc*ecc) + (mu/(h*h))*(-2*ecc*deccdt); // TODO: Fix this

    const OrbitalElements dsdt({
        dadt,
        deccdt,
        dincdt,
        draandt,
        dwdt,
        dthetadt
    },
    ElementSet::COE);

    return dsdt;
}

void CoesVop::check_degenerate(const double& ecc, const double& inc) const {
    if (ecc <= checkTol || inc <= checkTol) {
        std::string title;
        if (ecc <= checkTol && inc <= checkTol) {
            title = "Eccentricity and inclination";
        }
        else if (ecc <= checkTol) {
            title = "Eccentricity";
        }
        else {
            title = "Inclination";
        }
        std::cout << "WARNING: Degenerate case. " << title << " smaller than acceptable tolerance (" << checkTol
            << "). Results may be inaccurate." << std::endl << std::endl;
    }
}