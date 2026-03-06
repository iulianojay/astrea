

# File Callisto.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Jupiter**](dir_c4fa1b5971c1990efd87a43a39eac238.md) **>** [**Callisto.hpp**](Callisto_8hpp.md)

[Go to the documentation of this file](Callisto_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_CALLISTO_PARAMS{
    .name          = "Callisto",
    .parent        = CelestialBodyId::JUPITER,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(7179.3 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.10759 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(2410.3 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(2410.3 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(2410.3 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.003768525014695 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(3.486 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(21.571072760007375 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(16.68901 * mp_units::non_si::day),
    .semimajorAxis     = Distance(1882.7e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.007 * mp_units::one),
    .inclination       = Angle(0.19 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(298.848 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(351.491 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(532.899 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(382503.98 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(1012394.6 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(2837392757.1 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Callisto : public CelestialBody {

  public:
    constexpr Callisto() :
        CelestialBody(DEFAULT_CALLISTO_PARAMS)
    {
    }

    ~Callisto() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::CALLISTO; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


