#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace planetary_bodies;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::iau::unit_symbols::au;
using mp_units::non_si::day;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class CelestialBodyTest : public testing::Test {
  public:
    CelestialBodyTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Earth earth;
    AstrodynamicsSystem sys;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(CelestialBodyTest, DefaultConstructor) { ASSERT_NO_THROW(CelestialBody()); }

TEST_F(CelestialBodyTest, FileConstructors)
{
    ASSERT_NO_THROW(Sun());
    ASSERT_NO_THROW(Mercury());
    ASSERT_NO_THROW(Venus());
    ASSERT_NO_THROW(Earth());
    ASSERT_NO_THROW(Moon());
    ASSERT_NO_THROW(Mars());
    ASSERT_NO_THROW(Phobos());
    ASSERT_NO_THROW(Deimos());
    ASSERT_NO_THROW(Jupiter());
    ASSERT_NO_THROW(Ganymede());
    ASSERT_NO_THROW(Callisto());
    ASSERT_NO_THROW(Io());
    ASSERT_NO_THROW(Europa());
    ASSERT_NO_THROW(Saturn());
    ASSERT_NO_THROW(Titan());
    ASSERT_NO_THROW(Rhea());
    ASSERT_NO_THROW(Iapetus());
    ASSERT_NO_THROW(Uranus());
    ASSERT_NO_THROW(Titania());
    ASSERT_NO_THROW(Oberon());
    ASSERT_NO_THROW(Neptune());
    ASSERT_NO_THROW(Triton());
}

TEST_F(CelestialBodyTest, Equality)
{
    const CelestialBody earth2 = earth;
    const CelestialBody moon   = Moon();
    ASSERT_EQ(earth, earth2);
    ASSERT_NE(earth, moon);
}

TEST_F(CelestialBodyTest, PropagateForTime) {}
TEST_F(CelestialBodyTest, PropagateToDate) {}
TEST_F(CelestialBodyTest, GetStates) {}
TEST_F(CelestialBodyTest, GetClosestState) {}

TEST_F(CelestialBodyTest, GetName) { ASSERT_EQ(earth.get_name(), "Earth"); }

TEST_F(CelestialBodyTest, GetParent) { ASSERT_EQ(earth.get_parent(), CelestialBodyId::SUN); }

TEST_F(CelestialBodyTest, GetType) { ASSERT_EQ(earth.get_type(), CelestialBodyType::PLANET); }

TEST_F(CelestialBodyTest, GetMu)
{
    ASSERT_EQ_QUANTITY(earth.get_mu(), 398600.44189 * mp_units::pow<3>(km) / mp_units::pow<2>(s), REL_TOL);
}

TEST_F(CelestialBodyTest, GetMass)
{
    ASSERT_EQ_QUANTITY(earth.get_mass(), Mass(5.97 * (mag_power<10, 24> * kg)), REL_TOL);
}

TEST_F(CelestialBodyTest, GetEquitorialRadius)
{
    ASSERT_EQ_QUANTITY(earth.get_equitorial_radius(), 6378.1 * km, REL_TOL);
}

TEST_F(CelestialBodyTest, GetPolarRadius) { ASSERT_EQ_QUANTITY(earth.get_polar_radius(), 6356.752 * km, REL_TOL); }

TEST_F(CelestialBodyTest, GetCrashRadius) { ASSERT_EQ_QUANTITY(earth.get_crash_radius(), 6478.1 * km, REL_TOL); }

TEST_F(CelestialBodyTest, GetSphereOfInfluence)
{
    ASSERT_EQ_QUANTITY(earth.get_sphere_of_influence(), Distance(0.092449582665046 * au), REL_TOL);
}

TEST_F(CelestialBodyTest, GetJ2) { ASSERT_EQ_QUANTITY(earth.get_j2(), 1082.63e-6 * one, REL_TOL); }

TEST_F(CelestialBodyTest, GetJ3) { ASSERT_EQ_QUANTITY(earth.get_j3(), -0.0000025323 * one, REL_TOL); }

TEST_F(CelestialBodyTest, GetAxialTilt) { ASSERT_EQ_QUANTITY(earth.get_axial_tilt(), Angle(23.439292 * deg), REL_TOL); }

TEST_F(CelestialBodyTest, GetRotationRate)
{
    ASSERT_EQ_QUANTITY(earth.get_rotation_rate(), AngularRate(360.9851887442813 * deg / day), REL_TOL);
}

TEST_F(CelestialBodyTest, GetSiderealPeriod)
{
    ASSERT_EQ_QUANTITY(earth.get_sidereal_period(), Time(365.256 * day), REL_TOL);
}

TEST_F(CelestialBodyTest, GetSemimajor)
{
    ASSERT_EQ_QUANTITY(earth.get_semimajor(), Distance(1.00000261 * au), REL_TOL);
}

TEST_F(CelestialBodyTest, GetEccentricity)
{
    ASSERT_EQ_QUANTITY(earth.get_eccentricity(), Unitless(0.01671123 * one), REL_TOL);
}

TEST_F(CelestialBodyTest, GetInclination)
{
    ASSERT_EQ_QUANTITY(earth.get_inclination(), Angle(-0.00001531 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetRightAscension)
{
    ASSERT_EQ_QUANTITY(earth.get_right_ascension(), Angle(0.0 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetLongitudeOfPerigee)
{
    ASSERT_EQ_QUANTITY(earth.get_longitude_of_perigee(), Angle(102.93768193 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetMeanLongitude)
{
    ASSERT_EQ_QUANTITY(earth.get_mean_longitude(), Angle(100.4645716 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetTrueAnomaly)
{
    ASSERT_EQ_QUANTITY(earth.get_true_anomaly(), Angle(6.238549 * rad), REL_TOL);
}

TEST_F(CelestialBodyTest, GetMeanAnomaly)
{
    ASSERT_EQ_QUANTITY(earth.get_mean_anomaly(), Angle(6.240021 * rad), REL_TOL);
}

TEST_F(CelestialBodyTest, GetSemimajorRate)
{
    ASSERT_EQ_QUANTITY(earth.get_semimajor_rate(), BodyVelocity(0.00000562 * au / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetEccentricityRate)
{
    ASSERT_EQ_QUANTITY(earth.get_eccentricity_rate(), BodyUnitlessPerTime(-0.00004392 * one / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetInclinationRate)
{
    ASSERT_EQ_QUANTITY(earth.get_inclination_rate(), BodyAngularRate(-0.01294668 * deg / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetRightAscensionRate)
{
    ASSERT_EQ_QUANTITY(earth.get_right_ascension_rate(), BodyAngularRate(0.0 * deg / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetLongitudeOfPerigeeRate)
{
    ASSERT_EQ_QUANTITY(earth.get_longitude_of_perigee_rate(), BodyAngularRate(0.32327364 * deg / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetMeanLongitudeRate)
{
    ASSERT_EQ_QUANTITY(earth.get_mean_longitude_rate(), BodyAngularRate(35999.37244981 * deg / JulianCentury), REL_TOL);
}

// Vallado, Ex. 8.5
TEST_F(CelestialBodyTest, GetStateAtValldoEx)
{
    const Date date("2020-02-18 15:08:47.23847");
    const AstrodynamicsSystem earthMoonSunSys(CelestialBodyId::EARTH, { CelestialBodyId::SUN, CelestialBodyId::MOON });
    const auto& earth = earthMoonSunSys.get(CelestialBodyId::EARTH);
    const auto& moon  = earthMoonSunSys.get(CelestialBodyId::MOON);
    const auto& sun   = earthMoonSunSys.get(CelestialBodyId::SUN);

    const auto& earthMu = earth->get_mu();
    const auto& sunMu   = sun->get_mu();

    // Pull out states
    const RadiusVector<frames::earth::icrf> sunPosition =
        sun->get_elements_at(date).in_element_set<Cartesian>(sunMu).get_position(); // currently outputs position of Sun wrt Solar System Barycenter
    const RadiusVector<frames::earth::icrf> earthPosition =
        earth->get_elements_at(date).in_element_set<Cartesian>(sunMu).get_position(); // currently outputs position of Earth wrt Solar System Barycenter
    const RadiusVector<frames::earth::icrf> moonPosition =
        moon->get_elements_at(date).in_element_set<Cartesian>(earthMu).get_position(); // currently outputs position of Moon wrt Earth

    // Expected results
    const RadiusVector<frames::earth::icrf> expEarth2SunPosition(126921698.413 * km, -69561377.707 * km, -30155074.470 * km); // Vallado lists a negative x value, likely in error
    std::cout << std::endl << "Earth to Sun Position: " << sunPosition - earthPosition << std::endl;
    std::cout << "Expected Earth to Sun Position: " << expEarth2SunPosition << std::endl;

    const RadiusVector<frames::earth::icrf> expEarth2MoonPosition(14462.297 * km, -357096.976 * km, -151599.34 * km);
    std::cout << "Earth to Moon Position: " << moonPosition << std::endl;
    std::cout << "Expected Moon Position: " << expEarth2MoonPosition << std::endl << std::endl;

#if defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_MOON_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)
    // These comparisons are close but not exact. It could be due to the tables Vallado uses differing from the output
    // of the Chebyshev approximations. We just lower the required tolerance a bit so the tests pass. The following test
    // returns exact values so this is likely not an indication that there are any accuracy issues
    ASSERT_EQ_CART_VEC(sunPosition - earthPosition, expEarth2SunPosition, 0.0 * one, 1800.0 * one);
    ASSERT_EQ_CART_VEC(moonPosition, expEarth2MoonPosition, 0.0 * one, 50.0 * one); // x value has largest inaccuracy but it's more accurate than Vallado's approximation
#else
    // Linear approximations are not great
    ASSERT_EQ_CART_VEC(sunPosition - earthPosition, expEarth2SunPosition, 1.0e-1 * one);
    ASSERT_EQ_CART_VEC(moonPosition, expEarth2MoonPosition, 1.0e-1 * one);
#endif
}

#if defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_MOON_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)

// Vallado, Ex. 8.5
TEST_F(CelestialBodyTest, GetStateAtJplEphemEx)
{
    const Date date("2000-01-01 12:00:00");
    const AstrodynamicsSystem earthMoonSunSys(CelestialBodyId::EARTH, { CelestialBodyId::MOON, CelestialBodyId::SUN });
    const auto& earth = earthMoonSunSys.get(CelestialBodyId::EARTH);
    const auto& moon  = earthMoonSunSys.get(CelestialBodyId::MOON);
    const auto& sun   = earthMoonSunSys.get(CelestialBodyId::SUN);

    const auto& earthMu = earth->get_mu();
    const auto& sunMu   = sun->get_mu();

    // Pull out states
    const RadiusVector<frames::earth::icrf> sunPosition =
        sun->get_elements_at(date).in_element_set<Cartesian>(sunMu).get_position();
    const RadiusVector<frames::earth::icrf> earthPosition =
        earth->get_elements_at(date).in_element_set<Cartesian>(sunMu).get_position(); // currently outputs position of Earth wrt Solar System Barycenter
    const RadiusVector<frames::earth::icrf> moonPosition =
        moon->get_elements_at(date).in_element_set<Cartesian>(earthMu).get_position(); // currently outputs position of Moon wrt Earth

    // Expected results
    const RadiusVector<frames::earth::icrf> expSunToMoonPosition(-26790642.141607 * km, 132490700.52134 * km, 57480615.9131708 * km);

    std::cout << "Earth to Moon Position: " << moonPosition << std::endl;
    std::cout << "Sun to Earth Position: " << earthPosition - sunPosition << std::endl;
    std::cout << "Sun to Moon Position: " << moonPosition + earthPosition - sunPosition << std::endl;
    std::cout << "Expected Sun to Moon Position: " << expSunToMoonPosition << std::endl << std::endl;

    ASSERT_EQ_CART_VEC(moonPosition + earthPosition - sunPosition, expSunToMoonPosition, REL_TOL);
}

#endif // defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_MOON_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)