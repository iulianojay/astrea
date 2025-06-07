
#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {
namespace conversions {


/*
NOTE: This templating is to allow conversions for radius, velocity, and acceleration vectors.
    This is wrong and needs to be resolved.
*/
template <typename Vec_T>
Vec_T eci_to_ecef(const Vec_T& vecEci, const Date& date)
{
    using namespace mp_units;
    using namespace mp_units::angular;

    const auto& x = vecEci[0];
    const auto& y = vecEci[1];
    const auto& z = vecEci[2];

    // Calculate Greenwich Sidereal Time
    const Angle greenwichSiderealTime = julian_date_to_siderial_time(date.jd());

    // Calculate Eci-to-Ecef transformation matrix
    /* NOTE: This transformation only accounts for Earth rotation, not nutation or procession, so it
            is wrong by the order of several km. TODO: Make this accurate.
            https://space.stackexchange.com/questions/38807/transform-eci-to-ecef

        C_eci2ecef = [c_gst s_gst 0;
                     -s_gst c_gst 0;
                        0      0  1];
    */

    // Calculate Ecef radius vector
    const Unitless cosGST = cos(greenwichSiderealTime);
    const Unitless sinGST = sin(greenwichSiderealTime);

    return { cosGST * x + sinGST * y, -sinGST * x + cosGST * y, z };
}

/*
NOTE: This templating is to allow conversions for radius, velocity, and acceleration vectors.
    This is wrong and needs to be resolved.
*/
template <typename Vec_T>
Vec_T ecef_to_eci(const Vec_T& vecEcef, const Date& date)
{
    using namespace mp_units;
    using namespace mp_units::angular;

    // Calculate Greenwich Sidereal Time
    const Angle greenwichSiderealTime = julian_date_to_siderial_time(date.jd());

    // Calculate ECEC-to-Eci transformation matrix
    /* NOTE: This transformation only accounts for Earth rotation, not nutation or procession, so it
            is wrong by the order of several km. TODO: Make this accurate.
            https://space.stackexchange.com/questions/38807/transform-eci-to-ecef
        C_ecef2eci = [cos(-gst) sin(-gst) 0;
                      -sin(-gst) cos(-gst) 0;
                           0         0     1];
    */

    // Calculate Ecef radius vector
    const quantity cosGST = cos(-greenwichSiderealTime);
    const quantity sinGST = sin(-greenwichSiderealTime);

    Vec_T vecEci{ cosGST * vecEcef[0] + sinGST * vecEcef[1], -sinGST * vecEcef[0] + cosGST * vecEcef[1], vecEcef[2] };

    return vecEci;
}

void ecef_to_lla(const RadiusVector& rEcef, const Distance& equitorialRadius, const Distance& polarRadius, Angle& lat, Angle& lon, Distance& alt);
void lla_to_ecef(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& equitorialRadius, const Distance& polarRadius, RadiusVector& rEcef);

Angle sanitize_angle(const Angle& ang);

} // namespace conversions
} // namespace astro
