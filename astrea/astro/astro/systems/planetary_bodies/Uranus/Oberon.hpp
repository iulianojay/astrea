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

class Oberon : public CelestialBody {

  public:
    constexpr Oberon() :
        CelestialBody(
            "Oberon",                    //!< Name
            CelestialBodyId::URANUS,     //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("1980-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(192.4 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.00288 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(761.4 * mp_units::si::unit_symbols::km),                               //!< Equatorial radius
            Distance(761.4 * mp_units::si::unit_symbols::km),                               //!< Polar radius
            Distance(761.4 * mp_units::si::unit_symbols::km),                               //!< Crash radius
            Distance(9.42735725907e-04 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(0.0 * mp_units::angular::unit_symbols::deg),             //!< Axial tilt
            AngularRate(26.739489189595904 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(13.4632 * mp_units::non_si::day),                              //!< Orbital period
            Distance(583.50e3 * mp_units::si::unit_symbols::km),                //!< Semi-major axis of the orbit
            Unitless(0.0014 * mp_units::one),                                   //!< Eccentricity of the orbit
            Angle(0.07 * mp_units::angular::unit_symbols::deg),                 //!< Inclination of the orbit
            Angle(279.771 * mp_units::angular::unit_symbols::deg),              //!< Longitude of the ascending node
            Angle(24.171 * mp_units::angular::unit_symbols::deg),               //!< Longitude of perigee
            Angle(307.259 * mp_units::angular::unit_symbols::deg),              //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(663356.7 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(1465734.12 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(3517441116.43 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Oberon() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::OBERON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea