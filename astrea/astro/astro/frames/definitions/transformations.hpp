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
#include <astro/frames/definitions/defined_rotations.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/DirectionCosineMatrix.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
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

namespace {

// Diagnostic tag types — intentionally left undefined.
// When used as a template argument to always_false<>, the compiler prints the
// frame names (embedded in the mp_units::symbol_text NTTPs) in the error note,
// e.g.:  'always_false<NoDcmBetween<"gcrf", "eci">> evaluates to false'
template <auto...>
struct NoDcmBetween;

template <auto...>
struct DcmDefinedBothWays;

/**
 * @brief Retrieves the accumulated direction cosine matrix from the root frame to the given FixedOffsetFrame by recursively composing the DCMs along the parent chain.
 */
template <IsFrame auto frame, IsFrame auto root>
inline constexpr DCM<frame, root> get_dcm_to_root_frame(const Date& date)
{
    static constexpr auto axis      = frame.axis;
    static constexpr auto root_axis = root.axis;

    // first check if these transformations exist directly
    if constexpr (HasDcm<frame, root>) { return get_dcm<frame, root>(date); }
    else if constexpr (HasDcm<root, frame>) {
        return get_dcm<root, frame>(date).transpose();
    }
    // current frame is root
    else if constexpr (equivalent(axis, root_axis)) {
        return DCM<root, frame>::identity();
    }
    // current frame is a direct child of root
    else if constexpr (equivalent(axis.parent, root_axis)) {
        static constexpr auto parent = make_frame(frame.origin, axis.parent);
        return get_dcm_impl<frame, parent>(date);
    }
    // current frame is a descendant of root
    else if constexpr (IsDerivedAxis<decltype(axis.parent)>) {
        // DCM<grandparent, parent> * DCM<parent, child> = DCM<grandparent, child>
        static constexpr auto parent = make_frame(frame.origin, axis.parent);
        return get_dcm_impl<frame, parent>(date) * get_dcm_to_root_frame<parent, root>(date);
    }
    else {
        static_assert(always_false<NoDcmBetween<frame.name.portable(), root.name.portable()>>, "Frame is not a descendant of root frame.");
    }
}

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
        !(HasDcm<frame, frame_u> && HasDcm<frame_u, frame>) ||
            always_false<DcmDefinedBothWays<frame.name.portable(), frame_u.name.portable()>>,
        "DCM defined in both directions between these two frames; define only one to avoid symmetry issues."
    );
    static_assert(
        IsStaticFrame<decltype(frame)> && IsStaticFrame<decltype(frame_u)>,
        "Dynamic frame conversions cannot be called statically. "
        "Dynamic frames must be created at runtime with a position/velocity to reference."
    );
    static_assert(
        (HasDcm<frame, frame_u> || HasDcm<frame_u, frame> || equivalent(frame.axis, frame_u.axis) ||
         HasCommonAncestor<frame.axis, frame_u.axis>) ||
            always_false<NoDcmBetween<frame.name.portable(), frame_u.name.portable()>>,
        "No DCM (get_dcm method) defined between these two frames and no common ancestor found."
    );

    if constexpr (equivalent(frame.axis, frame_u.axis)) {
        return DCM<frame, frame_u>::identity(); // TODO: Make sure to do this earlier to avoid unnecessary matrix math
    }
    else if constexpr (HasDcm<frame, frame_u>) {
        return get_dcm<frame, frame_u>(date);
    }
    else if constexpr (HasDcm<frame_u, frame>) {
        return get_dcm<frame_u, frame>(date).transpose();
    }
    else if constexpr (HasCommonAncestor<frame.axis, frame_u.axis>) {
        // If no direct DCM defined but common ancestor exists, we can get the DCMs to the common ancestor and compose them
        static constexpr auto root_axis = find_common_ancestor(frame.axis, frame_u.axis);
        static constexpr auto root      = make_frame(frame.origin, root_axis);
        const DCM<frame, root> dcm1     = get_dcm_to_root_frame<frame, root>(date);
        const DCM<frame_u, root> dcm2   = get_dcm_to_root_frame<frame_u, root>(date);
        return dcm1 * dcm2.transpose(); // DCM_root->frame_u * DCM_frame->root = DCM_frame->frame_u
    }
    else {
        static_assert(always_false<NoDcmBetween<frame.name.portable(), frame_u.name.portable()>>, "Getting here means something is wrong with the static assertions. Please report this to the developers.");
    }
}

template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
inline constexpr CartesianVector<Value_T, frame_u> get_offset_impl(const Date& date)
{
    static_assert(std::is_same_v<Value_T, Distance> || std::is_same_v<Value_T, Velocity>, "translate_vector_into_frame: Value_T must be Distance or Velocity.");

    constexpr auto origin   = frame.origin;
    constexpr auto origin_u = frame_u.origin;

    if constexpr (equivalent(origin, origin_u)) {
        return CartesianVector<Value_T, frame_u>(Value_T::zero(), Value_T::zero(), Value_T::zero());
    }
    else if constexpr (IsCelestialReference<decltype(origin)> && IsCelestialReference<decltype(origin_u)>) {
        // Two celestial references and we hook into the ephemeris system
        if constexpr (std::is_same_v<Value_T, Distance>) {
            return get_relative_position<origin, origin_u>(date).template force_frame_conversion<frame_u>();
        }
        else if constexpr (std::is_same_v<Value_T, Velocity>) {
            return get_relative_velocity<origin, origin_u>(date).template force_frame_conversion<frame_u>();
        }
    }
    else if constexpr (IsFixedOffsetFrame<decltype(frame)> || IsFixedOffsetFrame<decltype(frame_u)>) {
        if constexpr (!std::is_same_v<Value_T, Distance>) {
            // We can only calculate velocity offsets for celestial references since we rely on the ephemeris system for the relative velocity
            throw std::logic_error("Fixed velocity offsets are not currently supported.");
        }

        // At least one fixed offset frame in the mix, so we can use the static offsets
        // We could explicitly write out all these frames to make sure they're correct, but this is more legible and the
        // forced conversions would be required anyway.
        if constexpr (IsFixedOffsetFrame<decltype(frame)> && IsFixedOffsetFrame<decltype(frame_u)>) {
            constexpr auto offset1 = get_offset_from_root(frame).template force_frame_conversion<frame_u>(); // r_root->frame
            constexpr auto offset2 = get_offset_from_root(frame_u).template force_frame_conversion<frame_u>(); // r_root_u->frame_u
            const auto rootOffsets = // r_root_u->root
                get_relative_position<get_root_frame(frame), get_root_frame(frame_u)>(date).template force_frame_conversion<frame_u>();
            return offset2 - offset1 + rootOffsets;
        }
        else if constexpr (IsFixedOffsetFrame<decltype(frame)>) {
            const auto offset1 = get_offset_from_root(frame).template force_frame_conversion<frame_u>(); // r_root->frame
            const auto rootOffsets = // r_root_u->root
                get_relative_position<get_root_frame(frame), origin_u>(date).template force_frame_conversion<frame_u>();
            return rootOffsets - offset1;
        }
        else if constexpr (IsFixedOffsetFrame<decltype(frame_u)>) {
            const auto offset2 = get_offset_from_root(frame_u).template force_frame_conversion<frame_u>(); // r_root_u->frame_u
            const auto rootOffsets = // r_root_u->root
                get_relative_position<origin, get_root_frame(frame_u)>(date).template force_frame_conversion<frame_u>();
            return offset2 + rootOffsets;
        }
    }
    // No origins in common and at least one frame is not fixed offset, so we don't have a way to determine the offset
    throw std::logic_error("Cannot determine center offset between these two frames as it is not linked to a common reference.");
}

} // namespace

template <IsFrame auto frame, IsFrame auto frame_u>
concept HasValidFrameTransformation = requires(Date date) {
    { get_dcm_impl<frame, frame_u>(date) } -> std::same_as<DCM<frame, frame_u>>;
} || requires(Date date) {
    { get_dcm_impl<frame_u, frame>(date) } -> std::same_as<DCM<frame_u, frame>>;
};


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
 */
template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
inline constexpr CartesianVector<Value_T, frame_u>
    translate_vector_into_frame(const CartesianVector<Value_T, frame>& vec, const Date& date)
{
    const CartesianVector<Value_T, frame_u> offset = get_offset_impl<Value_T, frame, frame_u>(date);
    return vec.template force_frame_conversion<frame_u>() + offset;
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
        constexpr auto IntermediateFrame = make_frame(frame_u.origin, frame.axis);
        const CartesianVector<Value_T, IntermediateFrame> vecInIntermediate =
            translate_vector_into_frame<Value_T, frame, IntermediateFrame>(vec, date);
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