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

class Europa : public CelestialBody {

  public:
    constexpr Europa() :
        CelestialBody(
            "Europa",                    //!< Name
            CelestialBodyId::JUPITER,    //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1997-01-16 00:00:00"), //!< Reference date for the celestial body data
            GravParam(3202.7 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.04800 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(1560.8 * mp_units::si::unit_symbols::km),                              //!< Equatorial radius
            Distance(1560.8 * mp_units::si::unit_symbols::km),                              //!< Polar radius
            Distance(1560.8 * mp_units::si::unit_symbols::km),                              //!< Crash radius
            Distance(9.72669393872e-04 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(3.146 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(101.3747257602471 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(3.551181 * mp_units::non_si::day),                             //!< Orbital period
            Distance(671.1e3 * mp_units::si::unit_symbols::km),                 //!< Semi-major axis of the orbit
            Unitless(0.009 * mp_units::one),                                    //!< Eccentricity of the orbit
            Angle(0.47 * mp_units::angular::unit_symbols::deg),                 //!< Inclination of the orbit
            Angle(219.106 * mp_units::angular::unit_symbols::deg),              //!< Longitude of the ascending node
            Angle(308.076 * mp_units::angular::unit_symbols::deg),              //!< Longtiude of perigee
            Angle(479.092 * mp_units::angular::unit_symbols::deg),              //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(4293665.52 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(97263536.4 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(13427026021.5 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Europa() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::EUROPA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea