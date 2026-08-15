

# File Io.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Jupiter**](dir_925acfda302d4aa496e86fec42e06785.md) **>** [**Io.hpp**](Io_8hpp.md)

[Go to the documentation of this file](Io_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Jupiter/Jupiter.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Io final : CelestialBody<"Io", planets::Jupiter> {
} Io;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Io>()
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
             .mu                     = GravParam(5959.9 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.08932 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(1821.5 * km),
             .polarRadius            = Distance(1821.5 * km),
             .crashRadius            = Distance(1841.5 * km),
             .sphereOfInfluence      = Distance(7.83731997166e-04 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(3.13 * deg),
             .rotationRate           = AngularVelocity(203.4889307674133 * deg / day),
             .siderealPeriod         = Time(1.769138 * day),
             .semimajorAxis          = Distance(421.8e3 * km),
             .eccentricity           = Unitless(0.004 * one),
             .inclination            = Angle(0.04 * deg),
             .rightAscension         = Angle(43.977 * deg),
             .longitudeOfPerigee     = Angle(128.106 * deg),
             .meanLongitude          = Angle(470.127 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / jc),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / jc),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / jc),
             .rightAscensionRate     = BodyAngularVelocity(17466307.28 * deg / jc),
             .longitudeOfPerigeeRate = BodyAngularVelocity(97220153.4 * deg / jc),
             .meanLongitudeRate      = BodyAngularVelocity(26853983280.3 * deg / jc) };
}

} // namespace astro
} // namespace astrea
```


