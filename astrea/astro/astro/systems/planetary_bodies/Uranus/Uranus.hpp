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

class Uranus : public CelestialBody {

  public:
    constexpr Uranus() :
        CelestialBody(
            "Uranus",                    //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(5793939.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(86.8 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(25559.0 * mp_units::si::unit_symbols::km),                          //!< Equatorial radius
            Distance(24973.0 * mp_units::si::unit_symbols::km),                          //!< Polar radius
            Distance(25559.0 * mp_units::si::unit_symbols::km),                          //!< Crash radius
            Distance(5.176385869757780 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(3343.43e-6 * mp_units::one),                          //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(82.23 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(-501.1600928074246 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(30685.4 * mp_units::non_si::day),                          //!< Orbital period
            Distance(2.870972225727093e9 * mp_units::si::unit_symbols::km), //!< Semi-major axis of the orbit
            Unitless(0.04716771 * mp_units::one),                           //!< Eccentricity of the orbit
            Angle(0.76986 * mp_units::angular::unit_symbols::deg),          //!< Inclination of the orbit
            Angle(74.22988 * mp_units::angular::unit_symbols::deg),         //!< Longitude of the ascending node
            Angle(170.96424 * mp_units::angular::unit_symbols::deg),        //!< Argument of perigee
            Angle(313.23218 * mp_units::angular::unit_symbols::deg),        //!< Mean anomaly or true latitude
            BodyVelocity(227426.1633877500 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(-0.00019150 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.0005805555555555555 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-1681.40 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(1312.56 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(1542547.79 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Uranus() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::URANUS; };

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS
    OrbitalElements get_elements_at(const Date& date) const override;
#endif // ASTREA_BUILD_URANUS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea