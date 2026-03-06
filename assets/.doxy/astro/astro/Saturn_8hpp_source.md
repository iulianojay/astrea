

# File Saturn.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Saturn**](dir_a10a33e87be611798e598d7dfa84b38d.md) **>** [**Saturn.hpp**](Saturn_8hpp.md)

[Go to the documentation of this file](Saturn_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_SATURN_PARAMS{
    .name          = "Saturn",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(37931187.0 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass               = Mass(568.0 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius   = Distance(60268.0 * mp_units::si::unit_symbols::km),
    .polarRadius        = Distance(54364.0 * mp_units::si::unit_symbols::km),
    .crashRadius        = Distance(60268.0 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence  = Distance(5.453426873248700 * mp_units::iau::unit_symbols::au),
    .j2                 = Unitless(16298e-6 * mp_units::one),
    .j3                 = Unitless(26.73 * mp_units::one),
    .axialTilt          = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .rotationRate       = AngularRate(810.8108108108107 * mp_units::angular::unit_symbols::deg / mp_units::non_si::day),
    .siderealPeriod     = Time(10759.22 * mp_units::non_si::day),
    .semimajorAxis      = Distance(9.53667594 * mp_units::iau::unit_symbols::au),
    .eccentricity       = Unitless(0.05386179 * mp_units::one),
    .inclination        = Angle(2.48599187 * mp_units::angular::unit_symbols::deg),
    .rightAscension     = Angle(113.66242448 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee = Angle(92.59887831 * mp_units::angular::unit_symbols::deg),
    .meanLongitude      = Angle(49.95424423 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate  = InterplanetaryVelocity(-0.00125060 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate   = BodyUnitlessPerTime(-0.00050991 * mp_units::one / JulianCentury),
    .inclinationRate    = BodyAngularRate(0.00193609 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate = BodyAngularRate(-0.28867794 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(-0.41897216 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(1222.49362201 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Saturn : public CelestialBody {

  public:
    constexpr Saturn() :
        CelestialBody(DEFAULT_SATURN_PARAMS)
    {
    }

    ~Saturn() = default;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::SATURN; };

#ifdef ASTREA_BUILD_SATURN_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_SATURN_EPHEMERIS

  private:
    constexpr CoefficientPack get_linear_expansion_coefficients() const override
    {
        using mp_units::angular::unit_symbols::rad;
        return std::make_tuple(0.00025899 * rad / (JulianCentury * JulianCentury), -0.13434469 * rad, 0.87320147 * rad, 38.35125000 * rad / JulianCentury);
    }
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


