

# File Mercury.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Mercury**](dir_b1a5af1521642f4d9f72715b19091401.md) **>** [**Mercury.hpp**](Mercury_8hpp.md)

[Go to the documentation of this file](Mercury_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_MERCURY_PARAMS{
    .name          = "Mercury",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(22032.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(0.330 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(2439.7 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(2439.7 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(2464.7 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(0.011239389492058 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(60.0e-6 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(0.034 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(6.138107416879796 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(87.969 * mp_units::non_si::day),
    .semimajorAxis      = Distance(0.38709927 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.20563593 * mp_units::one),
    .inclination        = Angle(7.00497902 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(48.33076593 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(77.45779628 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(252.25032350 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.00000037 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.00001906 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(-0.00594749 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(-0.12534081 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.16047689 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(149472.67411175 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Mercury : public CelestialBody {

  public:
    constexpr Mercury() :
        CelestialBody(DEFAULT_MERCURY_PARAMS)
    {
    }

    ~Mercury() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::MERCURY; };

#ifdef ASTREA_BUILD_MERCURY_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_MERCURY_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


