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

class Jupiter : public CelestialBody {

  public:
    constexpr Jupiter() :
        CelestialBody(
            "Jupiter",                   //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(126686535.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(1898.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(3396.2 * mp_units::si::unit_symbols::km),                             //!< Equatorial radius
            Distance(66854.0 * mp_units::si::unit_symbols::km),                            //!< Polar radius
            Distance(71492.0 * mp_units::si::unit_symbols::km),                            //!< Crash radius
            Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),                 //!< Crash radius
            Unitless(14736e-6 * mp_units::one),                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                      //!< J3 gravitational coefficient
            Angle(3.13 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Rotation rate
            Time(4332.589 * mp_units::non_si::day),                     //!< Sidereal period
            Distance(5.20288700 * mp_units::iau::unit_symbols::au),     //!< Semimajor axis
            Unitless(0.04838624 * mp_units::one),                       //!< Eccentricity
            Angle(1.30439695 * mp_units::angular::unit_symbols::deg),   //!< Inclination
            Angle(100.47390909 * mp_units::angular::unit_symbols::deg), //!< Longitude of ascending node
            Angle(14.72847983 * mp_units::angular::unit_symbols::deg),  //!< Longitude of perihelion
            Angle(34.39644051 * mp_units::angular::unit_symbols::deg),  //!< Mean longitude
            BodyVelocity(-0.00011607 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(-0.00013253 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.00183714 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(0.20469106 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.21252668 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(3034.74612775 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }
    ~Jupiter() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::JUPITER; };

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS
    OrbitalElements get_elements_at(const Date& date) const override;
#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

  private:
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00012452 * rad / (JulianCentury * JulianCentury), 0.06064060 * rad, -0.35635438 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea