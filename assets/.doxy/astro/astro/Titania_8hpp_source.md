

# File Titania.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Uranus**](dir_8fcaafb82204ae43552237a688fd4e7d.md) **>** [**Titania.hpp**](Titania_8hpp.md)

[Go to the documentation of this file](Titania_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Uranus/Uranus.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Titania final : CelestialBody<"Titania", planets::Uranus> {
} Titania;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Titania>()
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
             .mu                     = GravParam(228.2 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00342 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(788.9 * km),
             .polarRadius            = Distance(788.9 * km),
             .crashRadius            = Distance(1568.9 * km),
             .sphereOfInfluence      = Distance(7.55070955998e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(0.0 * deg),
             .rotationRate           = AngularVelocity(41.351424275146869 * deg / day),
             .siderealPeriod         = Time(8.70586 * day),
             .semimajorAxis          = Distance(436.30e3 * km),
             .eccentricity           = Unitless(0.0011 * one),
             .inclination            = Angle(0.08 * deg),
             .rightAscension         = Angle(99.771 * deg),
             .longitudeOfPerigee     = Angle(24.17 * deg),
             .meanLongitude          = Angle(48.785 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(663360.1 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(1465712.68 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(5438764533.33 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


