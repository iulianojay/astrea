

# File Europa.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Jupiter**](dir_925acfda302d4aa496e86fec42e06785.md) **>** [**Europa.hpp**](Europa_8hpp.md)

[Go to the documentation of this file](Europa_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Europa final : CelestialBody<"Europa", planets::Jupiter> {
} Europa;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Europa>()
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
             .mu                     = GravParam(3202.7 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.04800 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(1560.8 * km),
             .polarRadius            = Distance(1560.8 * km),
             .crashRadius            = Distance(1560.8 * km),
             .sphereOfInfluence      = Distance(9.72669393872e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.146 * deg),
             .rotationRate           = AngularVelocity(101.3747257602471 * deg / day),
             .siderealPeriod         = Time(3.551181 * day),
             .semimajorAxis          = Distance(671.1e3 * km),
             .eccentricity           = Unitless(0.009 * one),
             .inclination            = Angle(0.47 * deg),
             .rightAscension         = Angle(219.106 * deg),
             .longitudeOfPerigee     = Angle(308.076 * deg),
             .meanLongitude          = Angle(479.092 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(4293665.52 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(97263536.4 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(13427026021.5 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


