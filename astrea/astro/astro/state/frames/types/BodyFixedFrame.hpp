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

#include <astro/state/frames/Frame.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all rotating state/frames.
 */
template <class Frame_T, CelestialBodyId origin>
    requires(origin != CelestialBodyId::UNSET)
struct BodyFixedFrame : public Frame<Frame_T, origin, FrameAxis::BODY_FIXED> {
    virtual ~BodyFixedFrame() = default;
};

} // namespace astro
} // namespace astrea