

# File Earth.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**planetary\_bodies**](dir_18001f99c0231f827e3b1298618599da.md) **>** [**Earth**](dir_75c6709890bdaeca67b81158f928802c.md) **>** [**Earth.hpp**](Earth_8hpp.md)

[Go to the documentation of this file](Earth_8hpp.md)


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

static const CelestialBodyParameters DEFAULT_EARTH_PARAMS{
    .name          = "Earth",
    .parent        = CelestialBodyId::SUN,
    .type          = CelestialBodyType::PLANET,
    .referenceDate = Date("2000-01-01 12:00:00"),
    .mu = GravParam(398600.44189 * mp_units::pow<3>(mp_units::si::unit_symbols::km) / mp_units::pow<2>(mp_units::si::unit_symbols::s)),
    .mass              = Mass(5.97 * (mp_units::mag_power<10, 24> * mp_units::si::unit_symbols::kg)),
    .equitorialRadius  = Distance(6378.137 * mp_units::si::unit_symbols::km),
    .polarRadius       = Distance(6356.75538082 * mp_units::si::unit_symbols::km),
    .crashRadius       = Distance(6478.1 * mp_units::si::unit_symbols::km),
    .sphereOfInfluence = Distance(0.092449582665046 * mp_units::iau::unit_symbols::au),
    .j2                = Unitless(0.00108262982 * mp_units::one),
    .j3                = Unitless(-0.0000025323 * mp_units::one),
    .axialTilt         = Angle(23.439292 * mp_units::angular::unit_symbols::deg),
    .rotationRate = AngularRate(7.29211514670638e-5 * mp_units::angular::unit_symbols::rad / mp_units::si::unit_symbols::s),
    .siderealPeriod         = Time(365.256 * mp_units::non_si::day),
    .semimajorAxis          = Distance(1.00000261 * mp_units::iau::unit_symbols::au),
    .eccentricity           = Unitless(0.01671123 * mp_units::one),
    .inclination            = Angle(-0.00001531 * mp_units::angular::unit_symbols::deg),
    .rightAscension         = Angle(0.0 * mp_units::angular::unit_symbols::deg),
    .longitudeOfPerigee     = Angle(102.93768193 * mp_units::angular::unit_symbols::deg),
    .meanLongitude          = Angle(100.46457166 * mp_units::angular::unit_symbols::deg),
    .semimajorAxisRate      = InterplanetaryVelocity(0.00000562 * mp_units::iau::unit_symbols::au / JulianCentury),
    .eccentricityRate       = BodyUnitlessPerTime(-0.00004392 * mp_units::one / JulianCentury),
    .inclinationRate        = BodyAngularRate(-0.01294668 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .rightAscensionRate     = BodyAngularRate(0.0 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .longitudeOfPerigeeRate = BodyAngularRate(0.32327364 * mp_units::angular::unit_symbols::deg / JulianCentury),
    .meanLongitudeRate      = BodyAngularRate(35999.37244981 * mp_units::angular::unit_symbols::deg / JulianCentury)
};

class Earth : public CelestialBody {

  public:
    constexpr Earth() :
        CelestialBody(DEFAULT_EARTH_PARAMS)
    {
    }

    ~Earth() = default;

    Density find_atmospheric_density(const Date& date, const Distance& altitude) const override;

    static constexpr CelestialBodyId get_id() { return CelestialBodyId::EARTH; };

#ifdef ASTREA_BUILD_EARTH_EPHEMERIS

    RadiusVector<frames::solar_system_barycenter::icrf> get_position_at(const Date& date) const;

#endif // ASTREA_BUILD_EARTH_EPHEMERIS
};

} // namespace planetary_bodies
} // namespace astro
} // namespace astrea
```


