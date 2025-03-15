
#include <astro/utilities/conversions.hpp>

#include <astro/constants/astronomical_constants.h>
#include <math/utils.hpp>

#include <astro/systems/AstrodynamicsSystem.hpp>

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Frame Conversions --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void conversions::bci_to_bcbf(const basis_array& rBCI, double julianDate, double rotRate, basis_array& rBCBF)
{

    double x{}, y{}, z{}, cosGST{}, greenwichSiderealTime{}, sinGST{};

    x = rBCI[0];
    y = rBCI[1];
    z = rBCI[2];

    // Calculate Greenwich Sidereal Time
    greenwichSiderealTime = julian_date_to_siderial_time(julianDate, rotRate);

    // Calculate ECI-to-ECEF transformation matrix
    /* C_bci2bcbf = [c_gst s_gst 0;
                    -s_gst c_gst 0;
                        0      0  1]; */

    // Calculate ECEF radius vector
    cosGST = math::cos(greenwichSiderealTime);
    sinGST = math::sin(greenwichSiderealTime);

    rBCBF[0] = cosGST * x + sinGST * y;
    rBCBF[1] = -sinGST * x + cosGST * y;
    rBCBF[2] = z;
}

void conversions::bcbf_to_bci(const basis_array& rBCBF, double julianDate, double rotRate, basis_array& rBCI)
{

    double greenwichSiderealTime{}, cosGST{}, sinGST{};

    // Calculate Greenwich Sidereal Time
    greenwichSiderealTime = julian_date_to_siderial_time(julianDate, rotRate);

    // Calculate ECEC-to-ECI transformation matrix
    // C_ecef2eci = [cos(-gst) sin(-gst) 0;
    //               -sin(-gst) cos(-gst) 0;
    //                    0         0     1];

    // Calculate ECEF radius vector
    cosGST = cos(-greenwichSiderealTime);
    sinGST = math::sin(-greenwichSiderealTime);

    rBCI[0] = cosGST * rBCBF[0] + sinGST * rBCBF[1];
    rBCI[1] = -sinGST * rBCBF[0] + cosGST * rBCBF[1];
    rBCI[2] = rBCBF[2];
}

void conversions::bcbf_to_lla(const basis_array& rBCBF, const double& equitorialRadius, const double& polarRadius, basis_array& lla)
{

    double xBCBF{}, yBCBF{}, zBCBF{}, f{}, e_2{}, dz{}, err{}, s{}, N{};

    xBCBF = rBCBF[0];
    yBCBF = rBCBF[1];
    zBCBF = rBCBF[2];

    f   = (equitorialRadius - polarRadius) / equitorialRadius;
    e_2 = (2.0 - f) * f;

    dz  = e_2 * zBCBF;
    err = 1;

    int ii = 0;
    while (err > 1.0e-9 && ii < 1000) {
        s   = (zBCBF + dz) / std::sqrt(xBCBF * xBCBF + yBCBF * yBCBF + (zBCBF + dz) * (zBCBF + dz));
        N   = equitorialRadius / std::sqrt(1 - e_2 * s * s);
        err = fabs(dz - N * e_2 * s);
        dz  = N * e_2 * s;
        ++ii;
    }

    if (ii >= 999) { std::cout << "Error: Conversion from bcbf to lla failed to converge. \n\n"; }

    // Lat, long, alt (respectively)
    lla[0] = atan2(yBCBF, xBCBF);
    lla[1] = atan2(yBCBF + dz, std::sqrt(xBCBF * xBCBF + yBCBF * yBCBF)); // geodetic
    // lla[2] = asin(zbcbf/std::sqrt(xBCBF*xBCBF + yBCBF*yBCBF + zBCBF*zBCBF))*rad2deg; // geocentric
    lla[2] = std::max(std::sqrt(xBCBF * xBCBF + yBCBF * yBCBF + (zBCBF + dz) * (zBCBF + dz)) - N, 0.0);
}

void conversions::lla_to_bcbf(const basis_array& lla, const double& equitorialRadius, const double& polarRadius, basis_array& rBCBF)
{

    const double latitude  = lla[0] * DEG_TO_RAD;
    const double longitude = lla[1] * DEG_TO_RAD;

    const double sinLat = math::sin(latitude);
    const double cosLat = math::cos(latitude);

    const double f = (equitorialRadius - polarRadius) / equitorialRadius;
    const double N = equitorialRadius / std::sqrt(1 - f * (2 - f) * sinLat * sinLat);

    // BCBF coordinates
    rBCBF[0] = (N + lla[2]) * cosLat * math::cos(longitude);
    rBCBF[1] = (N + lla[2]) * cosLat * math::sin(longitude);
    rBCBF[2] = ((1 - f) * (1 - f) * N + lla[2]) * sinLat;
}

//----------------------------------------------------------------------------------------------------------//
//---------------------------------------- Element Set Conversions -----------------------------------------//
//----------------------------------------------------------------------------------------------------------//

element_array conversions::convert(const element_array& elements, const ElementSet& fromSet, const ElementSet& toSet, const AstrodynamicsSystem& system)
{
    element_set_pair setPair = std::make_pair(fromSet, toSet);
    return conversions::elementSetConversions.at(setPair)(elements, system);
}

std::vector<double> conversions::keplerian_to_bci(double a, double ecc, double inc, double raan, double w, double theta, double mu)
{

    // Precalculate
    const double cos_theta = math::cos(theta);
    const double sin_theta = math::sin(theta);
    const double cos_w     = math::cos(w);
    const double sin_w     = math::sin(w);
    const double cos_raan  = math::cos(raan);
    const double sin_raan  = math::sin(raan);
    const double cos_inc   = math::cos(inc);
    const double sin_inc   = math::sin(inc);

    const double h = std::sqrt(mu * a * (1 - ecc * ecc));
    const double A = h * h / mu / (1 + ecc * cos_theta);
    const double B = mu / h;

    // Perifocal Coordinates
    const double x_peri = A * cos_theta;
    const double y_peri = A * sin_theta;
    // double z_peri = 0.0;

    const double vx_peri = -B * sin_theta;
    const double vy_peri = B * (ecc + cos_theta);
    // double vz_peri = 0.0;

    // Preallocate DCM values for speed
    const double DCM_peri2ECI_11 = (cos_w * cos_raan - sin_w * cos_inc * sin_raan);
    const double DCM_peri2ECI_12 = (-sin_w * cos_raan - cos_w * cos_inc * sin_raan);

    const double DCM_peri2ECI_21 = (cos_w * sin_raan + sin_w * cos_inc * cos_raan);
    const double DCM_peri2ECI_22 = (-sin_w * sin_raan + cos_w * cos_inc * cos_raan);

    const double DCM_peri2ECI_31 = sin_inc * sin_w;
    const double DCM_peri2ECI_32 = sin_inc * cos_w;

    // Inertial position and velocity
    const std::vector<double> cartesian = {
        DCM_peri2ECI_11 * x_peri + DCM_peri2ECI_12 * y_peri,   DCM_peri2ECI_21 * x_peri + DCM_peri2ECI_22 * y_peri,
        DCM_peri2ECI_31 * x_peri + DCM_peri2ECI_32 * y_peri,   DCM_peri2ECI_11 * vx_peri + DCM_peri2ECI_12 * vy_peri,
        DCM_peri2ECI_21 * vx_peri + DCM_peri2ECI_22 * vy_peri, DCM_peri2ECI_31 * vx_peri + DCM_peri2ECI_32 * vy_peri
    };
    return cartesian;
}

std::vector<double> conversions::bci_to_keplerian(const std::vector<double>& radius, const std::vector<double>& velocity, double mu)
{

    /*
        Force rounding errors to assume zero values for angles. Assume complex
        results are the result of rounding errors. Flip values near their antipode
        to zero for simplicity. Assume NaN results are from singularities and force
        values to be 0.

        No idea how much of this is just wrong.
    */
    double tol = 1e-10;

    // Specific Relative Angular Momentum
    double hx = radius[1] * velocity[2] - radius[2] * velocity[1]; // h = cross(r, v)
    double hy = radius[2] * velocity[0] - radius[0] * velocity[2];
    double hz = radius[0] * velocity[1] - radius[1] * velocity[0];

    double normH = std::sqrt(hx * hx + hy * hy + hz * hz);

    // Setup
    double Nx = -hy; // N = cross([0 0 1], h)
    double Ny = hx;

    double normN = std::sqrt(Nx * Nx + Ny * Ny);

    double R = math::normalize(radius);
    double V = math::normalize(velocity);

    // Semimajor Axis
    double a = 1.0 / (2.0 / R - V * V / mu);

    // Eccentricity
    double dotRV = radius[0] * velocity[0] + radius[1] * velocity[1] + radius[2] * velocity[2];

    const std::vector<double> eccVec = { (1.0 / mu) * ((V * V - mu / R) * radius[0] - dotRV * velocity[0]),
                                         (1.0 / mu) * ((V * V - mu / R) * radius[1] - dotRV * velocity[1]),
                                         (1.0 / mu) * ((V * V - mu / R) * radius[2] - dotRV * velocity[2]) };
    double ecc                       = math::normalize(eccVec);
    /*
        If the orbit has an inclination of exactly 0, w is ill-defined, the
        eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (fabs(ecc) < tol) { ecc = 0.0; }

    // Inclination (rad)
    double inc = acos(hz / normH);
    if (std::isnan(inc) || fabs(inc - M_PI) < tol) { inc = 0.0; }

    // Right Ascension of Ascending Node (rad)
    double raan{};
    double acos_Nx_Nnorm = acos(Nx / normN);
    if (Ny > 0.0) { raan = acos_Nx_Nnorm; }
    else {
        raan = 2.0 * M_PI - acos_Nx_Nnorm;
    }

    if (normN == 0.0 || std::isnan(raan) || fabs(raan - 2.0 * M_PI) < tol) { raan = 0.0; }

    // True Anomaly (rad)
    double theta{};
    if (ecc == 0.0) {     // No argument of perigee, use nodal line
        if (inc == 0.0) { // No nodal line, use true longitude
            if (velocity[0] <= 0.0) { theta = acos(radius[0] / R); }
            else {
                theta = 2 * M_PI - acos(radius[0] / R);
            }
        }
        else { // Use argument of latitude
            double dot_n_r = Nx * radius[0] + Ny * radius[1];
            if (radius[2] >= 0.0) { theta = acos(dot_n_r / (normN * R)); }
            else {
                theta = 2 * M_PI - acos(dot_n_r / (normN * R));
            }
        }
    }
    else {
        double dot_ecc_r = eccVec[0] * radius[0] + eccVec[1] * radius[1] + eccVec[2] * radius[2];
        if (dotRV >= 0.0) { theta = acos(dot_ecc_r / (ecc * R)); }
        else {
            theta = 2.0 * M_PI - acos(dot_ecc_r / (ecc * R));
        }
    }

    if (std::isnan(theta) || fabs(theta - 2.0 * M_PI) < tol) { theta = 0.0; }

    // Argument of Parigee (rad)
    double w{};
    if (ecc == 0.0) { // Ill-defined. Assume zero
        w = 0.0;
    }
    else if (inc == 0.0) { // No nodal line, use ecc vec
        if (hz > 0.0) { w = atan2(eccVec[1], eccVec[0]); }
        else {
            w = 2 * M_PI - atan2(eccVec[1], eccVec[0]);
        }
    }
    else {
        double dot_ecc_N = eccVec[0] * Nx + eccVec[1] * Ny;
        if (eccVec[2] < 0.0) { w = 2.0 * M_PI - acos(dot_ecc_N / (ecc * normN)); }
        else {
            w = acos(dot_ecc_N / (ecc * normN));
        }
    }

    if (normN == 0.0 || std::isnan(w) || fabs(w - 2.0 * M_PI) < tol) { w = 0.0; }

    // Period(s)
    // T = 2.0*M_PI*std::sqrt(a*a*a/mu);

    // Mean Motion(rad/s)
    // n = 2.0*M_PI/T;

    // Assign to coes
    const std::vector<double> coes = { a, ecc, inc, raan, w, theta };
    return coes;
}

void conversions::_equinoctial_to_keplerian(double p, double f, double g, double h, double k, double L, double* coes)
{

    double ecc{}, a{}, inc{}, raan{}, atopo{}, w{}, theta{};

    ecc = std::sqrt(f * f + g * g);
    a   = p / (1 - ecc * ecc);                // km
    inc = 2 * atan(std::sqrt(h * h + k * k)); // rad

    raan  = math::atan3(k, h); // rad
    atopo = math::atan3(g, f);

    w     = std::fmod(atopo - raan, 2 * M_PI); // rad
    theta = std::fmod(L - atopo, 2 * M_PI);    // rad

    coes[0] = a;
    coes[1] = ecc;
    coes[2] = inc;
    coes[3] = w;
    coes[4] = raan;
    coes[5] = theta;
}


element_array conversions::keplerian_to_cartesian(const element_array& coes, const AstrodynamicsSystem& system)
{
    element_array cartesian;
    const auto elements = keplerian_to_bci(coes[0], coes[1], coes[2], coes[3], coes[4], coes[5], system.get_center()->get_mu());
    for (int ii = 0; ii < 6; ii++) {
        cartesian[ii] = elements[ii];
    }
    return cartesian;
};

element_array conversions::cartesian_to_keplerian(const element_array& cartesian, const AstrodynamicsSystem& system)
{
    std::vector<double> radius     = { cartesian[0], cartesian[1], cartesian[2] };
    std::vector<double> velocity   = { cartesian[3], cartesian[4], cartesian[5] };
    const std::vector<double> coes = bci_to_keplerian(radius, velocity, system.get_center()->get_mu());

    element_array keplerian_array;
    for (int ii = 0; ii < 6; ii++) {
        keplerian_array[ii] = coes[ii];
    }

    return keplerian_array;
};


element_array conversions::keplerian_to_equinoctial(const element_array& coes, const AstrodynamicsSystem& system)
{
    element_array mees;
    throw std::logic_error("This function has not been implemented yet");
    return mees;
};

element_array conversions::equinoctial_to_keplerian(const element_array& mees, const AstrodynamicsSystem& system)
{

    double coes[6];
    _equinoctial_to_keplerian(mees[0], mees[1], mees[2], mees[3], mees[4], mees[5], coes);

    element_array keplerian_array;
    std::copy(coes, coes + 6, keplerian_array.begin());

    return keplerian_array;
};

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Time Conversions ---------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

double conversions::epoch_to_julian_date(std::string epochString)
{

    std::string delimiter = "-";
    double year           = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    double month = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    delimiter  = " ";
    double day = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    delimiter   = ":";
    double hour = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    double min = std::stod(epochString.substr(0, epochString.find(delimiter)));
    epochString.erase(0, epochString.find(delimiter) + delimiter.length());

    double sec = std::stod(epochString);

    return 367.0 * year - floor((7.0 * (year + floor((month + 9.0) / 12.0))) / 4.0) + floor((275.0 * month) / 9.0) +
           day + 1721013.5 + (hour + min / 60.0 + sec / 3600.0) / 24.0;
}

double conversions::julian_date_to_siderial_time(double julianDate, double rotRate)
{

    double hour{}, minute{}, second{}, universalTime{}, T0{}, greenwichUniversalTime{}, greenwichSiderealTime{};

    // Get hour, min, sec
    hour   = (julianDate - (floor(julianDate + 0.5) - 0.5)) * 24; // accounts for JD-UTC 1/2 day offset
    minute = (hour - floor(hour)) * 60;
    second = (minute - floor(minute)) * 60;

    hour   = floor(hour);
    minute = floor(minute);

    universalTime = (hour + minute / 60 + second / 3600) / (rotRate / 3.609851887442813e+02 * 24); // in days

    // Greenwich Universal Time
    julianDate             = julianDate - universalTime; // julian day number on this julian date
    T0                     = (julianDate - 2451545) / 36525;
    greenwichUniversalTime = 100.4606184 + 36000.77004 * T0 + 0.000387933 * T0 * T0 -
                             2.583e-8 * T0 * T0 * T0; // This expansion only works for Earth :(

    // GST
    greenwichSiderealTime = (greenwichUniversalTime + rotRate * universalTime) * DEG_TO_RAD;

    return greenwichSiderealTime;
}
