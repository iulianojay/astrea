/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <astro/astro.hpp>
#include <units/units.hpp>

#include <hermes/hermes.hpp>

using namespace astrea;
using namespace astro;
using namespace hermes;


class SimsFlanaganTest : public testing::Test {
  public:
    SimsFlanaganTest() :
        eom(forces),
        propTime(weeks(1)),
        epoch(J2000)
    {
        state = astro::State({ Keplerian<frames::primary>::LEO() }, epoch);
        integrator.set_equations_of_motion(eom);
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;
    const Unitless ABS_TOL = 1.0e-2;

    CowellsMethod eom;
    ForceModel forces;
    Integrator integrator;
    Time propTime;
    std::size_t nSegments              = 2;
    std::size_t nSubsegmentsPerSegment = 2;
    Date epoch;
    Vehicle vehicle;
    astro::State state;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(SimsFlanaganTest, TransferOptimization)
{
    Trajectory trajectory = Trajectory::ballistic(integrator, vehicle, state, propTime, nSegments, nSubsegmentsPerSegment);
}

// Regression: previously propagate_no_storage left the integrator _store flag as false, causing
// subsequent calls to propagate(store=true) to return only the final state instead of the full history.
TEST_F(SimsFlanaganTest, BallisticPropagateProducesFullStateHistory)
{
    Trajectory trajectory = Trajectory::ballistic(integrator, vehicle, state, propTime, nSegments, nSubsegmentsPerSegment);

    const astro::StateHistory history = trajectory.propagate(integrator, vehicle, true);

    // With a fixed 1-minute timestep over 1 week, there should be many states.
    // We assert well above 1 to catch the regression where only the final state was stored.
    const std::size_t minExpectedStates = nSegments * nSubsegmentsPerSegment * 2;
    EXPECT_GT(history.size(), minExpectedStates) << "State history has too few states (" << history.size()
                                                 << "). The store=true path may not be propagating correctly.";
}
