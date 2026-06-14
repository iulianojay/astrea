

# File Rhea.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**Saturn**](dir_7fd613539f7980532282f5cbc20c34d1.md) **>** [**Rhea.hpp**](Rhea_8hpp.md)

[Go to the documentation of this file](Rhea_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies/Saturn/Saturn.hpp>

namespace astrea {
namespace astro {

namespace moons {

inline constexpr struct Rhea final : CelestialBody<"Rhea", planets::Saturn> {
} Rhea;

} // namespace moons

template <>
inline consteval CelestialBodyParameters get_celestial_body_parameters<moons::Rhea>()
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
             .mu                     = GravParam(120.50 * pow<3>(km) / pow<2>(s)),
             .mass                   = Mass(0.00181 * (mag_power<10, 24> * kg)),
             .equitorialRadius       = Distance(746.0 * km),
             .polarRadius            = Distance(712.0 * km),
             .crashRadius            = Distance(761.0 * km),
             .sphereOfInfluence      = Distance(0.002253931200283 * au),
             .j2                     = Unitless(0.0 * one),
             .j3                     = Unitless(0.0 * one),
             .axialTilt              = Angle(41.940 * deg),
             .rotationRate           = AngularVelocity(4.537995330226328 * deg / day),
             .siderealPeriod         = Time(79.33018 * day),
             .semimajorAxis          = Distance(3561.3e3 * km),
             .eccentricity           = Unitless(0.0283 * one),
             .inclination            = Angle(14.72 * deg),
             .rightAscension         = Angle(81.105 * deg),
             .longitudeOfPerigee     = Angle(352.711 * deg),
             .meanLongitude          = Angle(554.5 * deg),
             .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / JulianCentury),
             .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / JulianCentury),
             .inclinationRate        = BodyAngularVelocity(0.0 * deg / JulianCentury),
             .rightAscensionRate     = BodyAngularVelocity(37688.33 * deg / JulianCentury),
             .longitudeOfPerigeeRate = BodyAngularVelocity(11498.3 * deg / JulianCentury),
             .meanLongitudeRate      = BodyAngularVelocity(59680892.45 * deg / JulianCentury) };
}

} // namespace astro
} // namespace astrea
```


