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

class Earth : public CelestialBody {

  public:
    constexpr Earth() :
        CelestialBody(
            "Earth",                     //!< Name
            PlanetaryBody::SUN,          //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(398600.44189 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(5.97 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(6378.1 * mp_units::si::unit_symbols::km),                           //!< Equatorial radius
            Distance(6356.752 * mp_units::si::unit_symbols::km),                         //!< Polar radius
            Distance(6478.1 * mp_units::si::unit_symbols::km),                           //!< Crash radius
            Distance(0.092449582665046 * mp_units::iau::unit_symbols::au),               //!< Crash radius
            Unitless(1082.63e-6 * mp_units::one),                    //!< J2 gravitational coefficient
            Unitless(-0.0000025323 * mp_units::one),                 //!< J3 gravitational coefficient
            Angle(23.439292 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(360.9851887442813 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(365.256 * mp_units::non_si::day),                                        //!< Sidereal period
            Distance(0.149597887455766e9 * mp_units::si::unit_symbols::km),               //!< Semimajor axis
            Unitless(0.01671022 * mp_units::one),                                         //!< Eccentricity
            Angle(0.00005 * mp_units::angular::unit_symbols::deg),                        //!< Inclination
            Angle(-11.26064 * mp_units::angular::unit_symbols::deg),                      //!< Right ascension
            Angle(102.94719 * mp_units::angular::unit_symbols::deg),                      //!< Argument of perigee
            Angle(100.46435 * mp_units::angular::unit_symbols::deg),                      //!< True latitude
            BodyVelocity(-7.4798935500 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(-0.00003804 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.013038888888888888 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-18228.25 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(1198.28 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(129597740.63 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Earth() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::EARTH; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea