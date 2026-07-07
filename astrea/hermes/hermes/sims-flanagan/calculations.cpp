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

#include <hermes/sims-flanagan/calculations.hpp>

namespace astrea {
namespace hermes {

ContinuityViolations compute_continuity_violations(const Trajectory& trajectory)
{
    Distance positionViolation = 0.0 * km;
    Velocity velocityViolation = 0.0 * km / s;
    for (const auto& segment : trajectory.get_segments()) {
        const auto& initialState = segment.get_initial_state().get_cartesian();
        const auto& finalState   = segment.get_final_state().get_cartesian();

        const auto positionDiff = finalState.get_position() - initialState.get_position();
        const auto velocityDiff = finalState.get_velocity() - initialState.get_velocity();

        positionViolation += positionDiff.norm();
        velocityViolation += velocityDiff.norm();
    }
    return { .positionViolation = positionViolation, .velocityViolation = velocityViolation };
}

DeltaVCosts compute_total_delta_v(const Trajectory& trajectory)
{
    Velocity totalDeltaV = 0.0 * km / s;
    for (const auto& segment : trajectory.get_segments()) {
        for (const auto& burn : segment.get_burns()) {
            totalDeltaV += burn.get_delta_v().norm();
        }
    }
    for (const auto& burn : trajectory.get_burns()) {
        totalDeltaV += burn.get_delta_v().norm();
    }
    const Velocity initialBurnDV = trajectory.get_initial_burn().get_delta_v().norm();
    const Velocity finalBurnDV   = trajectory.get_final_burn().get_delta_v().norm();

    return { .initialBurnDV = initialBurnDV, .finalBurnDV = finalBurnDV, .totalDeltaV = totalDeltaV };
}

Time compute_total_time_of_flight(const Trajectory& trajectory)
{
    Time totalTimeOfFlight = 0.0 * s;
    for (const auto& segment : trajectory.get_segments()) {
        totalTimeOfFlight += segment.get_duration();
    }
    return totalTimeOfFlight;
}

} // namespace hermes
} // namespace astrea