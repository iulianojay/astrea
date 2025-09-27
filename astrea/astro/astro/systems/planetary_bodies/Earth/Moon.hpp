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

class Moon : public CelestialBody {
  public:
    constexpr Moon() :
        CelestialBody(
            "Moon",                      //!< Name
            CelestialBodyId::EARTH,      //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(4902.8 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.073 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(1737.5 * mp_units::si::unit_symbols::km),                            //!< Equatorial radius
            Distance(1736.0 * mp_units::si::unit_symbols::km),                            //!< Polar radius
            Distance(1737.5 * mp_units::si::unit_symbols::km),                            //!< Crash radius
            Distance(0.006602718630998 * mp_units::iau::unit_symbols::au),                //!< Crash radius
            Unitless(0.0 * mp_units::one),                       //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                       //!< J3 gravitational coefficient
            Angle(1.543 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(13.176195007686115 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(27.3220 * mp_units::non_si::day),                              //!< Sidereal period
            Distance(380318 * mp_units::si::unit_symbols::km),                  //!< Semimajor axis
            Unitless(0.063843 * mp_units::one),                                 //!< Eccentricity
            Angle(5.28619 * mp_units::angular::unit_symbols::deg),              //!< Inclination
            Angle(98.13908 * mp_units::angular::unit_symbols::deg),             //!< Right ascension
            Angle(179.16058 * mp_units::angular::unit_symbols::deg),            //!< Longitude of perigee
            Angle(135.89122 * mp_units::angular::unit_symbols::deg),            //!< Mean longitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(6967741.9 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(28578547 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(1761137860.75 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Moon() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MOON; };

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
    OrbitalElements get_elements_at(const Date& date) const override;
#endif // ASTREA_BUILD_EARTH_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea