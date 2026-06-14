

# File Triton.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Neptune**](dir_ec69e1477d245828e261b3b2dcdeacfc.md) **>** [**Triton.hpp**](Triton_8hpp.md)

[Go to the documentation of this file](Triton_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Neptune/Neptune.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Triton final : CelestialBody<"Triton", planets::Neptune> {
} Triton;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Triton>()
{
    using namespace mp_units;
    using mp_units::angular::unit_symbols::deg;
    using mp_units::iau::unit_symbols::au;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    return { .type                   = CelestialBodyType::MOON,
             .referenceDate          = Date(J2000),
             .mu                     = GravParam(1427.6 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.0214 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(1353.4 * km),
             .polarRadius            = Distance(1353.4 * km),
             .crashRadius            = Distance(1353.4 * km),
             .sphereOfInfluence      = Distance(0.001198560847624 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(28.33 * deg),
             .rotationRate           = AngularVelocity(61.257264516014864 * deg / day),
             .siderealPeriod         = Time(5.87685 * day),
             .semimajorAxis          = Distance(354.76e3 * km),
             .eccentricity           = Unitless(0.000016 * one),
             .inclination            = Angle(157.345 * deg),
             .rightAscension         = Angle(177.608 * deg),
             .longitudeOfPerigee     = Angle(243.75 * deg),
             .meanLongitude          = Angle(596.007 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(188523.9 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(523952.8 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(8055241569.86 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea
```


