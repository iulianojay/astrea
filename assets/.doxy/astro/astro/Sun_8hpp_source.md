

# File Sun.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Sun**](dir_2bae9223f0a869dce705c7092e11bc6c.md) **>** [**Sun.hpp**](Sun_8hpp.md)

[Go to the documentation of this file](Sun_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_SUN_PARAMS{
    .name          = "Sun",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::STAR,
    .referenceDate = Date("2000-01-01 00:00:00"),
    .mu = GravParam(1.32712e11 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass                   = Mass(1988500.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius       = Distance(695700.0 * mp_units::si::unit_symbols::km),
    .polarRadius            = Distance(695700.0 * mp_units::si::unit_symbols::km),
    .crashRadius            = Distance(795700.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence      = Distance(1.0e18 * mp_units::si::unit_symbols::km),
    .j2                     = Unitless(0.2e-6 * mp_units::one),
    .j3                     = Unitless(0.0 * mp_units::one),
    .axialTilt              = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate           = AngularRate(0.0 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod         = Time(0.0 * mp_units::non_si::day),
    .semimajorAxis          = Distance(0.0 * mp_units::si::unit_symbols::km),
    .eccentricity           = Unitless(0.0 * mp_units::one),
    .inclination            = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Sun : public CelestialBody {

  public:
    constexpr Sun() :
        CelestialBody(DEFAULT_SUN_PARAMS)
    {
    }

    ~Sun() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::SUN; };

#ifdef ASTREA_BUILD_SUN_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_SUN_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


