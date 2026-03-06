

# File Jupiter.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Jupiter**](dir_c4fa1b5971c1990efd87a43a39eac238.md) **>** [**Jupiter.hpp**](Jupiter_8hpp.md)

[Go to the documentation of this file](Jupiter_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_JUPITER_PARAMS{
    .name          = "Jupiter",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(126686535.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(1898.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(71492.0 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(66854.0 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(71492.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(0.057732173855358 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(14736e-6 * mp_units::one),
    .j3                 = Unitless(0.0 * mp_units::one),
    .axialTilt          = Angle(3.13 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(350.8928680212322 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(4332.589 * mp_units::non_si::day),
    .semimajorAxis      = Distance(5.20288700 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.04838624 * mp_units::one),
    .inclination        = Angle(1.30439695 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(100.47390909 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(14.72847983 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(34.39644051 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(-0.00011607 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(-0.00013253 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(-0.00183714 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(0.20469106 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.21252668 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(3034.74612775 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Jupiter : public CelestialBody {

  public:
    constexpr Jupiter() :
        CelestialBody(DEFAULT_JUPITER_PARAMS)
    {
    }

    ~Jupiter() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::JUPITER; };

#ifdef ASTREA_BUILD_JUPITER_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_JUPITER_EPHEMERIS

  private:
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(-0.00012452 * rad / (JulianCentury * JulianCentury), 0.06064060 * rad, -0.35635438 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


