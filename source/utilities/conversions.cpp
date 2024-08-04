
#include "conversions.hpp"

#include "math_constants.h"
#include "astronomical_constants.h"
#include "math_c.hpp"

#include "AstrodynamicsSystem.hpp"

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Frame Conversions --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void conversions::bci_to_bcbf(double* rBCI, double julianDate, double rotRate, double* rBCBF) {

    double x{}, y{}, z{}, cosGST{}, greenwichSiderealTime{}, sinGST{};

    x = rBCI[0];
    y = rBCI[1];
    z = rBCI[2];

    // Calculate Greenwich Sidereal Time
    greenwichSiderealTime = julian_date_to_sidereal_time(julianDate, rotRate);

    // Calculate ECI-to-ECEF transformation matrix
    /* C_bci2bcbf = [c_gst s_gst 0;
                    -s_gst c_gst 0;
                        0      0  1]; */

                        // Calculate ECEF radius vector
    cosGST = cos(greenwichSiderealTime);
    sinGST = sin(greenwichSiderealTime);

    rBCBF[0] = cosGST*x + sinGST*y;
    rBCBF[1] = -sinGST*x + cosGST*y;
    rBCBF[2] = z;
}

void conversions::bcbf_to_bci(double* rBCBF, double julianDate, double rotRate, double* rBCI) {

    double greenwichSiderealTime{}, cosGST{}, sinGST{};

    // Calculate Greenwich Sidereal Time
    greenwichSiderealTime = julian_date_to_sidereal_time(julianDate, rotRate);

    // Calculate ECEC-to-ECI transformation matrix
    // C_ecef2eci = [cos(-gst) sin(-gst) 0;
    //               -sin(-gst) cos(-gst) 0;
    //                    0         0     1];

    // Calculate ECEF radius vector
    cosGST = cos(-greenwichSiderealTime); sinGST = sin(-greenwichSiderealTime);

    rBCI[0] =  cosGST*rBCBF[0] + sinGST*rBCBF[1];
    rBCI[1] = -sinGST*rBCBF[0] + cosGST*rBCBF[1];
    rBCI[2] = rBCBF[2];
}

void conversions::bcbf_to_lla(double* rBCBF, double equitorialRadius, double polarRadius, double* lla) {

    double xBCBF{}, yBCBF{}, zBCBF{}, f{}, e_2{}, dz{}, err{}, s{}, N{};

    xBCBF = rBCBF[0];
    yBCBF = rBCBF[1];
    zBCBF = rBCBF[2];

    f = (equitorialRadius - polarRadius)/equitorialRadius;
    e_2 = (2.0 - f)*f;

    dz = e_2*zBCBF;
    err = 1;

    int ii = 0;
    while (err > 1.0e-9 && ii < 1000) {
        s = (zBCBF + dz)/sqrt(xBCBF*xBCBF + yBCBF*yBCBF + (zBCBF + dz)*(zBCBF + dz));
        N = equitorialRadius/sqrt(1 - e_2*s*s);
        err = abs(dz - N*e_2*s);
        dz = N*e_2*s;
        ++ii;
    }

    if (ii >= 999) {
        std::cout << "Error: Conversion from bcbf to lla failed to converge. \n\n";
    }

    // Lat, long, alt (respectively)
    lla[0] = atan2(yBCBF, xBCBF)*RAD_TO_DEG;
    lla[1] = atan2(yBCBF + dz, sqrt(xBCBF*xBCBF + yBCBF*yBCBF))*RAD_TO_DEG; // geodetic
    // lla[2] = asin(zbcbf/sqrt(xBCBF*xBCBF + yBCBF*yBCBF + zBCBF*zBCBF))*rad2deg; // geocentric
    lla[2] = std::max(sqrt(xBCBF*xBCBF + yBCBF*yBCBF + (zBCBF + dz)*(zBCBF + dz)) - N, 0.0);
}

void conversions::lla_to_bcbf(double* lla, double equitorialRadius, double polarRadius, double* rBCBF) {

    double latitude{}, longitude{}, f{}, N{}, sinLat{}, cosLat{}, sinLong{}, cosLong{};

    latitude = lla[0]*DEG_TO_RAD;
    longitude = lla[1]*DEG_TO_RAD;

    sinLat = sin(latitude);
    cosLat = cos(latitude);
    sinLong = sin(longitude);
    cosLong = cos(longitude);

    f = (equitorialRadius - polarRadius)/equitorialRadius;
    N = equitorialRadius/sqrt(1-f*(2-f)*sinLat*sinLat);

    // BCBF coordinates
    rBCBF[0] = (N + lla[2])*cosLat*cosLong;
    rBCBF[1] = (N + lla[2])*cosLat*sinLong;
    rBCBF[2] = ((1-f)*(1-f)*N + lla[2])*sinLat;
}

//----------------------------------------------------------------------------------------------------------//
//---------------------------------------- Element Set Conversions -----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

element_array conversions::convert(element_array elements, ElementSet fromSet, ElementSet toSet, AstrodynamicsSystem* system) {
    element_set_pair setPair = std::make_pair(fromSet, toSet);
    return conversions::elementSetConversions.at(setPair)(elements, system);
}

void conversions::coes_to_bci(double a, double ecc, double inc, double w, double raan, double theta, double mu, double* radius, double* velocity) {
    
    double ct{}, st{}, cw{}, sw{}, cr{}, sr{}, ci{}, si{}, A{}, B{}, x_peri{}, y_peri{}, vx_peri{}, vy_peri{};
    double DCM_peri2ECI_11{}, DCM_peri2ECI_12{}, DCM_peri2ECI_21{}, DCM_peri2ECI_22{}, DCM_peri2ECI_31{}, DCM_peri2ECI_32{};
    
    // Precalculate
    theta *= DEG_TO_RAD;
    w *= DEG_TO_RAD;
    raan *= DEG_TO_RAD;
    inc *= DEG_TO_RAD;

    ct = cos(theta); 
    st = sin(theta);
    cw = cos(w); 
    sw = sin(w);
    cr = cos(raan); 
    sr = sin(raan);
    ci = cos(inc); 
    si = sin(inc);

    double h = sqrt(mu*a*(1 - ecc));
    A = h*h/mu/(1 + ecc*ct);
    B = mu/h;

    // Perifocal Coordinates
    x_peri = A*ct;
    y_peri = A*st;
    // z_peri = 0;

    vx_peri = -B*st;
    vy_peri = B*(ecc + ct);
    // vz_peri = 0;

    // Preallocate DCM values for speed
    DCM_peri2ECI_11 = (cw*cr - sw*ci*sr);
    DCM_peri2ECI_12 = (-sw*cr - cw*ci*sr);

    DCM_peri2ECI_21 = (cw*sr + sw*ci*cr);
    DCM_peri2ECI_22 = (-sw*sr + cw*ci*cr);

    DCM_peri2ECI_31 = si*sw;
    DCM_peri2ECI_32 = si*cw;

    // Inertial position and velocity
    radius[0] = DCM_peri2ECI_11*x_peri + DCM_peri2ECI_12*y_peri;
    radius[1] = DCM_peri2ECI_21*x_peri + DCM_peri2ECI_22*y_peri;
    radius[2] = DCM_peri2ECI_31*x_peri + DCM_peri2ECI_32*y_peri;

    velocity[0] = DCM_peri2ECI_11*vx_peri + DCM_peri2ECI_12*vy_peri;
    velocity[1] = DCM_peri2ECI_21*vx_peri + DCM_peri2ECI_22*vy_peri;
    velocity[2] = DCM_peri2ECI_31*vx_peri + DCM_peri2ECI_32*vy_peri;
}

void conversions::bci_to_coes(double* radius, double* velocity, double mu, double* coes) {
    
    double hx{}, hy{}, hz{}, normH{}, Nx{}, Ny{}, normN{}, acos_Nx_Nnorm{};
    double R{}, V{}, dotRV{}, dot_ecc_r{}, dot_ecc_N{};
    double eccVec[3] = {};
    double a{}, ecc{}, inc{}, raan{}, w{}, theta{};
    
    // Specific Relative Angular Momentum
    hx = radius[1]*velocity[2] - radius[2]*velocity[1]; // h = cross(r, v)
    hy = radius[2]*velocity[0] - radius[0]*velocity[2];
    hz = radius[0]*velocity[1] - radius[1]*velocity[0];

    normH = sqrt(hx*hx + hy*hy + hz*hz);

    // Setup
    Nx = -hy;  // N = cross([0 0 1], h)
    Ny = hx;

    normN = sqrt(Nx*Nx + Ny*Ny);
        
    R = math_c::normalize(radius);
    V = math_c::normalize(velocity);

    // Semimajor Axis
    a = 1.0/(2.0/R - V*V/mu);

    // Eccentricity
    dotRV = radius[0]*velocity[0] + radius[1]*velocity[1] + radius[2]*velocity[2];

    eccVec[0] = (1.0/mu)*((V*V - mu/R)*radius[0] - dotRV*velocity[0]);
    eccVec[1] = (1.0/mu)*((V*V - mu/R)*radius[1] - dotRV*velocity[1]);
    eccVec[2] = (1.0/mu)*((V*V - mu/R)*radius[2] - dotRV*velocity[2]);

    ecc = math_c::normalize(eccVec,0,2);
    /*
        If the orbit has an eccentricity of exactly 0, w is ill-defined, the
        eccentricity vector is ill-defined, and true anomaly is ill defined.Force
        eccentricity to be slightly greater than 0.
    */
    if (abs(ecc) < 1.0e-10) {
        ecc = 1.0e-10;
    }

    // Inclination(rad)
    inc = acos(hz/normH);

    // Right Ascension of Ascending Node(rad)
    acos_Nx_Nnorm = acos(Nx/normN);

    if (Ny > 0.0) {
        raan = acos_Nx_Nnorm;
    }
    else {
        raan = 2.0*PI - acos_Nx_Nnorm;
    }

    // True Anomaly(rad)
    dot_ecc_r = eccVec[0]*radius[0] + eccVec[1]*radius[1] + eccVec[2]*radius[2];

    if (dot_ecc_r > 0.0) {
        theta = acos(dot_ecc_r/(ecc*R));
    }
    else {
        theta = 2.0*PI - acos(dot_ecc_r/(ecc*R));
    }

    // Argument of Parigee(degrees)
    dot_ecc_N = eccVec[0]*Nx + eccVec[1]*Ny;

    if (eccVec[2] > 0.0){
        w = 2.0*PI - acos(dot_ecc_N/(ecc*normN));
    }
    else {
        w = acos(dot_ecc_N/(ecc*normN));
    }

    // Period(s)
    // T = 2.0*PI*sqrt(a*a*a/mu);

    // Mean Motion(rad/s)
    //n = 2.0*PI/T;

    /*
        Force rounding errors to assume zero values for angles. Assume complex
        results are the result of rounding errors. Flip values near their antipode
        to zero for simplicity. If the orbit is in the equatorial plane,
        N = [0 0 0], right ascension and argument of perigee are ill-defined. Force
        to be zero. Assume NaN results are from singularities and force values to
        be 0.

        No idea how much of this is just wrong.
    */
    if (isnan(inc) || abs(inc - PI) < 1.0e-3){
        inc = 0.0;
    }

    if (normN == 0.0 || isnan(raan) || abs(raan - 2.0*PI) < 1.0e-3) {
        raan = 0.0;
    }

    if (normN == 0.0 || isnan(w) || abs(w - 2.0*PI) < 1.0e-3) {
        w = 0.0;
    }

    if (isnan(theta) || abs(theta - 2.0*PI) < 1.0e-3) {
        theta = 0.0;
    }

    // Assign to coes
    coes[0] = a;
    coes[1] = ecc;
    coes[2] = inc*RAD_TO_DEG;
    coes[3] = raan*RAD_TO_DEG;
    coes[4] = w*RAD_TO_DEG;
    coes[5] = theta*RAD_TO_DEG;
}

void conversions::mees_to_coes(double p, double f, double g, double h, double k, double L, double* coes) {
    
    double ecc{}, a{}, inc{}, raan{}, atopo{}, w{}, theta{};

    ecc = sqrt(f*f + g*g);
    a = p/(1 - ecc*ecc);            // km
    inc = 2*atan(sqrt(h*h + k*k));  // rad

    raan = math_c::atan3(k, h);     // rad
    atopo = math_c::atan3(g, f);

    w = std::fmod(atopo - raan, 2*PI);    // rad
    theta = std::fmod(L - atopo, 2*PI);   // rad

    coes[0] = a; 
    coes[1] = ecc;
    coes[2] = inc;
    coes[3] = w;
    coes[4] = raan;
    coes[5] = theta;
}


element_array conversions::coes_to_cartesian(element_array coes, AstrodynamicsSystem* system) {
    element_array cartesian;
    double radius[3];
    double velocity[3];
    coes_to_bci(coes[0], coes[1], coes[2], coes[3], coes[4], coes[5], system->get_center().mu(), radius, velocity);
    for (int ii = 0; ii < 3; ii++) {
        cartesian[ii] = radius[ii];
    }
    for (int ii = 0; ii < 3; ii++) {
        cartesian[ii+3] = velocity[ii];
    }
    return cartesian;
};

element_array conversions::cartesian_to_coes(element_array cartesian, AstrodynamicsSystem* system) {
    double coes[6];
    double radius[3];
    double velocity[3];
    for (int ii = 0; ii < 3; ii++) {
        radius[ii] = cartesian[ii];
    }
    for (int ii = 0; ii < 3; ii++) {
        velocity[ii] = cartesian[ii+3];
    }
    bci_to_coes(radius, velocity, system->get_center().mu(), coes);
    element_array coes_array;
    for (int ii = 0; ii < 6; ii++) {
        coes_array[ii] = coes[ii];
    }
    return coes_array;
};

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Time Conversions ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

double conversions::epoch_to_julian_date(std::string epochString) {

    std::string delimiter = "-";
    double year = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    double month = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    delimiter = " ";
    double day = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    delimiter = ":";
    double hour = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    double min = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    double sec = std::stod(epochString);

    return 367.0*year - floor((7.0*(year + floor((month + 9.0)/12.0)))/4.0) +
        floor((275.0*month)/9.0) + day + 1721013.5 + (hour + min/60.0 + sec/3600.0)/24.0;
}

double conversions::julian_date_to_sidereal_time(double julianDate, double rotRate) {

    double hour{}, minute{}, second{}, universalTime{}, T0{}, greenwichUniversalTime{}, greenwichSiderealTime{};

    // Get hour, min, sec
    hour = (julianDate - (floor(julianDate+0.5) - 0.5))*24; // accounts for JD-UTC 1/2 day offset
    minute = (hour - floor(hour))*60;
    second = (minute - floor(minute))*60;

    hour = floor(hour);
    minute = floor(minute);

    universalTime = (hour + minute/60 + second/3600)/(rotRate/3.609851887442813e+02*24); // in days

    // Greenwich Universal Time
    julianDate = julianDate - universalTime; // julian day number on this julian date
    T0 = (julianDate - 2451545)/36525;
    greenwichUniversalTime = 100.4606184 + 36000.77004*T0 + 0.000387933*T0*T0 - 2.583e-8*T0*T0*T0; // This expansion only works for Earth :(

    // GST
    greenwichSiderealTime = (greenwichUniversalTime + rotRate*universalTime)*DEG_TO_RAD;

    return greenwichSiderealTime;
}
