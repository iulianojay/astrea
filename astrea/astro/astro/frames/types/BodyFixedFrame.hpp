/**
 * @file BodyFixedFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the BodyFixedFrame class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
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
template <CelestialBodyId origin>
    requires(origin != CelestialBodyId::UNSET)
struct BodyFixedFrame : public Frame<origin, FrameAxis::BODY_FIXED> {
    virtual ~BodyFixedFrame() = default;

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr CelestialBodyId get_origin() { return Frame<origin, FrameAxis::BODY_FIXED>::get_origin(); }

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr FrameAxis get_axis() { return Frame<origin, FrameAxis::BODY_FIXED>::get_axis(); }
};

} // namespace astro
} // namespace astrea