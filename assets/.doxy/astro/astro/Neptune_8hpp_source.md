

# File Neptune.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Neptune**](dir_ec69e1477d245828e261b3b2dcdeacfc.md) **>** [**Neptune.hpp**](Neptune_8hpp.md)

[Go to the documentation of this file](Neptune_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS
#include <astro/ephemerides/Neptune/NeptuneEphemerisTable.hpp>
#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

inline constexpr struct Neptune final : CelestialBody<"Neptune", barycenters::SolarSystemBarycenter> {
} Neptune;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Neptune>()
{
    using namespace mp_units;
    using astrea::units::unit_symbols::jc;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::PLANET,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2433282.5 })),
             .mu                     = GravParam(6836529.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(102.0 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(24764.0 * km),
             .polarRadius            = Distance(24341.0 * km),
             .crashRadius            = Distance(24764.0 * km),
             .sphereOfInfluence      = Distance(8.651147189326089 * au),
             .j2                     = Unitless(3411e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(28.32 * deg),
             .rotationRate           = AngularVelocity(536.3128491620112 * deg / day),
             .siderealPeriod         = Time(60189 * day),
             .semimajorAxis          = Distance(30.06992276 * au),
             .eccentricity           = Unitless(0.00859048 * one),
             .inclination            = Angle(1.77004347 * deg),
             .rightAscension         = Angle(131.78422574 * deg),
             .longitudeOfPerigee     = Angle(44.96476227 * deg),
             .meanLongitude          = Angle(-55.12002969 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00026291 * au / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.00005105 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.00035372 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(-0.00508664 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(-0.32241464 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(218.45945325 * deg / jc) };
}

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Neptune, axes::icrf)>
    get_position_at<planets::Neptune>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Neptune, axes::icrf);
    return get_position_at_impl<ephemerides::NeptuneEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Neptune, axes::icrf)>
    get_velocity_at<planets::Neptune>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Neptune, axes::icrf);
    return get_velocity_at_impl<ephemerides::NeptuneEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Neptune, axes::icrf)>
    get_acceleration_at<planets::Neptune>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Neptune, axes::icrf);
    return get_acceleration_at_impl<ephemerides::NeptuneEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

template <>
inline constexpr CoefficientPack get_linear_expansion_coefficients<planets::Neptune>()
{
    using astrea::units::unit_symbols::jc;
    using mp_units::si::unit_symbols::rad;
    return std::make_tuple(-0.00041348 * rad / (jc * jc), 0.68346318 * rad, -0.10162547 * rad, 7.67025000 * rad / jc);
}

} // namespace astro
} // namespace astrea
```


