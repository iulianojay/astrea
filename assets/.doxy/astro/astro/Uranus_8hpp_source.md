

# File Uranus.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Uranus**](dir_7b592d311fa9a0d617c41c2d0e8e5c61.md) **>** [**Uranus.hpp**](Uranus_8hpp.md)

[Go to the documentation of this file](Uranus_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_URANUS_PARAMS{
    .name          = "Uranus",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(5793939.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(86.8 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(25559.0 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(24973.0 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(25559.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(5.176385869757780 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(3343.43e-6 * mp_units::one),
    .j3                = Unitless(0.0 * mp_units::one),
    .axialTilt         = Angle(82.23 * mp_units::angular::unit_symbols::deg),
    .rotationRate      = AngularRate(-501.1600928074246 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod    = Time(30685.4 * mp_units::non_si::day),
    .semimajorAxis     = Distance(19.18916464 * mp_units::iau::unit_symbols::au),
    .eccentricity      = Unitless(0.04725744 * mp_units::one),
    .inclination       = Angle(0.77263783 * mp_units::angular::unit_symbols::deg),
    .rightAscension    = Angle(74.01692503 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(170.95427630 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(313.23810451 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(-0.00196176 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004397 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(-0.00242939 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(0.04240589 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.40805281 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(428.48202785 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Uranus : public CelestialBody {

  public:
    constexpr Uranus() :
        CelestialBody(DEFAULT_URANUS_PARAMS)
    {
    }

    ~Uranus() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::URANUS; };

#ifdef ASTREA_BUILD_URANUS_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_URANUS_EPHEMERIS

  private:
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.00058331 * rad / (JulianCentury * JulianCentury), -0.97731848 * rad, 0.17689245 * rad, 7.67025000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


