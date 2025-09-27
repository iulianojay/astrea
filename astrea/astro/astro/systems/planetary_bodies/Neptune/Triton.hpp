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

class Triton : public CelestialBody {

  public:
    constexpr Triton() :
        CelestialBody(
            "Triton",                    //!< Name
            CelestialBodyId::NEPTUNE,    //!< Parent celestial body
            CelestialBodyType::MOON,     //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(1427.6 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(0.0214 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(1353.4 * mp_units::si::unit_symbols::km),                             //!< Equatorial radius
            Distance(1353.4 * mp_units::si::unit_symbols::km),                             //!< Polar radius
            Distance(1353.4 * mp_units::si::unit_symbols::km),                             //!< Crash radius
            Distance(0.001198560847624 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(0.0 * mp_units::one),                                 //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(28.33 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(61.257264516014864 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(5.87685 * mp_units::non_si::day),                              //!< Orbital period
            Distance(354.76e3 * mp_units::si::unit_symbols::km),                //!< Semi-major axis of the orbit
            Unitless(0.000016 * mp_units::one),                                 //!< Eccentricity of the orbit
            Angle(157.345 * mp_units::angular::unit_symbols::deg),              //!< Inclination of the orbit
            Angle(177.608 * mp_units::angular::unit_symbols::deg),              //!< Longitude of the ascending node
            Angle(243.75 * mp_units::angular::unit_symbols::deg),               //!< Longitude of perigee
            Angle(596.007 * mp_units::angular::unit_symbols::deg),              //!< Mean anomaly or true latitude
            BodyVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),           //!< Rate of change of the eccentricity
            BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(188523.9 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the right ascension
            BodyAngularRate(523952.8 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perigee
            BodyAngularRate(8055241569.86 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the true latitude
        )
    {
    }
    ~Triton() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TRITON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea