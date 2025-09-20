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

class Phobos : public CelestialBody {

  public:
    constexpr Phobos() :
        CelestialBody(
            "Phobos",                    //!< Name
            PlanetaryBody::MARS,         //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1950-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(9.85e-5 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(2.4e-9 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(6.2 * mp_units::si::unit_symbols::km),                                //!< Equatorial radius
            Distance(5.1 * mp_units::si::unit_symbols::km),                                //!< Polar radius
            Distance(6.25 * mp_units::si::unit_symbols::km),                               //!< Crash radius
            Distance(9.98573371442e-07 * mp_units::iau::unit_symbols::au),                 //!< Crash radius
            Unitless(0.0 * mp_units::one),                        //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                        //!< J3 gravitational coefficient
            Angle(25.079 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(6843.889610595355 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(1.26244 * mp_units::non_si::day),                              //!< Sidereal period
            Distance(23459.0 * mp_units::si::unit_symbols::km),                 //!< Semimajor axis
            Unitless(0.0005 * mp_units::one),                                   //!< Eccentricity
            Angle(1.79 * mp_units::angular::unit_symbols::deg),                 //!< Inclination
            Angle(24.525 * mp_units::angular::unit_symbols::deg),               //!< Right ascension
            Angle(285.254 * mp_units::angular::unit_symbols::deg),              //!< Argument of perigee
            Angle(610.583 * mp_units::angular::unit_symbols::deg),              //!< True latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(2376381 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(7111440.9 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(37503046910.7 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Phobos() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::PHOBOS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea