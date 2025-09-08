#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <stdio.h>

#include <gtest/gtest.h>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/international.h>
#include <mp-units/systems/isq.h>
#include <mp-units/systems/si.h>

#include <math/test_util.hpp>

#include <astro/astro.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


class J2MeanVopPropagationTest : public testing::Test {
  public:
    J2MeanVopPropagationTest() :
        eom(sys),
        start(seconds(0)),
        end(weeks(1)),
        propInterval({ start, end }),
        epoch(J2000)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;
    const Unitless ABS_TOL = 1.0e-2;

    AstrodynamicsSystem sys;
    J2MeanVop eom;
    ForceModel forces;
    Integrator integrator;
    Time start;
    Time end;
    Interval propInterval;
    Date epoch;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(J2MeanVopPropagationTest, GEONoForces)
{
    // Build constellation
    Keplerian state0 = Keplerian::GEO();
    Spacecraft geo({ state0, epoch, sys });
    Vehicle vehicle{ geo };

    // Propagate
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Validate
    for (const auto& [time, state] : stateHistory) {
        const Keplerian kep = state.in_element_set<Keplerian>();
        ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(kep, state0, true, REL_TOL));
    }
}


TEST_F(J2MeanVopPropagationTest, GPSNoForces)
{
    // Build constellation
    Keplerian state0 = Keplerian::GPS();
    Spacecraft meo({ state0, epoch, sys });
    Vehicle vehicle{ meo };

    // Propagate
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Validate
    for (const auto& [time, state] : stateHistory) {
        const Keplerian kep = state.in_element_set<Keplerian>();
        ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(kep, state0, true, REL_TOL));
    }
}


TEST_F(J2MeanVopPropagationTest, LEONoForces)
{
    // Build constellation
    Keplerian state0 = Keplerian::LEO();
    Spacecraft leo({ state0, epoch, sys });
    Vehicle vehicle{ leo };

    // Propagate
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Validate
    for (const auto& [time, state] : stateHistory) {
        const Keplerian kep = state.in_element_set<Keplerian>();
        ASSERT_NO_FATAL_FAILURE(ASSERT_EQ_ORB_ELEM(kep, state0, true, REL_TOL));
    }
}