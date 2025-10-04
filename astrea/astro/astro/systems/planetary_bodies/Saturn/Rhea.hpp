/**
 * @file Rhea.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Rhea class.
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
 * @class Rhea
 * @brief Represents the Rhea celestial body.
 *
 * This class provides properties and methods specific to Rhea, including its physical and orbital parameters.
 */
class Rhea : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Rhea class.
     *
     * Initializes the Rhea object with predefined physical and orbital parameters.
     */
    constexpr Rhea() :
        CelestialBody(
            "Rhea",                      //!< Name
            CelestialBodyId::SATURN,     //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(120.50 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.00181 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(746.0 * mp_units::si::unit_symbols::km),                               //!< Equatorial radius
            Distance(712.0 * mp_units::si::unit_symbols::km),                               //!< Polar radius
            Distance(761.0 * mp_units::si::unit_symbols::km),                               //!< Crash radius
            Distance(0.002253931200283 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(41.940 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(4.537995330226328 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(79.33018 * mp_units::non_si::day),                //!< Orbital period
            Distance(3561.3e3 * mp_units::si::unit_symbols::km),   //!< Semi-major axis of the orbit
            Unitless(0.0283 * mp_units::one),                      //!< Eccentricity of the orbit
            Angle(14.72 * mp_units::angular::unit_symbols::deg),   //!< Inclination of the orbit
            Angle(81.105 * mp_units::angular::unit_symbols::deg),  //!< Longitude of the ascending node
            Angle(352.711 * mp_units::angular::unit_symbols::deg), //!< Longitude of perigee
            Angle(554.5 * mp_units::angular::unit_symbols::deg),   //!< Mean anomaly or true latitude
            InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(37688.33 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(11498.3 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(59680892.45 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }

    /**
     * @brief Default destructor for the Rhea class.
     */
    ~Rhea() = default;

    /**
     * @brief Get the unique identifier for the Rhea celestial body.
     *
     * @return CelestialBodyId The unique identifier for Rhea.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::RHEA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea