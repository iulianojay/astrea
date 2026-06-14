

# File Jupiter.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Jupiter**](dir_925acfda302d4aa496e86fec42e06785.md) **>** [**Jupiter.hpp**](Jupiter_8hpp.md)

[Go to the documentation of this file](Jupiter_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/barycenters.hpp>
#include <astro/types/typedefs.hpp>

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS
#include <ephemerides/Jupiter/JupiterEphemerisTable.hpp>
#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

namespace astrea {
namespace astro {

namespace planets {

inline constexpr struct Jupiter final : CelestialBody<"Jupiter", barycenters::SolarSystemBarycenter> {
} Jupiter;

} // namespace planets

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<planets::Jupiter>()
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
             .mu                     = GravParam(126686535.0 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(1898.0 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(71492.0 * km),
             .polarRadius            = Distance(66854.0 * km),
             .crashRadius            = Distance(71492.0 * km),
             .sphereOfInfluence      = Distance(0.057732173855358 * au),
             .j2                     = Unitless(14736e-6 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.13 * deg),
             .rotationRate           = AngularVelocity(350.8928680212322 * deg / day),
             .siderealPeriod         = Time(4332.589 * day),
             .semimajorAxis          = Distance(5.20288700 * au),
             .eccentricity           = Unitless(0.04838624 * one),
             .inclination            = Angle(1.30439695 * deg),
             .rightAscension         = Angle(100.47390909 * deg),
             .longitudeOfPerigee     = Angle(14.72847983 * deg),
             .meanLongitude          = Angle(34.39644051 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(-0.00011607 * au / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(-0.00013253 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(-0.00183714 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(0.20469106 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(0.21252668 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(3034.74612775 * deg / JulianCentury) };
}

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS

template <>
inline constexpr CartesianVector<Distance, get_parent_frame(planets::Jupiter, axes::icrf)>
    get_position_at<planets::Jupiter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Jupiter, axes::icrf);
    return get_position_at_impl<ephemerides::JupiterEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Velocity, get_parent_frame(planets::Jupiter, axes::icrf)>
    get_velocity_at<planets::Jupiter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Jupiter, axes::icrf);
    return get_velocity_at_impl<ephemerides::JupiterEphemerisTable, frame>(date);
}

template <>
inline constexpr CartesianVector<Acceleration, get_parent_frame(planets::Jupiter, axes::icrf)>
    get_acceleration_at<planets::Jupiter>(const Date& date)
{
    constexpr auto frame = get_parent_frame(planets::Jupiter, axes::icrf);
    return get_acceleration_at_impl<ephemerides::JupiterEphemerisTable, frame>(date);
}

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

template <>
inline constexpr CoefficientPack get_linear_expansion_coefficients<planets::Jupiter>()
{
    using mp_units::angular::unit_symbols::rad;
    return std::make_tuple(-0.00012452 * rad / (JulianCentury * JulianCentury), 0.06064060 * rad, -0.35635438 * rad, 38.35125000 * rad / JulianCentury);
}

} // namespace astro
} // namespace astrea
```


