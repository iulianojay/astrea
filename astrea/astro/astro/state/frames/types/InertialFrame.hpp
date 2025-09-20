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
#include <astro/state/frames/Frame.hpp>
#include <astro/types/enums.hpp>

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
    InertialFrame(const std::string& name, const std::string& origin, const PlanetaryBody& centralBody) :
        Frame<Frame_T>(name, origin),
        _centralBody(centralBody)
    {
    }

    /**
     * @brief Default destructor for InertialFrame.
     */
    virtual ~InertialFrame() = default;

  private:
    const PlanetaryBody _centralBody; //!< The central body associated with the inertial frame.
                                      // TODO: Extend to barycenter. Maybe with a variant?
};

} // namespace astro
} // namespace astrea