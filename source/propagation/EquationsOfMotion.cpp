#include "EquationsOfMotion.hpp"
#include "conversions.hpp"

// Constructors 
EquationsOfMotion::EquationsOfMotion() : spacecraft() {
    // Make central Body
    const GravitationalBody& centralBody = system->get_center();

    // Assign properties from central body
    ;

    // Assign these defaults separately so they don't override mannual choices later
    mu = centralBody.mu();
    crashRadius = centralBody.crashR();
    crashVelocity = 0.0;
}

// Destructor
EquationsOfMotion::~EquationsOfMotion(){
    // Clean up
    if (sizeOfDateArray > 1){
        for (int ii = 0; ii < sizeOfDateArray; ++ii) {
            delete[] radiusSunToCentralBody[ii];
            delete[] radiusSunToNbody[ii];
        }
        delete[] radiusSunToCentralBody;
        delete[] radiusSunToNbody;

        delete[] nBodyGravitationalParameter;
    }
    else{
        delete radiusSunToCentralBody;
        delete radiusSunToNbody;

        delete nBodyGravitationalParameter;
    }

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
    system = sc->get_initial_state().elements.get_system();

    // Time
    t = time;
    julianDate = initialJulianDate + t*SEC_TO_DAY;

    // Assign state variables
    if ( twoBody || cowellsMethod ) {
        x = state[0];
        y = state[1];
        z = state[2];
        vx = state[3];
        vy = state[4];
        vz = state[5];
    }
    else if ( coesVoP || j2MeanVoP ) {
        h = state[0];
        ecc = state[1];
        inc = state[2];
        w = state[3];
        raan = state[4];
        theta = state[5];
    }
    else if ( meesVoP ) {
        p = state[0];
        f = state[1];
        g = state[2];
        h = state[3];
        k = state[4];
        L = state[5];
    }

    // Evaluate derivative
    if      ( twoBody       ) { evaluate_two_body_dynamics(); }
    else if ( cowellsMethod ) { evaluate_cowells_method(); }
    else if ( coesVoP       ) { evaluate_coes_vop(); }
    else if ( j2MeanVoP     ) { evaluate_j2mean_coes_vop(); }
    else if ( meesVoP       ) { evaluate_mees_vop(); }

    // Assign output variables
    if ( twoBody || cowellsMethod ) {
        stateDerivative[0] = dxdt;
        stateDerivative[1] = dydt;
        stateDerivative[2] = dzdt;
        stateDerivative[3] = dvxdt;
        stateDerivative[4] = dvydt;
        stateDerivative[5] = dvzdt;
    }
    else if ( coesVoP || j2MeanVoP ) {
        stateDerivative[0] = dhdt;
        stateDerivative[1] = deccdt;
        stateDerivative[2] = dincdt;
        stateDerivative[3] = dwdt;
        stateDerivative[4] = draandt;
        stateDerivative[5] = dthetadt;
    }
    else if ( meesVoP ) {
        stateDerivative[0] = dpdt;
        stateDerivative[1] = dfdt;
        stateDerivative[2] = dgdt;
        stateDerivative[3] = dhdt;
        stateDerivative[4] = dkdt;
        stateDerivative[5] = dLdt;
    }
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------ Equations of Motion -------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void EquationsOfMotion::evaluate_two_body_dynamics() {

    // Calculate required values for force model
    R = sqrt(x*x + y*y + z*z);

    // mu/R^3
    muOverRadiusCubed = mu/(R*R*R);

    // Derivative
    dxdt = vx;
    dydt = vy;
    dzdt = vz;
    dvxdt = -muOverRadiusCubed*x;
    dvydt = -muOverRadiusCubed*y;
    dvzdt = -muOverRadiusCubed*z;
}

void EquationsOfMotion::evaluate_cowells_method() {

    // Calculate required values for force model
    radius[0] = x;
    radius[1] = y;
    radius[2] = z;
    R = sqrt(x*x + y*y + z*z); // radius magnitude

    // mu/R^3
    muOverRadiusCubed = mu/(R*R*R);

    // Create force models in cartesian bci
    find_perts();

    // Derivative
    dxdt = vx;
    dydt = vy;
    dzdt = vz;
    dvxdt = -muOverRadiusCubed*x + accelPerts[0];
    dvydt = -muOverRadiusCubed*y + accelPerts[1];
    dvzdt = -muOverRadiusCubed*z + accelPerts[2];
}

void EquationsOfMotion::evaluate_coes_vop() {

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    if (ecc < 1.0e-5) {
        ecc = 1.0e-5;
        checkflag = true;
    }
    if (inc < 1.0e-5) {
        inc = 1.0e-5;
        checkflag = true;
    }

    // conversions COEs to r and v
    conversions::coes_to_bci(h,ecc,inc,w,raan,theta,mu,radius,velocity);

    x = radius[0]; 
    y = radius[1]; 
    z = radius[2];
    R = sqrt(x*x + y*y + z*z);

    vx = velocity[0]; 
    vy = velocity[1]; 
    vz = velocity[2];

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    Rhat[0] = x/R;
    Rhat[1] = y/R;
    Rhat[2] = z/R;

    Nhat[0] = (y*vz - z*vy)/h;
    Nhat[1] = (z*vx - x*vz)/h;
    Nhat[2] = (x*vy - y*vx)/h;

    Tv[0] = Nhat[1]*Rhat[2] - Nhat[2]*Rhat[1]; 
    Tv[1] = Nhat[2]*Rhat[0] - Nhat[0]*Rhat[2]; 
    Tv[2] = Nhat[0]*Rhat[1] - Nhat[1]*Rhat[0];

    normTv = sqrt(Tv[0]*Tv[0] + Tv[1]*Tv[1] + Tv[2]*Tv[2]);
    That[0] = Tv[0]/normTv;
    That[1] = Tv[1]/normTv;
    That[2] = Tv[2]/normTv;

    // Function for finding accel caused by perturbations
    find_perts();

    // Calculate R, N, and T
    radialPert     = accelPerts[0]*Rhat[0] + accelPerts[1]*Rhat[1] + accelPerts[2]*Rhat[2];
    normalPert     = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];
    tangentialPert = accelPerts[0]*That[0] + accelPerts[1]*That[1] + accelPerts[2]*That[2];

    // Argument of latitude
    u = w + theta;

    // Precalculate
    cosTA = cos(theta); 
    sinTA = sin(theta);
    cosU = cos(u); 
    sinU = sin(u);
    h_2 = h*h;
    hOverR_2 = h/(R*R);

    // Calculate the derivatives of the COEs - from the notes
    dhdt     = R*tangentialPert;
    deccdt   = h/mu*sinTA*radialPert + 1/(mu*h)*((h_2 + mu*R)*cosTA + mu*ecc*R)*tangentialPert;
    dincdt   = R/h*cosU*normalPert;
    dthetadt = hOverR_2 + (1/(ecc*h))*((h_2/mu)*cosTA*radialPert - (h_2/mu + R)*sinTA*tangentialPert);
    draandt  = R*sinU/(h*sin(inc))*normalPert;
    dwdt     = -dthetadt + (hOverR_2 - draandt*cos(inc));

    // Check to prevent crashes due to circular and zero inclination orbits.
    // Will cause innaccuracies
    if (ecc == 1e-5 && deccdt <= -1e-5) {
        deccdt = 0.0;
        checkflag = true;
    }
    if (inc == 1e-5 && dincdt <= -1e-5) {
        dincdt = 0.0;
        checkflag = true;
    }
}

void EquationsOfMotion::evaluate_j2mean_coes_vop() {

    // Prevents singularities from occuring in the propagation. Will cause
    // inaccuracies.
    if (inc < 1.0e-5) {
        inc = 1.0e-5;
        checkflag = true;
    }

    // conversions COEs to r and v
    conversions::coes_to_bci(h, ecc, inc, w, raan, theta, mu, radius, velocity);

    x = radius[0]; 
    y = radius[1]; 
    z = radius[2];
    R = sqrt(x*x + y*y + z*z);

    // Define perturbation vectors relative to the satellites RNT body frame
    /*
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
    */
    Nhat[0] = (y*vz - z*vy)/h;
    Nhat[1] = (z*vx - x*vz)/h;
    Nhat[2] = (x*vy - y*vx)/h;

    // Function for finding accel caused by perturbations
    find_perts();

    // Calculate R, N, and T
    normalPert = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];

    // Calculate the derivatives of the COEs - only raan and w considered
    dhdt = 0.0;
    deccdt = 0.0;
    dincdt = R/h*cos(w + theta)*normalPert;
    dthetadt = h/(R*R);
    draandt = R*sin(w + theta)/(h*sin(inc))*normalPert;
    dwdt = -draandt*cos(inc);

    // Loop to prevent crashes due to circular and zero inclination orbits.
    // Will cause an error
    if (inc == 1e-5 && dincdt <= -1e-5) {
        dincdt = 0.0;
        checkflag = true;
    }
}

void EquationsOfMotion::evaluate_mees_vop() {

    // conversions Modified Equinoctial Elements to COEs
    conversions::mees_to_coes(p, f, g, h, k, L, coes);

    ecc = coes[1];
    inc = coes[2];
    w = coes[3];
    raan = coes[4];
    theta = coes[5];

    // conversions COEs to r and v
    conversions::coes_to_bci(sqrt(p*mu), ecc, inc, w, raan, theta, mu, radius, velocity);

    x = radius[0]; 
    y = radius[1]; 
    z = radius[2];
    R = sqrt(x*x + y*y + z*z);

    vx = velocity[0]; 
    vy = velocity[1]; 
    vz = velocity[2];

    // Define perturbation vectors relative to the satellites SNC body frame
    /*
       R -> perturbing accel along radius vector outward
       N -> perturbing accel normal to orbital plane in direction of angular momentum vector
       T -> perturbing accel perpendicular to radius in direction of motion
    */
    Rhat[0] = x/R;
    Rhat[1] = y/R;
    Rhat[2] = z/R;

    Nhat[0] = (y*vz - z*vy)/h;
    Nhat[1] = (z*vx - x*vz)/h;
    Nhat[2] = (x*vy - y*vx)/h;

    Tv[0] = Nhat[1]*Rhat[2] - Nhat[2]*Rhat[1];
    Tv[1] = Nhat[2]*Rhat[0] - Nhat[0]*Rhat[2];
    Tv[2] = Nhat[0]*Rhat[1] - Nhat[1]*Rhat[0];

    normTv = sqrt(Tv[0]*Tv[0] + Tv[1]*Tv[1] + Tv[2]*Tv[2]);
    That[0] = Tv[0]/normTv;
    That[1] = Tv[1]/normTv;
    That[2] = Tv[2]/normTv;

    // Function for finding accel caused by perturbations
    find_perts();

    // Calculate R, N, and T
    radialPert     = accelPerts[0]*Rhat[0] + accelPerts[1]*Rhat[1] + accelPerts[2]*Rhat[2];
    normalPert     = accelPerts[0]*Nhat[0] + accelPerts[1]*Nhat[1] + accelPerts[2]*Nhat[2];
    tangentialPert = accelPerts[0]*That[0] + accelPerts[1]*That[1] + accelPerts[2]*That[2];

    // Variables precalculated for speed
    cosL = cos(L);
    sinL = sin(L);

    tempA = sqrt(p/mu);
    tempB = 1.0 + f*cos(L) + g*sin(L);
    s_2 = 1.0 + h*h + k*k;

    tempC = (h*sinL - k*cosL)/tempB;
    tempD = tempA*s_2/(2*tempB);

    // Derivative functions
    dpdt = 2*p/tempB*tempA*tangentialPert;
    dfdt = tempA*( radialPert*sinL + ((tempB + 1)*cosL + f)/tempB*tangentialPert - g*tempC*normalPert);
    dgdt = tempA*(-radialPert*cosL + ((tempB + 1)*sinL + g)/tempB*tangentialPert + f*tempC*normalPert);
    dhdt = tempD*cosL*normalPert;
    dkdt = tempD*sinL*normalPert;
    dLdt = sqrt(mu*p)*tempB*tempB/(p*p) + tempA*tempC*normalPert;
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------------- Force Models -----------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void EquationsOfMotion::find_perts() {
    // Run find functions for force model
    if (oblateness) { find_accel_oblateness(); }
    if (drag)       { find_accel_drag(); }
    if (lift)       { find_accel_lift(); }
    if (srp)        { find_accel_srp(); }
    if (nbody)      { find_accel_n_body(); }

    accelPerts[0] = accelOblateness[0] + accelDrag[0] + accelLift[0] + accelSRP[0] + accelNBody[0];
    accelPerts[1] = accelOblateness[1] + accelDrag[1] + accelLift[1] + accelSRP[1] + accelNBody[1];
    accelPerts[2] = accelOblateness[2] + accelDrag[2] + accelLift[2] + accelSRP[2] + accelNBody[2];
}

void EquationsOfMotion::find_accel_oblateness() {
    /* 
        To clarify this logic: Use J2 if
            1) NxM Oblateness is not selected
            2) N = 2 and M = 0, which is J2
            3) The central body is not Venus, Earth, the Moon, or Mars
            4) If Mars is the planet id, the moon id must be 0 to ensure the central body is not phobos or deimos
    */
    if (!NxMOblateness || (N == 2 && M == 0) || (planetId != 2 && planetId != 3 && !(planetId == 4 && moonId == 0))) { // J2 oblateness only
        // Variables to reduce calculations
        tempA = -1.5*j2*mu*equitorialR*equitorialR/pow(R,5);
        tempB = z*z/(R*R);

        // accel due to oblateness
        accelOblateness[0] = tempA*(1.0 - 5.0*tempB)*x;
        accelOblateness[1] = tempA*(1.0 - 5.0*tempB)*y;
        accelOblateness[2] = tempA*(1.0 - 3.0*tempB)*z;
    }
    else { // Any NxM gravitational field
        // Find lat and long
        conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);

        xBCBF = rBCBF[0];
        yBCBF = rBCBF[1];

        longitude = atan2(yBCBF,xBCBF);
        latitude = asin(z/R);

        cosLat = cos(latitude);
        sinLat = sin(latitude);
        tanLat = sinLat/cosLat;

        // Populate Legendre polynomial array
        assign_legendre();

        // Calculate serivative of gravitational potential field with respect to
        dVdr = 0;       // radius
        dVdlat = 0;     // geocentric latitude
        dVdlong = 0;    // longitude
        for (int n = 2; n < N+1; ++n) {
            nn = (double)n;

            // Reset inner sums
            dVdrInnerSum = 0;
            dVdlatInnerSum = 0;
            dVdlongInnerSum = 0;

            for (int m = 0; m < std::min(n,M)+1; ++m) {
                mm = (double) m;

                // Precalculate common terms
                cosLongM = cos(mm*longitude);
                sinLongM = sin(mm*longitude);

                // dVdr
                dVdrInnerSum += (C[n][m]*cosLongM + S[n][m]*sinLongM)*P[n][m];

                //dVdlat
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
            rRatio = pow(equitorialR/R, nn);

            // dVdr
            dVdr += rRatio*(nn + 1.0)*dVdrInnerSum;

            // dVdlat
            dVdlat += rRatio*dVdlatInnerSum;

            // dVdlong
            dVdlong += rRatio*dVdlongInnerSum;
        }

        // Correct
        tempA = mu/R;
        dVdr *= tempA/R;
        dVdlat *= tempA;
        dVdlong *= tempA/R;

        // Calculate partials of radius, geocentric latitude, and longitude with respect to BCBF frame
        drdrBCBF[0] = xBCBF/R;
        drdrBCBF[1] = yBCBF/R;
        drdrBCBF[2] = z/R;

        tempA = 1/sqrt(xBCBF*xBCBF + yBCBF*yBCBF);
        tempB = z/(R*R);
        dlatdrBCBF[0] = -tempA*xBCBF*tempB;
        dlatdrBCBF[1] = -tempA*yBCBF*tempB;
        dlatdrBCBF[2] =  tempA*(1 - z*tempB);

        tempA *= tempA;
        dlongdrBCBF[0] = -tempA*yBCBF;
        dlongdrBCBF[1] =  tempA*xBCBF;
        // dlongdrBCBF[2] = 0;

        // Calculate accel in BCBF (not with respect to BCBF)
        accelOblatenessBCBF[0] = dVdr*drdrBCBF[0] + dVdlat*dlatdrBCBF[0] + dVdlong*dlongdrBCBF[0];
        accelOblatenessBCBF[1] = dVdr*drdrBCBF[1] + dVdlat*dlatdrBCBF[1] + dVdlong*dlongdrBCBF[1];
        accelOblatenessBCBF[2] = dVdr*drdrBCBF[2] + dVdlat*dlatdrBCBF[2];

        // Rotate back into inertial coordinates
        conversions::bcbf_to_bci(accelOblatenessBCBF, julianDate, bodyRotationRate, accelOblateness);
    }
}

void EquationsOfMotion::find_accel_drag() {
    // Find velocity relative to atmosphere
    relativeVelocity[0] = vx - y*bodyRotationRate*SEC_TO_DAY*DEG_TO_RAD;
    relativeVelocity[1] = vy + x*bodyRotationRate*SEC_TO_DAY*DEG_TO_RAD;
    relativeVelocity[2] = vz;

    // Exponential Drag Model
    find_atmospheric_density();

    // accel due to drag
    relativeVelocityMagnitude = math_c::normalize(relativeVelocity);

    double coefficientOfDrag = spacecraft->get_coefficient_of_drag();
    double *areaRam = spacecraft->get_ram_area();
    double mass = spacecraft->get_mass();
    dragMagnitude = -0.5*coefficientOfDrag*(areaRam[0] + areaRam[1] + areaRam[2])/mass*atmosphericDensity*relativeVelocityMagnitude;

    accelDrag[0] = dragMagnitude*relativeVelocity[0];
    accelDrag[1] = dragMagnitude*relativeVelocity[1];
    accelDrag[2] = dragMagnitude*relativeVelocity[2];
}

void EquationsOfMotion::find_accel_lift() {
    // Velocity in the radial direction
    radialVelcityMagnitude = (vx*x + vy*y + vz*z)/R;

    if (!drag) { // no need to evaluate twice
        find_atmospheric_density();
    }

    // accel due to lift
    double coefficientOfLift = spacecraft->get_coefficient_of_lift();
    double* areaLift = spacecraft->get_lift_area();
    double mass = spacecraft->get_mass();
    tempA = 0.5*coefficientOfLift*(areaLift[0] + areaLift[1] + areaLift[2])/mass*atmosphericDensity*radialVelcityMagnitude*radialVelcityMagnitude/R;
    accelLift[0] = tempA*x;
    accelLift[1] = tempA*y;
    accelLift[2] = tempA*z;
}

void EquationsOfMotion::find_accel_srp() {
    // Find day nearest to current time
    index = std::min((int)round(t*SEC_TO_DAY), sizeOfDateArray-1);

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

    if (planetId != 0) {
        /* 
            This part calculates the angle between the occulating body and the Sun, the body and the satellite, and the Sun and the
            satellite. It then compares them to decide if the s/c is lit, in umbra, or in penumbra. See Vallado for details. 
        */

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
    double coefficientOfReflectivity = spacecraft->get_coefficient_of_reflectivity();
    double *areaSun = spacecraft->get_sun_area();
    double mass = spacecraft->get_mass();
    tempA = -solarRadiationPressure*coefficientOfReflectivity*(areaSun[0] + areaSun[1] + areaSun[2])/mass/radialMagnitudeSpacecraftToSun*fractionOfRecievedSunlight;
    accelSRP[0] = tempA*radiusSpacecraftToSun[0];
    accelSRP[1] = tempA*radiusSpacecraftToSun[1];
    accelSRP[2] = tempA*radiusSpacecraftToSun[2];
}

void EquationsOfMotion::find_accel_n_body() {
    if (!srp) {
        // Find day nearest to current time
        index = std::min((int)round(t*SEC_TO_DAY), sizeOfDateArray-1);

        // Radius from central body to sun
        for (int jj = 0; jj < 3; ++jj) {
            radiusCentralBodyToSun[jj] = -radiusSunToCentralBody[index][jj]; // flip vector direction
        }
    }

    // Reset perturbation
    accelNBody[0] = 0.0;
    accelNBody[1] = 0.0;
    accelNBody[2] = 0.0;
    for (int ii = 0; ii < numberOfBodies; ++ii) {
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
        tempA = nBodyGravitationalParameter[ii]/(radiusSpacecraftToNbodyMagnitude*radiusSpacecraftToNbodyMagnitude*radiusSpacecraftToNbodyMagnitude);
        tempB = nBodyGravitationalParameter[ii]/(radiusCentralToNbodyMagnitude*radiusCentralToNbodyMagnitude*radiusCentralToNbodyMagnitude);

        accelNBody[0] += tempA*radiusSpacecraftToNbody[0] - tempB*radiusCentralBodyToNbody[0];
        accelNBody[1] += tempA*radiusSpacecraftToNbody[1] - tempB*radiusCentralBodyToNbody[1];
        accelNBody[2] += tempA*radiusSpacecraftToNbody[2] - tempB*radiusCentralBodyToNbody[2];
    }
}

//----------------------------------------------------------------------------------------------------------//
//--------------------------------------- Atmospheric Density Model ----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void EquationsOfMotion::find_atmospheric_density() {
    // Find altitude
    if (doEstimateAltitude) {
        altitude = std::max(R - equitorialR, 0.0);
    }
    else {
        conversions::bci_to_bcbf(radius, julianDate, bodyRotationRate, rBCBF);
        conversions::bcbf_to_lla(rBCBF, equitorialR, polarR, lla);
        altitude = lla[2];
    }

    // Assume that bodies not listed have no significant atmosphere.Assume that
    // the atmosphere of the gas giants is defined by their radii, e.g.
    // outside of their equitorial radius, they have no noticible atmosphere
    // and inside that radius, the object will crash.
    atmosphericDensity = 0.0;
    switch (planetId) {
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
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------- Getters ------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

double* EquationsOfMotion::get_accel_gravity() {
    // Inertial evaluation of accel
    evaluate_two_body_dynamics();

    // Collect
    netAccel[0] = dvxdt;
    netAccel[1] = dvydt;
    netAccel[2] = dvzdt;

    // Output
    return netAccel;
}

double* EquationsOfMotion::get_accel_oblateness() {
    // Inertial evaluation of accel
    find_accel_oblateness();

    // Output
    return accelOblateness;
}

double* EquationsOfMotion::get_accel_drag() {
    // Inertial evaluation of accel
    find_accel_drag();

    // Output
    return accelDrag;
}

double* EquationsOfMotion::get_accel_lift() {
    // Inertial evaluation of accel
    find_accel_lift();

    // Output
    return accelLift;

}

double EquationsOfMotion::get_atmospheric_density(double time, double* state) {
    // Assign common variables
    t = time;

    x = state[0];
    y = state[1];
    z = state[2];
    vx = state[3];
    vy = state[4];
    vz = state[5];

    // Calculate required values for force model
    radius[0] = x;
    radius[1] = y;
    radius[2] = z;
    R = sqrt(x*x + y*y + z*z);

    find_atmospheric_density();

    return atmosphericDensity;
}

double* EquationsOfMotion::get_accel_srp() {
    // Inertial evaluation of accel
    find_accel_srp();

    // Output
    return accelSRP;

}

double* EquationsOfMotion::get_accel_nBody() {
    // Inertial evaluation of accel
    find_accel_n_body();

    // Output
    return accelNBody;
}

double* EquationsOfMotion::get_net_accel() {
    // Inertial evaluation of accel
    evaluate_cowells_method();

    // Collect
    netAccel[0] = dvxdt;
    netAccel[1] = dvydt;
    netAccel[2] = dvzdt;

    // Output
    return netAccel;
}

double* EquationsOfMotion::get_coes_rates() {
    // Inertial evaluation of dcoes
    evaluate_coes_vop();

    // Collect
    dcoesdt[0] = dhdt;
    dcoesdt[1] = deccdt;
    dcoesdt[2] = dincdt;
    dcoesdt[3] = dthetadt;
    dcoesdt[4] = draandt;
    dcoesdt[5] = dwdt;

    // Output
    return dcoesdt;
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------ Supporting Functions ------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void EquationsOfMotion::get_oblateness_coefficients(int N, int M) {
    // Open coefficients file
    char filename[200];
    char path[100];
    sprintf(path, "./data/gravity_models/");

    if (planetId == 2) { // Venus
        sprintf(filename, "%sshgj120p.txt", path); // Normalized?
    }
    else if (planetId == 3 && moonId == 0) { // Earth
        sprintf(filename, "%sEGM2008_to2190_ZeroTide_mod.txt", path); // Normalized
    }
    else if (planetId == 3 && moonId == 1) { // Moon
        sprintf(filename, "%sjgl165p1.txt", path); // Normalized?
    }
    else if (planetId == 3) { // Mars
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
        std::stringstream  lineStream(line);
        std::vector<double>   lineData;
        while (std::getline(lineStream, cell, ',')) {
            lineData.push_back(std::atof(cell.c_str()));
        }

        n = (int)lineData[0];
        m = (int)lineData[1];

        C[n][m] = lineData[2];
        S[n][m] = lineData[3];

        // Normalize coefficients if needed
        if (planetId == 4) {
            for (int m = 0; m < N+1; ++m) {
                nPlusMFactorial = 1;
                nMinusMFactorial = 1;
                for (int ii = n + m; ii > 0; --ii) {
                    nPlusMFactorial *= ii;
                    if (ii <= n-m) {
                        nMinusMFactorial *= ii;
                    }
                }
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

void EquationsOfMotion::assign_legendre() {
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
    for (int n = 0; n < N+1; ++n) {
        nn = (double)n;

        for (int m = 0; m < M+1; ++m) {
            mm = (double)m;

            if (n == m) {
                if (n == 0) {
                    P[n][m] = 1;
                }
                else {
                    tau = 1.0;
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
                alpha = sqrt((2.0*nn + 1.0)*(2.0*nn - 1.0)/((nn - mm)*(nn + mm)));
                beta = sqrt((2.0*nn + 1.0)*(nn + mm - 1.0)*(nn - mm - 1.0)/((2.0*nn - 3.0)*(nn - mm)*(nn + mm)));

                P[n][m] = alpha*sinLat*P[n-1][m] + beta*P[n-2][m];
            }
            else {
                P[n][m] = 0.0;
            }
        }
    }
}

bool EquationsOfMotion::check_crash(double* state) {

    R = math_c::normalize(state, 0, 2);
    V = math_c::normalize(state, 3, 5);

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
double EquationsOfMotion::get_mu() { return mu; }

// Perturbation toggles
void EquationsOfMotion::switch_oblateness(bool onOff) {
    oblateness = onOff;
}
void EquationsOfMotion::switch_oblateness(int N, int M) {
    // Switch perturbation toggle to true
    oblateness = true;
    NxMOblateness = true;

    // Set N and M
    N = N;
    M = M;

    // Get Cnm and Snm
    get_oblateness_coefficients(N, M);
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


// Set equations of motion
void EquationsOfMotion::switch_dynamics(std::string dynamics) {
    // Turn all off
    twoBody = false;
    cowellsMethod = false;
    coesVoP = false;
    j2MeanVoP = false;
    meesVoP = false;

    // Turn selected on
    if (dynamics == "Two Body" || dynamics == "two body"){
        twoBody = true;
    }
    else if (dynamics == "Cowells Method" || dynamics == "cowells method") {
        cowellsMethod = true;
    }
    else if (dynamics == "COEs VoP" || dynamics == "coes vop") {
        coesVoP = true;
    }
    else if (dynamics == "J2 Mean VoP" || dynamics == "j2 mean vop") {
        j2MeanVoP = true;
    }
    else if (dynamics == "MEEs VoP" || dynamics == "mees vop") {
        meesVoP = true;
    }
    else {
        std::cout << "Error: Selected dynamics set not recognized. \n\n";
    }
}