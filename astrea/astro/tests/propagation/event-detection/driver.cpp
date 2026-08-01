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

#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>
#include <astro/propagation/event_detection/Event.hpp>
#include <astro/propagation/event_detection/events/ImpulsiveBurn.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


class EventDetectionTest : public testing::Test {
  public:
    EventDetectionTest() :
        mu(get_mu<frames::primary.origin>()),
        propTime(weeks(1)),
        epoch(J2000)
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;
    const Unitless ABS_TOL = 1.0e-2;

    GravParam mu;
    ForceModel forces;
    Integrator integrator;
    Time propTime;
    Date epoch;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(EventDetectionTest, NoThrust)
{
    // Build constellation
    Keplerian<frames::earth::icrf> kep0 = Keplerian<frames::earth::icrf>::LEO();
    State state{ kep0, epoch };
    Spacecraft leo;
    Vehicle vehicle{ leo };

    // Impulsive burn event
    Event impulse = Event{ ImpulsiveBurn() };
    integrator.add_event(impulse);

    // Propagate
    const auto stateHistory = integrator.propagate(state, propTime, vehicle);

    // Validate
    for (const auto& state : stateHistory) {
        const Keplerian<frames::earth::icrf> kep = state.in_element_set<Keplerian<frames::earth::icrf>>();
        ASSERT_NO_FATAL_FAILURE(ASSERT_TRUE(nearly_equal(kep, kep0, true, REL_TOL)));
    }
}


TEST_F(EventDetectionTest, ImpulsiveBurn)
{
    // Build constellation
    const Keplerian<frames::earth::icrf> kep0 = Keplerian<frames::earth::icrf>::LEO();
    const ThrusterParameters thrusterParams(1.0e3 * mp_units::si::unit_symbols::kN);
    const State state{ kep0, epoch };

    Spacecraft leo;
    leo.attach_payload(thrusterParams);
    Vehicle vehicle{ leo };

    // Impulsive burn event
    Event impulse = Event{ ImpulsiveBurn() };
    integrator.add_event(impulse);

    // Propagate
    const auto stateHistory = integrator.propagate(state, propTime, vehicle);

    // Validate
    std::cout << "state0: " << kep0 << std::endl;
    bool elementsChanged = false;
    for (const auto& state : stateHistory) {
        const Keplerian<frames::earth::icrf> kep = state.in_element_set<Keplerian<frames::earth::icrf>>();
        std::cout << "\t" << state.get_epoch() << ": " << kep << std::endl;
        if (!nearly_equal(kep, kep0, true, REL_TOL)) {
            elementsChanged = true;
            break;
        }
    }
    ASSERT_TRUE(elementsChanged);
}