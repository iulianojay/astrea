/**
 * @file Venus.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Venus class.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS
#include <ephemerides/Venus/VenusEphemerisTable.hpp>
#endif // ASTREA_BUILD_VENUS_EPHEMERIS

namespace astrea {
namespace astro {

    // Forward-declare frame types to avoid circular include with frames.hpp
    namespace frames { namespace solar_system_barycenter { struct icrf; } }

namespace planets {

static CelestialBodyParameters DEFAULT_VENUS_PARAMS{
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(324860.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(4.87 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(6051.8 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(6051.8 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(6301.8 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.061640255733634 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(4.458e-6 * mp_units::one),
    .j3                = Unitless(-0.0000025323e-6 * mp_units::one),
    .axialTilt         = Angle(2.64 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(-1.481329081370229 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(224.701 * mp_units::non_si::day),
    .semimajorAxis          = Distance(0.72333566 * mp_units::iau::unit_symbols::au),
    .eccentricity           = Unitless(0.00677672 * mp_units::one),
    .inclination            = Angle(3.39467605 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(76.67984255 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(131.60246718 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(181.97909950 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00000390 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004107 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(-0.00078890 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(-0.27769418 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(0.00268329 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(58517.81538729 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Venus
 * @brief Represents the Venus celestial body.
 *
 * This class provides properties and methods specific to Venus, including its physical and orbital parameters.
 */
inline constexpr struct Venus : CelestialBody<"Venus", barycenters::SolarSystemBarycenter{}> {
} Venus;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Venus>()
{
    return planets::DEFAULT_VENUS_PARAMS;
}

// Altitude Conditions(TABLE 7-4, Vallado)
static const std::map<Altitude, Density> venutianAtmosphere = { // km, kg/m^3
    { 3.0 * mp_units::si::unit_symbols::km,
      5.53e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 6.0 * mp_units::si::unit_symbols::km,
      4.75e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 9.0 * mp_units::si::unit_symbols::km,
      4.02e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 12.0 * mp_units::si::unit_symbols::km,
      3.44e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 15.0 * mp_units::si::unit_symbols::km,
      2.91e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 18.0 * mp_units::si::unit_symbols::km,
      2.46e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 21.0 * mp_units::si::unit_symbols::km,
      2.06e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 24.0 * mp_units::si::unit_symbols::km,
      1.70e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 27.0 * mp_units::si::unit_symbols::km,
      1.405e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 30.0 * mp_units::si::unit_symbols::km,
      1.115e1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 33.0 * mp_units::si::unit_symbols::km,
      9.0 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 36.0 * mp_units::si::unit_symbols::km,
      7.15 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 39.0 * mp_units::si::unit_symbols::km,
      5.15 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 42.0 * mp_units::si::unit_symbols::km,
      4.34 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 45.0 * mp_units::si::unit_symbols::km,
      3.30 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 48.0 * mp_units::si::unit_symbols::km,
      2.39 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 51.0 * mp_units::si::unit_symbols::km,
      1.88 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 54.0 * mp_units::si::unit_symbols::km,
      1.38 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 57.0 * mp_units::si::unit_symbols::km,
      9.6e-1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 60.0 * mp_units::si::unit_symbols::km,
      6.2e-1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 70.0 * mp_units::si::unit_symbols::km,
      1.2e-1 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 80.0 * mp_units::si::unit_symbols::km,
      1.8e-2 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 90.0 * mp_units::si::unit_symbols::km,
      2.3e-3 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 100.0 * mp_units::si::unit_symbols::km,
      3.1e-4 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 110.0 * mp_units::si::unit_symbols::km,
      4.4e-5 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 120.0 * mp_units::si::unit_symbols::km,
      7.2e-6 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 130.0 * mp_units::si::unit_symbols::km,
      1.4e-6 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 140.0 * mp_units::si::unit_symbols::km,
      3.0e-7 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 150.0 * mp_units::si::unit_symbols::km,
      8.0e-8 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 160.0 * mp_units::si::unit_symbols::km,
      2.6e-8 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 170.0 * mp_units::si::unit_symbols::km,
      9.5e-9 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 180.0 * mp_units::si::unit_symbols::km,
      4.0e-9 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 190.0 * mp_units::si::unit_symbols::km,
      1.9e-9 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 200.0 * mp_units::si::unit_symbols::km,
      9.4e-10 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 210.0 * mp_units::si::unit_symbols::km,
      4.9e-10 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 220.0 * mp_units::si::unit_symbols::km,
      2.6e-10 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 230.0 * mp_units::si::unit_symbols::km,
      1.4e-10 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 240.0 * mp_units::si::unit_symbols::km,
      7.5e-11 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 250.0 * mp_units::si::unit_symbols::km,
      5.5e-11 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 260.0 * mp_units::si::unit_symbols::km,
      4.1e-11 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 270.0 * mp_units::si::unit_symbols::km,
      2.2e-11 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 280.0 * mp_units::si::unit_symbols::km,
      1.2e-11 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 290.0 * mp_units::si::unit_symbols::km,
      6.5e-12 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) },
    { 300.0 * mp_units::si::unit_symbols::km,
      3.5e-12 * mp_units::si::unit_symbols::kg / (mp_units::pow<3>(mp_units::si::unit_symbols::m)) }
};

/**
 * @brief Find the atmospheric density at a given date and altitude.
 *
 * @param date The date for which to find the atmospheric density.
 * @param altitude The altitude at which to find the atmospheric density.
 * @return Density The atmospheric density at the given date and altitude.
 */
template <>
inline constexpr Density find_atmospheric_density<planets::Venus>(const State& state)
{
    const auto& position = state.get_position_in_frame<frames::venus::venus_fixed>();
    const auto [latitude, longitude, altitude] =
        convert_body_fixed_to_geodetic(position, get_equitorial_radius(), get_polar_radius());

    const auto iter = venutianAtmosphere.upper_bound(altitude);
    return (iter != venutianAtmosphere.end()) ? iter->second : Density::zero();
}

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS

/**
 * @brief Get the position of the Venus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Venus.
 * @return RadiusVector<frames::solar_system_barycenter::icrf> The position of the Venus at the given date.
 */
template <>
inline constexpr RadiusVector<frames::solar_system_barycenter::icrf> get_position_at<planets::Venus>(const Date& date)
{
    return get_position_at_impl<VenusEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

/**
 * @brief Get the velocity of the Venus at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Venus.
 * @return VelocityVector<frames::solar_system_barycenter::icrf> The velocity of the Venus at the given date.
 */
template <>
inline constexpr VelocityVector<frames::solar_system_barycenter::icrf> get_velocity_at<planets::Venus>(const Date& date)
{
    return get_velocity_at_impl<VenusEphemerisTable, frames::solar_system_barycenter::icrf>(date);
}

#endif // ASTREA_BUILD_VENUS_EPHEMERIS

} // namespace astro
} // namespace astrea