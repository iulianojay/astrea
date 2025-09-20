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

class Mars : public CelestialBody {

  public:
    constexpr Mars() :
        CelestialBody(
            "Mars",                      //!< Name
            PlanetaryBody::SUN,          //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(42828.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.642 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(3396.2 * mp_units::si::unit_symbols::km),                            //!< Equatorial radius
            Distance(3376.2 * mp_units::si::unit_symbols::km),                            //!< Polar radius
            Distance(3496.2 * mp_units::si::unit_symbols::km),                            //!< Crash radius
            Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),                //!< Crash radius
            Unitless(1960.45e-6 * mp_units::one),                //!< J2 gravitational coefficient
            Unitless(0.000036 * mp_units::one),                  //!< J3 gravitational coefficient
            Angle(25.19 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(686.980 * mp_units::non_si::day),                                            //!< Sidereal period
            Distance(0.227936637698942e9 * mp_units::si::unit_symbols::km),                   //!< Semimajor axis
            Unitless(0.09341233 * mp_units::one),                                             //!< Eccentricity
            Angle(1.85061 * mp_units::angular::unit_symbols::deg),                            //!< Inclination
            Angle(49.57854 * mp_units::angular::unit_symbols::deg),                           //!< Right ascension
            Angle(336.04084 * mp_units::angular::unit_symbols::deg),                          //!< Argument of perigee
            Angle(355.45332 * mp_units::angular::unit_symbols::deg),                          //!< True latitude
            BodyVelocity(-10802.4622649100 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.00011902 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.007075 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-1020.19 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(1560.78 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(68905103.78 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Mars() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::MARS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea