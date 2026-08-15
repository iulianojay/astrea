

# File Uranus.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Uranus**](dir_8fcaafb82204ae43552237a688fd4e7d.md) **>** [**Uranus.hpp**](Uranus_8hpp.md)

[Go to the documentation of this file](Uranus_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS
#include <astro/ephemerides/Uranus/UranusEphemerisTable.hpp>
#endif // ASTREA_BUILD_URANUS_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

inline constexpr struct Uranus final : CelestialBody<"Uranus", barycenters::SolarSystemBarycenter> {
} Uranus;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Uranus>()
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
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(5793939.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(86.8 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(25559.0 * km),
             .polarRadius            = Distance(24973.0 * km),
             .crashRadius            = Distance(25559.0 * km),
             .sphereOfInfluence      = Distance(5.176385869757780 * au),
             .j2                     = Unitless(3343.43e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(82.23 * deg),
             .rotationRate           = AngularVelocity(-501.1600928074246 * deg / day),
             .siderealPeriod         = Time(30685.4 * day),
             .semimajorAxis          = Distance(19.18916464 * au),
             .eccentricity           = Unitless(0.04725744 * one),
             .inclination            = Angle(0.77263783 * deg),
             .rightAscension         = Angle(74.01692503 * deg),
             .longitudeOfPerigee     = Angle(170.95427630 * deg),
             .meanLongitude          = Angle(313.23810451 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(-0.00196176 * au / jc),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00004397 * one / jc),
             .inclinationRate        = BodyAngularVelocity(-0.00242939 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(0.04240589 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.40805281 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(428.48202785 * deg / jc) };
}

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Uranus, axes::icrf)>
    get_position_at<planets::Uranus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Uranus, axes::icrf);
    return get_position_at_impl<ephemerides::UranusEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Uranus, axes::icrf)>
    get_velocity_at<planets::Uranus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Uranus, axes::icrf);
    return get_velocity_at_impl<ephemerides::UranusEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Uranus, axes::icrf)>
    get_acceleration_at<planets::Uranus>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Uranus, axes::icrf);
    return get_acceleration_at_impl<ephemerides::UranusEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

template <>
inline constexpr CoefficientPack get_linear_expansion_coefficients<planets::Uranus>()
{
    using astrea::units::unit_symbols::jc;
    using mp_units::si::unit_symbols::rad;
    return std::make_tuple(0.00058331 * rad / (jc * jc), -0.97731848 * rad, 0.17689245 * rad, 7.67025000 * rad / jc);
}

} // namespace astro
} // namespace astrea
```


