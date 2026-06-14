

# File Venus.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Venus**](dir_8fa374767bd61918cc8bb3b53abef633.md) **>** [**Venus.hpp**](Venus_8hpp.md)

[Go to the documentation of this file](Venus_8hpp.md)


```C++

#pragma once

#include <map>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS
#include <ephemerides/Venus/VenusEphemerisTable.hpp>
#endif // ASTREA_BUILD_VENUS_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

inline constexpr struct Venus final : CelestialBody<"Venus", barycenters::SolarSystemBarycenter> {
} Venus;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Venus>()
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

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Venus, axes::icrf)>
    get_position_at<planets::Venus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Venus, axes::icrf);
    return get_position_at_impl<ephemerides::VenusEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Venus, axes::icrf)>
    get_velocity_at<planets::Venus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Venus, axes::icrf);
    return get_velocity_at_impl<ephemerides::VenusEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Venus, axes::icrf)>
    get_acceleration_at<planets::Venus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Venus, axes::icrf);
    return get_acceleration_at_impl<ephemerides::VenusEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_VENUS_EPHEMERIS

} // namespace astro
} // namespace astrea
```


