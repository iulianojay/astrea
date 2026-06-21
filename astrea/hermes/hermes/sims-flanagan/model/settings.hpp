/**
 * @file Trajectory.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Trajectory module
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


struct SegmentSettings {
    std::size_t nSubsegments;
    bool isForward;
    Time duration;
    std::vector<DeltaV> subsegBurns;
    astro::State initialState;
};


struct TrajectorySettings {
    std::size_t nSegments;
    std::vector<SegmentSettings> segmentSettings;
    DeltaV initialBurn;
    DeltaV finalBurn;
    std::vector<DeltaV> segBurns;
};

} // namespace hermes
} // namespace astrea