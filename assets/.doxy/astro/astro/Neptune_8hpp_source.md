

# File Neptune.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Neptune**](dir_218149e19931632c0aa773ce91bba6d7.md) **>** [**Neptune.hpp**](Neptune_8hpp.md)

[Go to the documentation of this file](Neptune_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_NEPTUNE_PARAMS{
    .name          = "Neptune",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("1950-01-01 00:00:00"),
    .mu = GravParam(6836529.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(102.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(24764.0 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(24341.0 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(24764.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(8.651147189326089 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(3411e-6 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(28.32 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(536.3128491620112 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(60189 * mp_units::non_si::day),
    .semimajorAxis      = Distance(30.06992276 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.00859048 * mp_units::one),
    .inclination        = Angle(1.77004347 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(131.78422574 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(44.96476227 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(-55.12002969 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(0.00026291 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(0.00005105 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.00035372 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(-0.00508664 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(-0.32241464 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(218.45945325 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Neptune : public CelestialBody {

  public:
    constexpr Neptune() :
        CelestialBody(DEFAULT_NEPTUNE_PARAMS)
    {
    }

    ~Neptune() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::NEPTUNE; };

#ifdef ASTREA_BUILD_NEPTUNE_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_NEPTUNE_EPHEMERIS

  private:
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00041348 * rad / (JulianCentury * JulianCentury), 0.68346318 * rad, -0.10162547 * rad, 7.67025000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


