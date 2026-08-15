

# File Phobos.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Mars**](dir_03ada0e9bf55f03b35fb491b4c546571.md) **>** [**Phobos.hpp**](Phobos_8hpp.md)

[Go to the documentation of this file](Phobos_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Mars/Mars.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Phobos final : CelestialBody<"Phobos", planets::Mars> {
} Phobos;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Phobos>()
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
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2433282.5 })),
             .mu                     = GravParam(9.85e-5 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(2.4e-9 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(6.2 * km),
             .polarRadius            = Distance(5.1 * km),
             .crashRadius            = Distance(6.25 * km),
             .sphereOfInfluence      = Distance(9.98573371442e-07 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(1128.844 * deg / day),
             .siderealPeriod         = Time(1.26244 * day),
             .semimajorAxis          = Distance(23459.0 * km),
             .eccentricity           = Unitless(0.0005 * one),
             .inclination            = Angle(1.79 * deg),
             .rightAscension         = Angle(24.525 * deg),
             .longitudeOfPerigee     = Angle(285.254 * deg),
             .meanLongitude          = Angle(610.583 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(2376381 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(7111440.9 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(37503046910.7 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


