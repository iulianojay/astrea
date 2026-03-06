

# File Venus.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Venus**](dir_c031715b0a158a554841f23d3696455e.md) **>** [**Venus.hpp**](Venus_8hpp.md)

[Go to the documentation of this file](Venus_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_VENUS_PARAMS{
    .name          = "Venus",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(324860.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(4.87 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(6051.8 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(6051.8 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(6301.8 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.061640255733634 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(4.458e-6 * mp_units::one),
    .j3                = Unitless(-0.0000025323e-6 * mp_units::one),
    .axialTilt         = Angle(2.64 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(-1.481329081370229 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(224.701 * mp_units::non_si::day),
    .semimajorAxis     = Distance(0.72333566 * mp_units::iau::unit_symbols::au),
    .eccentricity      = Unitless(0.00677672 * mp_units::one),
    .inclination       = Angle(3.39467605 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(76.67984255 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(131.60246718 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(181.97909950 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00000390 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004107 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(-0.00078890 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(-0.27769418 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.00268329 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(58517.81538729 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Venus : public CelestialBody {

  public:
    constexpr Venus() :
        CelestialBody(DEFAULT_VENUS_PARAMS)
    {
    }

    ~Venus() = default;

    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::VENUS; };

#ifdef ASTREA_BUILD_VENUS_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_VENUS_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


