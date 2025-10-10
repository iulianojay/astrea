/**
 * @file InertialFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the InertialFrame class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
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

#include <string>

#include <astro/astro.fwd.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all inertial state/frames.
 */
template <CelestialBodyId origin, FrameAxis axis = FrameAxis::ICRF>
    requires(origin != CelestialBodyId::UNSET && origin != CelestialBodyId::CUSTOM)
struct InertialFrame : Frame<origin, axis> {
    virtual ~InertialFrame() = default;

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr CelestialBodyId get_origin() { return Frame<origin, axis>::get_origin(); }

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr FrameAxis get_axis() { return Frame<origin, axis>::get_axis(); }
};

} // namespace astro
} // namespace astrea