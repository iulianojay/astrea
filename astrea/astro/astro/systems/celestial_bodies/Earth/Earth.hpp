/**
 * @file Earth.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Earth class.
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <ephemerides/Earth/EarthFromEmbEphemerisTable.hpp>
#include <ephemerides/Earth/EmbEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

enum class EarthAtmosphereModel { JACHIA_ROBERTS, NRLMSISE00, DTM2000, HARRIS_PRIESTER };

struct EarthParameters {
    EarthAtmosphereModel atmosphereModel = EarthAtmosphereModel::JACHIA_ROBERTS; //!< The atmospheric model to use for Earth.
};

/**
 * @class Earth
 * @brief Represents the Earth celestial body.
 *
 * This class provides properties and methods specific to Earth, including its physical and orbital parameters.
 */
#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
// SPICE ephemeris data for Earth is relative to the Earth-Moon barycenter, so we set the parent frame accordingly.
inline constexpr struct Earth final : CelestialBody<"Earth", barycenters::EarthMoonBarycenter> {
} Earth;
#else
inline constexpr struct Earth final : CelestialBody<"Earth", barycenters::SolarSystemBarycenter> {
} Earth;
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Earth>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(398600.44189 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(5.97 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(6378.137 * km),
             .polarRadius            = Distance(6356.75538082 * km),
             .crashRadius            = Distance(6478.1 * km),
             .sphereOfInfluence      = Distance(0.092449582665046 * au),
             .j2                     = Unitless(0.00108262982 * one),
             .j3                     = Unitless(-0.0000025323 * one),
             .axialTilt              = Angle(23.439292 * deg),
             .rotationRate           = AngularVelocity(360.98564736629 * deg / day),
             .siderealPeriod         = Time(365.256 * day),
             .semimajorAxis          = Distance(1.00000261 * au),
             .eccentricity           = Unitless(0.01671123 * one),
             .inclination            = Angle(-0.00001531 * deg),
             .rightAscension         = Angle(0.0 * deg),
             .longitudeOfPerigee     = Angle(102.93768193 * deg),
             .meanLongitude          = Angle(100.46457166 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00000562 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00004392 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.01294668 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.32327364 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(35999.37244981 * deg / JulianCentury) };
}

/**
 * @brief Find the atmospheric density at a given date and altitude using the US Standard Atmosphere 1976 model.
 *
 * @param date The date for which to find the atmospheric density.
 * @param altitude The altitude at which to find the atmospheric density.
 * @return Density The atmospheric density at the given date and altitude.
 * @note Numbers for this model are pulled from Vallado, 5th ed.
 * @note Full specialisation (with atmosphere model dispatch) is in atmosphere.hpp.
 */

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

/**
 * @brief Get the position of the Earth at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the position of the Earth.
 * @return RadiusVector<frames::earth_barycenter::icrf> The position of the Earth at the given date.
 */
template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Earth, axes::icrf)>
    get_position_at<planets::Earth>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Earth, axes::icrf);
    return get_position_at_impl<ephemerides::EarthFromEmbEphemerisTable, frame>(date);
}

/**
 * @brief Get the velocity of the Earth at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the velocity of the Earth.
 * @return VelocityVector<frames::earth_barycenter::icrf> The velocity of the Earth at the given date.
 */
template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Earth, axes::icrf)>
    get_velocity_at<planets::Earth>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Earth, axes::icrf);
    return get_velocity_at_impl<ephemerides::EarthFromEmbEphemerisTable, frame>(date);
}

/**
 * @brief Get the acceleration of the Earth at a specific date in the ICRF frame using JPL DE430 ephemeris data.
 *
 * @param date The date for which to find the acceleration of the Earth.
 * @return AccelerationVector<frames::earth_barycenter::icrf> The acceleration of the Earth at the given date.
 */
template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Earth, axes::icrf)>
    get_acceleration_at<planets::Earth>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Earth, axes::icrf);
    return get_acceleration_at_impl<ephemerides::EarthFromEmbEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea