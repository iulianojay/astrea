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
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>
#include <astro/time/Date.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Class representing the Earth-Centered Inertial (ECI) frame.
 *
 * @note This frame contiains the following conversions:
 * - ECI to ECI
 */
class EarthCenteredInertial : public InertialFrame {

  public:
    /**
     * @brief Default constructor for EarthCenteredInertial.
     *
     * Initializes the ECI frame with a name and origin.
     */
    EarthCenteredInertial() :
        InertialFrame("Earth Centered Inertial", "Earth")
    {
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     */
    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredInertial>
        convert_to_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date)
    {
        return eciVec;
    }
};

/**
 * @brief Alias for EarthCenteredInertial.
 */
using ECI = EarthCenteredInertial;

} // namespace astro
} // namespace waveguide