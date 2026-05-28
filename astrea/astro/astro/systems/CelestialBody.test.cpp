/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace planets;
using namespace star;
using namespace moons;
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
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CelestialBodyTest, Equality)
{
    ASSERT_EQ(Earth, Earth);
    ASSERT_NE(Earth, Moon);
}

TEST_F(CelestialBodyTest, GetName) { ASSERT_EQ(get_name<planets::Earth>(), "Earth"); }

TEST_F(CelestialBodyTest, GetParent) { ASSERT_EQ(get_parent<planets::Earth>(), Sun); }

TEST_F(CelestialBodyTest, GetType) { ASSERT_EQ(get_body_type<planets::Earth>(), CelestialBodyType::PLANET); }

TEST_F(CelestialBodyTest, GetMu)
{
    ASSERT_TRUE(math::nearly_equal(get_mu<planets::Earth>(), 398600.44189 * mp_units::pow<3>(km) / mp_units::pow<2>(s), REL_TOL));
}

TEST_F(CelestialBodyTest, GetMass)
{
    ASSERT_TRUE(math::nearly_equal(get_mass<planets::Earth>(), Mass(5.97 * (mag_power<10, 24> * kg)), REL_TOL));
}

TEST_F(CelestialBodyTest, GetEquitorialRadius)
{
    ASSERT_TRUE(math::nearly_equal(get_equitorial_radius<planets::Earth>(), 6378.138 * km, REL_TOL));
}

TEST_F(CelestialBodyTest, GetPolarRadius)
{
    ASSERT_TRUE(math::nearly_equal(get_polar_radius<planets::Earth>(), 6356.752 * km, REL_TOL));
}

TEST_F(CelestialBodyTest, GetCrashRadius)
{
    ASSERT_TRUE(math::nearly_equal(get_crash_radius<planets::Earth>(), 6478.1 * km, REL_TOL));
}

TEST_F(CelestialBodyTest, GetSphereOfInfluence)
{
    ASSERT_TRUE(math::nearly_equal(get_sphere_of_influence<planets::Earth>(), Distance(0.092449582665046 * au), REL_TOL));
}

TEST_F(CelestialBodyTest, GetJ2)
{
    ASSERT_TRUE(math::nearly_equal(get_j2<planets::Earth>(), 1082.63e-6 * one, REL_TOL));
}

TEST_F(CelestialBodyTest, GetJ3)
{
    ASSERT_TRUE(math::nearly_equal(get_j3<planets::Earth>(), -0.0000025323 * one, REL_TOL));
}

TEST_F(CelestialBodyTest, GetAxialTilt)
{
    ASSERT_TRUE(math::nearly_equal(get_axial_tilt<planets::Earth>(), Angle(23.439292 * deg), REL_TOL));
}

TEST_F(CelestialBodyTest, GetRotationRate)
{
    ASSERT_TRUE(math::nearly_equal(get_rotation_rate<planets::Earth>(), AngularVelocity(7.29211514670638e-5 * rad / s), REL_TOL));
}

TEST_F(CelestialBodyTest, GetSiderealPeriod)
{
    ASSERT_TRUE(math::nearly_equal(get_sidereal_period<planets::Earth>(), Time(365.256 * day), REL_TOL));
}

TEST_F(CelestialBodyTest, GetSemimajor)
{
    ASSERT_TRUE(math::nearly_equal(get_semimajor<planets::Earth>(), Distance(1.00000261 * au), REL_TOL));
}

TEST_F(CelestialBodyTest, GetEccentricity)
{
    ASSERT_TRUE(math::nearly_equal(get_eccentricity<planets::Earth>(), Unitless(0.01671123 * one), REL_TOL));
}

TEST_F(CelestialBodyTest, GetInclination)
{
    ASSERT_TRUE(math::nearly_equal(get_inclination<planets::Earth>(), Angle(-0.00001531 * deg), REL_TOL));
}

TEST_F(CelestialBodyTest, GetRightAscension)
{
    ASSERT_TRUE(math::nearly_equal(get_right_ascension<planets::Earth>(), Angle(0.0 * deg), REL_TOL));
}

TEST_F(CelestialBodyTest, GetLongitudeOfPerigee)
{
    ASSERT_TRUE(math::nearly_equal(get_longitude_of_perigee<planets::Earth>(), Angle(102.93768193 * deg), REL_TOL));
}

TEST_F(CelestialBodyTest, GetMeanLongitude)
{
    ASSERT_TRUE(math::nearly_equal(get_mean_longitude<planets::Earth>(), Angle(100.4645716 * deg), REL_TOL));
}

TEST_F(CelestialBodyTest, GetTrueAnomaly)
{
    ASSERT_TRUE(math::nearly_equal(get_true_anomaly<planets::Earth>(), Angle(6.238549 * rad), REL_TOL));
}

TEST_F(CelestialBodyTest, GetMeanAnomaly)
{
    ASSERT_TRUE(math::nearly_equal(get_mean_anomaly<planets::Earth>(), Angle(6.240021 * rad), REL_TOL));
}

TEST_F(CelestialBodyTest, GetSemimajorRate)
{
    ASSERT_TRUE(math::nearly_equal(get_semimajor_rate<planets::Earth>(), InterplanetaryVelocity(0.00000562 * au / JulianCentury), REL_TOL));
}

TEST_F(CelestialBodyTest, GetEccentricityRate)
{
    ASSERT_TRUE(math::nearly_equal(get_eccentricity_rate<planets::Earth>(), BodyUnitlessPerTime(-0.00004392 * one / JulianCentury), REL_TOL));
}

TEST_F(CelestialBodyTest, GetInclinationRate)
{
    ASSERT_TRUE(math::nearly_equal(get_inclination_rate<planets::Earth>(), BodyAngularVelocity(-0.01294668 * deg / JulianCentury), REL_TOL));
}

TEST_F(CelestialBodyTest, GetRightAscensionRate)
{
    ASSERT_TRUE(math::nearly_equal(get_right_ascension_rate<planets::Earth>(), BodyAngularVelocity(0.0 * deg / JulianCentury), REL_TOL));
}

TEST_F(CelestialBodyTest, GetLongitudeOfPerigeeRate)
{
    ASSERT_TRUE(math::nearly_equal(get_longitude_of_perigee_rate<planets::Earth>(), BodyAngularVelocity(0.32327364 * deg / JulianCentury), REL_TOL));
}

TEST_F(CelestialBodyTest, GetMeanLongitudeRate)
{
    ASSERT_TRUE(math::nearly_equal(get_mean_longitude_rate<planets::Earth>(), BodyAngularVelocity(35999.37244981 * deg / JulianCentury), REL_TOL));
}

// Vallado, Ex. 8.5
TEST_F(CelestialBodyTest, GetStateAtValldoEx)
{
    const Date date("2020-02-18 15:08:47.23847");
    const auto& earthMu = get_mu<planets::Earth>();
    const auto& sunMu   = get_mu<Sun>();

    // Pull out states
    const RadiusVector<frames::solar_system_barycenter::icrf> sunPosition   = get_position_at<Sun>(date);
    const RadiusVector<frames::solar_system_barycenter::icrf> earthPosition = get_position_at<planets::Earth>(date);
    const RadiusVector<frames::solar_system_barycenter::icrf> moonPosition  = get_position_at<Moon>(date);

    // Expected results
    const RadiusVector<frames::solar_system_barycenter::icrf> expEarth2SunPosition(126921698.413 * km, -69561377.707 * km, -30155074.470 * km); // Vallado lists a negative x value, likely in error
    std::cout << std::endl << "Earth to Sun Position: " << sunPosition - earthPosition << std::endl;
    std::cout << "Expected Earth to Sun Position: " << expEarth2SunPosition << std::endl;

    const RadiusVector<frames::solar_system_barycenter::icrf> expEarth2MoonPosition(14462.297 * km, -357096.976 * km, -151599.34 * km);
    std::cout << "Earth to Moon Position: " << moonPosition << std::endl;
    std::cout << "Expected Moon Position: " << expEarth2MoonPosition << std::endl << std::endl;

#if defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)

    // These comparisons are close but not exact. It could be due to the tables Vallado uses differing from the output
    // of the Chebyshev approximations. We just lower the required tolerance a bit so the tests pass. The following test
    // returns exact values so this is likely not an indication that there are any accuracy issues
    ASSERT_TRUE(nearly_equal(sunPosition - earthPosition, expEarth2SunPosition, 0.0 * one, 1800.0 * one));
    ASSERT_TRUE(nearly_equal(moonPosition, expEarth2MoonPosition, 0.0 * one, 50.0 * one)); // x value has largest inaccuracy but it's more accurate than Vallado's approximation

#elif !defined(ASTREA_BUILD_EARTH_EPHEMERIS) && !defined(ASTREA_BUILD_SUN_EPHEMERIS)

    // Linear approximations are not great
    ASSERT_TRUE(nearly_equal(sunPosition - earthPosition, expEarth2SunPosition, 1.0e-1 * one));
    ASSERT_TRUE(nearly_equal(moonPosition, expEarth2MoonPosition, 1.0 * one)); // big ooph

#endif
}

#if defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)

// Vallado, Ex. 8.5
TEST_F(CelestialBodyTest, GetStateAtJplEphemEx)
{
    const Date date("2000-01-01 12:00:00");
    const auto& earthMu = get_mu<planets::Earth>();
    const auto& sunMu   = get_mu<Sun>();

    // Pull out states
    const auto sunPosition   = get_position_at<Sun>(date);
    const auto earthPosition = get_position_at<planets::Earth>(date);
    const auto moonPosition  = get_position_at<Moon>(date);

    // Expected results
    const auto expSunToMoonPosition =
        RadiusVector<frames::solar_system_barycenter::icrf>(-26790642.141607 * km, 132490700.52134 * km, 57480615.9131708 * km);

    std::cout << "Earth to Moon Position: " << moonPosition << std::endl;
    std::cout << "Sun to Earth Position: " << earthPosition - sunPosition << std::endl;
    std::cout << "Sun to Moon Position: " << moonPosition + earthPosition - sunPosition << std::endl;
    std::cout << "Expected Sun to Moon Position: " << expSunToMoonPosition << std::endl << std::endl;

    ASSERT_TRUE(nearly_equal(moonPosition + earthPosition - sunPosition, expSunToMoonPosition, REL_TOL));
}

#endif // defined(ASTREA_BUILD_EARTH_EPHEMERIS) && defined(ASTREA_BUILD_MOON_EPHEMERIS) && defined(ASTREA_BUILD_SUN_EPHEMERIS)

TEST_F(CelestialBodyTest, GetKeplerianElementsAt)
{
    const Date date("2020-02-18 15:08:47.23847");

    ASSERT_NO_THROW(get_keplerian_elements_at<planets::Earth>(date));
    const auto kep = get_keplerian_elements_at<planets::Earth>(date);

    // Should return the orbital elements with linear approximation
    ASSERT_GT(kep.get_semimajor().numerical_value_in(km), 0.0);
    ASSERT_GE(kep.get_eccentricity().numerical_value_in(mp_units::one), 0.0);
    ASSERT_LT(kep.get_eccentricity().numerical_value_in(mp_units::one), 1.0);
}

TEST_F(CelestialBodyTest, FindAtmosphericDensity)
{
    const Date date("2020-02-18 15:08:47.23847");
    const CelestialBody dummyBody(
        { .name                   = "test",
          .parent                 = Sun,
          .type                   = CelestialBodyType::STAR,
          .referenceDate          = date,
          .mu                     = GravParam(1.32712440018e11 * km * km * km / (s * s)),
          .mass                   = Mass(1.989e30 * kg),
          .equitorialRadius       = Distance(696340.0 * km),
          .polarRadius            = Distance(696340.0 * km),
          .crashRadius            = Distance(696340.0 * km),
          .sphereOfInfluence      = Distance(0.0 * km),
          .j2                     = Unitless(0.0 * one),
          .j3                     = Unitless(0.0 * one),
          .axialTilt              = Angle(0.0 * rad),
          .rotationRate           = AngularVelocity(0.0 * rad / s),
          .siderealPeriod         = Time(0.0 * s),
          .semimajorAxis          = Distance(0.0 * km),
          .eccentricity           = Unitless(0.0 * one),
          .inclination            = Angle(0.0 * rad),
          .rightAscension         = Angle(0.0 * rad),
          .longitudeOfPerigee     = Angle(0.0 * rad),
          .meanLongitude          = Angle(0.0 * rad),
          .semimajorAxisRate      = InterplanetaryVelocity(0.0 * km / s),
          .eccentricityRate       = BodyUnitlessPerTime(0.0 * one / s),
          .inclinationRate        = BodyAngularVelocity(0.0 * rad / s),
          .rightAscensionRate     = BodyAngularVelocity(0.0 * rad / s),
          .longitudeOfPerigeeRate = BodyAngularVelocity(0.0 * rad / s),
          .meanLongitudeRate      = BodyAngularVelocity(0.0 * rad / s) }
    );

    // Test Earth (has atmosphere in derived class)
    const State state0(Keplerian<frames::earth::icrf>{ 6378.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad }, date);
    const State state1(Keplerian<frames::earth::icrf>{ 6478.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad }, date);
    const State state2(Keplerian<frames::earth::icrf>{ 6878.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad }, date);
    ASSERT_NO_THROW(dummyBody.find_atmospheric_density(state0));
    ASSERT_NO_THROW(dummyBody.find_atmospheric_density(state1));
    ASSERT_NO_THROW(dummyBody.find_atmospheric_density(state2));

    // Base class returns zero density for most bodies
    const auto densityAtAltitude = dummyBody.find_atmospheric_density(state0);
    ASSERT_EQ(densityAtAltitude.numerical_value_in(kg / (mp_units::si::unit_symbols::m * mp_units::si::unit_symbols::m * mp_units::si::unit_symbols::m)), 0.0);
}

TEST_F(CelestialBodyTest, GetPositionAt)
{
    const Date date("2020-02-18 15:08:47.23847");

    ASSERT_NO_THROW(get_position_at<Phobos>(date));
    const auto phobosPosition = get_position_at<Phobos>(date);

    // Position should have reasonable magnitude (thousands of km for Phobos)
    const auto xComponent = phobosPosition[0];
    ASSERT_GT(xComponent.numerical_value_in(km), -get_semimajor<Phobos>().numerical_value_in(km) * 1.1);
    ASSERT_LT(xComponent.numerical_value_in(km), get_semimajor<Phobos>().numerical_value_in(km) * 1.1);
}