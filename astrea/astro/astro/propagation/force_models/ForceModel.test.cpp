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

#include <math/comparisons.hpp>
#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
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
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class DummyForce : public PerturbingForce {
  public:
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        return Perturbation{ .force = { 0.0 * N }, .torque = { 0.0 * N * m } };
    }
};

class ForceModelTest : public testing::Test {
  public:
    ForceModelTest(){};
    void SetUp() override {}

    DummyForce force;
    Date date;
    Vehicle vehicle;
    AstrodynamicsSystem sys;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(ForceModelTest, DefaultConstructor) { ASSERT_NO_THROW(ForceModel()); }

TEST(ForceModelTest, AddForce)
{
    ForceModel model;
    auto& ptr = model.add<DummyForce>();
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelTest, ComputeForces)
{
    ForceModel model;
    model.add<DummyForce>();

    Vehicle vehicle;
    AstrodynamicsSystem sys;
    Date date;
    Cartesian cart;
    State state(cart, date, sys);

    auto [accel, torque] = model.compute_perturbations(state, vehicle);
    EXPECT_EQ(accel.get_x(), 0.0 * N);
    EXPECT_EQ(accel.get_y(), 0.0 * N);
    EXPECT_EQ(accel.get_z(), 0.0 * N);
    EXPECT_EQ(torque.get_x(), 0.0 * N * m);
    EXPECT_EQ(torque.get_y(), 0.0 * N * m);
    EXPECT_EQ(torque.get_z(), 0.0 * N * m);
}

TEST(ForceModelTest, AtByName)
{
    ForceModel model;
    model.add<DummyForce>();
    std::string name = typeid(DummyForce).name();
    auto& ptr        = model.at(name);
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelTest, GetByType)
{
    ForceModel model;
    model.add<DummyForce>();
    auto& ptr = model.get<DummyForce>();
    EXPECT_NE(ptr.get(), nullptr);
}
