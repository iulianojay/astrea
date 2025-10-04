/**
 * @file Io.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Io class.
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
 * @class Io
 * @brief Represents the Io celestial body.
 *
 * This class provides properties and methods specific to Io, including its physical and orbital parameters.
 */
class Io : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Io class.
     *
     * Initializes the Io object with predefined physical and orbital parameters.
     */
    constexpr Io() :
        CelestialBody(
            "Io",                        //!< Name
            CelestialBodyId::JUPITER,    //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1997-01-16 00:00:00"), //!< Reference date for the celestial body data
            GravParam(5959.9 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.08932 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(1821.5 * mp_units::si::unit_symbols::km),                              //!< Equatorial radius
            Distance(1821.5 * mp_units::si::unit_symbols::km),                              //!< Polar radius
            Distance(1841.5 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(7.83731997166e-04 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(3.13 * mp_units::angular::unit_symbols::deg),            //!< Axial tilt
            AngularRate(203.4889307674133 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(1.769138 * mp_units::non_si::day),                //!< Orbital period
            Distance(421.8e3 * mp_units::si::unit_symbols::km),    //!< Semi-major axis of the orbit
            Unitless(0.004 * mp_units::one),                       //!< Eccentricity of the orbit
            Angle(0.04 * mp_units::angular::unit_symbols::deg),    //!< Inclination of the orbit
            Angle(43.977 * mp_units::angular::unit_symbols::deg),  //!< Longitude of the ascending node
            Angle(128.106 * mp_units::angular::unit_symbols::deg), //!< Longitude of perigee
            Angle(470.127 * mp_units::angular::unit_symbols::deg), //!< Mean anomaly or true latitude
            InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(17466307.28 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(97220153.4 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(26853983280.3 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }

    /**
     * @brief Default destructor for the Io class.
     */
    ~Io() = default;

    /**
     * @brief Get the unique identifier for the Io celestial body.
     *
     * @return CelestialBodyId The unique identifier for Io.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::IO; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea