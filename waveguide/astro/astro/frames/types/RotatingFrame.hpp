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

namespace waveguide {
namespace astro {

/**
 * @brief Base class for all rotating frames.
 */
class RotatingFrame : public Frame {

  public:
    /**
     * @brief Constructor for RotatingFrame.
     *
     * @param name The name of the rotating frame.
     * @param origin The origin of the rotating frame.
     * @param parent The parent inertial frame that this rotating frame is based on.
     */
    RotatingFrame(const std::string& name, const std::string& origin, const InertialFrame& parent) :
        Frame(name, origin),
        parentFrame(parent)
    {
    }

  protected:
    InertialFrame parentFrame; //<! The parent inertial frame that this rotating frame is based on.
};

} // namespace astro
} // namespace waveguide