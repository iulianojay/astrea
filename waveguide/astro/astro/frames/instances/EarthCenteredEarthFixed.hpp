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
 */
class EarthCenteredEarthFixed : public RotatingFrame {

  public:
    /**
     * @brief Default constructor for EarthCenteredEarthFixed.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    EarthCenteredEarthFixed() :
        RotatingFrame("Earth Centered Earth Fixed", "Earth", EarthCenteredInertial()){};

    /**
     * @brief Default destructor for EarthCenteredEarthFixed.
     */
    ~EarthCenteredEarthFixed() = default;

    /**
     * @brief Converts a CartesianVector from Earth-Centered Earth Fixed (ECEF) to Earth-Centered Earth Fixed (ECEF) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param ecefVec The CartesianVector in ECEF coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, EarthCenteredEarthFixed> The converted CartesianVector in ECEF coordinates.
     */
    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredEarthFixed>
        convert_to(const CartesianVector<Value_T, EarthCenteredEarthFixed>& ecefVec, const Date& date)
    {
        return ecefVec;
    }

    /**
     * @brief Converts a CartesianVector from Earth-Centered Inertial (ECI) to Earth-Centered Earth Fixed (ECEF) coordinates.
     *
     * @tparam Value_T The type of the vector components.
     * @param eciVec The CartesianVector in ECI coordinates.
     * @param date The date for which the conversion is performed.
     * @return CartesianVector<Value_T, EarthCenteredEarthFixed> The converted CartesianVector in ECEF coordinates.
     */
    template <typename Value_T>
    static CartesianVector<Value_T, EarthCenteredEarthFixed>
        convert_to(const CartesianVector<Value_T, EarthCenteredInertial>& eciVec, const Date& date)
    {
        const Angle gst = julian_date_to_siderial_time(date.jd());
        const auto dcm  = DirectionCosineMatrix<EarthCenteredEarthFixed>::Z(gst);
        return dcm * eciVec;
    }
};

/**
 * @brief Alias for EarthCenteredEarthFixed.
 */
using ECEF = EarthCenteredEarthFixed; // Alias for convenience

} // namespace astro
} // namespace waveguide