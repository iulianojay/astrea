

# File Triton.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Neptune**](dir_218149e19931632c0aa773ce91bba6d7.md) **>** [**Triton.hpp**](Triton_8hpp.md)

[Go to the documentation of this file](Triton_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_TRITON_PARAMS{
    .name          = "Triton",
    .parent        = CelestialBodyId::NEPTUNE,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(1427.6 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.0214 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(1353.4 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(1353.4 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1353.4 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.001198560847624 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(28.33 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(61.257264516014864 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(5.87685 * mp_units::non_si::day),
    .semimajorAxis     = Distance(354.76e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.000016 * mp_units::one),
    .inclination       = Angle(157.345 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(177.608 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(243.75 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(596.007 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(188523.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(523952.8 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(8055241569.86 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Triton : public CelestialBody {

  public:
    constexpr Triton() :
        CelestialBody(DEFAULT_TRITON_PARAMS)
    {
    }

    ~Triton() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TRITON; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


