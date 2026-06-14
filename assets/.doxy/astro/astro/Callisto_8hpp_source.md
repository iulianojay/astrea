

# File Callisto.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Jupiter**](dir_925acfda302d4aa496e86fec42e06785.md) **>** [**Callisto.hpp**](Callisto_8hpp.md)

[Go to the documentation of this file](Callisto_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Callisto final : CelestialBody<"Callisto", planets::Jupiter> {
} Callisto;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Callisto>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(JulianDate(JulianDateClock::duration{ 2450464.5 })),
             .mu                     = GravParam(7179.3 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.10759 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(2410.3 * km),
             .polarRadius            = Distance(2410.3 * km),
             .crashRadius            = Distance(2410.3 * km),
             .sphereOfInfluence      = Distance(0.003768525014695 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.486 * deg),
             .rotationRate           = AngularVelocity(21.571072760007375 * deg / day),
             .siderealPeriod         = Time(16.68901 * day),
             .semimajorAxis          = Distance(1882.7e3 * km),
             .eccentricity           = Unitless(0.007 * one),
             .inclination            = Angle(0.19 * deg),
             .rightAscension         = Angle(298.848 * deg),
             .longitudeOfPerigee     = Angle(351.491 * deg),
             .meanLongitude          = Angle(532.899 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(382503.98 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(1012394.6 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(2837392757.1 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea
```


