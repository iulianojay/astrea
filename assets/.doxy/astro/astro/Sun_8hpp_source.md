

# File Sun.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Sun**](dir_15326b41008c26450ba4ed6847b82388.md) **>** [**Sun.hpp**](Sun_8hpp.md)

[Go to the documentation of this file](Sun_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_SUN_EPHEMERIS
#include <astro/ephemerides/Sun/SunEphemerisTable.hpp>
#endif // ASTREA_BUILD_SUN_EPHEMERIS

namespace astrea {
namespace astro {

namespace star {

inline constexpr struct Sun final : CelestialBody<"Sun", barycenters::SolarSystemBarycenter> {
} Sun;

} // namespace star

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<star::Sun>()
{
    using namespace mp_units;
    using astrea::units::unit_symbols::jc;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::STAR,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2451544.5 })),
             .mu                     = GravParam(1.32712e11 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(1988500.0 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(695700.0 * km),
             .polarRadius            = Distance(695700.0 * km),
             .crashRadius            = Distance(795700.0 * km),
             .sphereOfInfluence      = Distance(1.0e18 * km),
             .j2                     = Unitless(0.2e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(0.0 * deg / day),
             .siderealPeriod         = Time(0.0 * day),
             .semimajorAxis          = Distance(0.0 * km),
             .eccentricity           = Unitless(0.0 * one),
             .inclination            = Angle(0.0 * deg),
             .rightAscension         = Angle(0.0 * deg),
             .longitudeOfPerigee     = Angle(0.0 * deg),
             .meanLongitude          = Angle(0.0 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(0.0 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.0 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(0.0 * deg / jc) };
}

#ifdef ASTREA_BUILD_SUN_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(star::Sun, axes::icrf)> get_position_at<star::Sun>(const Date& date)
{
    constexpr auto frame = get_parent_frame(star::Sun, axes::icrf);
    return get_position_at_impl<ephemerides::SunEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(star::Sun, axes::icrf)> get_velocity_at<star::Sun>(const Date& date)
{
    constexpr auto frame = get_parent_frame(star::Sun, axes::icrf);
    return get_velocity_at_impl<ephemerides::SunEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(star::Sun, axes::icrf)>
    get_acceleration_at<star::Sun>(const Date& date)
{
    constexpr auto frame = get_parent_frame(star::Sun, axes::icrf);
    return get_acceleration_at_impl<ephemerides::SunEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_SUN_EPHEMERIS

} // namespace astro
} // namespace astrea
```


