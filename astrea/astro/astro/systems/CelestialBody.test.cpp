#include <chrono>
#include <filesystem>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <math/test_util.hpp>

#include <astro/astro.hpp>

static const std::string ROOT = std::getenv("ASTREA_ROOT");

using namespace astrea;
using namespace astro;
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
    CelestialBodyTest() :
        earth(ROOT + "/data/planetary/Earth/Earth.json", sys)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    CelestialBody earth;
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
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Sun/Sun.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Mercury/Mercury.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Venus/Venus.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Earth/Earth.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Earth/Moon.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Mars/Mars.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Mars/Phobos.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Mars/Deimos.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Jupiter/Jupiter.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Jupiter/Ganymede.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Jupiter/Callisto.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Jupiter/Io.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Jupiter/Europa.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Saturn/Saturn.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Saturn/Titan.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Saturn/Rhea.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Saturn/Iapetus.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Uranus/Uranus.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Uranus/Titania.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Uranus/Oberon.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Neptune/Neptune.json", sys));
    ASSERT_NO_THROW(CelestialBody(ROOT + "/data/planetary/Neptune/Triton.json", sys));
}

TEST_F(CelestialBodyTest, Equality)
{
    const CelestialBody earth2 = earth;
    const CelestialBody moon   = CelestialBody(ROOT + "/data/planetary/Earth/Moon.json", sys);
    ASSERT_EQ(earth, earth2);
    ASSERT_NE(earth, moon);
}

TEST_F(CelestialBodyTest, PropagateForTime) {}
TEST_F(CelestialBodyTest, PropagateToDate) {}
TEST_F(CelestialBodyTest, GetStates) {}
TEST_F(CelestialBodyTest, GetClosestState) {}

TEST_F(CelestialBodyTest, GetName) { ASSERT_EQ(earth.get_name(), "Earth"); }

TEST_F(CelestialBodyTest, GetParent) { ASSERT_EQ(earth.get_parent(), "Sun"); }

TEST_F(CelestialBodyTest, GetType) { ASSERT_EQ(earth.get_type(), "Planet"); }

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

TEST_F(CelestialBodyTest, GetAxialTilt) { ASSERT_EQ_QUANTITY(earth.get_axial_tilt(), Angle(23.44 * deg), REL_TOL); }

TEST_F(CelestialBodyTest, GetRotationRate)
{
    ASSERT_EQ_QUANTITY(earth.get_rotation_rate(), AngularRate(360.9851887442813 * deg / day), REL_TOL);
}

TEST_F(CelestialBodyTest, GetSiderialPeriod)
{
    ASSERT_EQ_QUANTITY(earth.get_siderial_period(), Time(365.256 * day), REL_TOL);
}

TEST_F(CelestialBodyTest, GetSemimajor)
{
    ASSERT_EQ_QUANTITY(earth.get_semimajor(), 0.149597887455766e9 * km, REL_TOL);
}

TEST_F(CelestialBodyTest, GetEccentricity) { ASSERT_EQ_QUANTITY(earth.get_eccentricity(), 0.01671022 * one, REL_TOL); }

TEST_F(CelestialBodyTest, GetInclination)
{
    ASSERT_EQ_QUANTITY(earth.get_inclination(), Angle(0.00005 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetRightAscension)
{
    ASSERT_EQ_QUANTITY(earth.get_right_ascension(), Angle(-11.26064 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetArgumentOfPerigee)
{
    ASSERT_EQ_QUANTITY(earth.get_argument_of_perigee(), Angle(102.94719 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetTrueLatitude)
{
    ASSERT_EQ_QUANTITY(earth.get_true_latitude(), Angle(100.46435 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetTrueAnomaly)
{
    ASSERT_EQ_QUANTITY(earth.get_true_anomaly(), Angle(357.4324 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetMeanAnomaly)
{
    ASSERT_EQ_QUANTITY(earth.get_mean_anomaly(), Angle(357.5172 * deg), REL_TOL);
}

TEST_F(CelestialBodyTest, GetSemimajorRate)
{
    ASSERT_EQ_QUANTITY(earth.get_semimajor_rate(), BodyVelocity(-7.4798935500 * km / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetEccentricityRate)
{
    ASSERT_EQ_QUANTITY(earth.get_eccentricity_rate(), BodyUnitlessPerTime(-0.00003804 * one / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetInclinationRate)
{
    ASSERT_EQ_QUANTITY(earth.get_inclination_rate(), BodyAngularRate(-0.013038888888888888 * deg / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetRightAscensionRate)
{
    ASSERT_EQ_QUANTITY(earth.get_right_ascension_rate(), BodyAngularRate(-18228.25 * deg / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetArgumentOfPerigeeRate)
{
    ASSERT_EQ_QUANTITY(earth.get_argument_of_perigee_rate(), BodyAngularRate(1198.28 * deg / JulianCentury), REL_TOL);
}

TEST_F(CelestialBodyTest, GetTrueLatitudeRate)
{
    ASSERT_EQ_QUANTITY(earth.get_true_latitude_rate(), BodyAngularRate(129597740.63 * deg / JulianCentury), REL_TOL);
}
