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

class Deimos : public CelestialBody {

  public:
    constexpr Deimos() :
        CelestialBody(
            "Deimos",                    //!< Name
            CelestialBodyId::MARS,       //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1950-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(7.112e-4 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(10.6e-9 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(11.1 * mp_units::si::unit_symbols::km),                                //!< Equatorial radius
            Distance(9.1 * mp_units::si::unit_symbols::km),                                 //!< Polar radius
            Distance(11.15 * mp_units::si::unit_symbols::km),                               //!< Crash radius
            Distance(7.23133636677e-07 * mp_units::iau::unit_symbols::au),                  //!< Crash radius
            Unitless(0.0 * mp_units::one),                        //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                        //!< J3 gravitational coefficient
            Angle(25.199 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(27092.28308927283 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(0.31891 * mp_units::non_si::day),                              //!< Sidereal period
            Distance(9378.0 * mp_units::si::unit_symbols::km),                  //!< Semimajor axis
            Unitless(0.0151 * mp_units::one),                                   //!< Eccentricity
            Angle(1.08 * mp_units::angular::unit_symbols::deg),                 //!< Inclination
            Angle(207.784 * mp_units::angular::unit_symbols::deg),              //!< Right ascension
            Angle(357.841 * mp_units::angular::unit_symbols::deg),              //!< Longitude of perigee
            Angle(448.9 * mp_units::angular::unit_symbols::deg),                //!< Mean longitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(57302029 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(171830131 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(148603627216.0 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Deimos() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::DEIMOS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea