/**
 * @file transformations.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions for frame transformations and other utilities.
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
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/DirectionCosineMatrix.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/instances/defined_rotations.hpp>
#include <astro/systems/system_utilities.hpp>

namespace astrea {
namespace astro {
namespace frames {

/**
 * @brief Concept to determine if a Direction Cosine Matrix (DCM) can be obtained between two frames at a given date.
 *
 * @tparam frame The first frame type to check.
 * @tparam frame_u The second frame type to check.
 * @param date The date at which to obtain the DCM.
 * @return true if the specialization of get_dcm has been defined, false otherwise.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
concept HasDcm = requires(const Date& date) { get_dcm<frame, frame_u>(date); };

/**
 * @brief Concept to determine if a frame class has a member function to obtain the Direction Cosine Matrix (DCM) to another frame at a given date.
 *
 * @tparam frame The frame type to check.
 * @tparam frame_u The target frame type to check.
 * @param frame An instance of the frame type.
 * @param date The date at which to obtain the DCM.
 * @return true if the frame class has a member function get_dcm for the target frame, false otherwise.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
concept HasDcmMethod = requires(const Date& date) { frame.template get_dcm<frame, frame_u>(date); };

/**
 * @brief Get the center offset between two frames at a given date.
 *
 * If the frames share the same origin, the offset is zero.
 * If the frames share the same axis but have different origins, the offset is the relative position between the two
 * origins in frame. All calculations are done in the solar_system_barycenter::icrf frame.
 *
 * @tparam frame The first frame type.
 * @tparam frame_u The second frame type.
 * @param date The date at which to calculate the offset.
 * @return CartesianVector<Distance, frame> The offset vector from frame to frame_u expressed in frame.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
    requires(frame.origin == frame_u.origin)
inline constexpr CartesianVector<Distance, frame> get_center_offset(const Date& date)
{
    return CartesianVector<Distance, frame>(Distance::zero(), Distance::zero(), Distance::zero());
}

/**
 * @brief Get the center offset between two frames at a given date.
 *
 * If the frames share the same origin, the offset is zero.
 * If the frames share the same axis but have different origins, the offset is the relative position between the two
 * origins in frame. All calculations are done in the solar_system_barycenter::icrf frame.
 *
 * @tparam frame The first frame type.
 * @tparam frame_u The second frame type.
 * @param date The date at which to calculate the offset.
 * @return CartesianVector<Distance, frame> The offset vector from frame to frame_u expressed in frame.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
    requires(frame.origin != frame_u.origin && frame.axis == frame_u.axis)
inline constexpr CartesianVector<Distance, frame> get_center_offset(const Date& date)
{
    // Forcing the frame change here doesn't matter since the offset is just a difference and it's already implied that
    // these two frames share an axis.
    return get_relative_position<frame.origin, frame_u.origin>(date).template force_frame_conversion<frame>();
}

namespace {

// Diagnostic tag types — intentionally left undefined.
// When used as a template argument to always_false<>, the compiler prints the
// frame names (embedded in the mp_units::symbol_text NTTPs) in the error note,
// e.g.:  'always_false<NoDcmBetween<"gcrf", "eci">> evaluates to false'
template <mp_units::symbol_text, mp_units::symbol_text>
struct NoDcmBetween;

template <mp_units::symbol_text, mp_units::symbol_text>
struct DcmDefinedBothWays;

template <typename>
inline constexpr bool always_false = false;

/**
 * @brief Get the Direction Cosine Matrix (DCM) between two frames at a given date.
 *
 * This function retrieves the DCM that transforms vectors from frame to frame_u.
 * If the DCM is not directly defined, it attempts to use the inverse DCM if available.
 *
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param date The date at which to retrieve the DCM.
 * @return DCM<frame, frame_u> The Direction Cosine Matrix from frame to frame_u.
 * @throws std::runtime_error If no DCM is defined between the two frames.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DCM<frame, frame_u> get_dcm_impl(const Date& date)
{
    static_assert(
        !always_false<DcmDefinedBothWays<frame.name, frame_u.name>> || !(HasDcm<frame, frame_u> && HasDcm<frame_u, frame>),
        "DCM defined in both directions between these two frames; define only one to avoid symmetry issues."
    );
    static_assert(
        IsStaticFrame<decltype(frame)> && IsStaticFrame<decltype(frame_u)>, "Dynamic frame conversions cannot be called statically. Dynamic frames must be created at runtime with a platform to reference."
    );
    static_assert(
        !always_false<NoDcmBetween<frame.name, frame_u.name>> || HasDcm<frame, frame_u> || HasDcm<frame_u, frame> || frame == frame_u,
        "No DCM (get_dcm method) defined between these two frames."
    );

    if constexpr (frame == frame_u) {
        return DCM<frame, frame_u>::identity(); // TODO: Figure out how to do this earlier to avoid unnecessary matrix math
    }
    else if constexpr (HasDcm<frame, frame_u>) {
        return get_dcm<frame, frame_u>(date);
    }
    else if constexpr (HasDcm<frame_u, frame>) {
        return get_dcm<frame_u, frame>(date).transpose();
    }
    throw std::logic_error("How did you get here?");
}

} // namespace

template <IsFrame auto frame, IsFrame auto frame_u>
concept HasValidFrameTransformation = requires(Date date) {
    { get_dcm_impl<frame, frame_u>(date) } -> std::same_as<DCM<frame, frame_u>>;
} || requires(Date date) {
    { get_dcm_impl<frame_u, frame>(date) } -> std::same_as<DCM<frame_u, frame>>;
} || frame == frame_u;

/**
 * @brief Rotate a vector from one frame to another at a given date using the Direction Cosine Matrix (DCM).
 *
 * @tparam Value_T The type of the vector components (e.g., Distance, Velocity).
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param vec The vector to rotate.
 * @param date The date at which to perform the rotation.
 * @return CartesianVector<Value_T, frame_u> A new CartesianVector in the target frame.
 */
template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
inline constexpr CartesianVector<Value_T, frame_u>
    rotate_vector_into_frame(const CartesianVector<Value_T, frame>& vec, const Date& date)
{
    const auto dcm = get_dcm_impl<frame, frame_u>(date);
    return dcm * vec;
}

/**
 * @brief Translate a vector from one frame to another at a given date by accounting for the center offset between the frames.
 *
 * This function calculates the center offset between frame and frame_u at the specified date and translates the input vector accordingly.
 *
 * @tparam Value_T The type of the vector components (e.g., Distance, Velocity).
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param vec The vector to translate.
 * @param date The date at which to perform the translation.
 * @return CartesianVector<Value_T, frame_u> A new CartesianVector in the target frame.
 *
 * @note: This overload doesn't change in the input frame to avoid unnecessary frame conversions when the frames share the same origin but different axes.
 */
template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
    requires(frame.origin == frame_u.origin)
inline constexpr CartesianVector<Value_T, frame>
    translate_vector_into_frame(const CartesianVector<Value_T, frame>& vec, const Date& date)
{
    return vec;
}

/**
 * @brief Translate a vector from one frame to another at a given date by accounting for the center offset between the frames.
 *
 * This function calculates the center offset between frame and frame_u at the specified date and translates the input vector accordingly.
 *
 * @tparam Value_T The type of the vector components (e.g., Distance, Velocity).
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param vec The vector to translate.
 * @param date The date at which to perform the translation.
 * @return CartesianVector<Value_T, frame_u> A new CartesianVector in the target frame.
 */
template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
    requires(frame.origin != frame_u.origin && frame.axis == frame_u.axis)
inline constexpr CartesianVector<Distance, frame_u>
    translate_vector_into_frame(const CartesianVector<Distance, frame>& vec, const Date& date)
{
    if constexpr (std::is_same_v<Value_T, Distance>) {
        const auto& posRel = get_relative_position<frame_u.origin, frame.origin>(date); // frame -> frame_u
        return vec.template force_frame_conversion<frame_u>() + posRel.template force_frame_conversion<frame_u>();
    }
    else if constexpr (std::is_same_v<Value_T, Velocity>) {
        const auto& velRel = get_relative_velocity<frame_u.origin, frame.origin>(date); // frame -> frame_u
        return vec.template force_frame_conversion<frame_u>() - velRel.template force_frame_conversion<frame_u>();
    }
    else {
        throw std::logic_error("Unsupported vector type for translation. Only Distance and Velocity are supported.");
    }
}

/**
 * @brief Transform a vector from one frame to another at a given date, accounting for both rotation and translation.
 *
 * This function first translates the vector by the center offset between the two frames, then rotates it using the
 * Direction Cosine Matrix (DCM).
 *
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param vec The vector to transform.
 * @param date The date at which to perform the transformation.
 * @return CartesianVector<Value_T, frame_u> A new CartesianVector in the target frame.
 */
template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
    requires(IsStaticFrame<decltype(frame)> && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Value_T, frame_u>
    transform_vector_into_frame(const CartesianVector<Value_T, frame>& vec, const Date& date)
{
    if constexpr (frame.origin == frame_u.origin) {
        // Same origin: rotation only
        return rotate_vector_into_frame<Value_T, frame, frame_u>(vec, date);
    }
    else if constexpr (frame.axis == frame_u.axis) {
        // Same axis: translation only
        return translate_vector_into_frame<Value_T, frame, frame_u>(vec, date);
    }
    else {
        // Different origin and axis: translate to the intermediate frame that shares frame's axis
        // but frame_u's origin (e.g. ssb::icrf -> earth::icrf), then rotate to frame_u.
        constexpr struct IntermediateFrame
            : Frame<frame.name + mp_units::symbol_text{ " / " } + frame_u.name, frame_u.origin, frame.axis> {
        } IntermediateFrame{};
        const auto vecInIntermediate = translate_vector_into_frame<Value_T, frame, IntermediateFrame>(vec, date);
        return rotate_vector_into_frame<Value_T, IntermediateFrame, frame_u>(vecInIntermediate, date);
    }
}


} // namespace frames

template <typename Value_T, IsFrame auto _frame_>
template <IsFrame auto frame_u>
    requires(_frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Value_T, frame_u> CartesianVector<Value_T, _frame_>::in_frame(const Date& date) const
{
    return frames::transform_vector_into_frame<Value_T, _frame_, frame_u>(*this, date);
}

} // namespace astro
} // namespace astrea