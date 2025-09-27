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

class Ganymede : public CelestialBody {

  public:
    constexpr Ganymede() :
        CelestialBody(
            "Ganymede",                  //!< Name
            CelestialBodyId::JUPITER,    //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1997-01-16 00:00:00"), //!< Reference date for the celestial body data
            GravParam(9887.8 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.14819 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(2631.2 * mp_units::si::unit_symbols::km),                              //!< Equatorial radius
            Distance(2631.2 * mp_units::si::unit_symbols::km),                              //!< Polar radius
            Distance(2631.2 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(0.002435315183093 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(3.198 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(50.317608940768210 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(7.154553 * mp_units::non_si::day),                             //!< Orbital period
            Distance(1070.4e3 * mp_units::si::unit_symbols::km),                //!< Semi-major axis of the orbit
            Unitless(0.001 * mp_units::one),                                    //!< Eccentricity of the orbit
            Angle(0.18 * mp_units::angular::unit_symbols::deg),                 //!< Inclination of the orbit
            Angle(63.552 * mp_units::angular::unit_symbols::deg),               //!< Longitude of the ascending node
            Angle(255.969 * mp_units::angular::unit_symbols::deg),              //!< Longtiude of perigee
            Angle(573.509 * mp_units::angular::unit_symbols::deg),              //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(976977.7 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(3016348.9 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(6619278519.62 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Ganymede() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::GANYMEDE; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea