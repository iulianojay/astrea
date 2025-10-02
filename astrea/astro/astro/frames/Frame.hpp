/**
 * @file Frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Frame in astrea.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all state/frames.
 */
template <CelestialBodyId origin, FrameAxis axis>
struct Frame {

  protected:
    /**
     * @brief Default destructor for Frame.
     */
    virtual ~Frame() = default;

  public:
    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr CelestialBodyId get_origin() { return _origin; }

    /**
     * @brief Get the origin of the frame.
     *
     * @return The origin of the frame.
     */
    static constexpr FrameAxis get_axis() { return _axis; }

  protected:
    static constexpr CelestialBodyId _origin = origin; //!< The central body associated with the inertial frame.
    static constexpr FrameAxis _axis         = axis;   //!< The axis type of the inertial frame.
};


} // namespace astro
} // namespace astrea