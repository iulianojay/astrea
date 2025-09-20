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

class Titania : public CelestialBody {

  public:
    constexpr Titania() :
        CelestialBody(
            "Titania",                   //!< Name
            PlanetaryBody::URANUS,       //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1980-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(228.2 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.00342 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(788.9 * mp_units::si::unit_symbols::km),                               //!< Equatorial radius
            Distance(788.9 * mp_units::si::unit_symbols::km),                               //!< Polar radius
            Distance(1568.9 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(7.55070955998e-04 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(0.0 * mp_units::angular::unit_symbols::deg),             //!< Axial tilt
            AngularRate(41.351424275146869 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(8.70586 * mp_units::non_si::day),                              //!< Orbital period
            Distance(436.30e3 * mp_units::si::unit_symbols::km),                //!< Semi-major axis of the orbit
            Unitless(0.0011 * mp_units::one),                                   //!< Eccentricity of the orbit
            Angle(0.08 * mp_units::angular::unit_symbols::deg),                 //!< Inclination of the orbit
            Angle(99.771 * mp_units::angular::unit_symbols::deg),               //!< Longitude of the ascending node
            Angle(24.17 * mp_units::angular::unit_symbols::deg),                //!< Argument of perigee
            Angle(48.785 * mp_units::angular::unit_symbols::deg),               //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(663360.1 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(1465712.68 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(5438764533.33 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Titania() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::TITANIA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea