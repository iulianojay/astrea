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

#include <astro/state/frames/Frame.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all inertial state/frames.
 */
template <class Frame_T>
class InertialFrame : public Frame<Frame_T> {

  public:
    /**
     * @brief Constructor for InertialFrame.
     *
     * @param name The name of the inertial frame.
     * @param origin The origin of the inertial frame.
     */
    InertialFrame(const std::string& name, const std::string& origin) :
        Frame<Frame_T>(name, origin)
    {
    }

    /**
     * @brief Default destructor for InertialFrame.
     */
    virtual ~InertialFrame() = default;
};

} // namespace astro
} // namespace astrea