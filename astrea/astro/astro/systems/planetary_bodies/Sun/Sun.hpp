/**
 * @file Sun.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Sun class.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

/**
 * @class Sun
 * @brief Represents the Sun celestial body.
 *
 * This class provides properties and methods specific to the Sun, including its physical and orbital parameters.
 */
class Sun : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Sun class.
     *
     * Initializes the Sun object with predefined physical and orbital parameters.
     */
    constexpr Sun() :
        CelestialBody(
            "Sun",                       //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::STAR,     //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(1.32712e11 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(1988500.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(695700.0 * mp_units::si::unit_symbols::km),                              //!< Equatorial radius
            Distance(695700.0 * mp_units::si::unit_symbols::km),                              //!< Polar radius
            Distance(795700.0 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(1.0e18 * mp_units::si::unit_symbols::km),                                //!< Crash radius
            Unitless(0.2e-6 * mp_units::one),                  //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                     //!< J3 gravitational coefficient
            Angle(0.0 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(0.0 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(0.0 * mp_units::non_si::day),                                               //!< Sidereal period
            Distance(0.0 * mp_units::si::unit_symbols::km),                                  //!< Semimajor axis
            Unitless(0.0 * mp_units::one),                                                   //!< Eccentricity
            Angle(0.0 * mp_units::angular::unit_symbols::deg),                               //!< Inclination
            Angle(0.0 * mp_units::angular::unit_symbols::deg),                               //!< Right ascension
            Angle(0.0 * mp_units::angular::unit_symbols::deg),                               //!< Longitude of perigee
            Angle(0.0 * mp_units::angular::unit_symbols::deg),                               //!< Mean longitude
            InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }

    /**
     * @brief Default destructor for the Sun class.
     */
    ~Sun() = default;

    /**
     * @brief Get the unique identifier for the Sun celestial body.
     *
     * @return CelestialBodyId The unique identifier for the Sun.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::SUN; };

#ifdef ASTREA_BUILD_SUN_EPHEMERIS

    /**
     * @brief Get the position of the Sun at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Sun.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Sun at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_SUN_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea