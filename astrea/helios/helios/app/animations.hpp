/**
 * @file animations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the animations module
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <string>

#include <helios/types.hpp>

namespace astrea {
namespace helios {

/**
 * @brief Builds an HTML string for visualizing the animation frames.
 *
 * @param frames A vector of AnimationFrame objects representing the propagated states.
 * @param maxRadiusKm The maximum radius in kilometers for scaling the visualization.
 * @param elapsedMs The elapsed time in milliseconds for the propagation.
 * @param propMinutes The total propagation time in minutes.
 * @param stepMinutes The step size in minutes for each frame.
 * @return A string containing the HTML representation of the animation.
 */
std::string
    build_html(const std::vector<AnimationFrame>& frames, const double maxRadiusKm, const double elapsedMs, const double propMinutes, const double stepMinutes);

/**
 * @brief Builds a JSON string for re-propagating the animation frames.
 *
 * @param settings The propagation settings used for the original propagation.
 * @param results The PropagationResult containing the propagated frames and the number of frames.
 * @return A string containing the JSON representation for re-propagation.
 */
std::string build_repropagate_json(const PropagationSettings& settings, const PropagationResult& results);

/**
 * @brief Builds a JSON string for the animation frames.
 *
 * @param frames A vector of AnimationFrame objects representing the propagated states.
 * @return A string containing the JSON representation of the animation frames.
 */
std::string build_frames_js(const std::vector<AnimationFrame>& frames);

} // namespace helios
} // namespace astrea