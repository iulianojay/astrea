

# File Earth.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Earth**](dir_0d926747df7aa4605536658442a7f1d2.md) **>** [**Earth.hpp**](Earth_8hpp.md)

[Go to the documentation of this file](Earth_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/astro.macros.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
#include <astro/ephemerides/Earth/EarthFromEmbEphemerisTable.hpp>
#include <astro/ephemerides/Earth/EmbEphemerisTable.hpp>
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

enum class EarthAtmosphereModel { JACHIA_ROBERTS, NRLMSISE00, DTM2000, HARRIS_PRIESTER };

struct EarthParameters {
    EarthAtmosphereModel atmosphereModel = EarthAtmosphereModel::JACHIA_ROBERTS; 
};

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS
// SPICE ephemeris data for Earth is relative to the Earth-Moon barycenter, so we set the parent frame accordingly.
inline constexpr struct Earth final : CelestialBody<"Earth", barycenters::EarthMoonBarycenter> {
} Earth;
#else
inline constexpr struct Earth final : CelestialBody<"Earth", barycenters::SolarSystemBarycenter> {
} Earth;
#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Earth>()
{
    using namespace mp_units;
    using astrea::units::unit_symbols::jc;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::deg;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return {
        .type                   = CelestialBodyType::PLANET,
        .referenceDate          = Date(J2000),
        .mu                     = GravParam(398600.44189 * pow<3>(km) / pow<2>(s)),
        .mass                   = Mass(5.97 * (mag_power<10, 24> * kg)),
        .equitorialRadius       = Distance(6378.137 * km),
        .polarRadius            = Distance(6356.75538082 * km),
        .crashRadius            = Distance(6478.1 * km),
        .sphereOfInfluence      = Distance(0.092449582665046 * au),
        .j2                     = Unitless(0.00108262982 * one),
        .j3                     = Unitless(-0.0000025323 * one),
        .axialTilt              = Angle(23.439292 * deg),
        .rotationRate           = AngularVelocity(360.98564736629 * deg / day),
        .siderealPeriod         = Time(365.256 * day),
        .semimajorAxis          = Distance(1.00000261 * au),
        .eccentricity           = Unitless(0.01671123 * one),
        .inclination            = Angle(-0.00001531 * deg),
        .rightAscension         = Angle(0.0 * deg),
        .longitudeOfPerigee     = Angle(102.93768193 * deg),
        .meanLongitude          = Angle(100.46457166 * deg),
        .semimajorAxisRate      = InterplanetaryVelocity(0.00000562 * au / jc),
        .eccentricityRate       = BodyUnitlessPerTime(-0.00004392 * one / jc),
        .inclinationRate        = BodyAngularVelocity(-0.01294668 * deg / jc),
        .rightAscensionRate     = BodyAngularVelocity(0.0 * deg / jc),
        .longitudeOfPerigeeRate = BodyAngularVelocity(0.32327364 * deg / jc),
        .meanLongitudeRate      = BodyAngularVelocity(35999.37244981 * deg / jc),
        .gravityCoefficientFile = _ASTRO_GRAV_DATA_ROOT_ "/Earth/EGM2008_to2190_ZeroTide_mod.txt" // normalized
        // .gravityCoefficientFile = _ASTRO_GRAV_DATA_ROOT_ "/Earth/WGS84" // normalized
        // .gravityCoefficientFile = _ASTRO_GRAV_DATA_ROOT_ "/Earth/NASA_6DoF" // normalized - only goes to 8x8
    };
}

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Earth, axes::icrf)>
    get_position_at<planets::Earth>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Earth, axes::icrf);
    return get_position_at_impl<ephemerides::EarthFromEmbEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Earth, axes::icrf)>
    get_velocity_at<planets::Earth>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Earth, axes::icrf);
    return get_velocity_at_impl<ephemerides::EarthFromEmbEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Earth, axes::icrf)>
    get_acceleration_at<planets::Earth>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Earth, axes::icrf);
    return get_acceleration_at_impl<ephemerides::EarthFromEmbEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_EARTH_EPHEMERIS

} // namespace astro
} // namespace astrea
```


