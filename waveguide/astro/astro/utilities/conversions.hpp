/**
 * @file conversions.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file contains functions for converting between different coordinate systems and formats in astrodynamics.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cmath>
#include <functional>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si/math.h>

#include <math/utils.hpp>

#include <units/CartesianVector.hpp>
#include <units/typedefs.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Convert a vector from ECI (Earth-Centered Inertial) to ECEF (Earth-Centered Earth-Fixed) coordinates.
 * * @note: This templating is to allow conversions for radius, velocity, and acceleration vectors.
 *
 * @tparam Vec_T The type of the vector to be converted, which should be a 3-element vector.
 * @param vecEci The vector in ECI coordinates.
 * @param date The date for which the conversion is performed, used to calculate the Greenwich Sidereal Time.
 * @return The vector in ECEF coordinates.
 */
// TODO: This is wrong for non-radial vectors (defined w.r.t the frame) and needs to be resolved.
template <typename T>
CartesianVector<T> eci_to_ecef(const CartesianVector<T>& vecEci, const Date& date)
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

    return CartesianVector(cosGST * x + sinGST * y, -sinGST * x + cosGST * y, z);
}


/**
 * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to ECI (Earth-Centered Inertial) coordinates.
 * * @note: This templating is to allow conversions for radius, velocity, and acceleration vectors.
 *
 * @tparam Vec_T The type of the vector to be converted, which should be a 3-element vector.
 * @param vecEcef The vector in ECEF coordinates.
 * @param date The date for which the conversion is performed, used to calculate the Greenwich Sidereal Time.
 * @return The vector in ECI coordinates.
 */
template <typename T>
CartesianVector<T> ecef_to_eci(const CartesianVector<T>& vecEcef, const Date& date)
{
    using namespace mp_units;
    using namespace mp_units::angular;

    const auto& x = vecEcef[0];
    const auto& y = vecEcef[1];
    const auto& z = vecEcef[2];

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

    return CartesianVector<T>(cosGST * x + sinGST * y, -sinGST * x + cosGST * y, z);
}

/**
 * @brief Convert a vector from ECEF (Earth-Centered Earth-Fixed) to LLA (Latitude, Longitude, Altitude) coordinates.
 *
 * @param rEcef The radius vector in ECEF coordinates.
 * @param rEquitorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @param lat The latitude in radians (output).
 * @param lon The longitude in radians (output).
 * @param alt The altitude in meters (output).
 */
void ecef_to_lla(const RadiusVector& rEcef, const Distance& rEquitorial, const Distance& rPolar, Angle& lat, Angle& lon, Distance& alt);

/**
 * @brief Convert a vector from LLA (Latitude, Longitude, Altitude) to ECEF (Earth-Centered Earth-Fixed) coordinates.
 *
 * @param lat The latitude in radians.
 * @param lon The longitude in radians.
 * @param alt The altitude in meters.
 * @param rEquitorial The equatorial radius of the Earth.
 * @param rPolar The polar radius of the Earth.
 * @return The radius vector in ECEF coordinates.
 */
RadiusVector lla_to_ecef(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar);

/**
 * @brief Sanitize an angle to ensure it is within the range [0, 2π).
 *
 * @param ang The angle to sanitize.
 * @return The sanitized angle.
 */
Angle sanitize_angle(const Angle& ang);

} // namespace astro
} // namespace waveguide
