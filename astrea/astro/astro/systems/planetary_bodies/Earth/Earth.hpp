/**
 * @file Earth.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Earth class.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
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

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

/**
 * @class Earth
 * @brief Represents the Earth celestial body.
 *
 * This class provides properties and methods specific to Earth, including its physical and orbital parameters.
 */
class Earth : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Earth class.
     *
     * Initializes the Earth object with predefined physical and orbital parameters.
     */
    constexpr Earth() :
        CelestialBody(
            "Earth",                     //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            // GravParam(398600.44189 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu) - real published number
            GravParam(398600.436 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu) - number that matches the NASA checkcases
            Mass(5.97 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(6378.137 * mp_units::si::unit_symbols::km),                         //!< Equatorial radius
            // Distance(6356.752 * mp_units::si::unit_symbols::km),                         //!< Polar radius
            Distance(6356755.38082 * mp_units::si::unit_symbols::m),       //!< Polar radius
            Distance(6478.1 * mp_units::si::unit_symbols::km),             //!< Crash radius
            Distance(0.092449582665046 * mp_units::iau::unit_symbols::au), //!< Crash radius
            // Unitless(1082.63e-6 * mp_units::one),                    //!< J2 gravitational coefficient
            Unitless(0.00108262982 * mp_units::one),                 //!< J2 gravitational coefficient
            Unitless(-0.0000025323 * mp_units::one),                 //!< J3 gravitational coefficient
            Angle(23.439292 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            // AngularRate(360.9851887442813 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            AngularRate(7.29211514670638e-5 * mp_units::angular::unit_symbols::rad / mp_units::si::unit_symbols::s), //!< Rotation rate
            Time(365.256 * mp_units::non_si::day),                      //!< Sidereal period
            Distance(1.00000261 * mp_units::iau::unit_symbols::au),     //!< Semimajor axis
            Unitless(0.01671123 * mp_units::one),                       //!< Eccentricity
            Angle(-0.00001531 * mp_units::angular::unit_symbols::deg),  //!< Inclination
            Angle(0.0 * mp_units::angular::unit_symbols::deg),          //!< Longitude of ascending node
            Angle(102.93768193 * mp_units::angular::unit_symbols::deg), //!< Longitude of perihelion
            Angle(100.46457166 * mp_units::angular::unit_symbols::deg), //!< Mean longitude
            InterplanetaryVelocity(0.00000562 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(-0.00004392 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.01294668 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.32327364 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(35999.37244981 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }

    /**
     * @brief Default destructor for the Earth class.
     */
    ~Earth() = default;

    /**
     * @brief Find the atmospheric density at a given date and altitude using the US Standard Atmosphere 1976 model.
     *
     * @param date The date for which to find the atmospheric density.
     * @param altitude The altitude at which to find the atmospheric density.
     * @return Density The atmospheric density at the given date and altitude.
     * @note Numbers for this model are pulled from Vallado, 5th ed.
     */
    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    /**
     * @brief Get the unique identifier for the Earth celestial body.
     *
     * @return CelestialBodyId The unique identifier for Earth.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::EARTH; };

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

    /**
     * @brief Get the position of the Earth at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Earth.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Earth at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_EARTH_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea