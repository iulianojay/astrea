

# File Moon.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Earth**](dir_0d926747df7aa4605536658442a7f1d2.md) **>** [**Moon.hpp**](Moon_8hpp.md)

[Go to the documentation of this file](Moon_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/astro.macros.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <astro/ephemerides/Earth/MoonEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Moon final : CelestialBody<"Moon", planets::Earth> {
} Moon;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Moon>()
{
    using namespace mp_units;
    using astrea::units::unit_symbols::jc;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(4902.8 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.073 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(1737.5 * km),
             .polarRadius            = Distance(1736.0 * km),
             .crashRadius            = Distance(1737.5 * km),
             .sphereOfInfluence      = Distance(0.006602718630998 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(1.543 * deg),
             .rotationRate           = AngularVelocity(13.176195007686115 * deg / day),
             .siderealPeriod         = Time(27.3220 * day),
             .semimajorAxis          = Distance(380318 * km),
             .eccentricity           = Unitless(0.063843 * one),
             .inclination            = Angle(5.28619 * deg),
             .rightAscension         = Angle(98.13908 * deg),
             .longitudeOfPerigee     = Angle(179.16058 * deg),
             .meanLongitude          = Angle(135.89122 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(6967741.9 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(28578547 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(1761137860.75 * deg / jc),
             // https://pds-geosciences.wustl.edu/grail/grail-l-lgrs-5-rdr-v1/grail_1001/shadr/ - normalized?
             .gravityCoefficientFile = _ASTRO_GRAV_DATA_ROOT_ "/Earth/jggrx_0420a_sha.tab" };
}

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(moons::Moon, axes::icrf)> get_position_at<moons::Moon>(const Date& date)
{
    constexpr auto frame = get_parent_frame(moons::Moon, axes::icrf);
    return get_position_at_impl<ephemerides::MoonEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(moons::Moon, axes::icrf)> get_velocity_at<moons::Moon>(const Date& date)
{
    constexpr auto frame = get_parent_frame(moons::Moon, axes::icrf);
    return get_velocity_at_impl<ephemerides::MoonEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(moons::Moon, axes::icrf)>
    get_acceleration_at<moons::Moon>(const Date& date)
{
    constexpr auto frame = get_parent_frame(moons::Moon, axes::icrf);
    return get_acceleration_at_impl<ephemerides::MoonEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea
```


