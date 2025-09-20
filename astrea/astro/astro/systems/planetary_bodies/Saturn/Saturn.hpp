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

class Saturn : public CelestialBody {

  public:
    constexpr Saturn() :
        CelestialBody(
            "Saturn",                    //!< Name
            PlanetaryBody::SUN,          //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(37931187.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(568.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(60268.0 * mp_units::si::unit_symbols::km),                           //!< Equatorial radius
            Distance(54364.0 * mp_units::si::unit_symbols::km),                           //!< Polar radius
            Distance(60268.0 * mp_units::si::unit_symbols::km),                           //!< Crash radius
            Distance(5.453426873248700 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(16298e-6 * mp_units::one),                            //!< J2 gravitational coefficient
            Unitless(26.73 * mp_units::one),                               //!< J3 gravitational coefficient
            Angle(0.0 * mp_units::angular::unit_symbols::deg),             //!< Axial tilt
            AngularRate(810.8108108108107 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(10759.22 * mp_units::non_si::day),                         //!< Orbital period
            Distance(1.426725415449289e9 * mp_units::si::unit_symbols::km), //!< Semi-major axis of the orbit
            Unitless(0.05415060 * mp_units::one),                           //!< Eccentricity of the orbit
            Angle(2.48446 * mp_units::angular::unit_symbols::deg),          //!< Inclination of the orbit
            Angle(113.71504 * mp_units::angular::unit_symbols::deg),        //!< Longitude of the ascending node
            Angle(92.43194 * mp_units::angular::unit_symbols::deg),         //!< Argument of perigee
            Angle(49.94432 * mp_units::angular::unit_symbols::deg),         //!< Mean anomaly or true latitude
            BodyVelocity(-451082.4604262999 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(-0.00036762 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.0016972222222222224 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-1591.05 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(-1948.89 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(4401052.95 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Saturn() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::SATURN; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea