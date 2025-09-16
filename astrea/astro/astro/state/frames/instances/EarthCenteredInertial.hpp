/**
 * @file EarthCenteredInertial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the EarthCenteredInertial class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/state/frames/types/InertialFrame.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing the Earth-Centered Inertial (ECI) frame.
 *
 * @note This frame contiains the following conversions:
 * - ECI to ECI
 */
class EarthCenteredInertial : public InertialFrame<EarthCenteredInertial> {

  public:
    /**
     * @brief Default constructor for EarthCenteredInertial.
     *
     * Initializes the ECI frame with a name and origin.
     */
    EarthCenteredInertial() :
        InertialFrame<EarthCenteredInertial>("Earth Centered Inertial", "Earth")
    {
    }
};

/**
 * @brief Alias for EarthCenteredInertial.
 */
using ECI = EarthCenteredInertial;

} // namespace astro
} // namespace astrea