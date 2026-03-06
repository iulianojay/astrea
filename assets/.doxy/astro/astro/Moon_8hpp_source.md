

# File Moon.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Earth**](dir_75c6709890bdaeca67b81158f928802c.md) **>** [**Moon.hpp**](Moon_8hpp.md)

[Go to the documentation of this file](Moon_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_MOON_PARAMS{
    .name          = "Moon",
    .parent        = CelestialBodyId::EARTH,
    .type          = CelestialBodyType::MOON,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(4902.8 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(0.073 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(1737.5 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(1736.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(1737.5 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.006602718630998 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.0 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(1.543 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(13.176195007686115 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(27.3220 * mp_units::non_si::day),
    .semimajorAxis     = Distance(380318 * mp_units::si::unit_symbols::km),
    .eccentricity      = Unitless(0.063843 * mp_units::one),
    .inclination       = Angle(5.28619 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(98.13908 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(179.16058 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(135.89122 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.0 * mp_units::si::unit_symbols::km / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(0.0 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(6967741.9 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(28578547 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(1761137860.75 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Moon : public CelestialBody {
  public:
    constexpr Moon() :
        CelestialBody(DEFAULT_MOON_PARAMS)
    {
    }

    ~Moon() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MOON; };

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_EARTH_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


