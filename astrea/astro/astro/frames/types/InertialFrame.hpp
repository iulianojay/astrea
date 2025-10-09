/**
 * @file InertialFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the InertialFrame class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
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