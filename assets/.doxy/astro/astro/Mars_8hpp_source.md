

# File Mars.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Mars**](dir_03ada0e9bf55f03b35fb491b4c546571.md) **>** [**Mars.hpp**](Mars_8hpp.md)

[Go to the documentation of this file](Mars_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <map>

#include <astro/astro.fwd.hpp>
#include <astro/astro.macros.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_MARS_EPHEMERIS
#include <astro/ephemerides/Mars/MarsEphemerisTable.hpp>
#endif // ASTREA_BUILD_MARS_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

inline constexpr struct Mars final : CelestialBody<"Mars", barycenters::SolarSystemBarycenter> {
} Mars;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Mars>()
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
             .mu                     = GravParam(42828.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.642 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(3396.2 * km),
             .polarRadius            = Distance(3376.2 * km),
             .crashRadius            = Distance(3496.2 * km),
             .sphereOfInfluence      = Distance(0.057732173855358 * au),
             .j2                     = Unitless(1960.45e-6 * one),
             .j3                     = Unitless(0.000036 * one),
             .axialTilt              = Angle(25.19 * deg),
             .rotationRate           = AngularVelocity(350.8928680212322 * deg / day),
             .siderealPeriod         = Time(686.980 * day),
             .semimajorAxis          = Distance(1.52371034 * au),
             .eccentricity           = Unitless(0.09339410 * one),
             .inclination            = Angle(1.84969142 * deg),
             .rightAscension         = Angle(49.55953891 * deg),
             .longitudeOfPerigee     = Angle(-23.94362959 * deg),
             .meanLongitude          = Angle(-4.55343205 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00001847 * au / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.00007882 * one / jc),
             .inclinationRate        = BodyAngularVelocity(-0.00813131 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(-0.29257343 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.44441088 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(19140.30268499 * deg / jc),
             // https://pds-geosciences.wustl.edu/mro/mro-m-rss-5-sdp-v1/mrors_1xxx/data/shadr/ - normalized?
             .gravityCoefficientFile = _ASTRO_GRAV_DATA_ROOT_ "/Mars/jgmro_120f_sha.tab" };
}

#ifdef ASTREA_BUILD_MARS_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Mars, axes::icrf)>
    get_position_at<planets::Mars>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mars, axes::icrf);
    return get_position_at_impl<ephemerides::MarsEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Mars, axes::icrf)>
    get_velocity_at<planets::Mars>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mars, axes::icrf);
    return get_velocity_at_impl<ephemerides::MarsEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Mars, axes::icrf)>
    get_acceleration_at<planets::Mars>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mars, axes::icrf);
    return get_acceleration_at_impl<ephemerides::MarsEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_MARS_EPHEMERIS

} // namespace astro
} // namespace astrea
```


