/**
 * @file LambertSolver.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the LambertSolver class, which provides methods for solving Lambert's problem.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class for solving Lambert's problem.
 *
 * This class provides methods for solving Lambert's problem, which involves finding
 * the orbital trajectory between two points in space given certain initial conditions.
 */
class LambertSolver {
  public:
    /**
     * @brief Deleted constructor for LambertSolver.
     *
     * This constructor is deleted to prevent instantiation of the LambertSolver class.
     */
    LambertSolver() = delete;

    /**
     * @brief Deleted destructor for LambertSolver.
     *
     * This destructor is deleted to prevent destruction of the LambertSolver class.
     */
    ~LambertSolver() = delete;

    /**
     * @brief Enum class for orbit direction.
     */
    enum class OrbitDirection : EnumType {
        PROGRADE,  //!< Prograde orbit
        RETROGRADE //!< Retrograde orbit
    };

    /**
     * @brief Enum class for the type of optimal Lambert solution.
     */
    enum class SolutionType : EnumType {
        MINIMUM_ENERGY, //!< Minimum delta-v (minimum semi-major axis) transfer
        MINIMUM_TIME    //!< Minimum time of flight (parabolic) transfer
    };

    /**
     * @brief Result structure for optimal Lambert solutions.
     */
    struct Solution {
        Time tof;                               //!< Time of flight for the transfer
        VelocityVector<frames::earth::icrf> v0; //!< Initial velocity vector at r0
        VelocityVector<frames::earth::icrf> vf; //!< Final velocity vector at rf
    };

    /**
     * @brief Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution.
     *
     * @param state0 The initial state (position and velocity) of the spacecraft.
     * @param dt The time of flight.
     * @param mu The gravitational parameter of the central body.
     * @return The final state (position and velocity) of the spacecraft.
     */
    static Cartesian solve(const Cartesian& state0, const Time& dt, const GravParam& mu);

    /**
     * @brief Solve Lambert's problem for a given initial and final state. Returns the minimum energy solution.
     *
     * @param r0 The initial position of the spacecraft.
     * @param rf The final position of the spacecraft.
     * @param dt The time of flight.
     * @param mu The gravitational parameter of the central body.
     * @param direction The direction of the orbit (prograde or retrograde).
     * @return A pair of velocity vectors (initial and final) for the spacecraft.
     */
    static std::pair<VelocityVector<frames::earth::icrf>, VelocityVector<frames::earth::icrf>> solve(
        const RadiusVector<frames::earth::icrf>& r0,
        const RadiusVector<frames::earth::icrf>& rf,
        const Time& dt,
        const GravParam& mu,
        const OrbitDirection& direction
    );

    /**
     * @brief Solve Lambert's problem for an optimal trajectory without a fixed time of flight.
     *
     * @param r0 The initial position of the spacecraft.
     * @param rf The final position of the spacecraft.
     * @param mu The gravitational parameter of the central body.
     * @param direction The direction of the orbit (prograde or retrograde).
     * @param solutionType MINIMUM_ENERGY returns the minimum delta-v (minimum semi-major axis) transfer;
     *                     MINIMUM_TIME returns the minimum time of flight (parabolic) transfer.
     * @return A Solution containing the time of flight and the initial/final velocity vectors.
     */
    static Solution solve(
        const RadiusVector<frames::earth::icrf>& r0,
        const RadiusVector<frames::earth::icrf>& rf,
        const GravParam& mu,
        const OrbitDirection& direction,
        const SolutionType& solutionType
    );

  private:
    static constexpr unsigned ITER_MAX = 1e4;                     //!< Maximum number of iterations for the solver.
    static constexpr Unitless TOL      = 1.0e-12 * mp_units::one; //!< Tolerance for convergence.

    /**
     * @brief Evaluate the Stumpff functions for a given input.
     *
     * @param z The input value.
     * @return A pair of Stumpff function values (Cz, Sz).
     */
    static std::pair<Unitless, Unitless> evaluate_stumpff(const Unitless& z);
};

} // namespace astro
} // namespace astrea