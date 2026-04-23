/**
 * @file BodyFixedFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the BodyFixedFrame class in the astro namespace
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

#include <astro/frames/Frame.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all body fixed frames.
 */
template <CelestialBodyId _origin>
    requires(_origin != CelestialBodyId::UNSET)
struct BodyFixedFrame : public Frame<_origin, FrameAxis::BODY_FIXED> {
    virtual ~BodyFixedFrame() = default;

    static constexpr CelestialBodyId origin =
        Frame<_origin, FrameAxis::BODY_FIXED>::origin; //!< The central body associated with the inertial frame.
    static constexpr FrameAxis axis = Frame<_origin, FrameAxis::BODY_FIXED>::axis; //!< The axis type of the inertial frame.
};

} // namespace astro
} // namespace astrea