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

class Mars : public CelestialBody {

  public:
    constexpr Mars() :
        CelestialBody(
            "Mars",                      //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(42828.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.642 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(3396.2 * mp_units::si::unit_symbols::km),                            //!< Equatorial radius
            Distance(3376.2 * mp_units::si::unit_symbols::km),                            //!< Polar radius
            Distance(3496.2 * mp_units::si::unit_symbols::km),                            //!< Crash radius
            Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),                //!< Crash radius
            Unitless(1960.45e-6 * mp_units::one),                //!< J2 gravitational coefficient
            Unitless(0.000036 * mp_units::one),                  //!< J3 gravitational coefficient
            Angle(25.19 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(686.980 * mp_units::non_si::day),                                      //!< Sidereal period
            Distance(1.52371034 * mp_units::iau::unit_symbols::au),                     //!< Semimajor axis
            Unitless(0.09339410 * mp_units::one),                                       //!< Eccentricity
            Angle(1.84969142 * mp_units::angular::unit_symbols::deg),                   //!< Inclination
            Angle(49.55953891 * mp_units::angular::unit_symbols::deg),                  //!< Longitude of ascending node
            Angle(-23.94362959 * mp_units::angular::unit_symbols::deg),                 //!< Longitude of perihelion
            Angle(-4.55343205 * mp_units::angular::unit_symbols::deg),                  //!< Mean longitude
            BodyVelocity(0.00001847 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.00007882 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.00813131 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-0.29257343 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.44441088 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(19140.30268499 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }
    ~Mars() = default;

    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MARS; };

#ifdef ASTREA_BUILD_MARS_EPHEMERIS
    CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;
#endif // ASTREA_BUILD_MARS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea