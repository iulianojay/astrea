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

class Venus : public CelestialBody {

  public:
    constexpr Venus() :
        CelestialBody(
            "Venus",                     //!< Name
            PlanetaryBody::SUN,          //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(324860.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(4.87 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(6051.8 * mp_units::si::unit_symbols::km),                           //!< Equatorial radius
            Distance(6051.8 * mp_units::si::unit_symbols::km),                           //!< Polar radius
            Distance(6301.8 * mp_units::si::unit_symbols::km),                           //!< Crash radius
            Distance(0.061640255733634 * mp_units::iau::unit_symbols::au),               //!< Crash radius
            Unitless(4.458e-6 * mp_units::one),                 //!< J2 gravitational coefficient
            Unitless(-0.0000025323e-6 * mp_units::one),         //!< J3 gravitational coefficient
            Angle(2.64 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(-1.481329081370229 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(224.701 * mp_units::non_si::day),                                         //!< Sidereal period
            Distance(0.108208925730193e9 * mp_units::si::unit_symbols::km),                //!< Semimajor axis
            Unitless(0.00677323 * mp_units::one),                                          //!< Eccentricity
            Angle(3.39471 * mp_units::angular::unit_symbols::deg),                         //!< Inclination
            Angle(76.68069 * mp_units::angular::unit_symbols::deg),                        //!< Right ascension
            Angle(131.53298 * mp_units::angular::unit_symbols::deg),                       //!< Argument of perigee
            Angle(181.97973 * mp_units::angular::unit_symbols::deg),                       //!< True latitude
            BodyVelocity(137.6300413200 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(-0.00004938 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.0007944444444444444 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-996.89 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(-108.80 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(210664136.06 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Venus() = default;

    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::VENUS; };

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS
    Cartesian get_ephemeris_at(const Date& date) const override;
#endif // ASTREA_BUILD_VENUS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea