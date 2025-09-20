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

class Titan : public CelestialBody {

  public:
    constexpr Titan() :
        CelestialBody(
            "Titan",                     //!< Name
            PlanetaryBody::SATURN,       //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(8978.1 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.13455 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(2575.0 * mp_units::si::unit_symbols::km),                              //!< Equatorial radius
            Distance(2575.0 * mp_units::si::unit_symbols::km),                              //!< Polar radius
            Distance(2575.0 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(0.004333361603448 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(27.359 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(22.577014429408919 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(15.94542 * mp_units::non_si::day),                             //!< Orbital period
            Distance(1221.83e3 * mp_units::si::unit_symbols::km),               //!< Semi-major axis of the orbit
            Unitless(0.0292 * mp_units::one),                                   //!< Eccentricity of the orbit
            Angle(0.33 * mp_units::angular::unit_symbols::deg),                 //!< Inclination of the orbit
            Angle(28.060 * mp_units::angular::unit_symbols::deg),               //!< Longitude of the ascending node
            Angle(208.592 * mp_units::angular::unit_symbols::deg),              //!< Argument of perigee
            Angle(371.902 * mp_units::angular::unit_symbols::deg),              //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(183934.15 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(551990.5 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(2969198512.13 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Titan() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::TITAN; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea