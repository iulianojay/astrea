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

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/equations_of_motion/StateTransitionMatrix.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/attitude/Attitude.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

using namespace astrea;
using namespace astro;

/**
 * @brief Mock implementation of EquationsOfMotion for testing purposes.
 */
class MockEquationsOfMotion : public EquationsOfMotion {
  public:
    MockEquationsOfMotion() = default;
    MockEquationsOfMotion(const ForceModel& forces) :
        EquationsOfMotion(forces)
    {
    }

    // Implementation of pure virtual methods
    OrbitalElementPartials compute_dynamics(
        const State& state,
        const Vehicle& vehicle,
        const ForceVector<frames::primary>& perts,
        const ForceVector<frames::primary>& control
    ) const override
    {
        // Return simple mock dynamics (zero acceleration for testing)
        return CartesianPartial(0.0 * km / s, 0.0 * km / s, 0.0 * km / s, 0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s));
    }

    constexpr std::size_t get_expected_set_id() const override
    {
        return OrbitalElements::get_set_id<Cartesian<frames::primary>>();
    }
};

class EquationsOfMotionTest : public testing::Test {
  public:
    EquationsOfMotionTest() {}

    void SetUp() override
    {
        // Set up test state with basic Cartesian<frames::primary> elements
        cart  = Cartesian<frames::primary>::LEO(get_mu<frames::primary::origin>());
        state = State(cart, epoch, sys);
    }

    const Unitless REL_TOL = 1.0e-6;

    ForceModel forceModel;
    ForceVector<frames::primary> noForce;
    TorqueVector<frames::primary> noTorque;
    Vehicle vehicle;
    CelestialBody sys;
    Date epoch;
    Cartesian<frames::primary> cart;
    State state;
    MockEquationsOfMotion eomDefault;
    MockEquationsOfMotion eomWithForces{ forceModel };
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Test constructors
TEST_F(EquationsOfMotionTest, DefaultConstructor) { ASSERT_NO_THROW(MockEquationsOfMotion()); }

TEST_F(EquationsOfMotionTest, ConstructorWithForceModel) { ASSERT_NO_THROW(MockEquationsOfMotion(forceModel)); }

// Test get_expected_set_id method
TEST_F(EquationsOfMotionTest, GetExpectedSetId)
{
    ASSERT_EQ(eomDefault.get_expected_set_id(), OrbitalElements::get_set_id<Cartesian<frames::primary>>());
    ASSERT_EQ(eomWithForces.get_expected_set_id(), OrbitalElements::get_set_id<Cartesian<frames::primary>>());
}

// Test operator() method
TEST_F(EquationsOfMotionTest, OperatorCall)
{
    // Test with default constructor (no force model)
    StatePartial result1;
    ASSERT_NO_THROW(result1 = eomDefault(state, vehicle));

    // Verify the result has proper structure
    ASSERT_EQ(result1.get_epoch(), epoch);

    // Test with force model
    StatePartial result2;
    ASSERT_NO_THROW(result2 = eomWithForces(state, vehicle));

    // Verify the result has proper structure
    ASSERT_EQ(result2.get_epoch(), epoch);
}

// Test compute_dynamics method
TEST_F(EquationsOfMotionTest, ComputeDynamics)
{
    OrbitalElementPartials result;
    ASSERT_NO_THROW(result = eomDefault.compute_dynamics(state, vehicle, noForce, noForce));

    // Check that we get a valid CartesianPartial (our mock returns zeros)
    auto cartResult = std::get<CartesianPartial<frames::primary>>(result.extract());
    EXPECT_TRUE(math::nearly_equal(cartResult.get_vx(), 0.0 * km / s));
    EXPECT_TRUE(math::nearly_equal(cartResult.get_vy(), 0.0 * km / s));
    EXPECT_TRUE(math::nearly_equal(cartResult.get_vz(), 0.0 * km / s));
    EXPECT_TRUE(math::nearly_equal(cartResult.get_ax(), 0.0 * km / (s * s)));
    EXPECT_TRUE(math::nearly_equal(cartResult.get_ay(), 0.0 * km / (s * s)));
    EXPECT_TRUE(math::nearly_equal(cartResult.get_az(), 0.0 * km / (s * s)));
}

// Test compute_kinematics method with attitude
TEST_F(EquationsOfMotionTest, ComputeKinematicsWithAttitude)
{
    // Create a state with attitude
    Attitude attitude;
    State stateWithAttitude = state;
    stateWithAttitude.set_attitude(attitude);

    AttitudePartials result;
    ASSERT_NO_THROW(result = eomDefault.compute_kinematics(stateWithAttitude, vehicle, noTorque, noTorque));

    // Verify that we get valid attitude partials (check structure exists)
    ASSERT_NO_THROW(result.force_to_vector());
}

// Test operator() with different force scenarios
TEST_F(EquationsOfMotionTest, OperatorCallWithForces)
{
    // Test with non-zero forces (still using mock that returns zeros)
    ForceVector<frames::primary> testForce(1.0 * N, 0.0 * N, 0.0 * N);
    TorqueVector<frames::primary> testTorque(0.1 * N * m, 0.0 * N * m, 0.0 * N * m);

    StatePartial result;
    ASSERT_NO_THROW(result = eomDefault(state, vehicle));

    // Verify basic structure
    ASSERT_EQ(result.get_epoch(), epoch);
}

// Test operator() with attitude state
TEST_F(EquationsOfMotionTest, OperatorCallWithAttitude)
{
    // Create state with attitude
    Attitude attitude;
    State stateWithAttitude = state;
    stateWithAttitude.set_attitude(attitude);

    StatePartial result;
    ASSERT_NO_THROW(result = eomDefault(stateWithAttitude, vehicle));

    // Verify the result has proper structure and includes attitude partials
    ASSERT_EQ(result.get_epoch(), epoch);

    // The result should include attitude partials when attitude is present
    auto vectorResult = result.force_to_vector();
    ASSERT_GT(vectorResult.size(), 6); // Should have more than just 6 orbital elements
}

// Test operator() without attitude state
TEST_F(EquationsOfMotionTest, OperatorCallWithoutAttitude)
{
    // Use default state without attitude
    StatePartial result;
    ASSERT_NO_THROW(result = eomDefault(state, vehicle));

    // Verify the result has proper structure
    ASSERT_EQ(result.get_epoch(), epoch);

    // The result should only have orbital elements (6 components)
    auto vectorResult = result.force_to_vector();
    ASSERT_EQ(vectorResult.size(), 6); // Should have exactly 6 orbital elements
}

// Test that different EOM objects can be created and used
TEST_F(EquationsOfMotionTest, MultipleInstances)
{
    MockEquationsOfMotion eom1;
    MockEquationsOfMotion eom2(forceModel);

    StatePartial result1, result2;
    ASSERT_NO_THROW(result1 = eom1(state, vehicle));
    ASSERT_NO_THROW(result2 = eom2(state, vehicle));
}

// Test virtual destructor functionality
TEST_F(EquationsOfMotionTest, VirtualDestructor)
{
    // Test that we can properly delete through base class pointer
    std::unique_ptr<EquationsOfMotion> eomPtr = std::make_unique<MockEquationsOfMotion>();
    ASSERT_NO_THROW(eomPtr.reset()); // Should call virtual destructor without issues
}