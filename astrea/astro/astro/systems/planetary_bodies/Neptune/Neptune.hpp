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

class Neptune : public CelestialBody {

  public:
    constexpr Neptune() :
        CelestialBody(
            "Neptune",                   //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 00:00:00"), //!< Reference date for the celestial body data
            GravParam(6836529.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(102.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(24764.0 * mp_units::si::unit_symbols::km),                           //!< Equatorial radius
            Distance(24341.0 * mp_units::si::unit_symbols::km),                           //!< Polar radius
            Distance(24764.0 * mp_units::si::unit_symbols::km),                           //!< Crash radius
            Distance(8.651147189326089 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(3411e-6 * mp_units::one),                             //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(28.32 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(536.3128491620112 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(60189 * mp_units::non_si::day),                              //!< Orbital period
            Distance(4.498252919784751e9 * mp_units::si::unit_symbols::km),   //!< Semi-major axis of the orbit
            Unitless(0.00858587 * mp_units::one),                             //!< Eccentricity of the orbit
            Angle(131.72169 * mp_units::angular::unit_symbols::deg),          //!< Inclination of the orbit
            Angle(44.97135 * mp_units::angular::unit_symbols::deg),           //!< Longitude of the ascending node
            Angle(304.88003 * mp_units::angular::unit_symbols::deg),          //!< Argument of perigee
            Angle(-187290.5505771600 * mp_units::angular::unit_symbols::deg), //!< Mean anomaly or true latitude
            BodyVelocity(-187290.5505771600 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0000251 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.001011111111111111 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-151.25 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(-844.43 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the argument of perigee
            BodyAngularRate(786449.21 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Neptune() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::NEPTUNE; };

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS
    OrbitalElements get_elements_at(const Date& date) const override;
#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea