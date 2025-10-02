/**
 * @file Mars.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Mars class.
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
 * @class Mars
 * @brief Represents the Mars celestial body.
 *
 * This class provides properties and methods specific to Mars, including its physical and orbital parameters.
 */
class Mars : public CelestialBody {

  public:
    /**
     * @brief Default constructor for the Mars class.
     *
     * Initializes the Mars object with predefined physical and orbital parameters.
     */
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
            Time(686.980 * mp_units::non_si::day),                      //!< Sidereal period
            Distance(1.52371034 * mp_units::iau::unit_symbols::au),     //!< Semimajor axis
            Unitless(0.09339410 * mp_units::one),                       //!< Eccentricity
            Angle(1.84969142 * mp_units::angular::unit_symbols::deg),   //!< Inclination
            Angle(49.55953891 * mp_units::angular::unit_symbols::deg),  //!< Longitude of ascending node
            Angle(-23.94362959 * mp_units::angular::unit_symbols::deg), //!< Longitude of perihelion
            Angle(-4.55343205 * mp_units::angular::unit_symbols::deg),  //!< Mean longitude
            InterplanetaryVelocity(0.00001847 * mp_units::iau::unit_symbols::au / JulianCentury), //!< Rate of change of the semimajor axis
            BodyUnitlessPerTime(0.00007882 * mp_units::one / JulianCentury), //!< Rate of change of the eccentricity
            BodyAngularRate(-0.00813131 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the inclination
            BodyAngularRate(-0.29257343 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of ascending node
            BodyAngularRate(0.44441088 * mp_units::angular::unit_symbols::deg / JulianCentury), //!< Rate of change of the longitude of perihelion
            BodyAngularRate(19140.30268499 * mp_units::angular::unit_symbols::deg / JulianCentury) //!< Rate of change of the mean longitude
        )
    {
    }

    /**
     * @brief Default destructor for the Mars class.
     */
    ~Mars() = default;

    /**
     * @brief Calculate the atmospheric density at a given altitude and date.
     *
     * This function uses a simple exponential model to estimate the atmospheric density
     * based on the altitude above the surface of Mars. The model parameters are based on
     * average conditions and do not account for seasonal or diurnal variations.
     *
     * @param date The date for which to calculate the atmospheric density.
     * @param altitude The altitude above the surface of Mars in kilometers.
     * @return Density The estimated atmospheric density in kg/m^3.
     */
    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    /**
     * @brief Get the unique identifier for the Mars celestial body.
     *
     * @return CelestialBodyId The unique identifier for Mars.
     */
    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MARS; };

#ifdef ASTREA_BUILD_MARS_EPHEMERIS

    /**
     * @brief Get the position of the Mars at a specific date in the ICRF frame using JPL DE430 ephemeris data.
     *
     * @param date The date for which to find the position of the Mars.
     * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Mars at the given date.
     */
    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_MARS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea