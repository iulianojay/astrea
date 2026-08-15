

# File Ganymede.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Jupiter**](dir_925acfda302d4aa496e86fec42e06785.md) **>** [**Ganymede.hpp**](Ganymede_8hpp.md)

[Go to the documentation of this file](Ganymede_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Ganymede final : CelestialBody<"Ganymede", planets::Jupiter> {
} Ganymede;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Ganymede>()
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
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2450464.5 })),
             .mu                     = GravParam(9887.8 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.14819 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2631.2 * km),
             .polarRadius            = Distance(2631.2 * km),
             .crashRadius            = Distance(2631.2 * km),
             .sphereOfInfluence      = Distance(0.002435315183093 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.198 * deg),
             .rotationRate           = AngularVelocity(50.317608940768210 * deg / day),
             .siderealPeriod         = Time(7.154553 * day),
             .semimajorAxis          = Distance(1070.4e3 * km),
             .eccentricity           = Unitless(0.001 * one),
             .inclination            = Angle(0.18 * deg),
             .rightAscension         = Angle(63.552 * deg),
             .longitudeOfPerigee     = Angle(255.969 * deg),
             .meanLongitude          = Angle(573.509 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(976977.7 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(3016348.9 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(6619278519.62 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


