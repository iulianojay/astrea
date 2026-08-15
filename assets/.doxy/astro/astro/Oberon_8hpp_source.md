

# File Oberon.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Uranus**](dir_8fcaafb82204ae43552237a688fd4e7d.md) **>** [**Oberon.hpp**](Oberon_8hpp.md)

[Go to the documentation of this file](Oberon_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Uranus/Uranus.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Oberon final : CelestialBody<"Oberon", planets::Uranus> {
} Oberon;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Oberon>()
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
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2444239.5 })),
             .mu                     = GravParam(192.4 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00288 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(761.4 * km),
             .polarRadius            = Distance(761.4 * km),
             .crashRadius            = Distance(761.4 * km),
             .sphereOfInfluence      = Distance(9.42735725907e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(26.739489189595904 * deg / day),
             .siderealPeriod         = Time(13.4632 * day),
             .semimajorAxis          = Distance(583.50e3 * km),
             .eccentricity           = Unitless(0.0014 * one),
             .inclination            = Angle(0.07 * deg),
             .rightAscension         = Angle(279.771 * deg),
             .longitudeOfPerigee     = Angle(24.171 * deg),
             .meanLongitude          = Angle(307.259 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(663356.7 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(1465734.12 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(3517441116.43 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


