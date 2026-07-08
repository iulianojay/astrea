/**
 * @file settings.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the settings module
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

#include <vector>

#include <astro/astro.hpp>
#include <units/units.hpp>

#include <hermes/hermes.fwd.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A struct representing the settings for a Sims-Flanagan trajectory
 */
struct SegmentSettings {
    std::size_t nSubsegments; //!< The number of subsegments in the segment
    bool isForward;           //!< Whether the segment is forward-propagating (true) or backward-propagating (false)
    Time duration;            //!< The duration of the segment
    std::vector<DeltaV> subsegBurns; //!< The delta-v burns for each subsegment
    State initialState;              //!< The initial state of the segment
};

/**
 * @brief A struct representing the settings for a Sims-Flanagan trajectory
 */
struct TrajectorySettings {
    std::size_t nSegments;                        //!< The number of segments in the trajectory
    std::vector<SegmentSettings> segmentSettings; //!< The settings for each segment
    DeltaV initialBurn;                           //!< The initial burn of the trajectory
    DeltaV finalBurn;                             //!< The final burn of the trajectory
    std::vector<DeltaV> segBurns;                 //!< The burns for each segment
};

/**
 * @brief A struct representing the settings for a Sims-Flanagan problem
 */
struct SimsFlanaganSettings {
    astro::Date epoch;                  //!< The epoch for the trajectory
    std::size_t nSegments;              //!< The number of segments in the trajectory
    std::size_t nSubsegmentsPerSegment; //!< The number of subsegments per segment in the trajectory
    Time maxFlightTime;                 //!< The maximum flight time for the entire trajectory
    Distance minPosition;               //!< The minimum position magnitude for any state in the trajectory
    Distance maxPosition;               //!< The maximum position magnitude for any state in the trajectory
    Velocity minVelocity;               //!< The minimum velocity magnitude for any state in the trajectory
    Velocity maxVelocity;               //!< The maximum velocity magnitude for any state in the trajectory
    Velocity maxDeltaV;                 //!< The maximum delta-v magnitude for any burn in the trajectory
    astro::Integrator integrator;       //!< The integrator to use for propagating the trajectory
    astro::Vehicle vehicle;             //!< The vehicle to use for propagating the trajectory
    astro::Cartesian<astro::frames::primary> initialCartesian; //!< The initial state of the first segment
    astro::Cartesian<astro::frames::primary> targetCartesian;  //!< The final state of the last segment
};

} // namespace hermes
} // namespace astrea