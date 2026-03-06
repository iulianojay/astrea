

# File Mars.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Mars**](dir_262a2d2e73be89b2c0c48090ebaaa7f9.md) **>** [**Mars.hpp**](Mars_8hpp.md)

[Go to the documentation of this file](Mars_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_MARS_PARAMS{
    .name          = "Mars",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(42828.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.642 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(3396.2 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(3376.2 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(3496.2 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(1960.45e-6 * mp_units::one),
    .j3                 = Unitless(0.000036 * mp_units::one),
    .axialTilt          = Angle(25.19 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(686.980 * mp_units::non_si::day),
    .semimajorAxis      = Distance(1.52371034 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.09339410 * mp_units::one),
    .inclination        = Angle(1.84969142 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(49.55953891 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(-23.94362959 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(-4.55343205 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.00001847 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.00007882 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(-0.00813131 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(-0.29257343 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.44441088 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(19140.30268499 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Mars : public CelestialBody {

  public:
    constexpr Mars() :
        CelestialBody(DEFAULT_MARS_PARAMS)
    {
    }

    ~Mars() = default;

    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MARS; };

#ifdef ASTREA_BUILD_MARS_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_MARS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


