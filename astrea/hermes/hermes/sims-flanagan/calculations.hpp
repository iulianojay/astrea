/**
 * @file calculations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the calculations module
 * @date 2026-04-24
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

#include <astro/astro.hpp>
#include <units/units.hpp>

#include <hermes/sims-flanagan/model.hpp>

namespace astrea {
namespace hermes {

struct ContinuityViolations {
    Distance positionViolation; //!< The position continuity violation for the given trajectory
    Velocity velocityViolation; //!< The velocity continuity violation for the given trajectory
};

struct DeltaVCosts {
    Velocity initialBurnDV; //!< The delta-v for the initial burn of the given trajectory
    Velocity finalBurnDV;   //!< The delta-v for the final burn of the given trajectory
    Velocity totalDeltaV;   //!< The total delta-v for the given trajectory
};

/**
 * @brief Compute the position and velocity continuity violations for a given trajectory
 *
 * @param trajectory The trajectory to compute the continuity violations for
 * @return ContinuityViolations The position and velocity continuity violations for the given trajectory
 */
ContinuityViolations compute_continuity_violations(const Trajectory& trajectory);

/**
 * @brief Compute the total delta-v for a given trajectory
 *
 * @param trajectory The trajectory to compute the total delta-v for
 * @return DeltaVCosts The delta-v costs for the given trajectory
 */
DeltaVCosts compute_total_delta_v(const Trajectory& trajectory);

/**
 * @brief Compute the total time of flight for a given trajectory
 *
 * @param trajectory The trajectory to compute the total time of flight for
 * @return Time The total time of flight for the given trajectory
 */
Time compute_total_time_of_flight(const Trajectory& trajectory);

} // namespace hermes
} // namespace astrea