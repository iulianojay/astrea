

# File Phobos.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Mars**](dir_262a2d2e73be89b2c0c48090ebaaa7f9.md) **>** [**Phobos.hpp**](Phobos_8hpp.md)

[Go to the documentation of this file](Phobos_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_PHOBOS_PARAMS{
    .name          = "Phobos",
    .parent        = CelestialBodyId::MARS,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1950-01-01 00:00:00"),
    .mu = GravParam(9.85e-5 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass                   = Mass(2.4e-9 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius       = Distance(6.2 * mp_units::si::unit_symbols::km),
    .polarRadius            = Distance(5.1 * mp_units::si::unit_symbols::km),
    .crashRadius            = Distance(6.25 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence      = Distance(9.98573371442e-07 * mp_units::iau::unit_symbols::au),
    .j2                     = Unitless(0.0 * mp_units::one),
    .j3                     = Unitless(0.0 * mp_units::one),
    .axialTilt              = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate           = AngularRate(1128.844 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(1.26244 * mp_units::non_si::day),
    .semimajorAxis          = Distance(23459.0 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0005 * mp_units::one),
    .inclination            = Angle(1.79 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(24.525 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(285.254 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(610.583 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(2376381 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(7111440.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(37503046910.7 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Phobos : public CelestialBody {

  public:
    constexpr Phobos() :
        CelestialBody(DEFAULT_PHOBOS_PARAMS)
    {
    }

    ~Phobos() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::PHOBOS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


