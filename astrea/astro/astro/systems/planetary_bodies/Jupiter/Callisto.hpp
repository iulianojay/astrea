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

class Callisto : public CelestialBody {

  public:
    constexpr Callisto() :
        CelestialBody(
            "Callisto",                  //!< Name
            CelestialBodyId::JUPITER,    //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1997-01-16 00:00:00"), //!< Reference date for the celestial body data
            GravParam(7179.3 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.10759 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(2410.3 * mp_units::si::unit_symbols::km),                              //!< Equatorial radius
            Distance(2410.3 * mp_units::si::unit_symbols::km),                              //!< Polar radius
            Distance(2410.3 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(0.003768525014695 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(3.486 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(21.571072760007375 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(16.68901 * mp_units::non_si::day),                             //!< Orbital period
            Distance(1882.7e3 * mp_units::si::unit_symbols::km),                //!< Semi-major axis of the orbit
            Unitless(0.007 * mp_units::one),                                    //!< Eccentricity of the orbit
            Angle(0.19 * mp_units::angular::unit_symbols::deg),                 //!< Inclination of the orbit
            Angle(298.848 * mp_units::angular::unit_symbols::deg),              //!< Longitude of the ascending node
            Angle(351.491 * mp_units::angular::unit_symbols::deg),              //!< Longtiude of perigee
            Angle(532.899 * mp_units::angular::unit_symbols::deg),              //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(382503.98 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(1012394.6 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(2837392757.1 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Callisto() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::CALLISTO; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea