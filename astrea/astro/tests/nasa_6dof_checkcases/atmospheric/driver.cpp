// /*
//  * The GNU Lesser General Public License (LGPL)
//  *
//  * Copyright (c) 2025-2026 Jay Iuliano
//  *
//  * This file is part of Astrea.
//  * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
//  * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//  * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
//  * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
//  */

// #include <gtest/gtest.h>

// #include <math/operations.hpp>
// #include <units/units.hpp>

// #include <astro/platforms/vehicles/Spacecraft.hpp>
// #include <astro/propagation/equations_of_motion/TwoBody.hpp>
// #include <astro/propagation/force_models/ForceModel.hpp>
// #include <astro/propagation/numerical/Integrator.hpp>
// #include <astro/state/orbital_elements/OrbitalElements.hpp>
// #include <astro/systems/system_utilities.hpp>
// #include <astro/time/Date.hpp>
// #include <astro/time/Interval.hpp>
// #include <tests/utilities/comparisons.hpp>

// using namespace astrea;
// using namespace astro;

// using namespace mp_units;
// using mp_units::si::unit_symbols::deg;
// using mp_units::si::unit_symbols::km;
// using mp_units::si::unit_symbols::s;

// using mp_units::si::unit_symbols::m;
// using mp_units::si::unit_symbols::W;


// class Atmospheric6DofTest : public testing::Test {
//   public:
//     Atmospheric6DofTest() :
//         mu(get_mu<frames::primary.origin>()),
//         propTime(weeks(1)),
//         propInterval({ start, end }),
//         epoch(J2000)
//     {
//     }

//     void SetUp() override {}

//     const Unitless REL_TOL = 1.0e-6;
//     const Unitless ABS_TOL = 1.0e-2;

//     GravParam mu;
//     TwoBody eom;
//     ForceModel forces;
//     Integrator integrator;
//     Time propTime;
//     Date epoch;
// };


// int main(int argc, char** argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }


// TEST_F(Atmospheric6DofTest, GEO)
// {
//     // Build constellation
//     Keplerian state0 = Keplerian<frames::earth::icrf>::GEO();
//     Spacecraft geo({ Cartesian(state0, mu), epoch });
//     Vehicle vehicle{ geo };

//     // Propagate
//     const auto stateHistory = integrator.propagate(state0, propTime, eom, vehicle, true);

//     // Validate
//     for (const auto& state : stateHistory) {
//         const Keplerian kep = state.in_element_set<Keplerian<frames::earth::icrf>> ();
//         ASSERT_NO_FATAL_FAILURE(ASSERT_TRUE(nearly_equal(kep, state0, true, REL_TOL));
//     }
// }


// TEST_F(Atmospheric6DofTest, GPS)
// {
//     // Build constellation
//     Keplerian state0 = Keplerian<frames::earth::icrf>::GPS();
//     Spacecraft meo({ Cartesian(state0, mu), epoch });
//     Vehicle vehicle{ meo };

//     // Propagate
//     const auto stateHistory = integrator.propagate(state0, propTime, eom, vehicle, true);

//     // Validate
//     for (const auto& state : stateHistory) {
//         const Keplerian kep = state.in_element_set<Keplerian<frames::earth::icrf>> ();
//         ASSERT_NO_FATAL_FAILURE(ASSERT_TRUE(nearly_equal(kep, state0, true, REL_TOL));
//     }
// }


// TEST_F(Atmospheric6DofTest, GEO)
// {
//     // Build constellation
//     Keplerian state0 = Keplerian<frames::earth::icrf>::GEO();
//     Spacecraft leo({ Cartesian(state0, mu), epoch });
//     Vehicle vehicle{ leo };

//     // Propagate
//     const auto stateHistory = integrator.propagate(state0, propTime, eom, vehicle, true);

//     // Validate
//     for (const auto& state : stateHistory) {
//         const Keplerian kep = state.in_element_set<Keplerian<frames::earth::icrf>> ();
//         ASSERT_NO_FATAL_FAILURE(ASSERT_TRUE(nearly_equal(kep, state0, true, REL_TOL));
//     }
// }