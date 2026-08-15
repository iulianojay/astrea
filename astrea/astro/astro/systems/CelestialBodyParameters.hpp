/**
 * @file CelestialBodyParameters.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the CelestialBodyParameters class, which represents planetary data in an astrodynamics system.
 * @date 2026-03-01
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

struct CelestialBodyParameters {
    CelestialBodyType type;                     //!< Type of the celestial body.
    Date referenceDate;                         //!< Reference date for the celestial body data.
    GravParam mu;                               //!< Gravitational parameter (mu) of the celestial body.
    Mass mass;                                  //!< Mass of the celestial body.
    Distance equitorialRadius;                  //!< Equatorial radius of the celestial body.
    Distance polarRadius;                       //!< Polar radius of the celestial body.
    Distance crashRadius;                       //!< Crash radius of the celestial body.
    Distance sphereOfInfluence;                 //!< Sphere of influence of the celestial body.
    Unitless j2;                                //!< J2 gravitational coefficient of the celestial body.
    Unitless j3;                                //!< J3 gravitational coefficient of the celestial body.
    Angle axialTilt;                            //!< Axial tilt of the celestial body.
    AngularVelocity rotationRate;               //!< Rotation rate of the celestial body.
    Time siderealPeriod;                        //!< Sidereal period of the celestial body.
    Distance semimajorAxis;                     //!< Semimajor axis.
    Unitless eccentricity;                      //!< Eccentricity.
    Angle inclination;                          //!< Inclination.
    Angle rightAscension;                       //!< Right ascension.
    Angle longitudeOfPerigee;                   //!< Longitude of perigee.
    Angle meanLongitude;                        //!< Mean longitude.
    InterplanetaryVelocity semimajorAxisRate;   //!< Rate of change of the semimajor axis.
    BodyUnitlessPerTime eccentricityRate;       //!< Rate of change of the eccentricity.
    BodyAngularVelocity inclinationRate;        //!< Rate of change of the inclination.
    BodyAngularVelocity rightAscensionRate;     //!< Rate of change of the right ascension.
    BodyAngularVelocity longitudeOfPerigeeRate; //!< Rate of change of the longitude of perigee.
    BodyAngularVelocity meanLongitudeRate;      //!< Rate of change of the mean longitude.
};

} // namespace astro
} // namespace astrea
