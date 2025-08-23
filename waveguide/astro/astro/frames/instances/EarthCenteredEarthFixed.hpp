/**
 * @file EarthCenteredEarthFixed.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the EarthCenteredEarthFixed class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/CartesianVector.hpp>
#include <astro/frames/instances/EarthCenteredInertial.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/RotatingFrame.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Class representing the Earth-Centered Earth Fixed (ECEF) frame.
 *
 * @note This frame contiains the following conversions:
 * - ECEF to ECEF
 * - ECI to ECEF
 * - ECEF to ECI
 */
class EarthCenteredEarthFixed : public RotatingFrame<EarthCenteredEarthFixed, EarthCenteredInertial> {

  public:
    /**
     * @brief Default constructor for EarthCenteredEarthFixed.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    EarthCenteredEarthFixed() :
        RotatingFrame<EarthCenteredEarthFixed, EarthCenteredInertial>("Earth Centered Earth Fixed", "Earth") {};

    /**
     * @brief Default destructor for EarthCenteredEarthFixed.
     */
    ~EarthCenteredEarthFixed() = default;

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to Earth-Centered Earth Fixed (ECEF) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, EarthCenteredEarthFixed> The converted CartesianVector in ECEF coordinates.
     *
     * @note: This transformation only accounts for Earth rotation, not nutation or procession, so it
     *      is wrong by the order of several km. TODO: Make this accurate.
     *      https://space.stackexchange.com/questions/38807/transform-eci-to-ecef
     *
     *  C_eci2ecef = [c_gst s_gst 0;
     *               -s_gst c_gst 0;
     *                  0      0  1];
     */
    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredEarthFixed>
        rotate_into_this_frame(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date)
    {
        return get_dcm(date) * eciVec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Earth-Fixed (ECEF) to Earth-Centered Inertial (ECI) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param ecefVec The CartesianVector in Earth-Centered Earth-Fixed coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, EarthCenteredInertial> The converted CartesianVector in ECI coordinates.
     *
     *  @note: This transformation only accounts for Earth rotation, not nutation or procession, so it
     *      is wrong by the order of several km. TODO: Make this accurate.
     *      https://space.stackexchange.com/questions/38807/transform-eci-to-ecef
     *  C_ecef2eci = [ cos(-gst) sin(-gst) 0;
     *                -sin(-gst) cos(-gst) 0;
     *                     0         0     1];
     */
    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredInertial>
        rotate_out_of_this_frame(const CartesianVector<Value_T, EarthCenteredEarthFixed>& ecefVec, const Date& date)
    {
        return get_dcm(date).transpose() * ecefVec;
    }

    /**
     * @brief Get the Direction Cosine Matrix (DCM) for the ECEF frame at a given date.
     *
     * @param date The date for which to get the DCM.
     * @return DirectionCosineMatrix<EarthCenteredInertial, EarthCenteredEarthFixed> The DCM from ECI to ECEF.
     */
    static DirectionCosineMatrix<EarthCenteredInertial, EarthCenteredEarthFixed> get_dcm(const Date& date)
    {
        const Angle gst = julian_date_to_siderial_time(date.jd());
        return DirectionCosineMatrix<EarthCenteredInertial, EarthCenteredEarthFixed>::Z(gst);
    }

  private:
};

/**
 * @brief Alias for EarthCenteredEarthFixed.
 */
using ECEF = EarthCenteredEarthFixed; // Alias for convenience

} // namespace astro
} // namespace waveguide