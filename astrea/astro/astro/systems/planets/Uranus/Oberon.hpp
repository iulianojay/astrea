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
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planets {

static CelestialBodyParameters DEFAULT_OBERON_PARAMS{
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1980-01-01 00:00:00"),
    .mu = GravParam(192.4 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.00288 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(761.4 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(761.4 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(761.4 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(9.42735725907e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularVelocity(26.739489189595904 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(13.4632 * mp_units::non_si::day),
    .semimajorAxis          = Distance(583.50e3 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0014 * mp_units::one),
    .inclination            = Angle(0.07 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(279.771 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(24.171 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(307.259 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularVelocity(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularVelocity(663356.7 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularVelocity(1465734.12 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularVelocity(3517441116.43 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

/**
 * @class Oberon
 * @brief Represents the Oberon celestial body.
 *
 * This class provides properties and methods specific to Oberon, including its physical and orbital parameters.
 */
inline constexpr struct Oberon : CelestialBody<"Oberon", Uranus, DEFAULT_OBERON_PARAMS> {
} Oberon;

} // namespace planets
} // namespace astro
} // namespace astrea