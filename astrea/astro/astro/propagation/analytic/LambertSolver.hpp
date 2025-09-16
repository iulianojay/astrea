/**
 * @file LambertSolver.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the LambertSolver class, which provides methods for solving Lambert's problem.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/CartesianVector.hpp>
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
    static std::pair<VelocityVector<EarthCenteredInertial>, VelocityVector<EarthCenteredInertial>> solve(
        const RadiusVector<EarthCenteredInertial>& r0,
        const RadiusVector<EarthCenteredInertial>& rf,
        const Time& dt,
        const GravParam& mu,
        const OrbitDirection& direction
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

// TODO: Implement Battin algorithm
// TODO: give min time and min energy options

} // namespace astro
} // namespace astrea