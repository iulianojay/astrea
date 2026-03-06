

# File Rhea.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Saturn**](dir_a10a33e87be611798e598d7dfa84b38d.md) **>** [**Rhea.hpp**](Rhea_8hpp.md)

[Go to the documentation of this file](Rhea_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_RHEA_PARAMS{
    .name          = "Rhea",
    .parent        = CelestialBodyId::SATURN,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(120.50 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.00181 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(746.0 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(712.0 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(761.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(0.002253931200283 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(0.0 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(41.940 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(4.537995330226328 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(79.33018 * mp_units::non_si::day),
    .semimajorAxis      = Distance(3561.3e3 * mp_units::si::unit_symbols::km),
    .eccentricity       = Unitless(0.0283 * mp_units::one),
    .inclination        = Angle(14.72 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(81.105 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(352.711 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(554.5 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(37688.33 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(11498.3 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(59680892.45 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Rhea : public CelestialBody {

  public:
    constexpr Rhea() :
        CelestialBody(DEFAULT_RHEA_PARAMS)
    {
    }

    ~Rhea() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::RHEA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


