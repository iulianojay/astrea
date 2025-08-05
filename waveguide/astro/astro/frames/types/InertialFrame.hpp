#pragma once

#include <astro/frames/Frame.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Base class for all inertial frames.
 */
class InertialFrame : public Frame {

  public:
    /**
     * @brief Constructor for InertialFrame.
     *
     * @param name The name of the inertial frame.
     * @param origin The origin of the inertial frame.
     */
    InertialFrame(const std::string& name, const std::string& origin) :
        Frame(name, origin)
    {
    }

    /**
     * @brief Default destructor for InertialFrame.
     */
    virtual ~InertialFrame() = default;
};

} // namespace astro
} // namespace waveguide