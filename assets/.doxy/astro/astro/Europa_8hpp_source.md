

# File Europa.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Jupiter**](dir_c4fa1b5971c1990efd87a43a39eac238.md) **>** [**Europa.hpp**](Europa_8hpp.md)

[Go to the documentation of this file](Europa_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_EUROPA_PARAMS{
    .name          = "Europa",
    .parent        = CelestialBodyId::JUPITER,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(3202.7 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.04800 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(1560.8 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(1560.8 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(1560.8 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(9.72669393872e-04 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(0.0 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(3.146 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(101.3747257602471 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(3.551181 * mp_units::non_si::day),
    .semimajorAxis      = Distance(671.1e3 * mp_units::si::unit_symbols::km),
    .eccentricity       = Unitless(0.009 * mp_units::one),
    .inclination        = Angle(0.47 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(219.106 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(308.076 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(479.092 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(4293665.52 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(97263536.4 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(13427026021.5 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Europa : public CelestialBody {

  public:
    constexpr Europa() :
        CelestialBody(DEFAULT_EUROPA_PARAMS)
    {
    }

    ~Europa() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::EUROPA; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


