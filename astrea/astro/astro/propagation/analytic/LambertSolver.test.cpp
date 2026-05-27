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
#include <astro/frames/frame_registry.hpp>
#include <astro/propagation/analytic/LambertSolver.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

class LambertSolverTest : public testing::Test {
  public:
    LambertSolverTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;
    const GravParam mu     = get_mu<frames::primary.origin>();

    // Numbers from Vallado, 5th Ed., Ex. 7-5
    RadiusVector<frames::earth::icrf> r0{ 15945.34 * km, 0.0 * km, 0.0 * km }, rf{ 12214.83899 * km, 10249.46731 * km, 0.0 * km };
    VelocityVector<frames::earth::icrf> v0{ 2.058913 * km / s, 2.915964 * km / s }, vf{ -3.451565 * km / s, 0.910314 * km / s };
    Time dt = 76.0 * min;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(LambertSolverTest, SolveRV)
{
    const Cartesian<frames::earth::icrf> result = LambertSolver::solve<frames::earth::icrf>({ r0, v0 }, dt, mu);
    ASSERT_TRUE(nearly_equal(result.get_position(), rf, REL_TOL));
    ASSERT_TRUE(nearly_equal(result.get_velocity(), vf, REL_TOL));
}

TEST_F(LambertSolverTest, SolveRR)
{
    const auto [res0, resf] = LambertSolver::solve<frames::earth::icrf>(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE);
    ASSERT_TRUE(nearly_equal(res0, v0, REL_TOL));
    ASSERT_TRUE(nearly_equal(resf, vf, REL_TOL));
}

TEST_F(LambertSolverTest, SolveOptimalMinimumEnergy)
{
    const auto sol =
        LambertSolver::solve<frames::earth::icrf>(r0, rf, mu, LambertSolver::OrbitDirection::PROGRADE, LambertSolver::SolutionType::MINIMUM_ENERGY);

    // Round-trip: feeding the returned tof back into the r&r solver must reproduce the same velocities
    const auto [v0Check, vfCheck] =
        LambertSolver::solve<frames::earth::icrf>(r0, rf, sol.tof, mu, LambertSolver::OrbitDirection::PROGRADE);
    ASSERT_TRUE(nearly_equal(v0Check, sol.v0, REL_TOL));
    ASSERT_TRUE(nearly_equal(vfCheck, sol.vf, REL_TOL));
}

TEST_F(LambertSolverTest, SolveOptimalMinimumTime)
{
    const auto sol =
        LambertSolver::solve<frames::earth::icrf>(r0, rf, mu, LambertSolver::OrbitDirection::PROGRADE, LambertSolver::SolutionType::MINIMUM_TIME);

    // Round-trip: feeding the returned tof back into the r&r solver must reproduce the same velocities
    const auto [v0Check, vfCheck] =
        LambertSolver::solve<frames::earth::icrf>(r0, rf, sol.tof, mu, LambertSolver::OrbitDirection::PROGRADE);
    ASSERT_TRUE(nearly_equal(v0Check, sol.v0, REL_TOL));
    ASSERT_TRUE(nearly_equal(vfCheck, sol.vf, REL_TOL));
}

TEST_F(LambertSolverTest, MinimumTimeHasShorterTOFThanMinimumEnergy)
{
    const auto minEnergy =
        LambertSolver::solve<frames::earth::icrf>(r0, rf, mu, LambertSolver::OrbitDirection::PROGRADE, LambertSolver::SolutionType::MINIMUM_ENERGY);
    const auto minTime =
        LambertSolver::solve<frames::earth::icrf>(r0, rf, mu, LambertSolver::OrbitDirection::PROGRADE, LambertSolver::SolutionType::MINIMUM_TIME);

    EXPECT_LT(minTime.tof.numerical_value_in(s), minEnergy.tof.numerical_value_in(s));
}

// ── Multi-revolution tests ────────────────────────────────────────────────────

class LambertSolverMultiRevTest : public testing::Test {
  public:
    LambertSolverMultiRevTest() :
        mu(get_mu<frames::primary.origin>())
    {
    }

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    const GravParam mu;

    // ISS-like LEO endpoints separated by ~90° in the orbit plane
    RadiusVector<frames::earth::icrf> r0{ 6778.0 * km, 0.0 * km, 0.0 * km };
    RadiusVector<frames::earth::icrf> rf{ 0.0 * km, 6778.0 * km, 0.0 * km };
};

TEST_F(LambertSolverMultiRevTest, N1LeftBranchRoundTrip)
{
    // 1-rev LEFT branch: choose a TOF well above the 1-rev minimum
    // T_orbit for ISS ≈ 5559 s; use 1.5× that for a safe margin
    const Time dt = 8000.0 * s;

    const auto [v0Res, vfRes] =
        LambertSolver::solve(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE, 1, LambertSolver::MultiRevBranch::LEFT);

    // Physics round-trip: specific orbital energy must be identical at both endpoints (same orbit)
    const auto eps0 = v0Res.norm() * v0Res.norm() * 0.5 - mu / r0.norm();
    const auto epsf = vfRes.norm() * vfRes.norm() * 0.5 - mu / rf.norm();
    ASSERT_TRUE(math::nearly_equal(eps0, epsf, REL_TOL));

    // Specific angular momentum magnitude must also match
    ASSERT_TRUE(math::nearly_equal(r0.cross(v0Res).norm(), rf.cross(vfRes).norm(), REL_TOL));
}

TEST_F(LambertSolverMultiRevTest, N1RightBranchRoundTrip)
{
    const Time dt = 8000.0 * s;

    const auto [v0Res, vfRes] =
        LambertSolver::solve(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE, 1, LambertSolver::MultiRevBranch::RIGHT);

    // Physics round-trip: specific orbital energy must be identical at both endpoints (same orbit)
    const auto eps0 = v0Res.norm() * v0Res.norm() * 0.5 - mu / r0.norm();
    const auto epsf = vfRes.norm() * vfRes.norm() * 0.5 - mu / rf.norm();
    ASSERT_TRUE(math::nearly_equal(eps0, epsf, REL_TOL));

    // Specific angular momentum magnitude must also match
    ASSERT_TRUE(math::nearly_equal(r0.cross(v0Res).norm(), rf.cross(vfRes).norm(), REL_TOL));
}

TEST_F(LambertSolverMultiRevTest, TwoBranchesProduceDifferentVelocities)
{
    const Time dt = 8000.0 * s;

    const auto [v0Left, vfLeft] =
        LambertSolver::solve(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE, 1, LambertSolver::MultiRevBranch::LEFT);
    const auto [v0Right, vfRight] =
        LambertSolver::solve(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE, 1, LambertSolver::MultiRevBranch::RIGHT);

    // The two branches must yield distinct initial velocities
    const bool v0Same = (v0Left - v0Right).norm().numerical_value_in(km / s) < 1e-6;
    EXPECT_FALSE(v0Same);
}

TEST_F(LambertSolverMultiRevTest, BelowMinimumTOFThrows)
{
    // 1-rev min TOF for a circular 6778 km orbit is roughly T_orbit/2 (half-period ≈ 2779 s)
    // Use a very short TOF that is guaranteed to be below the multi-rev minimum
    const Time dt = 100.0 * s;

    EXPECT_THROW(LambertSolver::solve(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE, 1, LambertSolver::MultiRevBranch::LEFT), std::runtime_error);
}

TEST_F(LambertSolverMultiRevTest, ZeroRevsThrows)
{
    const Time dt = 8000.0 * s;

    EXPECT_THROW(LambertSolver::solve(r0, rf, dt, mu, LambertSolver::OrbitDirection::PROGRADE, 0, LambertSolver::MultiRevBranch::LEFT), std::invalid_argument);
}
