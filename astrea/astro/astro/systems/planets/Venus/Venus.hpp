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
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS
#include <ephemerides/Venus/VenusEphemerisTable.hpp>
#endif // ASTREA_BUILD_VENUS_EPHEMERIS

namespace astrea {
namespace astro {

// Forward-declare frame types to avoid circular include with frames.hpp
namespace frames {
namespace solar_system_barycenter {
struct icrf;
}
} // namespace frames

namespace planets {

/**
 * @class Venus
 * @brief Represents the Venus celestial body.
 *
 * This class provides properties and methods specific to Venus, including its physical and orbital parameters.
 */
inline constexpr struct Venus : CelestialBody<"Venus", barycenters::SolarSystemBarycenter> {
} Venus;

} // namespace planets

template <>
inline constexpr CelestialBodyParameters get_celestial_body_parameters<planets::Venus>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::unit_symbols::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date("2000-01-01 12:00:00"),
             .mu                     = GravParam(324860.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(4.87 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(6051.8 * km),
             .polarRadius            = Distance(6051.8 * km),
             .crashRadius            = Distance(6301.8 * km),
             .sphereOfInfluence      = Distance(0.061640255733634 * au),
             .j2                     = Unitless(4.458e-6 * one),
             .j3                     = Unitless(-0.0000025323e-6 * one),
             .axialTilt              = Angle(2.64 * deg),
             .rotationRate           = AngularVelocity(-1.481329081370229 * deg / day),
             .siderealPeriod         = Time(224.701 * day),
             .semimajorAxis          = Distance(0.72333566 * au),
             .eccentricity           = Unitless(0.00677672 * one),
             .inclination            = Angle(3.39467605 * deg),
             .rightAscension         = Angle(76.67984255 * deg),
             .longitudeOfPerigee     = Angle(131.60246718 * deg),
             .meanLongitude          = Angle(181.97909950 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00000390 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00004107 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00078890 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(-0.27769418 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.00268329 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(58517.81538729 * deg / JulianCentury) };
}

/**
 * @brief Find the atmospheric density at a given altitude and date.
 *
 * This function overrides the base class method to provide atmospheric density specific to Venus.
 *
 * @param date The date for which to find the atmospheric density.
 * @param altitude The altitude above the surface of Venus.
 * @return Density The atmospheric density at the specified altitude and date.
 */
Density find_atmospheric_density<planets::Venus>(const Date& date, const Distance& altitude) const
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::m;

    // Altitude Conditions(TABLE 7-4, Vallado)
    static const std::map<Altitude, Density> venutianAtmosphere = {
        // km, kg/m^3
        { 3.0 * km, 5.53e1 * kg / (pow<3>(m)) },    { 6.0 * km, 4.75e1 * kg / (pow<3>(m)) },
        { 9.0 * km, 4.02e1 * kg / (pow<3>(m)) },    { 12.0 * km, 3.44e1 * kg / (pow<3>(m)) },
        { 15.0 * km, 2.91e1 * kg / (pow<3>(m)) },   { 18.0 * km, 2.46e1 * kg / (pow<3>(m)) },
        { 21.0 * km, 2.06e1 * kg / (pow<3>(m)) },   { 24.0 * km, 1.70e1 * kg / (pow<3>(m)) },
        { 27.0 * km, 1.405e1 * kg / (pow<3>(m)) },  { 30.0 * km, 1.115e1 * kg / (pow<3>(m)) },
        { 33.0 * km, 9.0 * kg / (pow<3>(m)) },      { 36.0 * km, 7.15 * kg / (pow<3>(m)) },
        { 39.0 * km, 5.15 * kg / (pow<3>(m)) },     { 42.0 * km, 4.34 * kg / (pow<3>(m)) },
        { 45.0 * km, 3.30 * kg / (pow<3>(m)) },     { 48.0 * km, 2.39 * kg / (pow<3>(m)) },
        { 51.0 * km, 1.88 * kg / (pow<3>(m)) },     { 54.0 * km, 1.38 * kg / (pow<3>(m)) },
        { 57.0 * km, 9.6e-1 * kg / (pow<3>(m)) },   { 60.0 * km, 6.2e-1 * kg / (pow<3>(m)) },
        { 70.0 * km, 1.2e-1 * kg / (pow<3>(m)) },   { 80.0 * km, 1.8e-2 * kg / (pow<3>(m)) },
        { 90.0 * km, 2.3e-3 * kg / (pow<3>(m)) },   { 100.0 * km, 3.1e-4 * kg / (pow<3>(m)) },
        { 110.0 * km, 4.4e-5 * kg / (pow<3>(m)) },  { 120.0 * km, 7.2e-6 * kg / (pow<3>(m)) },
        { 130.0 * km, 1.4e-6 * kg / (pow<3>(m)) },  { 140.0 * km, 3.0e-7 * kg / (pow<3>(m)) },
        { 150.0 * km, 8.0e-8 * kg / (pow<3>(m)) },  { 160.0 * km, 2.6e-8 * kg / (pow<3>(m)) },
        { 170.0 * km, 9.5e-9 * kg / (pow<3>(m)) },  { 180.0 * km, 4.0e-9 * kg / (pow<3>(m)) },
        { 190.0 * km, 1.9e-9 * kg / (pow<3>(m)) },  { 200.0 * km, 9.4e-10 * kg / (pow<3>(m)) },
        { 210.0 * km, 4.9e-10 * kg / (pow<3>(m)) }, { 220.0 * km, 2.6e-10 * kg / (pow<3>(m)) },
        { 230.0 * km, 1.4e-10 * kg / (pow<3>(m)) }, { 240.0 * km, 7.5e-11 * kg / (pow<3>(m)) },
        { 250.0 * km, 5.5e-11 * kg / (pow<3>(m)) }, { 260.0 * km, 4.1e-11 * kg / (pow<3>(m)) },
        { 270.0 * km, 2.2e-11 * kg / (pow<3>(m)) }, { 280.0 * km, 1.2e-11 * kg / (pow<3>(m)) },
        { 290.0 * km, 6.5e-12 * kg / (pow<3>(m)) }, { 300.0 * km, 3.5e-12 * kg / (pow<3>(m)) }
    };

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