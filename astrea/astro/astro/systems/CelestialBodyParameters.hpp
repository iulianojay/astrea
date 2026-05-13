/**
 * @file CelestialBodyParameters.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the CelestialBodyParameters class, which represents planetary data in an astrodynamics system.
 * @date 2026-03-01
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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
    static constexpr CelestialBodyType type;                   //!< Type of the celestial body.
    static constexpr Date referenceDate;                       //!< Reference date for the celestial body data.
    static constexpr GravParam mu;                             //!< Gravitational parameter (mu) of the celestial body.
    static constexpr Mass mass;                                //!< Mass of the celestial body.
    static constexpr Distance equitorialRadius;                //!< Equatorial radius of the celestial body.
    static constexpr Distance polarRadius;                     //!< Polar radius of the celestial body.
    static constexpr Distance crashRadius;                     //!< Crash radius of the celestial body.
    static constexpr Distance sphereOfInfluence;               //!< Sphere of influence of the celestial body.
    static constexpr Unitless j2;                              //!< J2 gravitational coefficient of the celestial body.
    static constexpr Unitless j3;                              //!< J3 gravitational coefficient of the celestial body.
    static constexpr Angle axialTilt;                          //!< Axial tilt of the celestial body.
    static constexpr AngularVelocity rotationRate;             //!< Rotation rate of the celestial body.
    static constexpr Time siderealPeriod;                      //!< Sidereal period of the celestial body.
    static constexpr Distance semimajorAxis;                   //!< Semimajor axis.
    static constexpr Unitless eccentricity;                    //!< Eccentricity.
    static constexpr Angle inclination;                        //!< Inclination.
    static constexpr Angle rightAscension;                     //!< Right ascension.
    static constexpr Angle longitudeOfPerigee;                 //!< Longitude of perigee.
    static constexpr Angle meanLongitude;                      //!< Mean longitude.
    static constexpr InterplanetaryVelocity semimajorAxisRate; //!< Rate of change of the semimajor axis.
    static constexpr BodyUnitlessPerTime eccentricityRate;     //!< Rate of change of the eccentricity.
    static constexpr BodyAngularVelocity inclinationRate;      //!< Rate of change of the inclination.
    static constexpr BodyAngularVelocity rightAscensionRate;   //!< Rate of change of the right ascension.
    static constexpr BodyAngularVelocity longitudeOfPerigeeRate; //!< Rate of change of the longitude of perigee.
    static constexpr BodyAngularVelocity meanLongitudeRate;      //!< Rate of change of the mean longitude.
};

} // namespace astro
} // namespace astrea
