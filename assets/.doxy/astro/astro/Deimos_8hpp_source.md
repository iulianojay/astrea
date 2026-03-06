

# File Deimos.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Mars**](dir_262a2d2e73be89b2c0c48090ebaaa7f9.md) **>** [**Deimos.hpp**](Deimos_8hpp.md)

[Go to the documentation of this file](Deimos_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_DEIMOS_PARAMS{
    .name          = "Deimos",
    .parent        = CelestialBodyId::MARS,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1950-01-01 00:00:00"),
    .mu = GravParam(7.112e-4 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(10.6e-9 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(11.1 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(9.1 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(11.15 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(7.23133636677e-07 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(0.0 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(25.199 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(27092.28308927283 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(0.31891 * mp_units::non_si::day),
    .semimajorAxis      = Distance(9378.0 * mp_units::si::unit_symbols::km),
    .eccentricity       = Unitless(0.0151 * mp_units::one),
    .inclination        = Angle(1.08 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(207.784 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(357.841 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(448.9 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(57302029 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(171830131 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(148603627216.0 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Deimos : public CelestialBody {

  public:
    constexpr Deimos() :
        CelestialBody(DEFAULT_DEIMOS_PARAMS)
    {
    }

    ~Deimos() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::DEIMOS; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


