/**
 * @file RotatingFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the RotatingFrame class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/frames/Frame.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Base class for all rotating frames.
 */
template <class Frame_T, class Parent_Frame_T>
class RotatingFrame : public Frame<Frame_T> {

  public:
    /**
     * @brief Constructor for RotatingFrame.
     *
     * @param name The name of the rotating frame.
     * @param origin The origin of the rotating frame.
     * @param parent The parent inertial frame that this rotating frame is based on.
     */
    RotatingFrame(const std::string& name, const std::string& origin) :
        Frame<Frame_T>(name, origin)
    {
    }
};

} // namespace astro
} // namespace astrea