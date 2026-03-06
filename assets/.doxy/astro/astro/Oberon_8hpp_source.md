

# File Oberon.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Uranus**](dir_7b592d311fa9a0d617c41c2d0e8e5c61.md) **>** [**Oberon.hpp**](Oberon_8hpp.md)

[Go to the documentation of this file](Oberon_8hpp.md)


```C++

#pragma once

#include <mp-units/systems/angular.h>
#include <mp-units/systems/iau.h>
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {
namespace planetary_bodies {

static const CelestialBodyParameters DEFAULT_OBERON_PARAMS{
    .name          = "Oberon",
    .parent        = CelestialBodyId::URANUS,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1980-01-01 00:00:00"),
    .mu = GravParam(192.4 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.00288 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(761.4 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(761.4 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(761.4 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(9.42735725907e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(26.739489189595904 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(13.4632 * mp_units::non_si::day),
    .semimajorAxis     = Distance(583.50e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.0014 * mp_units::one),
    .inclination       = Angle(0.07 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(279.771 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(24.171 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(307.259 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(663356.7 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(1465734.12 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(3517441116.43 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Oberon : public CelestialBody {

  public:
    constexpr Oberon() :
        CelestialBody(DEFAULT_OBERON_PARAMS)
    {
    }

    ~Oberon() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::OBERON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


