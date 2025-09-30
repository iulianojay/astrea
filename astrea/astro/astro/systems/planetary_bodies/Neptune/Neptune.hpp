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
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
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
            Time(60189 * mp_units::non_si::day),                        //!< Orbital period
            Distance(30.06992276 * mp_units::iau::unit_symbols::au),    //!< Semi-major axis of the orbit
            Unitless(0.00859048 * mp_units::one),                       //!< Eccentricity of the orbit
            Angle(1.77004347 * mp_units::angular::unit_symbols::deg),   //!< Inclination of the orbit
            Angle(131.78422574 * mp_units::angular::unit_symbols::deg), //!< Longitude of the ascending node
            Angle(44.96476227 * mp_units::angular::unit_symbols::deg),  //!< Longitude of perihelion
            Angle(-55.12002969 * mp_units::angular::unit_symbols::deg), //!< Mean longitude
            BodyVelocity(0.00026291 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.00005105 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.00035372 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-0.00508664 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(-0.32241464 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(218.45945325 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }
    ~Neptune() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::NEPTUNE; };

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS
    CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;
#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

  private:
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00041348 * rad / (JulianCentury * JulianCentury), 0.68346318 * rad, -0.10162547 * rad, 7.67025000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea