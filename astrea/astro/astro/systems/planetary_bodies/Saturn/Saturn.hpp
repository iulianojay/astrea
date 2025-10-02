/**
 * @file Saturn.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Saturn class.
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
 * @class Saturn
 * @brief Represents the Saturn celestial body.
 *
 * This class provides properties and methods specific to Saturn, including its physical and orbital parameters.
 */
class Saturn : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Saturn class.
     *
     * Initializes the Saturn object with predefined physical and orbital parameters.
     */
    constexpr Saturn() :
        CelestialBody(
            "Saturn",                    //!< Name
            CelestialBodyId::SUN,        //!< Parent celestial body
            CelestialBodyType::PLANET,   //!< Type
            Date("2000-01-01 12:00:00"), //!< Reference date for the celestial body data
            GravParam(37931187.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)), //!< Gravitational parameter (mu)
            Mass(568.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)), //!< Mass
            Distance(60268.0 * mp_units::si::unit_symbols::km),                           //!< Equatorial radius
            Distance(54364.0 * mp_units::si::unit_symbols::km),                           //!< Polar radius
            Distance(60268.0 * mp_units::si::unit_symbols::km),                           //!< Crash radius
            Distance(5.453426873248700 * mp_units::iau::unit_symbols::au), //!< Semi-major axis of the orbit around the parent body
            Unitless(16298e-6 * mp_units::one),                            //!< J2 gravitational coefficient
            Unitless(26.73 * mp_units::one),                               //!< J3 gravitational coefficient
            Angle(0.0 * mp_units::angular::unit_symbols::deg),             //!< Axial tilt
            AngularRate(810.8108108108107 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day), //!< Mean motion
            Time(10759.22 * mp_units::non_si::day),                     //!< Orbital period
            Distance(9.53667594 * mp_units::iau::unit_symbols::au),     //!< Semi-major axis of the orbit
            Unitless(0.05386179 * mp_units::one),                       //!< Eccentricity of the orbit
            Angle(2.48599187 * mp_units::angular::unit_symbols::deg),   //!< Inclination of the orbit
            Angle(113.66242448 * mp_units::angular::unit_symbols::deg), //!< Longitude of the ascending node
            Angle(92.59887831 * mp_units::angular::unit_symbols::deg),  //!< Longitude of perihelion
            Angle(49.95424423 * mp_units::angular::unit_symbols::deg),  //!< Mean longitude
            InterplanetaryVelocity(-0.00125060 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semi-major axis
            BodyUnitlessPerTime(-0.00050991 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(0.00193609 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-0.28867794 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(-0.41897216 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(1222.49362201 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }

    /**
     * @brief Default destructor for the Saturn class.
     */
    ~Saturn() = default;

    /**
     * @brief Get the unique identifier for the Saturn celestial body.
     *
     * @return CelestialBodyId The unique identifier for Saturn.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::SATURN; };

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

    /**
     * @brief Get the position of the Saturn at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Saturn.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Saturn at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

  private:
    /**
     * @brief Get the coefficients for the linear expansion of Saturn's orbital elements.
     *
     * This function returns a tuple containing the coefficients used in the linear expansion
     * of Saturn's orbital elements, which are essential for calculating its position and motion
     * over time.
     *
     * @return CoefficientPack A tuple containing the coefficients for the linear expansion.
     */
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.00025899 * rad / (JulianCentury * JulianCentury), -0.13434469 * rad, 0.87320147 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea