#include <astro/utilities/conversions.hpp>

// mp-units
#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <astro/constants/astronomical_constants.h>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <math/utils.hpp>


using namespace mp_units;
using angular::unit_symbols::deg;
using non_si::unit_symbols::day;

namespace astro {

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------- Frame Conversions --------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

void conversions::bci_to_bcbf(const RadiusVector& rBCI, JulianDate julianDate, AngularRate rotRate, RadiusVector& rBCBF)
{

    const Distance& x = rBCI[0];
    const Distance& y = rBCI[1];
    const Distance& z = rBCI[2];

    // Calculate Greenwich Sidereal Time
    const Angle greenwichSiderealTime = julian_date_to_siderial_time(julianDate, rotRate);

    // Calculate ECI-to-ECEF transformation matrix
    /* C_bci2bcbf = [c_gst s_gst 0;
                    -s_gst c_gst 0;
                        0      0  1]; */

    // Calculate ECEF radius vector
    const Unitless cosGST = cos(greenwichSiderealTime);
    const Unitless sinGST = sin(greenwichSiderealTime);

    rBCBF[0] = cosGST * x + sinGST * y;
    rBCBF[1] = -sinGST * x + cosGST * y;
    rBCBF[2] = z;
}

void conversions::bcbf_to_bci(const RadiusVector& rBCBF, JulianDate julianDate, AngularRate rotRate, RadiusVector& rBCI)
{

    // Calculate Greenwich Sidereal Time
    const Angle greenwichSiderealTime = julian_date_to_siderial_time(julianDate, rotRate);

    // Calculate ECEC-to-ECI transformation matrix
    // C_ecef2eci = [cos(-gst) sin(-gst) 0;
    //               -sin(-gst) cos(-gst) 0;
    //                    0         0     1];

    // Calculate ECEF radius vector
    const quantity cosGST = cos(-greenwichSiderealTime);
    const quantity sinGST = sin(-greenwichSiderealTime);

    rBCI[0] = cosGST * rBCBF[0] + sinGST * rBCBF[1];
    rBCI[1] = -sinGST * rBCBF[0] + cosGST * rBCBF[1];
    rBCI[2] = rBCBF[2];
}

void conversions::bcbf_to_lla(const RadiusVector& rBCBF, const Distance& equitorialRadius, const Distance& polarRadius, Angle& lat, Angle& lon, Distance& alt)
{
    static const unsigned maxIter    = 1e3;
    static const Distance errorBound = 1.0e-9 * km;

    const Distance& xBCBF = rBCBF[0];
    const Distance& yBCBF = rBCBF[1];
    const Distance& zBCBF = rBCBF[2];

    const Unitless f   = (equitorialRadius - polarRadius) / equitorialRadius;
    const Unitless e_2 = (2.0 - f) * f;

    quantity dz  = e_2 * zBCBF;
    Distance err = 1 * km;
    unsigned ii  = 0;
    while (err > errorBound && ii < maxIter) {
        const Unitless s = (zBCBF + dz) / sqrt(xBCBF * xBCBF + yBCBF * yBCBF + (zBCBF + dz) * (zBCBF + dz));
        const Distance N = equitorialRadius / sqrt(1 - e_2 * s * s);
        err              = abs(dz - N * e_2 * s);
        dz               = N * e_2 * s;
        ++ii;
    }

    if (ii >= maxIter - 1) { throw std::runtime_error("Error: Conversion from bcbf to lla failed to converge."); }

    // Lat, long, alt (respectively)
    lat = atan2(yBCBF, xBCBF);
    lon = atan2(yBCBF + dz, sqrt(xBCBF * xBCBF + yBCBF * yBCBF)); // geodetic
    // alt = asin(zbcbf/sqrt(xBCBF*xBCBF + yBCBF*yBCBF + zBCBF*zBCBF))*rad2deg; // geocentric
    alt = max(sqrt(xBCBF * xBCBF + yBCBF * yBCBF + (zBCBF + dz) * (zBCBF + dz)) - N, 0.0 * km);
}

void conversions::lla_to_bcbf(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& equitorialRadius, const Distance& polarRadius, RadiusVector& rBCBF)
{

    const quantity sinLat = sin(latitude);
    const quantity cosLat = cos(latitude);

    const quantity f = (equitorialRadius - polarRadius) / equitorialRadius;
    const quantity N = equitorialRadius / sqrt(1 - f * (2 - f) * sinLat * sinLat);

    // BCBF coordinates
    rBCBF[0] = (N + lla[2]) * cosLat * cos(longitude);
    rBCBF[1] = (N + lla[2]) * cosLat * sin(longitude);
    rBCBF[2] = ((1 - f) * (1 - f) * N + lla[2]) * sinLat;
}

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

Angle conversions::julian_date_to_siderial_time(JulianDate julianDate, AngularRate rotRate)
{
    double julianDay = julianDate.count<days>();

    // Get hour, min, sec
    double hour   = (julianDay - (floor(julianDay + 0.5) - 0.5)) * 24; // accounts for JD-UTC 1/2 day offset
    double minute = (hour - floor(hour)) * 60;
    double second = (minute - floor(minute)) * 60;

    hour   = floor(hour);
    minute = floor(minute);

    double universalTime = (hour + minute / 60.0 + second / 3600.0) / (rotRate / 3.609851887442813e+02 * 24) * day;

    // Greenwich Universal Time
    double julianDay                   = julianDay - universalTime; // julian day number on this julian date
    double T0                          = (julianDay - 2451545) / 36525;
    const Angle greenwichUniversalTime = (100.4606184 + 36000.77004 * T0 + 0.000387933 * T0 * T0 - 2.583e-8 * T0 * T0 * T0) *
                                         deg; // This expansion only works for Earth :(

    // GST
    const Angle greenwichSiderealTime = (greenwichUniversalTime + rotRate * universalTime);

    return greenwichSiderealTime;
}

} // namespace astro