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

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class EquinoctialTest : public testing::Test {
  public:
    EquinoctialTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Date epoch;
    AstrodynamicsSystem sys;

    Distance p = 7000.0 * km;
    Unitless f = 0.01 * one;
    Unitless g = 0.0 * one;
    Unitless h = 0.0 * one;
    Unitless k = 0.0 * one;
    Angle L    = 0.0 * rad;
    Equinoctial state{ p, f, g, h, k, L };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(EquinoctialTest, Stream)
{
    std::stringstream ss;
    ss << state;
    std::stringstream expected;
    expected << "[" << p << ", " << f << ", " << g << ", " << h << ", " << k << ", " << L << "] (Equinoctial)";
    ASSERT_EQ(ss.str(), expected.str());
}

TEST_F(EquinoctialTest, DefaultConstructor)
{
    Equinoctial defaultState;
    ASSERT_EQ_QUANTITY(defaultState.get_semilatus(), Distance(0.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(defaultState.get_f(), Unitless(0.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(defaultState.get_g(), Unitless(0.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(defaultState.get_h(), Unitless(0.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(defaultState.get_k(), Unitless(0.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(defaultState.get_true_longitude(), Angle(0.0 * rad), REL_TOL);
}

TEST_F(EquinoctialTest, UnitlessConstructor)
{
    Equinoctial scaledState(2.0 * one);
    ASSERT_EQ_QUANTITY(scaledState.get_semilatus(), Distance(2.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_f(), Unitless(2.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_g(), Unitless(2.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_h(), Unitless(2.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_k(), Unitless(2.0 * one), REL_TOL);
    ASSERT_EQ_QUANTITY(scaledState.get_true_longitude(), Angle(2.0 * rad), REL_TOL);
}

TEST_F(EquinoctialTest, ParameterizedConstructor) { ASSERT_NO_THROW(Equinoctial(p, f, g, h, k, L)); }

TEST_F(EquinoctialTest, EquinoctialConstructor)
{
    Equinoctial other{ 8000.0 * km, 0.02 * one, 0.01 * one, 0.005 * one, 0.003 * one, 0.5 * rad };
    ASSERT_NO_THROW(Equinoctial(other, sys.get_mu()));
}

TEST_F(EquinoctialTest, KeplerianConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    ASSERT_NO_THROW(Equinoctial(kep, sys.get_mu()));
}

TEST_F(EquinoctialTest, CartesianConstructor)
{
    Cartesian cart{ 7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.546 * km / s, 0.0 * km / s };
    ASSERT_NO_THROW(Equinoctial(cart, sys.get_mu()));
}

TEST_F(EquinoctialTest, OrbitalElementsConstructor)
{
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    OrbitalElements elements(kep);
    ASSERT_NO_THROW(Equinoctial(elements, sys.get_mu()));
}

TEST_F(EquinoctialTest, LEOStaticMethod)
{
    ASSERT_NO_THROW(Equinoctial::LEO(sys.get_mu()));
    auto leo = Equinoctial::LEO(sys.get_mu());
    ASSERT_GT(leo.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, LMEOStaticMethod)
{
    ASSERT_NO_THROW(Equinoctial::LMEO(sys.get_mu()));
    auto lmeo = Equinoctial::LMEO(sys.get_mu());
    ASSERT_GT(lmeo.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, GPSStaticMethod)
{
    ASSERT_NO_THROW(Equinoctial::GPS(sys.get_mu()));
    auto gps = Equinoctial::GPS(sys.get_mu());
    ASSERT_GT(gps.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, HMEOStaticMethod)
{
    ASSERT_NO_THROW(Equinoctial::HMEO(sys.get_mu()));
    auto hmeo = Equinoctial::HMEO(sys.get_mu());
    ASSERT_GT(hmeo.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, GEOStaticMethod)
{
    ASSERT_NO_THROW(Equinoctial::GEO(sys.get_mu()));
    auto geo = Equinoctial::GEO(sys.get_mu());
    ASSERT_GT(geo.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, CopyConstructor)
{
    ASSERT_NO_THROW(Equinoctial newEqui(state));
    Equinoctial newEqui(state);
    ASSERT_EQ_QUANTITY(newEqui.get_semilatus(), p, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_f(), f, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_g(), g, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_h(), h, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_k(), k, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_true_longitude(), L, REL_TOL);
}

TEST_F(EquinoctialTest, MoveConstructor)
{
    Equinoctial temp{ p, f, g, h, k, L };
    ASSERT_NO_THROW(Equinoctial newEqui(std::move(temp)));
}

TEST_F(EquinoctialTest, CopyAssignment)
{
    ASSERT_NO_THROW(Equinoctial newEqui = state);
    Equinoctial newEqui = state;
    ASSERT_EQ_QUANTITY(newEqui.get_semilatus(), p, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_f(), f, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_g(), g, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_h(), h, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_k(), k, REL_TOL);
    ASSERT_EQ_QUANTITY(newEqui.get_true_longitude(), L, REL_TOL);
}

TEST_F(EquinoctialTest, MoveAssignment)
{
    Equinoctial temp{ p, f, g, h, k, L };
    ASSERT_NO_THROW(Equinoctial newEqui = std::move(temp));
}

TEST_F(EquinoctialTest, EqualityOperator)
{
    Equinoctial sameState{ p, f, g, h, k, L };
    Equinoctial diffState{ p + 1000.0 * km, f, g, h, k, L };
    ASSERT_TRUE(state == sameState);
    ASSERT_FALSE(state == diffState);
    ASSERT_FALSE(state != sameState);
    ASSERT_TRUE(state != diffState);
}

TEST_F(EquinoctialTest, AdditionOperator)
{
    Equinoctial other{ 1000.0 * km, 0.005 * one, 0.003 * one, 0.002 * one, 0.001 * one, 0.1 * rad };
    Equinoctial result = state + other;
    ASSERT_EQ_QUANTITY(result.get_semilatus(), p + 1000.0 * km, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_f(), f + 0.005 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_g(), g + 0.003 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_h(), h + 0.002 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_k(), k + 0.001 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_true_longitude(), L + 0.1 * rad, REL_TOL);
}

TEST_F(EquinoctialTest, AdditionAssignmentOperator)
{
    Equinoctial other{ 1000.0 * km, 0.005 * one, 0.003 * one, 0.002 * one, 0.001 * one, 0.1 * rad };
    state += other;
    ASSERT_EQ_QUANTITY(state.get_semilatus(), p + 1000.0 * km, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_f(), f + 0.005 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_g(), g + 0.003 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_h(), h + 0.002 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_k(), k + 0.001 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_true_longitude(), L + 0.1 * rad, REL_TOL);
}

TEST_F(EquinoctialTest, SubtractionOperator)
{
    Equinoctial other{ 1000.0 * km, 0.005 * one, 0.003 * one, 0.002 * one, 0.001 * one, 0.1 * rad };
    Equinoctial result = state - other;
    ASSERT_EQ_QUANTITY(result.get_semilatus(), p - 1000.0 * km, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_f(), f - 0.005 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_g(), g - 0.003 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_h(), h - 0.002 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_k(), k - 0.001 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_true_longitude(), L - 0.1 * rad, REL_TOL);
}

TEST_F(EquinoctialTest, SubtractionAssignmentOperator)
{
    Equinoctial other{ 1000.0 * km, 0.005 * one, 0.003 * one, 0.002 * one, 0.001 * one, 0.1 * rad };
    state -= other;
    ASSERT_EQ_QUANTITY(state.get_semilatus(), p - 1000.0 * km, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_f(), f - 0.005 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_g(), g - 0.003 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_h(), h - 0.002 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_k(), k - 0.001 * one, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_true_longitude(), L - 0.1 * rad, REL_TOL);
}

TEST_F(EquinoctialTest, MultiplicationOperator)
{
    Unitless multiplier = 2.0 * one;
    Equinoctial result  = state * multiplier;
    ASSERT_EQ_QUANTITY(result.get_semilatus(), p * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_f(), f * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_g(), g * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_h(), h * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_k(), k * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_true_longitude(), L * multiplier, REL_TOL);
}

TEST_F(EquinoctialTest, MultiplicationAssignmentOperator)
{
    Unitless multiplier = 2.0 * one;
    state *= multiplier;
    ASSERT_EQ_QUANTITY(state.get_semilatus(), p * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_f(), f * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_g(), g * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_h(), h * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_k(), k * multiplier, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_true_longitude(), L * multiplier, REL_TOL);
}

TEST_F(EquinoctialTest, DivisionByTimeOperator)
{
    Time time   = 2.0 * s;
    auto result = state / time;
    // Result is EquinoctialPartial with partial derivatives
    // This test just ensures it compiles and runs
    ASSERT_NO_THROW(state / time);
}

TEST_F(EquinoctialTest, DivisionByScalarOperator)
{
    Unitless divisor   = 2.0 * one;
    Equinoctial result = state / divisor;
    ASSERT_EQ_QUANTITY(result.get_semilatus(), p / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_f(), f / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_g(), g / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_h(), h / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_k(), k / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_true_longitude(), L / divisor, REL_TOL);
}

TEST_F(EquinoctialTest, DivisionAssignmentOperator)
{
    Unitless divisor = 2.0 * one;
    state /= divisor;
    ASSERT_EQ_QUANTITY(state.get_semilatus(), p / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_f(), f / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_g(), g / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_h(), h / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_k(), k / divisor, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_true_longitude(), L / divisor, REL_TOL);
}

TEST_F(EquinoctialTest, Getters)
{
    ASSERT_EQ_QUANTITY(state.get_semilatus(), p, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_f(), f, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_g(), g, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_h(), h, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_k(), k, REL_TOL);
    ASSERT_EQ_QUANTITY(state.get_true_longitude(), L, REL_TOL);
}

TEST_F(EquinoctialTest, ToVector)
{
    std::vector<Unitless> vec = state.force_to_vector();
    ASSERT_EQ(vec.size(), 6);
    ASSERT_EQ_QUANTITY(vec[0], p / (1.0 * km), REL_TOL);
    ASSERT_EQ_QUANTITY(vec[1], f, REL_TOL);
    ASSERT_EQ_QUANTITY(vec[2], g, REL_TOL);
    ASSERT_EQ_QUANTITY(vec[3], h, REL_TOL);
    ASSERT_EQ_QUANTITY(vec[4], k, REL_TOL);
    ASSERT_EQ_QUANTITY(vec[5], L / (1.0 * rad), REL_TOL);
}

TEST_F(EquinoctialTest, Interpolate)
{
    Equinoctial other{ 14000.0 * km, 0.02 * one, 0.01 * one, 0.005 * one, 0.003 * one, 0.5 * rad };
    Time thisTime      = 0.0 * s;
    Time otherTime     = 10.0 * s;
    Time targetTime    = 5.0 * s;
    Equinoctial result = state.interpolate(thisTime, otherTime, other, sys.get_mu(), targetTime);

    // At t=5s (midpoint), expect average of start and end values
    ASSERT_EQ_QUANTITY(result.get_semilatus(), (p + 14000.0 * km) / 2.0, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_f(), (f + 0.02 * one) / 2.0, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_g(), (g + 0.01 * one) / 2.0, REL_TOL);
}

TEST_F(EquinoctialTest, FromKeplerianConversion)
{
    // Test conversion from Keplerian to Equinoctial
    Keplerian kep{ 7000.0 * km, 0.01 * one, 98.0 * deg, 40.0 * deg, 80.0 * deg, 0.0 * deg };
    Equinoctial equi(kep, sys.get_mu());

    // Verify the Equinoctial state has reasonable values
    ASSERT_GT(equi.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, FromCartesianConversion)
{
    // Test conversion from Cartesian to Equinoctial
    Cartesian cart{ 7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.546 * km / s, 0.0 * km / s };
    Equinoctial equi(cart, sys.get_mu());

    // Verify the Equinoctial state has reasonable values
    ASSERT_GT(equi.get_semilatus().numerical_value_in(km), 0.0);
}

TEST_F(EquinoctialTest, EquinoctialPartialMultiplicationByTime)
{
    // Test EquinoctialPartial operator* with Time
    Velocity pDot        = 1.0 * km / s;
    UnitlessPerTime fDot = 0.001 / s;
    UnitlessPerTime gDot = 0.002 / s;
    UnitlessPerTime hDot = 0.003 / s;
    UnitlessPerTime kDot = 0.004 / s;
    AngularRate LDot     = 0.5 * rad / s;
    EquinoctialPartial partial(pDot, fDot, gDot, hDot, kDot, LDot);

    Time dt            = 2.0 * s;
    Equinoctial result = partial * dt;

    // Verify the result is an Equinoctial state
    ASSERT_EQ_QUANTITY(result.get_semilatus(), pDot * dt, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_f(), fDot * dt, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_g(), gDot * dt, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_h(), hDot * dt, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_k(), kDot * dt, REL_TOL);
    ASSERT_EQ_QUANTITY(result.get_true_longitude(), LDot * dt, REL_TOL);
}

TEST_F(EquinoctialTest, EquinoctialPartialStream)
{
    // Test EquinoctialPartial stream operator
    Velocity pDot        = 1.0 * km / s;
    UnitlessPerTime fDot = 0.001 / s;
    UnitlessPerTime gDot = 0.002 / s;
    UnitlessPerTime hDot = 0.003 / s;
    UnitlessPerTime kDot = 0.004 / s;
    AngularRate LDot     = 0.5 * rad / s;
    EquinoctialPartial partial(pDot, fDot, gDot, hDot, kDot, LDot);

    std::stringstream ss;
    ss << partial;
    ASSERT_FALSE(ss.str().empty());
    ASSERT_NE(ss.str().find("EquinoctialPartial"), std::string::npos);
}
