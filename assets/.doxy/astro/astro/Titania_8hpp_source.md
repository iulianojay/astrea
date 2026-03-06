

# File Titania.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Uranus**](dir_7b592d311fa9a0d617c41c2d0e8e5c61.md) **>** [**Titania.hpp**](Titania_8hpp.md)

[Go to the documentation of this file](Titania_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_TITANIA_PARAMS{
    .name          = "Titania",
    .parent        = CelestialBodyId::URANUS,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1980-01-01 00:00:00"),
    .mu = GravParam(228.2 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.00342 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(788.9 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(788.9 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1568.9 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(7.55070955998e-04 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(41.351424275146869 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(8.70586 * mp_units::non_si::day),
    .semimajorAxis     = Distance(436.30e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.0011 * mp_units::one),
    .inclination       = Angle(0.08 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(99.771 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(24.17 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(48.785 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(663360.1 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(1465712.68 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(5438764533.33 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Titania : public CelestialBody {

  public:
    constexpr Titania() :
        CelestialBody(DEFAULT_TITANIA_PARAMS)
    {
    }

    ~Titania() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TITANIA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


