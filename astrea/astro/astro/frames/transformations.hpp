/**
 * @file transformations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions for frame transformations and other utilities.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/instances/defined_rotations.hpp>
#include <astro/frames/types/BodyFixedFrame.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>
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

namespace {

/**
 * @brief Get the Direction Cosine Matrix (DCM) between two frames at a given date.
 *
 * This function retrieves the DCM that transforms vectors from Frame_T to Frame_U.
 * If the DCM is not directly defined, it attempts to use the inverse DCM if available.
 *
 * @tparam Frame_T The source frame type.
 * @tparam Frame_U The target frame type.
 * @param date The date at which to retrieve the DCM.
 * @return DCM<Frame_T, Frame_U> The Direction Cosine Matrix from Frame_T to Frame_U.
 * @throws std::runtime_error If no DCM is defined between the two frames.
 */
template <typename Frame_T, typename Frame_U>
DCM<Frame_T, Frame_U> get_dcm_impl(const Date& date)
{
    static_assert(!(HasDcm<Frame_T, Frame_U> && HasDcm<Frame_U, Frame_T>), "DCM defined in both directions, please define only one to avoid symmetry issues.");
    static_assert(IsStaticFrame<Frame_T> && IsStaticFrame<Frame_U>, "Dynamic frame conversions cannot be called statically. Dynamic frames must be created at runtime with a platform to reference.");
    static_assert(HasDcm<Frame_T, Frame_U> || HasDcm<Frame_U, Frame_T> || IsSameFrame<Frame_T, Frame_U>, "No DCM defined between these two frames.");

    if constexpr (IsSameFrame<Frame_T, Frame_U>) {
        return DCM<Frame_T, Frame_U>::identity(); // TODO: Figure out how to do this earlier to avoid unnecessary matrix math
    }
    else if constexpr (HasDcm<Frame_T, Frame_U>) {
        return get_dcm<Frame_T, Frame_U>(date);
    }
    else if constexpr (HasDcm<Frame_U, Frame_T>) {
        return get_dcm<Frame_U, Frame_T>(date).transpose();
    }
    throw std::logic_error("How did you get here?");
}

} // namespace

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
    const auto dcm = get_dcm_impl<Frame_T, Frame_U>(date);
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
// template <typename Value_T, typename Frame_T, typename Frame_U>
// CartesianVector<Value_T, Frame_U> transform_vector_into_frame(const CartesianVector<Value_T, Frame_T>& vec, const Date& date)
// {
//     static_assert(std::is_same_v<Value_T, Distance>, "Transformations with respect to a frame are only implemented for Distance vectors at this time.");

//     const auto offset = get_center_offset<Frame_T, Frame_U>(date);
//     const auto dcm    = DcmManager::get_dcm<Frame_T, Frame_U>(date);
//     return CartesianVector<Value_T, Frame_U>(dcm * vec + offset);
// }


} // namespace frames
} // namespace astro
} // namespace astrea