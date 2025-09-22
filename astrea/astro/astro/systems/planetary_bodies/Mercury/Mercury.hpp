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

class Mercury : public CelestialBody {

  public:
    constexpr Mercury() :
        CelestialBody(
            "Mercury",                   //!< Name
            PlanetaryBody::SUN,          //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(22032.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.330 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(2439.7 * mp_units::si::unit_symbols::km),                            //!< Equatorial radius
            Distance(2439.7 * mp_units::si::unit_symbols::km),                            //!< Polar radius
            Distance(2464.7 * mp_units::si::unit_symbols::km),                            //!< Crash radius
            Distance(0.011239389492058 * mp_units::iau::unit_symbols::au),                //!< Crash radius
            Unitless(60.0e-6 * mp_units::one),                   //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                       //!< J3 gravitational coefficient
            Angle(0.034 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(6.138107416879796 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(87.969 * mp_units::non_si::day),                                         //!< Sidereal period
            Distance(0.057909175794378e9 * mp_units::si::unit_symbols::km),               //!< Semimajor axis
            Unitless(0.20563069 * mp_units::one),                                         //!< Eccentricity
            Angle(7.00487 * mp_units::angular::unit_symbols::deg),                        //!< Inclination
            Angle(48.33167 * mp_units::angular::unit_symbols::deg),                       //!< Right ascension
            Angle(77.45645 * mp_units::angular::unit_symbols::deg),                       //!< Argument of perigee
            Angle(252.25084 * mp_units::angular::unit_symbols::deg),                      //!< True latitude
            BodyVelocity(98.7345948600 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.00002527 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.006530555555555556 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-446.30 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(573.57 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(538101628.29 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Mercury() = default;

    static constexpr PlanetaryBody get_id() { return PlanetaryBody::MERCURY; };

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
    OrbitalElements get_elements_at(const Date& date) const override;
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea