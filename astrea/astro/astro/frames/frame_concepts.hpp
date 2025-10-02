/**
 * @file frame_concepts.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions for frame concepts and other compile-time utilities.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to determine if a frame is inertial.
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is inertial (ICRF or J2000), false otherwise.
 */
template <typename Frame_T>
concept IsInertialFrame = requires {
    { Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 };
};

/**
 * @brief Concept to determine if a frame is body-fixed.
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is body-fixed, false otherwise.
 */
template <typename Frame_T>
concept IsBodyFixedFrame = requires {
    { Frame_T::get_axis() == FrameAxis::BODY_FIXED };
};

/**
 * @brief Concept to determine if a frame is static (inertial or body-fixed).
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is static, false otherwise.
 */
template <typename Frame_T>
concept IsStaticFrame = requires {
    {
        Frame_T::get_axis() == FrameAxis::ICRF || Frame_T::get_axis() == FrameAxis::J2000 || Frame_T::get_axis() == FrameAxis::BODY_FIXED
    };
};

/**
 * @brief Concept to determine if a frame is dynamic (LVLH, RIC, VNB).
 *
 * @tparam Frame_T The frame type to check.
 * @return true if the frame is dynamic, false otherwise.
 */
template <typename Frame_T>
concept IsDynamicFrame = requires {
    {
        Frame_T::get_axis() == FrameAxis::LVLH || Frame_T::get_axis() == FrameAxis::RIC || Frame_T::get_axis() == FrameAxis::VNB
    };
};

/**
 * @brief Concept to determine if two frames share the same origin.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames share the same origin, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasSameOrigin = requires {
    { Frame_T::get_origin() == Frame_U::get_origin() };
};

/**
 * @brief Concept to determine if two frames share the same axis.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames share the same axis, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasSameAxis = requires {
    { Frame_T::get_axis() == Frame_U::get_axis() };
};

/**
 * @brief Concept to determine if two frames are the same (same origin and same axis).
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @return true if both frames are the same, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept IsSameFrame = requires {
    requires HasSameOrigin<Frame_T, Frame_U>;
    requires HasSameAxis<Frame_T, Frame_U>;
    { Frame_T::get_origin() != CelestialBodyId::CUSTOM }; // dynamic frames will look the same
    { Frame_U::get_origin() != CelestialBodyId::CUSTOM };
};

/**
 * @brief Concept to determine if a Direction Cosine Matrix (DCM) can be obtained between two frames at a given date.
 *
 * @tparam Frame_T The first frame type to check.
 * @tparam Frame_U The second frame type to check.
 * @param date The date at which to obtain the DCM.
 * @return true if the specialization of get_dcm has been defined, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasDcm = requires(const Date& date) {
    { get_dcm<Frame_T, Frame_U>(date) };
};

/**
 * @brief Concept to determine if a frame class has a member function to obtain the Direction Cosine Matrix (DCM) to another frame at a given date.
 *
 * @tparam Frame_T The frame type to check.
 * @tparam Frame_U The target frame type to check.
 * @param frame An instance of the frame type.
 * @param date The date at which to obtain the DCM.
 * @return true if the frame class has a member function get_dcm for the target frame, false otherwise.
 */
template <typename Frame_T, typename Frame_U>
concept HasDcmMethod = requires(const Frame_T& frame, const Date& date) {
    { frame.template get_dcm<Frame_T, Frame_U>(date) };
};

} // namespace astro
} // namespace astrea