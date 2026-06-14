

# File Deimos.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Mars**](dir_03ada0e9bf55f03b35fb491b4c546571.md) **>** [**Deimos.hpp**](Deimos_8hpp.md)

[Go to the documentation of this file](Deimos_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Mars/Mars.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Deimos final : CelestialBody<"Deimos", planets::Mars> {
} Deimos;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Deimos>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2433282.5 })),
             .mu                     = GravParam(7.112e-4 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(10.6e-9 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(11.1 * km),
             .polarRadius            = Distance(9.1 * km),
             .crashRadius            = Distance(11.15 * km),
             .sphereOfInfluence      = Distance(7.23133636677e-07 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(25.199 * deg),
             .rotationRate           = AngularVelocity(27092.28308927283 * deg / day),
             .siderealPeriod         = Time(0.31891 * day),
             .semimajorAxis          = Distance(9378.0 * km),
             .eccentricity           = Unitless(0.0151 * one),
             .inclination            = Angle(1.08 * deg),
             .rightAscension         = Angle(207.784 * deg),
             .longitudeOfPerigee     = Angle(357.841 * deg),
             .meanLongitude          = Angle(448.9 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(57302029 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(171830131 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(148603627216.0 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea
```


