/**
 * @file LocalHorizontalLocalVertical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the LocalHorizontalLocalVertical class in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/DynamicFrame.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing the Local Horizontal, Local Vertical (LVLH) frame.
 */
class LocalHorizontalLocalVertical : public DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH> {

    friend DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>;

  public:
    LocalHorizontalLocalVertical() = delete; //!< Default constructor is deleted to prevent instantiation without a parent frame

    /**
     * @brief Default constructor for LocalHorizontalLocalVertical.
     *
     * Initializes the ECEF frame with a name and origin.
     */
    LocalHorizontalLocalVertical(const FrameReference* parent) :
        DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>(parent)
    {
    }

    /**
     * @brief Default destructor for LocalHorizontalLocalVertical.
     */
    ~LocalHorizontalLocalVertical() = default;

    /**
     * @brief Gets the Direction Cosine Matrix (DCM) for the Local Horizontal, Local Vertical frame at a given date.
     *
     * @param date The date for which the DCM is computed.
     * @return DirectionCosineMatrix<frames::earth::icrf, LocalHorizontalLocalVertical> The DCM from ECI to LVLH.
     */
    DirectionCosineMatrix<frames::earth::icrf, LocalHorizontalLocalVertical> get_dcm(const Date& date) const
    {
        const auto r = get_inertial_position(date).unit();
        const auto v = get_inertial_velocity(date).unit();
        const auto h = r.cross(v).unit();
        return DirectionCosineMatrix<frames::earth::icrf, LocalHorizontalLocalVertical>::from_vectors((-h).cross(-r), -h, -r);
    }

  private:
    /**
     * @brief Constructor for instantaneous dynamic state/frames.
     *
     * @param position The position vector in the ECI frame.
     * @param velocity The velocity vector in the ECI frame.
     */
    LocalHorizontalLocalVertical(const RadiusVector<frames::earth::icrf>& position, const VelocityVector<frames::earth::icrf>& velocity) :
        DynamicFrame<LocalHorizontalLocalVertical, FrameAxis::LVLH>(position, velocity)
    {
    }
};

/**
 * @brief Alias for LocalHorizontalLocalVertical.
 */
using LVLH = LocalHorizontalLocalVertical; // Alias for convenience

} // namespace astro
} // namespace astrea