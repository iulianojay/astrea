

# File Io.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Jupiter**](dir_c4fa1b5971c1990efd87a43a39eac238.md) **>** [**Io.hpp**](Io_8hpp.md)

[Go to the documentation of this file](Io_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_IO_PARAMS{
    .name          = "Io",
    .parent        = CelestialBodyId::JUPITER,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("1997-01-16 00:00:00"),
    .mu = GravParam(5959.9 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.08932 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(1821.5 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(1821.5 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(1841.5 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(7.83731997166e-04 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(0.0 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(3.13 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(203.4889307674133 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(1.769138 * mp_units::non_si::day),
    .semimajorAxis      = Distance(421.8e3 * mp_units::si::unit_symbols::km),
    .eccentricity       = Unitless(0.004 * mp_units::one),
    .inclination        = Angle(0.04 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(43.977 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(128.106 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(470.127 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(17466307.28 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(97220153.4 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(26853983280.3 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Io : public CelestialBody {

  public:
    constexpr Io() :
        CelestialBody(DEFAULT_IO_PARAMS)
    {
    }

    ~Io() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::IO; };
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


