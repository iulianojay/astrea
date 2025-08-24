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

#include <units/typedefs.hpp>
#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/frames/types/RotatingFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

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
void ecef_to_lla(const RadiusVector<EarthCenteredEarthFixed>& rEcef, const Distance& rEquitorial, const Distance& rPolar, Angle& lat, Angle& lon, Distance& alt);

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
RadiusVector<EarthCenteredEarthFixed>
    lla_to_ecef(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& rEquitorial, const Distance& rPolar);

/**
 * @brief Sanitize an angle to ensure it is within the range [0, 2π).
 *
 * @param ang The angle to sanitize.
 * @return The sanitized angle.
 */
Angle sanitize_angle(const Angle& ang);

} // namespace astro
} // namespace astrea
