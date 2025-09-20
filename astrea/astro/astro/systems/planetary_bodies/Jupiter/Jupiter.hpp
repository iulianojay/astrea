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

class Jupiter : public CelestialBody {

  public:
    constexpr Jupiter() :
        CelestialBody(
            "Jupiter",                   //!< Name
            PlanetaryBody::SUN,          //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(126686535.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(1898.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(3396.2 * mp_units::si::unit_symbols::km),                             //!< Equatorial radius
            Distance(66854.0 * mp_units::si::unit_symbols::km),                            //!< Polar radius
            Distance(71492.0 * mp_units::si::unit_symbols::km),                            //!< Crash radius
            Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),                 //!< Crash radius
            Unitless(14736e-6 * mp_units::one),                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                      //!< J3 gravitational coefficient
            Angle(3.13 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(4332.589 * mp_units::non_si::day),                                          //!< Sidereal period
            Distance(0.778412028336152e9 * mp_units::si::unit_symbols::km),                  //!< Semimajor axis
            Unitless(0.04839266 * mp_units::one),                                            //!< Eccentricity
            Angle(1.30530 * mp_units::angular::unit_symbols::deg),                           //!< Inclination
            Angle(100.55615 * mp_units::angular::unit_symbols::deg),                         //!< Right ascension
            Angle(14.75385 * mp_units::angular::unit_symbols::deg),                          //!< Argument of perigee
            Angle(34.40438 * mp_units::angular::unit_symbols::deg),                          //!< True latitude
            BodyVelocity(90861.2589092700 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(-0.00012880 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.001152777777777778 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(1217.17 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(839.93 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(68905103.78 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Jupiter() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::JUPITER; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea