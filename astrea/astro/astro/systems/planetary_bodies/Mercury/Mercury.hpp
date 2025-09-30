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
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
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
            Time(87.969 * mp_units::non_si::day),                                       //!< Sidereal period
            Distance(0.38709927 * mp_units::iau::unit_symbols::au),                     //!< Semimajor axis
            Unitless(0.20563593 * mp_units::one),                                       //!< Eccentricity
            Angle(7.00497902 * mp_units::angular::unit_symbols::deg),                   //!< Inclination
            Angle(48.33076593 * mp_units::angular::unit_symbols::deg),                  //!< Longitude of ascending node
            Angle(77.45779628 * mp_units::angular::unit_symbols::deg),                  //!< Longitude of perihelion
            Angle(252.25032350 * mp_units::angular::unit_symbols::deg),                 //!< Mean longitude
            BodyVelocity(0.00000037 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.00001906 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.00594749 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-0.12534081 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.16047689 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(149472.67411175 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }
    ~Mercury() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MERCURY; };

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
    CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea