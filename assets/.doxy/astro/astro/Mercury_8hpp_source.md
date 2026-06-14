

# File Mercury.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Mercury**](dir_3b6d9a919e6250ccdc1fa4c9fa0fff50.md) **>** [**Mercury.hpp**](Mercury_8hpp.md)

[Go to the documentation of this file](Mercury_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS
#include <ephemerides/Mercury/MercuryEphemerisTable.hpp>
#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

inline constexpr struct Mercury final : CelestialBody<"Mercury", barycenters::SolarSystemBarycenter> {
} Mercury;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Mercury>()
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
             .mu                     = GravParam(22032.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.330 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2439.7 * km),
             .polarRadius            = Distance(2439.7 * km),
             .crashRadius            = Distance(2464.7 * km),
             .sphereOfInfluence      = Distance(0.011239389492058 * au),
             .j2                     = Unitless(60.0e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.034 * deg),
             .rotationRate           = AngularVelocity(6.138107416879796 * deg / day),
             .siderealPeriod         = Time(87.969 * day),
             .semimajorAxis          = Distance(0.38709927 * au),
             .eccentricity           = Unitless(0.20563593 * one),
             .inclination            = Angle(7.00497902 * deg),
             .rightAscension         = Angle(48.33076593 * deg),
             .longitudeOfPerigee     = Angle(77.45779628 * deg),
             .meanLongitude          = Angle(252.25032350 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.00000037 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.00001906 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00594749 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(-0.12534081 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.16047689 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(149472.67411175 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Mercury, axes::icrf)>
    get_position_at<planets::Mercury>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mercury, axes::icrf);
    return get_position_at_impl<ephemerides::MercuryEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Mercury, axes::icrf)>
    get_velocity_at<planets::Mercury>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mercury, axes::icrf);
    return get_velocity_at_impl<ephemerides::MercuryEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Mercury, axes::icrf)>
    get_acceleration_at<planets::Mercury>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Mercury, axes::icrf);
    return get_acceleration_at_impl<ephemerides::MercuryEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS

} // namespace astro
} // namespace astrea
```


