#include "EquationsOfMotion.hpp"

OrbitalElements EquationsOfMotion::evaluate_state_derivative(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

    // Time
    julianDate = spacecraft.get_epoch().julian_day() + time;

    // Evaluate derivative
    OrbitalElements dsdt;
    switch (dynamicsSet) {
        case (COWELLS):
            dsdt = evaluate_cowells_method(time, state, spacecraft);
            break;

        case (COES_VOP):
            dsdt = evaluate_coes_vop(time, state, spacecraft);
            break;

        case (J2_MEAN):
            dsdt = evaluate_j2mean_coes_vop(time, state, spacecraft);
            break;

        case (MEES_VOP):
            dsdt = evaluate_mees_vop(time, state, spacecraft);
            break;

        case (TWO_BODY):
        default:
            dsdt = evaluate_two_body_dynamics(time, state, spacecraft);
    }

    return dsdt;
}


const OrbitalElements EquationsOfMotion::evaluate_two_body_dynamics(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

    if (state.get_set() != ElementSet::CARTESIAN) {
        throw std::runtime_error("The two-body dynamics evaluator requires that the incoming Orbital Element set is in Cartesian coordinates.");
    }

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Calculate required values for force model
    const double R = sqrt(x*x + y*y + z*z);

    // mu/R^3
    const double muOverRadiusCubed = system.get_center().mu()/(R*R*R);

    // Derivative
    const OrbitalElements dsdt ({
        vx,
        vy,
        vz,
        (-muOverRadiusCubed*x),
        (-muOverRadiusCubed*y),
        (-muOverRadiusCubed*z)
    },
    ElementSet::CARTESIAN);

    return dsdt;
}

const OrbitalElements EquationsOfMotion::evaluate_cowells_method(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

    if (state.get_set() != ElementSet::CARTESIAN) {
        throw std::runtime_error("The Cowell's Method dynamics evaluator requires that the incoming Orbital Element set is in Cartesian coordinates.");
    }

    // Extract
    const double& x = state[0];
    const double& y = state[1];
    const double& z = state[2];
    const double& vx = state[3];
    const double& vy = state[4];
    const double& vz = state[5];

    // Calculate required values for force model
    const double R = sqrt(x*x + y*y + z*z); // radius magnitude

    // mu/R^3
    const double muOverRadiusCubed = system.get_center().mu()/(R*R*R);

    // Create force models in cartesian bci
    const auto accelPerts = find_perts(time, state, spacecraft);

    // Derivative
    const OrbitalElements dsdt ({
        vx,
        vy,
        vz,
        -muOverRadiusCubed*x + accelPerts[0],
        -muOverRadiusCubed*y + accelPerts[1],
        -muOverRadiusCubed*z + accelPerts[2]
    },
    ElementSet::CARTESIAN);

    return dsdt;
}

const OrbitalElements EquationsOfMotion::evaluate_coes_vop(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

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
    const double& mu = system.get_center().mu();
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
    const double normTv = sqrt(Tv[0]*Tv[0] + Tv[1]*Tv[1] + Tv[2]*Tv[2]);

    const double That[3] = {
        Tv[0]/normTv,
        Tv[1]/normTv,
        Tv[2]/normTv
    };

    // Function for finding accel caused by perturbations
    const auto accelPerts = find_perts(time, cartesianState, spacecraft);

    // Calculate R, N, and T
    const double radialPert     = accelPerts[0]*Rhat[0] + accelPerts[1]*Rhat[1] + accelPerts[2]*Rhat[2];
    const double normalPert     = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];
    const double tangentialPert = accelPerts[0]*That[0] + accelPerts[1]*That[1] + accelPerts[2]*That[2];

    // Argument of latitude
    const double u = w + theta;

    // Precalculate
    const double cosTA = cos(theta);
    const double sinTA = sin(theta);
    const double cosU = cos(u);
    const double sinU = sin(u);
    const double h_2 = h*h;
    const double hOverR_2 = h/(R*R);

    // Calculate the derivatives of the COEs - from the notes
    const double dhdt     = R*tangentialPert;
    const double _deccdt   = h/mu*sinTA*radialPert + 1/(mu*h)*((h_2 + mu*R)*cosTA + mu*ecc*R)*tangentialPert;
    const double _dincdt   = R/h*cosU*normalPert;
    const double dthetadt = hOverR_2 + (1/(ecc*h))*((h_2/mu)*cosTA*radialPert - (h_2/mu + R)*sinTA*tangentialPert);
    const double draandt  = R*sinU/(h*sin(inc))*normalPert;
    const double dwdt     = -dthetadt + (hOverR_2 - draandt*cos(inc));

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

const OrbitalElements EquationsOfMotion::evaluate_j2mean_coes_vop(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

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
    const double& mu = system.get_center().mu();
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
    const auto accelPerts = find_perts(time, cartesianState, spacecraft);

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

const OrbitalElements EquationsOfMotion::evaluate_mees_vop(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

    if (state.get_set() != ElementSet::MEE) {
        throw std::runtime_error("The Mean Equinoctial dynamics evaluator requires that the incoming Orbital Element set is in MEE coordinates.");
    }

    // Extract
    const double& p = state[0];
    const double& f = state[1];
    const double& g = state[2];
    const double& h = state[3];
    const double& k = state[4];
    const double& L = state[5];

    // conversions Modified Equinoctial Elements to COEs
    const auto coesState = conversions::convert(state, ElementSet::MEE, ElementSet::COE, system);

    // h and mu
    const double& mu = system.get_center().mu();

    // conversions COEs to r and v
    const auto cartesianState = conversions::convert(coesState, ElementSet::COE, ElementSet::CARTESIAN, system);

    const double& x = cartesianState[0];
    const double& y = cartesianState[1];
    const double& z = cartesianState[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = cartesianState[3];
    const double& vy = cartesianState[4];
    const double& vz = cartesianState[5];

    // Define perturbation vectors relative to the satellites SNC body frame
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
    const double normTv = sqrt(Tv[0]*Tv[0] + Tv[1]*Tv[1] + Tv[2]*Tv[2]);

    const double That[3] = {
        Tv[0]/normTv,
        Tv[1]/normTv,
        Tv[2]/normTv
    };

    // Function for finding accel caused by perturbations
    const auto accelPerts = find_perts(time, cartesianState, spacecraft);

    // Calculate R, N, and T
    const double radialPert     = accelPerts[0]*Rhat[0] + accelPerts[1]*Rhat[1] + accelPerts[2]*Rhat[2];
    const double normalPert     = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];
    const double tangentialPert = accelPerts[0]*That[0] + accelPerts[1]*That[1] + accelPerts[2]*That[2];

    // Variables precalculated for speed
    const double cosL = cos(L);
    const double sinL = sin(L);

    const double tempA = sqrt(p/mu);
    const double tempB = 1.0 + f*cos(L) + g*sin(L);
    const double s_2 = 1.0 + h*h + k*k;

    const double tempC = (h*sinL - k*cosL)/tempB;
    const double tempD = tempA*s_2/(2*tempB);

    // Derivative functions
    const OrbitalElements dsdt({
        2*p/tempB*tempA*tangentialPert,                                                                 // dpdt
        tempA*( radialPert*sinL + ((tempB + 1)*cosL + f)/tempB*tangentialPert - g*tempC*normalPert),    // dfdt
        tempA*(-radialPert*cosL + ((tempB + 1)*sinL + g)/tempB*tangentialPert + f*tempC*normalPert),    // dgdt
        tempD*cosL*normalPert,                                                                          // dhdt
        tempD*sinL*normalPert,                                                                          // dkdt
        sqrt(mu*p)*tempB*tempB/(p*p) + tempA*tempC*normalPert                                           // dLdt
    }, ElementSet::MEE);

    return dsdt;
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- Force Models -----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

const basis_array EquationsOfMotion::find_perts(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) {

    if (state.get_set() != ElementSet::CARTESIAN) {
        throw std::runtime_error("The find_perts method requires that the incoming Orbital Element set is in CARTESIAN coordinates.");
    }

    // Run find functions for force model
    basis_array accelPerts = forces.compute_forces(julianDate, state, spacecraft, system);

    return accelPerts;
}

bool EquationsOfMotion::check_crash(const Time& time, const OrbitalElements& state, const Spacecraft& spacecraft) const {

    const OrbitalElements cartesian = state.convert(ElementSet::CARTESIAN, system);

    const double R = math_c::normalize(cartesian, 2, 0, 2);
    const double V = math_c::normalize(cartesian, 2, 3, 5);

    if ((R <= crashRadius) || (V <= crashVelocity)) {
        return true;
    }
    return false;
}

void EquationsOfMotion::set_crash_radius(double crashRadius) {
    crashRadius = crashRadius;
}
void EquationsOfMotion::set_crash_velocity(double crashVelocity) {
    crashVelocity = crashVelocity;
}

// Perturbation toggles
void EquationsOfMotion::switch_oblateness(bool onOff) {
    oblateness = onOff;
}
void EquationsOfMotion::switch_oblateness(size_t _N, size_t _M) {
    // Switch perturbation toggle to true
    oblateness = true;
    NxMOblateness = true;

    // Set N and M
    N = _N;
    M = _M;

    // Get Cnm and Snm
    get_oblateness_coefficients(_N, _M);
}
void EquationsOfMotion::switch_drag(bool onOff) {
    drag = onOff;
}
void EquationsOfMotion::switch_lift(bool onOff) {
    lift = onOff;
}
void EquationsOfMotion::switch_srp(bool onOff) {
    srp = onOff;
}
void EquationsOfMotion::switch_nbody(bool onOff) {
    nbody = onOff;
}
