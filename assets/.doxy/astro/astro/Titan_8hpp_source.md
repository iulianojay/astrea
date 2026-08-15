

# File Titan.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Saturn**](dir_7fd613539f7980532282f5cbc20c34d1.md) **>** [**Titan.hpp**](Titan_8hpp.md)

[Go to the documentation of this file](Titan_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <map>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Saturn/Saturn.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Titan final : CelestialBody<"Titan", planets::Saturn> {
} Titan;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Titan>()
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
             .mu                     = GravParam(8978.1 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.13455 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2575.0 * km),
             .polarRadius            = Distance(2575.0 * km),
             .crashRadius            = Distance(2575.0 * km),
             .sphereOfInfluence      = Distance(0.004333361603448 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(27.359 * deg),
             .rotationRate           = AngularVelocity(22.577014429408919 * deg / day),
             .siderealPeriod         = Time(15.94542 * day),
             .semimajorAxis          = Distance(1221.83e3 * km),
             .eccentricity           = Unitless(0.0292 * one),
             .inclination            = Angle(0.33 * deg),
             .rightAscension         = Angle(28.060 * deg),
             .longitudeOfPerigee     = Angle(208.592 * deg),
             .meanLongitude          = Angle(371.902 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(183934.15 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(551990.5 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(2969198512.13 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


