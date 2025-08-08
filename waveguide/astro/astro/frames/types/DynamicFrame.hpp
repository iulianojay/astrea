/**
 * @file DynamicFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DynamicFrame class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <memory>

#include <astro/frames/Frame.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/time/Date.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Base class for all dynamic frames.
 */
class DynamicFrame : public Frame {

  public:
    /**
     * @brief Constructor for DynamicFrame.
     *
     * @param name The name of the dynamic frame.
     * @param origin The origin of the dynamic frame.
     * @param parent The parent inertial frame that this dynamic frame is based on.
     */
    DynamicFrame(const std::string& name, const FrameReference* parent) :
        Frame(name, parent->get_name()),
        _parent(parent)
    {
    }

  protected:
    const FrameReference* _parent; //<! The parent object this frame is attached to.
};

} // namespace astro
} // namespace waveguide