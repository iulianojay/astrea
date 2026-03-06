

# File Titan.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Saturn**](dir_a10a33e87be611798e598d7dfa84b38d.md) **>** [**Titan.hpp**](Titan_8hpp.md)

[Go to the documentation of this file](Titan_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_TITAN_PARAMS{
    .name          = "Titan",
    .parent        = CelestialBodyId::SATURN,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(8978.1 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.13455 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(2575.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.004333361603448 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(27.359 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(22.577014429408919 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(15.94542 * mp_units::non_si::day),
    .semimajorAxis     = Distance(1221.83e3 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.0292 * mp_units::one),
    .inclination       = Angle(0.33 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(28.060 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(208.592 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(371.902 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(183934.15 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(551990.5 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(2969198512.13 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Titan : public CelestialBody {

  public:
    constexpr Titan() :
        CelestialBody(DEFAULT_TITAN_PARAMS)
    {
    }

    ~Titan() = default;

    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::TITAN; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


