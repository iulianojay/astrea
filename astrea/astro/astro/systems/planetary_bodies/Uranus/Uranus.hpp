/**
 * @file Uranus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Uranus class.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
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

/**
 * @class Uranus
 * @brief Represents the Uranus celestial body.
 *
 * This class provides properties and methods specific to Uranus, including its physical and orbital parameters.
 */
class Uranus : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Uranus class.
     *
     * Initializes the Uranus object with predefined physical and orbital parameters.
     */
    constexpr Uranus() :
        CelestialBody(
            "Uranus",                    //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(5793939.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(86.8 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(25559.0 * mp_units::si::unit_symbols::km),                          //!< Equatorial radius
            Distance(24973.0 * mp_units::si::unit_symbols::km),                          //!< Polar radius
            Distance(25559.0 * mp_units::si::unit_symbols::km),                          //!< Crash radius
            Distance(5.176385869757780 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(3343.43e-6 * mp_units::one),                          //!< J2 gravitational coefficient
            Unitless(0.0 * mp_units::one),                                 //!< J3 gravitational coefficient
            Angle(82.23 * mp_units::angular::unit_symbols::deg), //!< Axial tilt
            AngularRate(-501.1600928074246 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(30685.4 * mp_units::non_si::day),                      //!< Orbital period
            Distance(19.18916464 * mp_units::iau::unit_symbols::au),    //!< Semi-major axis of the orbit
            Unitless(0.04725744 * mp_units::one),                       //!< Eccentricity of the orbit
            Angle(0.77263783 * mp_units::angular::unit_symbols::deg),   //!< Inclination of the orbit
            Angle(74.01692503 * mp_units::angular::unit_symbols::deg),  //!< Longitude of the ascending node
            Angle(170.95427630 * mp_units::angular::unit_symbols::deg), //!< Longitude of perihelion
            Angle(313.23810451 * mp_units::angular::unit_symbols::deg), //!< Mean longitude
            InterplanetaryVelocity(-0.00196176 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(-0.00004397 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.00242939 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(0.04240589 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.40805281 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(428.48202785 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }

    /**
     * @brief Default destructor for the Uranus class.
     */
    ~Uranus() = default;

    /**
     * @brief Get the unique identifier for the Uranus celestial body.
     *
     * @return CelestialBodyId The unique identifier for Uranus.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::URANUS; };

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

    /**
     * @brief Get the position of the Uranus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Uranus.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Uranus at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

  private:
    /**
     * @brief Get the coefficients for the linear expansion of the Uranus' orientation angles.
     *
     * This function provides the coefficients used in the linear expansion to calculate
     * the orientation angles of Uranus over time.
     *
     * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.00058331 * rad / (JulianCentury * JulianCentury), -0.97731848 * rad, 0.17689245 * rad, 7.67025000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea