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
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

class DummyForce : public PerturbingForce {
  public:
    DummyForce() = default;
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        return { .force = AccelerationVector<frames::earth::icrf>(0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s)) };
    }
};

class ForceTest : public testing::Test {
  public:
    ForceTest() = default;
    void SetUp() override {}

    DummyForce force;
    Date date;
    Cartesian cart;
    Vehicle vehicle;
    AstrodynamicsSystem sys;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(ForceTest, DefaultConstructor) { ASSERT_NO_THROW(DummyForce()); }

TEST_F(ForceTest, ComputeForce)
{
    const State state(cart, date, sys);
    auto [accel, torque] = force.compute_perturbation(state, vehicle);
    ASSERT_EQ(accel.get_x(), 0.0 * km / (s * s));
    ASSERT_EQ(accel.get_y(), 0.0 * km / (s * s));
    ASSERT_EQ(accel.get_z(), 0.0 * km / (s * s));
}
