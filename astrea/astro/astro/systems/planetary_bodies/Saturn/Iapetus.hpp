/**
 * @file Iapetus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Iapetus class.
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
 * @class Iapetus
 * @brief Represents the Iapetus celestial body.
 *
 * This class provides properties and methods specific to Iapetus, including its physical and orbital parameters.
 */
class Iapetus : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Iapetus class.
     *
     * Initializes the Iapetus object with predefined physical and orbital parameters.
     */
    constexpr Iapetus() :
        CelestialBody(
            "Iapetus",                   //!< Name
            CelestialBodyId::SATURN,     //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(153.94 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.00231 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(765.0 * mp_units::si::unit_symbols::km),                               //!< Equatorial radius
            Distance(762.0 * mp_units::si::unit_symbols::km),                               //!< Polar radius
            Distance(765.0 * mp_units::si::unit_symbols::km),                               //!< Crash radius
            Distance(3.67746912467e-04 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(26.766 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(79.690094078583286 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(4.517500 * mp_units::non_si::day),                //!< Orbital period
            Distance(527.04e3 * mp_units::si::unit_symbols::km),   //!< Semi-major axis of the orbit
            Unitless(0.0010 * mp_units::one),                      //!< Eccentricity of the orbit
            Angle(0.35 * mp_units::angular::unit_symbols::deg),    //!< Inclination of the orbit
            Angle(351.042 * mp_units::angular::unit_symbols::deg), //!< Longitude of the ascending node
            Angle(232.661 * mp_units::angular::unit_symbols::deg), //!< Longitude of perigee
            Angle(412.44 * mp_units::angular::unit_symbols::deg),  //!< Mean anomaly or true latitude
            InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(3616878.77 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(10841361.7 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(10489285497.13 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }

    /**
     * @brief Default destructor for the Iapetus class.
     */
    ~Iapetus() = default;

    /**
     * @brief Get the unique identifier for the Iapetus celestial body.
     *
     * @return CelestialBodyId The unique identifier for Iapetus.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::IAPETUS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea