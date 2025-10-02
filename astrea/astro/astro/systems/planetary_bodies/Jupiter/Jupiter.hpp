/**
 * @file Jupiter.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Jupiter class.
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
 * @class Jupiter
 * @brief Represents the Jupiter celestial body.
 *
 * This class provides properties and methods specific to Jupiter, including its physical and orbital parameters.
 */
class Jupiter : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Jupiter class.
     *
     * Initializes the Jupiter object with predefined physical and orbital parameters.
     */
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
            InterplanetaryVelocity(-0.00011607 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(-0.00013253 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.00183714 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(0.20469106 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.21252668 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(3034.74612775 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }

    /**
     * @brief Default destructor for the Jupiter class.
     */
    ~Jupiter() = default;

    /**
     * @brief Get the unique identifier for the Jupiter celestial body.
     *
     * @return CelestialBodyId The unique identifier for Jupiter.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::JUPITER; };

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS

    /**
     * @brief Get the position of the Jupiter at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Jupiter.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Jupiter at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

  private:
    /**
     * @brief Get the linear expansion coefficients for Jupiter's orbital elements.
     *
     * This function returns a tuple containing the coefficients for the linear expansion of Jupiter's
     * orbital elements, which are used to compute the position and velocity of Jupiter over time.
     *
     * @return CoefficientPack A tuple containing the linear expansion coefficients.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00012452 * rad / (JulianCentury * JulianCentury), 0.06064060 * rad, -0.35635438 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea