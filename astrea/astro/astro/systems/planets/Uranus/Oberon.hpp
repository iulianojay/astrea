/**
 * @file Oberon.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Oberon class.
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/planets/Uranus/Uranus.hpp>

namespace astrea {
namespace astro {
namespace planets {

/**
 * @class Oberon
 * @brief Represents the Oberon celestial body.
 *
 * This class provides properties and methods specific to Oberon, including its physical and orbital parameters.
 */
inline constexpr struct Oberon : CelestialBody<"Oberon", Uranus> {
} Oberon;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Oberon>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2444239.5 })),
             .mu                     = GravParam(192.4 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00288 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(761.4 * km),
             .polarRadius            = Distance(761.4 * km),
             .crashRadius            = Distance(761.4 * km),
             .sphereOfInfluence      = Distance(9.42735725907e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(26.739489189595904 * deg / day),
             .siderealPeriod         = Time(13.4632 * day),
             .semimajorAxis          = Distance(583.50e3 * km),
             .eccentricity           = Unitless(0.0014 * one),
             .inclination            = Angle(0.07 * deg),
             .rightAscension         = Angle(279.771 * deg),
             .longitudeOfPerigee     = Angle(24.171 * deg),
             .meanLongitude          = Angle(307.259 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(663356.7 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(1465734.12 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(3517441116.43 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea