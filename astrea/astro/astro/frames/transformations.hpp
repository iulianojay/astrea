/**
 * @file transformations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions for frame transformations and other utilities.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Get the center offset between two frames at a given date.
 *
 * If the frames share the same origin, the offset is zero.
 * If the frames share the same axis but have different origins, the offset is the relative position between the two
 * origins in Frame_T. All calculations are done in the solar_system_barycenter::icrf frame.
 *
 * @tparam Frame_T The first frame type.
 * @tparam Frame_U The second frame type.
 * @param date The date at which to calculate the offset.
 * @return CartesianVector<Distance, Frame_T> The offset vector from Frame_T to Frame_U expressed in Frame_T.
 */
template <typename Frame_T, typename Frame_U>
    requires(HasSameOrigin<Frame_T, Frame_U>)
CartesianVector<Distance, Frame_T> get_center_offset(const Date& date)
{
    return CartesianVector<Distance, Frame_T>(
        0.0 * mp_units::si::unit_symbols::m, 0.0 * mp_units::si::unit_symbols::m, 0.0 * mp_units::si::unit_symbols::m
    );
}

/**
 * @brief Get the center offset between two frames at a given date.
 *
 * If the frames share the same origin, the offset is zero.
 * If the frames share the same axis but have different origins, the offset is the relative position between the two
 * origins in Frame_T. All calculations are done in the solar_system_barycenter::icrf frame.
 *
 * @tparam Frame_T The first frame type.
 * @tparam Frame_U The second frame type.
 * @param date The date at which to calculate the offset.
 * @return CartesianVector<Distance, Frame_T> The offset vector from Frame_T to Frame_U expressed in Frame_T.
 */
template <typename Frame_T, typename Frame_U>
    requires(!HasSameOrigin<Frame_T, Frame_U> && HasSameAxis<Frame_T, Frame_U>)
CartesianVector<Distance, Frame_T> get_center_offset(const Date& date)
{
    // Build a system out of these bodies
    static const AstrodynamicsSystem sys(CelestialBodyId::SUN, { Frame_T::get_origin(), Frame_U::get_origin() });

    // Forcing the frame change here doesn't matter since the offset is just a difference and it's already implied that
    // these two frames share an axis.
    return sys.get_relative_position(date, Frame_T::get_origin(), Frame_U::get_origin()).template force_frame_conversion<Frame_T>();
}

/**
 * @brief Rotate a vector from one frame to another at a given date using the Direction Cosine Matrix (DCM).
 *
 * @tparam Value_T The type of the vector components (e.g., Distance, Velocity).
 * @tparam Frame_T The source frame type.
 * @tparam Frame_U The target frame type.
 * @param vec The vector to rotate.
 * @param date The date at which to perform the rotation.
 * @return CartesianVector<Value_T, Frame_U> A new CartesianVector in the target frame.
 * @throws std::runtime_error If the frames do not share the same origin or if the DCM cannot be obtained.
 * @note This function multiplies the vector by the DCM and does NOT return a vector with respect to the new frame.
 * It is the user's responsibility to understand if this makes sense or not.
 */
template <typename Value_T, typename Frame_T, typename Frame_U>
CartesianVector<Value_T, Frame_U> rotate_vector_into_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
{
    const auto dcm = DcmManager::get_dcm<Frame_T, Frame_U>(date);
    return dcm * vec;
}

/**
 * @brief Transform a vector from one frame to another at a given date, accounting for both rotation and translation.
 *
 * This function first translates the vector by the center offset between the two frames, then rotates it using the
 * Direction Cosine Matrix (DCM).
 *
 * @tparam Frame_T The source frame type.
 * @tparam Frame_U The target frame type.
 * @param vec The vector to transform.
 * @param date The date at which to perform the transformation.
 * @return CartesianVector<Distance, Frame_U> A new CartesianVector in the target frame.
 * @throws std::runtime_error If the frames do not have a known transformation or if the DCM cannot be obtained.
 * @note This function returns a vector with respect to the new frame, but specializations currently only exist for
 * inertial frames directly provided by this library. It will not work for custom or dynamic frames.
 */
template <typename Frame_T, typename Frame_U>
CartesianVector<Distance, Frame_U> transform_vector_into_frame(const CartesianVector<Distance, Frame_T>& vec, const Date& date)
{
    const auto offset = get_center_offset<Frame_T, Frame_U>(date);
    const auto dcm    = DcmManager::get_dcm<Frame_T, Frame_U>(date);
    return CartesianVector<Distance, Frame_U>(dcm * (vec + offset));
}


} // namespace frames
} // namespace astro
} // namespace astrea