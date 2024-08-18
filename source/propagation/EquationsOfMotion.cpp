#include "EquationsOfMotion.hpp"

// Constructors 
EquationsOfMotion::EquationsOfMotion(const AstrodynamicsSystem& system) : spacecraft(), system(system), centralBody(system.get_center()) {
}

// Destructor
EquationsOfMotion::~EquationsOfMotion(){
    // Clean up
    if (NxMOblateness) {
        for (int ii = 0; ii < N; ++ii) {
            delete[] P[ii];
            delete[] C[ii];
            delete[] S[ii];
        }
        delete[] P;
        delete[] C;
        delete[] S;
    }
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------ Get Derivatives for Integrator --------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void EquationsOfMotion::evaluate_state_derivative(double time, double* state, Spacecraft* sc, double* stateDerivative) {

    // TODO: Fix this
    spacecraft = sc;

    // Time
    t = time;
    julianDate = spacecraft->get_epoch().julian_day() + t*SEC_TO_DAY;

    // Assign state variables // TODO: Fix this
    OrbitalElements s;
    std::copy(state, state+6, s.begin());

    // Evaluate derivative
    OrbitalElements dsdt;
    switch (dynamicsSet) {
        case (COWELLS):
            dsdt = evaluate_cowells_method(s); 
            break;
            
        case (COES_VOP):
            dsdt = evaluate_coes_vop(s); 
            break;
            
        case (J2_MEAN):
            dsdt = evaluate_j2mean_coes_vop(s); 
            break;
            
        case (MEES_VOP):
            dsdt = evaluate_mees_vop(s); 
            break;

        case (TWO_BODY):
        default:
            dsdt = evaluate_two_body_dynamics(s); 
    }

    // Assign output variables
    std::copy(dsdt.begin(), dsdt.end(), stateDerivative);
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------ Equations of Motion -------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

const OrbitalElements EquationsOfMotion::evaluate_two_body_dynamics(const OrbitalElements& state) const {

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
    const double muOverRadiusCubed = centralBody.mu()/(R*R*R);

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

const OrbitalElements EquationsOfMotion::evaluate_cowells_method(const OrbitalElements& state) {

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
    const double muOverRadiusCubed = centralBody.mu()/(R*R*R);

    // Create force models in cartesian bci
    const auto accelPerts = find_perts(state);

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

const OrbitalElements EquationsOfMotion::evaluate_coes_vop(const OrbitalElements& state) {

    if (state.get_set() != ElementSet::COE) {
        throw std::runtime_error("The COEs VoP dynamics evaluator requires that the incoming Orbital Element set is in COE coordinates.");
    }

    // Extract
    const double& a = state[0];
    const double& _ecc = state[1];
    const double& _inc = state[2];
    const double& raan = state[3];
    const double& w = state[4];
    const double& theta = state[5];

    // h and mu
    const double& mu = centralBody.mu();
    const double h = sqrt(mu*a*(1 - _ecc));

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    double ecc = _ecc;
    if (ecc < checkTol) {
        checkflag = true;
        ecc = checkTol;
    }
    double inc = _inc;
    if (inc < checkTol) {
        checkflag = true;
        inc = checkTol;
    }

    // conversions COEs to r and v
    const auto cartesianState = conversions::convert(state, ElementSet::COE, ElementSet::CARTESIAN, &system);

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
    const auto accelPerts = find_perts(cartesianState);

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

const OrbitalElements EquationsOfMotion::evaluate_j2mean_coes_vop(const OrbitalElements& state) {

    if (state.get_set() != ElementSet::COE) {
        throw std::runtime_error("The Mean J2 dynamics evaluator requires that the incoming Orbital Element set is in COE coordinates.");
    }

    // Extract
    const double& a = state[0];
    const double& _ecc = state[1];
    const double& _inc = state[2];
    const double& raan = state[3];
    const double& w = state[4];
    const double& theta = state[5];

    // h and mu
    const double& mu = centralBody.mu();
    const double h = sqrt(mu*a*(1 - _ecc));

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    double inc = _inc;
    if (inc < checkTol) {
        checkflag = true;
        inc = checkTol;
    }

    // conversions COEs to r and v
    const auto cartesianState = conversions::convert(state, ElementSet::COE, ElementSet::CARTESIAN, &system);

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
    const auto accelPerts = find_perts(cartesianState);

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

const OrbitalElements EquationsOfMotion::evaluate_mees_vop(const OrbitalElements& state) {

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
    const auto coesState = conversions::convert(state, ElementSet::MEE, ElementSet::COE, &system);

    const double& ecc = coesState[1];
    const double& inc = coesState[2];
    const double& w = coesState[3];
    const double& raan = coesState[4];
    const double& theta = coesState[5];

    // h and mu
    const double& mu = centralBody.mu();

    // conversions COEs to r and v
    const auto cartesianState = conversions::convert(coesState, ElementSet::COE, ElementSet::CARTESIAN, &system);

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
    const auto accelPerts = find_perts(cartesianState);

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

const OrbitalElements EquationsOfMotion::find_perts(const OrbitalElements& state) {

    if (state.get_set() != ElementSet::CARTESIAN) {
        throw std::runtime_error("The find_perts method requires that the incoming Orbital Element set is in CARTESIAN coordinates.");
    }

    // Run find functions for force model
    OrbitalElements accelPerts;
    if (oblateness) { accelPerts += find_accel_oblateness(state); }
    if (drag)       { accelPerts += find_accel_drag(state); }
    if (lift)       { accelPerts += find_accel_lift(state); }
    if (srp)        { accelPerts += find_accel_srp(state); }
    if (nbody)      { accelPerts += find_accel_n_body(state); }

    return accelPerts;
}

const OrbitalElements EquationsOfMotion::find_accel_oblateness(const OrbitalElements& state) {
    
    // Extract
    const double& x = state[0]; 
    const double& y = state[1]; 
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3]; 
    const double& vy = state[4]; 
    const double& vz = state[5];

    // Central body properties
    const double& mu = centralBody.mu();
    const double& equitorialR = centralBody.eqR();
    const double& bodyRotationRate = centralBody.rotRate();
    
    /* 
        To clarify this logic: Use J2 if
            1) NxM Oblateness is not selected
            2) N = 2 and M = 0, which is J2
            3) The central body is not Venus, Earth, the Moon, or Mars
            4) If Mars is the planet id, the moon id must be 0 to ensure the central body is not phobos or deimos
    */
    double accelOblateness[3] = {0.0, 0.0, 0.0};
    if (!NxMOblateness || (N == 2 && M == 0) || (centralBody.planetId() != 2 && centralBody.planetId() != 3 && !(centralBody.planetId() == 4 && centralBody.moonId() == 0))) { // J2 oblateness only
        // Variables to reduce calculations
        const double& J2 = centralBody.j2();
        const double tempA = -1.5*J2*mu*equitorialR*equitorialR/pow(R,5);
        const double tempB = z*z/(R*R);

        // accel due to oblateness
        accelOblateness[0] = tempA*(1.0 - 5.0*tempB)*x;
        accelOblateness[1] = tempA*(1.0 - 5.0*tempB)*y;
        accelOblateness[2] = tempA*(1.0 - 3.0*tempB)*z;
    }
    else { // Any NxM gravitational field
        // Find lat and long
        double radius[3] = {x, y, z};
        double rBCBF[3];
        conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);

        const double& xBCBF = rBCBF[0];
        const double& yBCBF = rBCBF[1];

        const double longitude = atan2(yBCBF,xBCBF);
        const double latitude = asin(z/R);

        const double cosLat = cos(latitude);
        const double sinLat = sin(latitude);
        const double tanLat = sinLat/cosLat;

        // Populate Legendre polynomial array
        assign_legendre(latitude);

        // Calculate serivative of gravitational potential field with respect to
        double dVdr = 0.0;       // radius
        double dVdlat = 0.0;     // geocentric latitude
        double dVdlong = 0.0;    // longitude
        for (int n = 2; n < N+1; ++n) {
            const double nn = (double)n;

            // Reset inner sums
            double dVdrInnerSum = 0.0;
            double dVdlatInnerSum = 0.0;
            double dVdlongInnerSum = 0.0;

            for (int m = 0; m < std::min(n,M)+1; ++m) {
                const double mm = (double) m;

                // Precalculate common terms
                const double cosLongM = cos(mm*longitude);
                const double sinLongM = sin(mm*longitude);

                // dVdr
                dVdrInnerSum += (C[n][m]*cosLongM + S[n][m]*sinLongM)*P[n][m];

                //dVdlat
                double gamma;
                if (m == 0) {
                    gamma = sqrt((nn - mm)*(nn + mm + 1.0)*0.5);
                }
                else{
                    gamma = sqrt((nn - mm)*(nn + mm + 1.0));
                }
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
        double accelOblatenessBCBF[3] = { 
            dVdr*drdrBCBF[0] + dVdlat*dlatdrBCBF[0] + dVdlong*dlongdrBCBF[0],
            dVdr*drdrBCBF[1] + dVdlat*dlatdrBCBF[1] + dVdlong*dlongdrBCBF[1],
            dVdr*drdrBCBF[2] + dVdlat*dlatdrBCBF[2]
        };

        // Rotate back into inertial coordinates
        conversions::bcbf_to_bci(accelOblatenessBCBF, julianDate, bodyRotationRate, accelOblateness);
    }
    
    const OrbitalElements accelOblate({
        accelOblateness[0],
        accelOblateness[1],
        accelOblateness[2]
    }, ElementSet::CARTESIAN);

    return accelOblate;
}

const OrbitalElements EquationsOfMotion::find_accel_drag(const OrbitalElements& state) {
    
    // Extract
    const double& x = state[0]; 
    const double& y = state[1]; 
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3]; 
    const double& vy = state[4]; 
    const double& vz = state[5];

    // Central body properties
    const double& mu = centralBody.mu();
    const double& bodyRotationRate = centralBody.rotRate();

    // Find velocity relative to atmosphere
    const double relativeVelocity[3] = {
        vx - y*bodyRotationRate*SEC_TO_DAY*DEG_TO_RAD,
        vy + x*bodyRotationRate*SEC_TO_DAY*DEG_TO_RAD,
        vz
    };

    // Exponential Drag Model
    const double atmosphericDensity = find_atmospheric_density(state);

    // accel due to drag
    const double relativeVelocityMagnitude = math_c::normalize(relativeVelocity);

    double coefficientOfDrag = spacecraft->get_coefficient_of_drag();
    double *areaRam = spacecraft->get_ram_area();
    double mass = spacecraft->get_mass();
    const double dragMagnitude = -0.5*coefficientOfDrag*(areaRam[0] + areaRam[1] + areaRam[2])/mass*atmosphericDensity*relativeVelocityMagnitude;
    
    const OrbitalElements accelDrag({
        dragMagnitude*relativeVelocity[0],
        dragMagnitude*relativeVelocity[1],
        dragMagnitude*relativeVelocity[2]
    }, ElementSet::CARTESIAN);
    
    return accelDrag;
}

const OrbitalElements EquationsOfMotion::find_accel_lift(const OrbitalElements& state) {
    
    // Extract
    const double& x = state[0]; 
    const double& y = state[1]; 
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3]; 
    const double& vy = state[4]; 
    const double& vz = state[5];

    // Velocity in the radial direction
    const double radialVelcityMagnitude = (vx*x + vy*y + vz*z)/R;

    double atmosphericDensity = 0.0;
    if (!drag) { // no need to evaluate twice
        atmosphericDensity = find_atmospheric_density(state);
    }

    // accel due to lift
    const double coefficientOfLift = spacecraft->get_coefficient_of_lift();
    const double* areaLift = spacecraft->get_lift_area();
    const double mass = spacecraft->get_mass();
    const double tempA = 0.5*coefficientOfLift*(areaLift[0] + areaLift[1] + areaLift[2])/mass*atmosphericDensity*radialVelcityMagnitude*radialVelcityMagnitude/R;

    const OrbitalElements accelLift({
        tempA*x,
        tempA*y,
        tempA*z
    }, ElementSet::CARTESIAN);
    
    return accelLift;
}

const OrbitalElements EquationsOfMotion::find_accel_srp(const OrbitalElements& state) {
    
    // Extract
    const double& x = state[0]; 
    const double& y = state[1]; 
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3]; 
    const double& vy = state[4]; 
    const double& vz = state[5];

    // Central body properties
    const double& equitorialR = centralBody.eqR();

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*

    // Find day nearest to current time
    const int index = std::min((int)round(t*SEC_TO_DAY), sizeOfDateArray-1);

    // Radius from central body to sun
    for (int jj = 0; jj < 3; ++jj) {
        radiusCentralBodyToSun[jj] = -radiusSunToCentralBody[index][jj]; // flip vector direction
    }
    radialMagnitudeCentralBodyToSun = math_c::normalize(radiusCentralBodyToSun);

    radiusSpacecraftToSun[0] = radiusCentralBodyToSun[0] - x;
    radiusSpacecraftToSun[1] = radiusCentralBodyToSun[1] - y;
    radiusSpacecraftToSun[2] = radiusCentralBodyToSun[2] - z;
    radialMagnitudeSpacecraftToSun = math_c::normalize(radiusSpacecraftToSun);

    // Solar radiation pressure
    solarRadiationPressure = solarRadiationPressureAt1AU*AU*AU/(radialMagnitudeSpacecraftToSun*radialMagnitudeSpacecraftToSun); // Scale by(1AU/R)^2 for other bodies
    fractionOfRecievedSunlight = 1.0;

    if (centralBody.planetId() != 0) {
        // 
        //  This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
        //  satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details. 
        //

        referenceAngle = acos((radiusCentralBodyToSun[0]*x + radiusCentralBodyToSun[1]*y + radiusCentralBodyToSun[2]*z)/(radialMagnitudeCentralBodyToSun*R));
        referenceAngle1 = acos(equitorialR/R);
        referenceAngle2 = acos(equitorialR/radialMagnitudeCentralBodyToSun);

        if (referenceAngle1 + referenceAngle2 <= referenceAngle) { // In shadow
            Xu = equitorialR*radialMagnitudeCentralBodyToSun/(696000.0 - equitorialR); // that constant has something to do with the diameter of the sun

            rP[0] = -Xu*radiusCentralBodyToSun[0]/radialMagnitudeCentralBodyToSun;
            rP[1] = -Xu*radiusCentralBodyToSun[1]/radialMagnitudeCentralBodyToSun;
            rP[2] = -Xu*radiusCentralBodyToSun[2]/radialMagnitudeCentralBodyToSun;

            rPs[0] = x - rP[0];
            rPs[1] = y - rP[1];
            rPs[2] = z - rP[2];

            normRP = math_c::normalize(rP);
            normRPs = math_c::normalize(rPs);

            alphaps = abs(asin((-rPs[0]*rP[0] - rPs[1]*rP[1] - rPs[2]*rP[2])/(normRP*normRPs)));

            if (alphaps < asin(equitorialR/Xu)) { // Umbra
                fractionOfRecievedSunlight = 0.0; 
            }
            else { // Penumbra
                fractionOfRecievedSunlight = 0.5; 
            } 
        }
    }

    // accel due to srp
    const double coefficientOfReflectivity = spacecraft->get_coefficient_of_reflectivity();
    const double *areaSun = spacecraft->get_sun_area();
    const double mass = spacecraft->get_mass();
    const double tempA = -solarRadiationPressure*coefficientOfReflectivity*(areaSun[0] + areaSun[1] + areaSun[2])/mass/radialMagnitudeSpacecraftToSun*fractionOfRecievedSunlight;

    accelSRP[0] = tempA*radiusSpacecraftToSun[0];
    accelSRP[1] = tempA*radiusSpacecraftToSun[1];
    accelSRP[2] = tempA*radiusSpacecraftToSun[2];

    */
    const OrbitalElements accelSRP({
        0.0,
        0.0,
        0.0
    }, ElementSet::CARTESIAN);
    
    return accelSRP;
}

const OrbitalElements EquationsOfMotion::find_accel_n_body(const OrbitalElements& state) {
    
    // Extract
    const double& x = state[0]; 
    const double& y = state[1]; 
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    const double& vx = state[3]; 
    const double& vy = state[4]; 
    const double& vz = state[5];

    // Central body properties
    const double& mu = centralBody.mu();
    const double& equitorialR = centralBody.eqR();
    const double& bodyRotationRate = centralBody.rotRate();

    throw std::logic_error("This function has not been properly updated and is not currently functional.");

    /*
    
    // Find day nearest to current time
    const int index = std::min((int)round(t*SEC_TO_DAY), sizeOfDateArray-1);

    // Radius from central body to sun
    for (int jj = 0; jj < 3; ++jj) {
        radiusCentralBodyToSun[jj] = -radiusSunToCentralBody[index][jj]; // flip vector direction
    }

    // Reset perturbation
    accelNBody[0] = 0.0;
    accelNBody[1] = 0.0;
    accelNBody[2] = 0.0;
    for (int ii = 0; ii < nBodies; ++ii) {
        // Find radius from central body and spacecraft to nth body
        radiusCentralBodyToNbody[0] = radiusSunToNbody[index][ii*3]   + radiusCentralBodyToSun[0];
        radiusCentralBodyToNbody[1] = radiusSunToNbody[index][ii*3+1] + radiusCentralBodyToSun[1];
        radiusCentralBodyToNbody[2] = radiusSunToNbody[index][ii*3+2] + radiusCentralBodyToSun[2];

        radiusSpacecraftToNbody[0] = radiusCentralBodyToNbody[0] - x;
        radiusSpacecraftToNbody[1] = radiusCentralBodyToNbody[1] - y;
        radiusSpacecraftToNbody[2] = radiusCentralBodyToNbody[2] - z;

        // Normalize
        radiusSpacecraftToNbodyMagnitude = math_c::normalize(radiusSpacecraftToNbody);
        radiusCentralToNbodyMagnitude = math_c::normalize(radiusCentralBodyToNbody);

        // Perturbational force from nth body
        const double tempA = nBodyGravitationalParameter[ii]/(radiusSpacecraftToNbodyMagnitude*radiusSpacecraftToNbodyMagnitude*radiusSpacecraftToNbodyMagnitude);
        const double tempB = nBodyGravitationalParameter[ii]/(radiusCentralToNbodyMagnitude*radiusCentralToNbodyMagnitude*radiusCentralToNbodyMagnitude);

        accelNBody[0] += tempA*radiusSpacecraftToNbody[0] - tempB*radiusCentralBodyToNbody[0];
        accelNBody[1] += tempA*radiusSpacecraftToNbody[1] - tempB*radiusCentralBodyToNbody[1];
        accelNBody[2] += tempA*radiusSpacecraftToNbody[2] - tempB*radiusCentralBodyToNbody[2];
    }
    */
    const OrbitalElements accelNBody({
        0.0,
        0.0,
        0.0
    }, ElementSet::CARTESIAN);
    
    return accelNBody;
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------- Atmospheric Density Model ----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

const double EquationsOfMotion::find_atmospheric_density(const OrbitalElements& state) {
    
    // Extract
    const double& x = state[0]; 
    const double& y = state[1]; 
    const double& z = state[2];
    const double R = sqrt(x*x + y*y + z*z);

    // Central body properties
    const double& equitorialR = centralBody.eqR();
    const double& polarR = centralBody.polR();
    const double& bodyRotationRate = centralBody.rotRate();

    // Find altitude
    double altitude{};
    if (doEstimateAltitude) {
        altitude = std::max(R - equitorialR, 0.0);
    }
    else {
        double radius[3] = {x, y, z};
        double rBCBF[3]{};
        double lla[3]{};
        conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);
        conversions::bcbf_to_lla(rBCBF, equitorialR, polarR, lla);
        altitude = lla[2];
    }

    // Assume that bodies not listed have no significant atmosphere.Assume that
    // the atmosphere of the gas giants is defined by their radii, e.g.
    // outside of their equitorial radius, they have no noticible atmosphere
    // and inside that radius, the object will crash.
    double atmosphericDensity = 0.0;
    double referenceAltitude{};
    double referenceDensity{};
    double scaleHeight{};
    switch (centralBody.planetId()) {
    case 2: // Venus
        if      (altitude < 3.0)   { atmosphericDensity = 5.53e1; } // kg/m^3
        else if (altitude < 6.0)   { atmosphericDensity = 4.75e1; }
        else if (altitude < 9.0)   { atmosphericDensity = 4.02e1; }
        else if (altitude < 12.0)  { atmosphericDensity = 3.44e1; }
        else if (altitude < 15.0)  { atmosphericDensity = 2.91e1; }
        else if (altitude < 18.0)  { atmosphericDensity = 2.46e1; }
        else if (altitude < 21.0)  { atmosphericDensity = 2.06e1; }
        else if (altitude < 24.0)  { atmosphericDensity = 1.70e1; }
        else if (altitude < 27.0)  { atmosphericDensity = 1.405e1; }
        else if (altitude < 30.0)  { atmosphericDensity = 1.115e1; }
        else if (altitude < 33.0)  { atmosphericDensity = 9.0; }
        else if (altitude < 36.0)  { atmosphericDensity = 7.15; }
        else if (altitude < 39.0)  { atmosphericDensity = 5.15; }
        else if (altitude < 42.0)  { atmosphericDensity = 4.34; }
        else if (altitude < 45.0)  { atmosphericDensity = 3.30; }
        else if (altitude < 48.0)  { atmosphericDensity = 2.39; }
        else if (altitude < 51.0)  { atmosphericDensity = 1.88; }
        else if (altitude < 54.0)  { atmosphericDensity = 1.38; }
        else if (altitude < 57.0)  { atmosphericDensity = 9.6e-1; }
        else if (altitude < 60.0)  { atmosphericDensity = 6.2e-1; }
        else if (altitude < 70.0)  { atmosphericDensity = 1.2e-1; }
        else if (altitude < 80.0)  { atmosphericDensity = 1.8e-2; }
        else if (altitude < 90.0)  { atmosphericDensity = 2.3e-3; }
        else if (altitude < 100.0) { atmosphericDensity = 3.1e-4; }
        else if (altitude < 110.0) { atmosphericDensity = 4.4e-5; }
        else if (altitude < 120.0) { atmosphericDensity = 7.2e-6; }
        else if (altitude < 130.0) { atmosphericDensity = 1.4e-6; }
        else if (altitude < 140.0) { atmosphericDensity = 3.0e-7; }
        else if (altitude < 150.0) { atmosphericDensity = 8.0e-8; }
        else if (altitude < 160.0) { atmosphericDensity = 2.6e-8; }
        else if (altitude < 170.0) { atmosphericDensity = 9.5e-9; }
        else if (altitude < 180.0) { atmosphericDensity = 4.0e-9; }
        else if (altitude < 190.0) { atmosphericDensity = 1.9e-9; }
        else if (altitude < 200.0) { atmosphericDensity = 9.4e-10; }
        else if (altitude < 210.0) { atmosphericDensity = 4.9e-10; }
        else if (altitude < 220.0) { atmosphericDensity = 2.6e-10; }
        else if (altitude < 230.0) { atmosphericDensity = 1.4e-10; }
        else if (altitude < 240.0) { atmosphericDensity = 7.5e-11; }
        else if (altitude < 250.0) { atmosphericDensity = 5.5e-11; }
        else if (altitude < 260.0) { atmosphericDensity = 4.1e-11; }
        else if (altitude < 270.0) { atmosphericDensity = 2.2e-11; }
        else if (altitude < 280.0) { atmosphericDensity = 1.2e-11; }
        else if (altitude < 290.0) { atmosphericDensity = 6.5e-12; }
        else if (altitude < 300.0) { atmosphericDensity = 3.5e-12; }
        else                       { atmosphericDensity = 0.0; }

        atmosphericDensity *= 1.0e9; // kg/m^3->kg/km^3
        break;

    case 3: // Earth
        // Altitude Conditions(TABLE 7-4, Vallado)
        if      (altitude < 25.0)   { referenceAltitude = 0.0;    referenceDensity = 1.225;     scaleHeight = 7.249; } // km, kg/m^3, km 
        else if (altitude < 30.0)   { referenceAltitude = 25.0;   referenceDensity = 3.899e-2;  scaleHeight = 6.349; }
        else if (altitude < 40.0)   { referenceAltitude = 30.0;   referenceDensity = 1.774e-2;  scaleHeight = 6.682; }
        else if (altitude < 50.0)   { referenceAltitude = 40.0;   referenceDensity = 3.972e-3;  scaleHeight = 7.554; }
        else if (altitude < 60.0)   { referenceAltitude = 50.0;   referenceDensity = 1.057e-3;  scaleHeight = 8.382; }
        else if (altitude < 70.0)   { referenceAltitude = 60.0;   referenceDensity = 3.206e-4;  scaleHeight = 7.714; }
        else if (altitude < 80.0)   { referenceAltitude = 70.0;   referenceDensity = 8.770e-5;  scaleHeight = 6.549; }
        else if (altitude < 90.0)   { referenceAltitude = 80.0;   referenceDensity = 1.905e-5;  scaleHeight = 5.799; } 
        else if (altitude < 100.0)  { referenceAltitude = 90.0;   referenceDensity = 3.396e-6;  scaleHeight = 5.382; }
        else if (altitude < 110.0)  { referenceAltitude = 100.0;  referenceDensity = 5.297e-7;  scaleHeight = 5.877; }
        else if (altitude < 120.0)  { referenceAltitude = 110.0;  referenceDensity = 9.661e-8;  scaleHeight = 7.263; }
        else if (altitude < 130.0)  { referenceAltitude = 120.0;  referenceDensity = 2.438e-8;  scaleHeight = 9.473; }
        else if (altitude < 140.0)  { referenceAltitude = 130.0;  referenceDensity = 8.484e-9;  scaleHeight = 12.636; }
        else if (altitude < 150.0)  { referenceAltitude = 140.0;  referenceDensity = 3.845e-9;  scaleHeight = 16.149; }
        else if (altitude < 180.0)  { referenceAltitude = 150.0;  referenceDensity = 2.070e-9;  scaleHeight = 22.523; }
        else if (altitude < 200.0)  { referenceAltitude = 180.0;  referenceDensity = 5.464e-10; scaleHeight = 29.740; }
        else if (altitude < 250.0)  { referenceAltitude = 200.0;  referenceDensity = 2.789e-10; scaleHeight = 37.105; }
        else if (altitude < 300.0)  { referenceAltitude = 250.0;  referenceDensity = 7.248e-11; scaleHeight = 45.546; }
        else if (altitude < 350.0)  { referenceAltitude = 300.0;  referenceDensity = 2.418e-11; scaleHeight = 53.628; }
        else if (altitude < 400.0)  { referenceAltitude = 350.0;  referenceDensity = 9.158e-12; scaleHeight = 53.298; }
        else if (altitude < 450.0)  { referenceAltitude = 400.0;  referenceDensity = 3.725e-12; scaleHeight = 58.515; }
        else if (altitude < 500.0)  { referenceAltitude = 450.0;  referenceDensity = 1.585e-12; scaleHeight = 60.828; }
        else if (altitude < 600.0)  { referenceAltitude = 500.0;  referenceDensity = 6.967e-13; scaleHeight = 63.822; }
        else if (altitude < 700.0)  { referenceAltitude = 600.0;  referenceDensity = 1.454e-13; scaleHeight = 71.835; }
        else if (altitude < 800.0)  { referenceAltitude = 700.0;  referenceDensity = 3.614e-14; scaleHeight = 88.667; }
        else if (altitude < 900.0)  { referenceAltitude = 800.0;  referenceDensity = 1.170e-14; scaleHeight = 124.64; }
        else if (altitude < 1000.0) { referenceAltitude = 900.0;  referenceDensity = 5.245e-15; scaleHeight = 181.05; }
        else if (altitude < 1100.0) { referenceAltitude = 1000.0; referenceDensity = 2.019e-15; scaleHeight = 268.00; }
        else                        { referenceAltitude = 1100.0; referenceDensity = 0.0;       scaleHeight = 1.0; }

        atmosphericDensity = referenceDensity*exp((referenceAltitude - altitude)/scaleHeight)*1.0e9; // kg/m^3 -> kg/km^3

        break;

    case 4: // Mars
        // The values up to 80 km are almost definitely wrong.I can't find any
        // sources that contradict them though.Please fix them(and the
        // associated crash radius of Mars) if you can find better numbers.
        if      (altitude < 2.0)   { atmosphericDensity = 1.19e-1; } // kg/m^3
        else if (altitude < 4.0)   { atmosphericDensity = 1.10e-1; }
        else if (altitude < 6.0)   { atmosphericDensity = 1.02e-1; }
        else if (altitude < 8.0)   { atmosphericDensity = 9.39e-2; }
        else if (altitude < 10.0)  { atmosphericDensity = 8.64e-2; }
        else if (altitude < 12.0)  { atmosphericDensity = 7.93e-2; }
        else if (altitude < 14.0)  { atmosphericDensity = 7.25e-2; }
        else if (altitude < 16.0)  { atmosphericDensity = 6.61e-2; }
        else if (altitude < 18.0)  { atmosphericDensity = 6.00e-2; }
        else if (altitude < 20.0)  { atmosphericDensity = 5.43e-2; }
        else if (altitude < 22.0)  { atmosphericDensity = 4.89e-2; }
        else if (altitude < 24.0)  { atmosphericDensity = 3.91e-2; }
        else if (altitude < 26.0)  { atmosphericDensity = 3.32e-2; }
        else if (altitude < 28.0)  { atmosphericDensity = 2.82e-2; }
        else if (altitude < 30.0)  { atmosphericDensity = 2.40e-2; }
        else if (altitude < 32.0)  { atmosphericDensity = 2.04e-2; }
        else if (altitude < 34.0)  { atmosphericDensity = 1.73e-2; }
        else if (altitude < 36.0)  { atmosphericDensity = 1.47e-2; }
        else if (altitude < 38.0)  { atmosphericDensity = 1.25e-2; }
        else if (altitude < 40.0)  { atmosphericDensity = 1.06e-2; }
        else if (altitude < 45.0)  { atmosphericDensity = 7.03e-3; }
        else if (altitude < 50.0)  { atmosphericDensity = 4.67e-3; }
        else if (altitude < 55.0)  { atmosphericDensity = 3.10e-3; }
        else if (altitude < 60.0)  { atmosphericDensity = 2.06e-3; }
        else if (altitude < 65.0)  { atmosphericDensity = 1.36e-3; }
        else if (altitude < 70.0)  { atmosphericDensity = 9.11e-4; }
        else if (altitude < 75.0)  { atmosphericDensity = 6.05e-4; }
        else if (altitude < 80.0)  { atmosphericDensity = 4.02e-4; }
        else if (altitude < 200.0) { atmosphericDensity = exp(-2.55314e-10*pow(altitude, 5) + 2.31927e-7*pow(altitude, 4) - 8.33206e-5*pow(altitude, 3) + 0.0151947*pow(altitude, 2) - 1.52799*altitude + 48.69659); }
        else if (altitude < 300.0) { atmosphericDensity = exp(2.65472e-11*pow(altitude, 5) - 2.45558e-8*pow(altitude, 4) + 6.31410e-6*pow(altitude, 3) + 4.73359e-4*pow(altitude, 2) - 0.443712*altitude + 23.79408); }
        else { atmosphericDensity = 0.0; }

        atmosphericDensity *= 1.0e9;  // kg/m^3->kg/km^3
        break;

    case 5: // Titan
        if      (altitude < 780.0)  { atmosphericDensity = 1.00e-12; } // g/cm^3
        else if (altitude < 790.0)  { atmosphericDensity = 8.45e-12; }
        else if (altitude < 800.0)  { atmosphericDensity = 7.16e-12; }
        else if (altitude < 810.0)  { atmosphericDensity = 6.08e-12; }
        else if (altitude < 820.0)  { atmosphericDensity = 5.17e-12; }
        else if (altitude < 830.0)  { atmosphericDensity = 4.41e-12; }
        else if (altitude < 840.0)  { atmosphericDensity = 3.77e-12; }
        else if (altitude < 850.0)  { atmosphericDensity = 3.23e-12; }
        else if (altitude < 860.0)  { atmosphericDensity = 2.78e-12; }
        else if (altitude < 870.0)  { atmosphericDensity = 2.39e-12; }
        else if (altitude < 880.0)  { atmosphericDensity = 2.06e-12; }
        else if (altitude < 890.0)  { atmosphericDensity = 1.78e-12; }
        else if (altitude < 900.0)  { atmosphericDensity = 1.54e-12; }
        else if (altitude < 910.0)  { atmosphericDensity = 1.34e-12; }
        else if (altitude < 920.0)  { atmosphericDensity = 1.16e-12; }
        else if (altitude < 930.0)  { atmosphericDensity = 1.01e-12; }
        else if (altitude < 940.0)  { atmosphericDensity = 8.80e-13; }
        else if (altitude < 950.0)  { atmosphericDensity = 7.67e-13; }
        else if (altitude < 960.0)  { atmosphericDensity = 6.69e-13; }
        else if (altitude < 970.0)  { atmosphericDensity = 5.84e-13; }
        else if (altitude < 980.0)  { atmosphericDensity = 5.10e-13; }
        else if (altitude < 990.0)  { atmosphericDensity = 4.46e-13; }
        else if (altitude < 1000.0) { atmosphericDensity = 3.90e-13; }
        else if (altitude < 1010.0) { atmosphericDensity = 1.81e-13; }
        else if (altitude < 1020.0) { atmosphericDensity = 2.99e-13; }
        else if (altitude < 1030.0) { atmosphericDensity = 2.62e-13; }
        else if (altitude < 1040.0) { atmosphericDensity = 2.30e-13; }
        else if (altitude < 1050.0) { atmosphericDensity = 2.02e-13; }
        else if (altitude < 1060.0) { atmosphericDensity = 1.78e-13; }
        else if (altitude < 1070.0) { atmosphericDensity = 1.56e-13; }
        else if (altitude < 1080.0) { atmosphericDensity = 1.38e-13; }
        else if (altitude < 1090.0) { atmosphericDensity = 1.21e-13; }
        else if (altitude < 1100.0) { atmosphericDensity = 1.07e-13; }
        else if (altitude < 1110.0) { atmosphericDensity = 9.43e-14; }
        else if (altitude < 1120.0) { atmosphericDensity = 8.33e-14; }
        else if (altitude < 1130.0) { atmosphericDensity = 7.36e-14; }
        else if (altitude < 1140.0) { atmosphericDensity = 6.51e-14; }
        else if (altitude < 1150.0) { atmosphericDensity = 5.76e-14; }
        else if (altitude < 1160.0) { atmosphericDensity = 5.10e-14; }
        else if (altitude < 1170.0) { atmosphericDensity = 4.52e-14; }
        else if (altitude < 1180.0) { atmosphericDensity = 4.01e-14; }
        else if (altitude < 1190.0) { atmosphericDensity = 3.56e-14; }
        else if (altitude < 1200.0) { atmosphericDensity = 3.16e-14; }
        else if (altitude < 1210.0) { atmosphericDensity = 2.81e-14; }
        else if (altitude < 1220.0) { atmosphericDensity = 2.50e-14; }
        else if (altitude < 1230.0) { atmosphericDensity = 2.22e-14; }
        else if (altitude < 1240.0) { atmosphericDensity = 1.98e-14; }
        else if (altitude < 1250.0) { atmosphericDensity = 1.77e-14; }
        else if (altitude < 1260.0) { atmosphericDensity = 1.58e-14; }
        else if (altitude < 1270.0) { atmosphericDensity = 1.41e-14; }
        else if (altitude < 1280.0) { atmosphericDensity = 1.26e-14; }
        else if (altitude < 1290.0) { atmosphericDensity = 1.12e-14; }
        else if (altitude < 1300.0) { atmosphericDensity = 1.00e-14; }
        else                        { atmosphericDensity = 0.0; }

        atmosphericDensity *= 1.0e12;  // g/cm^3->kg/km^3
        break;
    }

    return atmosphericDensity;
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------- Getters ------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------ Supporting Functions ------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void EquationsOfMotion::get_oblateness_coefficients(int N, int M) {
    // Open coefficients file
    char filename[200];
    char path[100];
    sprintf(path, "./data/gravity_models/");

    if (centralBody.planetId() == 2) { // Venus
        sprintf(filename, "%sshgj120p.txt", path); // Normalized?
    }
    else if (centralBody.planetId() == 3 && centralBody.moonId() == 0) { // Earth
        sprintf(filename, "%sEGM2008_to2190_ZeroTide_mod.txt", path); // Normalized
    }
    else if (centralBody.planetId() == 3 && centralBody.moonId() == 1) { // Moon
        sprintf(filename, "%sjgl165p1.txt", path); // Normalized?
    }
    else if (centralBody.planetId() == 3) { // Mars
        sprintf(filename, "%sgmm3120.txt", path); // Do not appear to be normalized
    }
    std::ifstream file(filename);

    // Size arrays (size Legendre array now so it only happens once)
    C = new double*[N+1];
    S = new double*[N+1];
    P = new double*[N+1];
    for (int n = 0; n < N+1; ++n) {
        C[n] = new double[M+1];
        S[n] = new double[M+1];
        P[n] = new double[M+1];

        for (int m = 0; m < M+1; ++m) {
            C[n][m] = 0.0;
            S[n][m] = 0.0;
            P[n][m] = 0.0;
        }
    }
    
    // Read coefficients from file
    std::string line;
    std::vector<std::vector<double>> coefficients;

    std::string cell;
    
    int n = 0, m = 0;
    while (file) {
        // Read line from stream
        std::getline(file, line);
        std::stringstream lineStream(line);
        std::vector<double> lineData;
        while (std::getline(lineStream, cell, ',')) {
            lineData.push_back(std::atof(cell.c_str()));
        }

        n = (int)lineData[0];
        m = (int)lineData[1];

        C[n][m] = lineData[2];
        S[n][m] = lineData[3];

        // Normalize coefficients if needed
        if (centralBody.planetId() == 4) {
            for (int m = 0; m < N+1; ++m) {
                double nPlusMFactorial = 1;
                double nMinusMFactorial = 1;
                for (int ii = n + m; ii > 0; --ii) {
                    nPlusMFactorial *= ii;
                    if (ii <= n-m) {
                        nMinusMFactorial *= ii;
                    }
                }

                double Nnm;
                if (m == 0) {
                    Nnm = sqrt(nMinusMFactorial*(2*n + 1)/nPlusMFactorial);
                }
                else {
                    Nnm = sqrt(nMinusMFactorial*(2*n + 1)*2/nPlusMFactorial);
                }

                C[n][m] /= Nnm;
                S[n][m] /= Nnm;
            }
        }

        if (n >= N && m >= M) { break; }
    }
    file.close();
}

void EquationsOfMotion::assign_legendre(const double latitude) {
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
    */
    const double cosLat = cos(latitude);
    const double sinLat = sin(latitude);
    for (int n = 0; n < N+1; ++n) {
        const double nn = (double)n;

        for (int m = 0; m < M+1; ++m) {
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

bool EquationsOfMotion::check_crash(double* state) {

    const double R = math_c::normalize(state, 0, 2);
    const double V = math_c::normalize(state, 3, 5);

    if ((R <= crashRadius) || (V <= crashVelocity)) {
        return true;
    }
    return false;
}


// Central Body stuff
void EquationsOfMotion::set_mu(double mu) {
    mu = mu;
}

void EquationsOfMotion::set_crash_radius(double crashRadius) {
    crashRadius = crashRadius;
}
void EquationsOfMotion::set_crash_velocity(double crashVelocity) {
    crashVelocity = crashVelocity;
}

// Central Body getter
double EquationsOfMotion::get_mu() { return centralBody.mu(); }

// Perturbation toggles
void EquationsOfMotion::switch_oblateness(bool onOff) {
    oblateness = onOff;
}
void EquationsOfMotion::switch_oblateness(int _N, int _M) {
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
