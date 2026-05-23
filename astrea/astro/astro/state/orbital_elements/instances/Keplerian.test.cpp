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

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class KeplerianTest : public testing::Test {
  public:
    KeplerianTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    const auto mu = get_mu<frames::primary::origin>();
    Distance a    = 7000.0 * km;
    Unitless ecc  = 0.01 * one;
    Angle inc     = 98.0 * deg;
    Angle raan    = 40.0 * deg;
    Angle w       = 80.0 * deg;
    Angle theta   = 0.0 * deg;
    Keplerian<frames::earth::icrf> state{ a, ecc, inc, raan, w, theta };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(KeplerianTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << a << ", " << ecc << ", " << inc << ", " << raan << ", " << w << ", " << theta << "] (Keplerian)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(KeplerianTest, DefaultConstructor)
{
    Keplerian<frames::earth::icrf> defaultState;
    ASSERT_TRUE(math::nearly_equal(defaultState.get_semimajor(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_eccentricity(), Unitless(0.0 * one), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_inclination(), Angle(0.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_right_ascension(), Angle(0.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_argument_of_perigee(), Angle(0.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(defaultState.get_true_anomaly(), Angle(0.0 * rad), REL_TOL));
}

TEST_F(KeplerianTest, UnitlessConstructor)
{
    Keplerian<frames::earth::icrf> scaledState(2.0 * one);
    ASSERT_TRUE(math::nearly_equal(scaledState.get_semimajor(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_eccentricity(), Unitless(2.0 * one), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_inclination(), Angle(2.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_right_ascension(), Angle(2.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_argument_of_perigee(), Angle(2.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(scaledState.get_true_anomaly(), Angle(2.0 * rad), REL_TOL));
}

TEST_F(KeplerianTest, ParameterizedConstructor) { ASSERT_NO_THROW(Keplerian(a, ecc, inc, raan, w, theta)); }

TEST_F(KeplerianTest, KeplerianConstructor)
{
    Keplerian<frames::earth::icrf> other{ 8000.0 * km, 0.02 * one, 45.0 * deg, 30.0 * deg, 60.0 * deg, 90.0 * deg };
    ASSERT_NO_THROW(Keplerian(other.get_mu()));
}

TEST_F(KeplerianTest, CartesianConstructor)
{
    Cartesian<frames::earth::icrf> cart{ 7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.546 * km / s, 0.0 * km / s };
    ASSERT_NO_THROW(Keplerian(cart.get_mu()));
}

TEST_F(KeplerianTest, EquinoctialConstructor)
{
    Equinoctial<frames::earth::icrf> equi{ 7000.0 * km, 0.01 * one, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * rad };
    ASSERT_NO_THROW(Keplerian(equi.get_mu()));
}

TEST_F(KeplerianTest, LEOStaticMethod)
{
    ASSERT_NO_THROW(Keplerian::LEO());
    auto leo = Keplerian::LEO();
    ASSERT_GT(leo.get_semimajor().numerical_value_in(km), 0.0);
}

TEST_F(KeplerianTest, LMEOStaticMethod)
{
    ASSERT_NO_THROW(Keplerian::LMEO());
    auto lmeo = Keplerian::LMEO();
    ASSERT_GT(lmeo.get_semimajor().numerical_value_in(km), 0.0);
}

TEST_F(KeplerianTest, GPSStaticMethod)
{
    ASSERT_NO_THROW(Keplerian::GPS());
    auto gps = Keplerian::GPS();
    ASSERT_GT(gps.get_semimajor().numerical_value_in(km), 0.0);
}

TEST_F(KeplerianTest, HMEOStaticMethod)
{
    ASSERT_NO_THROW(Keplerian::HMEO());
    auto hmeo = Keplerian::HMEO();
    ASSERT_GT(hmeo.get_semimajor().numerical_value_in(km), 0.0);
}

TEST_F(KeplerianTest, GEOStaticMethod)
{
    ASSERT_NO_THROW(Keplerian::GEO());
    auto geo = Keplerian::GEO();
    ASSERT_GT(geo.get_semimajor().numerical_value_in(km), 0.0);
}

TEST_F(KeplerianTest, CopyConstructor)
{
    ASSERT_NO_THROW(Keplerian<frames::earth::icrf> newKep(state));
    Keplerian<frames::earth::icrf> newKep(state);
    ASSERT_TRUE(math::nearly_equal(newKep.get_semimajor(), a, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_eccentricity(), ecc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_inclination(), inc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_right_ascension(), raan, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_argument_of_perigee(), w, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_true_anomaly(), theta, REL_TOL));
}

TEST_F(KeplerianTest, MoveConstructor)
{
    Keplerian<frames::earth::icrf> temp{ a, ecc, inc, raan, w, theta };
    ASSERT_NO_THROW(Keplerian<frames::earth::icrf> newKep(std::move(temp)));
}

TEST_F(KeplerianTest, CopyAssignment)
{
    ASSERT_NO_THROW(Keplerian<frames::earth::icrf> newKep = state);
    Keplerian<frames::earth::icrf> newKep = state;
    ASSERT_TRUE(math::nearly_equal(newKep.get_semimajor(), a, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_eccentricity(), ecc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_inclination(), inc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_right_ascension(), raan, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_argument_of_perigee(), w, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(newKep.get_true_anomaly(), theta, REL_TOL));
}

TEST_F(KeplerianTest, MoveAssignment)
{
    Keplerian<frames::earth::icrf> frames::earth::icrf > temp{ a, ecc, inc, raan, w, theta };
    ASSERT_NO_THROW(Keplerian<frames::earth::icrf> newKep = std::move(temp));
}

TEST_F(KeplerianTest, EqualityOperator)
{
    Keplerian<frames::earth::icrf> frames::earth::icrf > sameState{ a, ecc, inc, raan, w, theta };
    Keplerian<frames::earth::icrf> frames::earth::icrf > frames::earth::icrf >
        diffState{ a + 1000.0 * km, ecc, inc, raan, w, theta };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(KeplerianTest, AdditionOperator)
{
    Keplerian<frames::earth::icrf> Keplerian<frames::earth::icrf> other{ 1000.0 * km, 0.005 * one, 10.0 * deg,
                                                                         5.0 * deg,   10.0 * deg,  15.0 * deg };
    Keplerian<frames::earth::icrf> result = state + other;
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), a + 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), ecc + 0.005 * one, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_inclination(), inc + 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_right_ascension(), raan + 5.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_argument_of_perigee(), w + 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_anomaly(), theta + 15.0 * deg, REL_TOL));
}

TEST_F(KeplerianTest, AdditionAssignmentOperator)
{
    Keplerian<frames::earth::icrf> other{ 1000.0 * km, 0.005 * one, 10.0 * deg, 5.0 * deg, 10.0 * deg, 15.0 * deg };
    state += other;
    ASSERT_TRUE(math::nearly_equal(state.get_semimajor(), a + 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_eccentricity(), ecc + 0.005 * one, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_inclination(), inc + 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_right_ascension(), raan + 5.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_argument_of_perigee(), w + 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_true_anomaly(), theta + 15.0 * deg, REL_TOL));
}

TEST_F(KeplerianTest, SubtractionOperator)
{
    Keplerian<frames::earth::icrf> other{ 1000.0 * km, 0.005 * one, 10.0 * deg, 5.0 * deg, 10.0 * deg, 15.0 * deg };
    Keplerian<frames::earth::icrf> result = state - other;
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), a - 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), ecc - 0.005 * one, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_inclination(), inc - 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_right_ascension(), raan - 5.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_argument_of_perigee(), w - 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_anomaly(), theta - 15.0 * deg, REL_TOL));
}

TEST_F(KeplerianTest, SubtractionAssignmentOperator)
{
    Keplerian<frames::earth::icrf> other{ 1000.0 * km, 0.005 * one, 10.0 * deg, 5.0 * deg, 10.0 * deg, 15.0 * deg };
    state -= other;
    ASSERT_TRUE(math::nearly_equal(state.get_semimajor(), a - 1000.0 * km, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_eccentricity(), ecc - 0.005 * one, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_inclination(), inc - 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_right_ascension(), raan - 5.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_argument_of_perigee(), w - 10.0 * deg, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_true_anomaly(), theta - 15.0 * deg, REL_TOL));
}

TEST_F(KeplerianTest, MultiplicationOperator)
{
    Unitless multiplier                   = 2.0 * one;
    Keplerian<frames::earth::icrf> result = state * multiplier;
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), a * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), ecc * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_inclination(), inc * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_right_ascension(), raan * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_argument_of_perigee(), w * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_anomaly(), theta * multiplier, REL_TOL));
}

TEST_F(KeplerianTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_TRUE(math::nearly_equal(state.get_semimajor(), a * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_eccentricity(), ecc * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_inclination(), inc * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_right_ascension(), raan * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_argument_of_perigee(), w * multiplier, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_true_anomaly(), theta * multiplier, REL_TOL));
}

TEST_F(KeplerianTest, DivisionByTimeOperator)
{
    Time time   = 2.0 * s;
    auto result = state / time;
    // Result is KeplerianPartial with partial derivatives
    // This test just ensures it compiles and runs
    ASSERT_NO_THROW(state / time);
}

TEST_F(KeplerianTest, DivisionByScalarOperator)
{
    Unitless divisor                      = 2.0 * one;
    Keplerian<frames::earth::icrf> result = state / divisor;
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), a / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), ecc / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_inclination(), inc / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_right_ascension(), raan / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_argument_of_perigee(), w / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_anomaly(), theta / divisor, REL_TOL));
}

TEST_F(KeplerianTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_TRUE(math::nearly_equal(state.get_semimajor(), a / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_eccentricity(), ecc / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_inclination(), inc / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_right_ascension(), raan / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_argument_of_perigee(), w / divisor, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(state.get_true_anomaly(), theta / divisor, REL_TOL));
}

TEST_F(KeplerianTest, SettersAndGetters)
{
    Keplerian<frames::earth::icrf> testState;

    testState.set_semimajor(a);
    testState.set_eccentricity(ecc);
    testState.set_inclination(inc);
    testState.set_right_ascension(raan);
    testState.set_argument_of_perigee(w);
    testState.set_true_anomaly(theta);

    ASSERT_TRUE(math::nearly_equal(testState.get_semimajor(), a, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(testState.get_eccentricity(), ecc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(testState.get_inclination(), inc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(testState.get_right_ascension(), raan, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(testState.get_argument_of_perigee(), w, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(testState.get_true_anomaly(), theta, REL_TOL));
}

TEST_F(KeplerianTest, GetMeanAnomaly)
{
    auto ma = state.get_mean_anomaly();
    // For small eccentricity and zero true anomaly, mean anomaly should be close to zero
    ASSERT_LT(abs(ma).numerical_value_in(rad), 0.1);
}

TEST_F(KeplerianTest, GetMeanMotion)
{
    auto n = state.get_mean_motion(mu);
    ASSERT_GT(n.numerical_value_in(one / s), 0.0);
}

TEST_F(KeplerianTest, ToVector)
{
    std::vector<Unitless> vec = state.force_to_vector();
    ASSERT_EQ(vec.size(), 6);
    ASSERT_TRUE(math::nearly_equal(vec[0], a / (1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[1], ecc, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[2], inc / (1.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[3], raan / (1.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[4], w / (1.0 * rad), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(vec[5], theta / (1.0 * rad), REL_TOL));
}

TEST_F(KeplerianTest, Interpolate)
{
    Keplerian<frames::earth::icrf> other{ 14000.0 * km, 0.02 * one, 100.0 * deg, 45.0 * deg, 85.0 * deg, 10.0 * deg };
    Time thisTime                         = 0.0 * s;
    Time otherTime                        = 10.0 * s;
    Time targetTime                       = 5.0 * s;
    Keplerian<frames::earth::icrf> result = state.interpolate(thisTime, otherTime, other.get_mu(), targetTime);

    // At t=5s (midpoint), expect average of start and end values
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), (a + 14000.0 * km) / 2.0, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), (ecc + 0.02 * one) / 2.0, REL_TOL));
}

TEST_F(KeplerianTest, FromCartesianConversion)
{
    // Test conversion from Cartesian to Keplerian
    Cartesian<frames::earth::icrf> cart{ 7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.546 * km / s, 0.0 * km / s };
    Keplerian<frames::earth::icrf> kep(cart.get_mu());

    // Verify the Keplerian state has reasonable values
    ASSERT_GT(kep.get_semimajor().numerical_value_in(km), 0.0);
    ASSERT_GE(kep.get_eccentricity().numerical_value_in(one), 0.0);
    ASSERT_LT(kep.get_eccentricity().numerical_value_in(one), 1.0);
}

TEST_F(KeplerianTest, FromEquinoctialConversion)
{
    // Test conversion from Equinoctial to Keplerian
    Equinoctial<frames::earth::icrf> equi{ 7000.0 * km, 0.01 * one, 0.0 * one, 0.0 * one, 0.0 * one, 0.0 * rad };
    Keplerian<frames::earth::icrf> kep(equi.get_mu());

    // Verify the Keplerian state has reasonable values
    ASSERT_GT(kep.get_semimajor().numerical_value_in(km), 0.0);
}

TEST_F(KeplerianTest, KeplerianPartialMultiplicationByTime)
{
    // Test KeplerianPartial operator* with Time
    Velocity aDot            = 1.0 * km / s;
    UnitlessPerTime eDot     = 0.001 / s;
    AngularVelocity incDot   = 0.1 * deg / s;
    AngularVelocity raanDot  = 0.2 * deg / s;
    AngularVelocity wDot     = 0.3 * deg / s;
    AngularVelocity thetaDot = 0.5 * deg / s;
    KeplerianPartial<frames::earth::icrf> partial(aDot, eDot, incDot, raanDot, wDot, thetaDot);

    Time dt                               = 2.0 * s;
    Keplerian<frames::earth::icrf> result = partial * dt;

    // Verify the result is a Keplerian state
    ASSERT_TRUE(math::nearly_equal(result.get_semimajor(), aDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_eccentricity(), eDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_inclination(), incDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_right_ascension(), raanDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_argument_of_perigee(), wDot * dt, REL_TOL));
    ASSERT_TRUE(math::nearly_equal(result.get_true_anomaly(), thetaDot * dt, REL_TOL));
}

TEST_F(KeplerianTest, KeplerianPartialStream)
{
    // Test KeplerianPartial stream operator
    Velocity aDot            = 1.0 * km / s;
    UnitlessPerTime eDot     = 0.001 / s;
    AngularVelocity incDot   = 0.1 * deg / s;
    AngularVelocity raanDot  = 0.2 * deg / s;
    AngularVelocity wDot     = 0.3 * deg / s;
    AngularVelocity thetaDot = 0.5 * deg / s;
    KeplerianPartial<frames::earth::icrf> partial(aDot, eDot, incDot, raanDot, wDot, thetaDot);

    std::stringstream ss;
    ss << partial;
    ASSERT_FALSE(ss.str().empty());
    ASSERT_NE(ss.str().find("KeplerianPartial"), std::string::npos);
}
