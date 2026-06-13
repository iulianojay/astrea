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
 * @brief Concept to determine if a Direction Cosine Matrix Rate can be obtained between two frames at a given date.
 *
 * @tparam frame The first frame type to check.
 * @tparam frame_u The second frame type to check.
 * @param date The date at which to obtain the DCM rate.
 * @return true if the specialization of get_dcm_rate has been defined, false otherwise.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
concept HasDcmRate = requires(const Date& date) { get_dcm_rate<frame, frame_u>(date); };

/**
 * @brief Concept to determine if a Direction Cosine Matrix Acceleration can be obtained between two frames at a given date.
 *
 * @tparam frame The first frame type to check.
 * @tparam frame_u The second frame type to check.
 * @param date The date at which to obtain the DCM acceleration.
 * @return true if the specialization of get_dcm_accel has been defined, false otherwise.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
concept HasDcmAccel = requires(const Date& date) { get_dcm_accel<frame, frame_u>(date); };

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

template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DCM<frame, frame_u> get_dcm_impl(const Date& date);

template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmRate<frame, frame_u> get_dcm_rate_impl(const Date& date);

template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmAccel<frame, frame_u> get_dcm_accel_impl(const Date& date);

/**
 * @brief Retrieves the accumulated direction cosine matrix from the root frame to the given FixedOffsetFrame by recursively composing the DCMs along the parent chain.
 *
 * @tparam frame The frame type for which to retrieve the DCM to the root frame.
 * @tparam root The root frame type to which the DCM should be obtained.
 * @param date The date at which to retrieve the DCM.
 * @return DCM<frame, root> The direction cosine matrix from the root frame to the given frame.
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
 * @brief Retrieves the accumulated direction cosine matrix rate from the root frame to the given frame by recursively composing the DCM rates along the parent chain.
 *
 * @tparam frame The frame type for which to retrieve the DCM rate to the root frame.
 * @tparam root The root frame type to which the DCM rate should be obtained.
 * @param date The date at which to retrieve the DCM rate.
 * @return DcmRate<frame, root> The direction cosine matrix rate from the root frame to the given frame.
 */
template <IsFrame auto frame, IsFrame auto root>
inline constexpr DcmRate<frame, root> get_dcm_rate_to_root_frame(const Date& date)
{
    static constexpr auto axis      = frame.axis;
    static constexpr auto root_axis = root.axis;

    // first check if these transformations exist directly
    if constexpr (HasDcmRate<frame, root>) { return get_dcm_rate<frame, root>(date); }
    else if constexpr (HasDcmRate<root, frame>) {
        return get_dcm_rate<root, frame>(date).transpose();
    }
    // current frame is root
    else if constexpr (equivalent(axis, root_axis)) {
        return DcmRate<root, frame>::zero();
    }
    // current frame is a direct child of root
    else if constexpr (equivalent(axis.parent, root_axis)) {
        static constexpr auto parent = make_frame(frame.origin, axis.parent);
        return get_dcm_rate_impl<frame, parent>(date);
    }
    // current frame is a descendant of root
    else if constexpr (IsDerivedAxis<decltype(axis.parent)>) {
        static constexpr auto parent = make_frame(frame.origin, axis.parent);

        const DCM<frame, parent> dcmToParent            = get_dcm_impl<frame, parent>(date);
        const DCM<parent, root> dcmParentToRoot         = get_dcm_to_root_frame<parent, root>(date);
        const DcmRate<frame, parent> dcmRateToParent    = get_dcm_rate_impl<frame, parent>(date);
        const DcmRate<parent, root> dcmRateParentToRoot = get_dcm_rate_to_root_frame<parent, root>(date);

        // Dcm<grandparent, parent> * DCM<parent, child> = DCM<grandparent, child>
        // DcmRate<grandparent, parent> * DCM<parent, child> + Dcm<grandparent, parent> * DcmRate<parent, child> = DcmRate<grandparent, child>
        return dcmToParent * dcmRateParentToRoot + dcmParentToRoot * dcmRateToParent;
    }
    else {
        return DcmRate<root, frame>::zero();
    }
}

/**
 * @brief Retrieves the accumulated direction cosine matrix acceleration from the root frame to the given frame by
 * recursively composing the DCM accelerations along the parent chain.
 *
 * @tparam frame The frame type for which to retrieve the DCM acceleration to the root frame.
 * @tparam root The root frame type to which the DCM acceleration should be obtained.
 * @param date The date at which to retrieve the DCM acceleration.
 * @return DcmAccel<frame, root> The direction cosine matrix acceleration from the root frame to the given frame.
 */
template <IsFrame auto frame, IsFrame auto root>
inline constexpr DcmAccel<frame, root> get_dcm_accel_to_root_frame(const Date& date)
{
    static constexpr auto axis      = frame.axis;
    static constexpr auto root_axis = root.axis;

    // first check if these transformations exist directly
    if constexpr (HasDcmAccel<frame, root>) { return get_dcm_accel<frame, root>(date); }
    else if constexpr (HasDcmAccel<root, frame>) {
        return get_dcm_accel<root, frame>(date).transpose();
    }
    // current frame is root
    else if constexpr (equivalent(axis, root_axis)) {
        return DcmAccel<root, frame>::zero();
    }
    // current frame is a direct child of root
    else if constexpr (equivalent(axis.parent, root_axis)) {
        static constexpr auto parent = make_frame(frame.origin, axis.parent);
        return get_dcm_accel_impl<frame, parent>(date);
    }
    // current frame is a descendant of root
    else if constexpr (IsDerivedAxis<decltype(axis.parent)>) {
        // DCM<grandparent, parent> * DCM<parent, child> = DCM<grandparent, child>
        static constexpr auto parent = make_frame(frame.origin, axis.parent);

        const DCM<frame, parent> dcmToParent              = get_dcm_impl<frame, parent>(date);
        const DCM<parent, root> dcmParentToRoot           = get_dcm_to_root_frame<parent, root>(date);
        const DcmRate<frame, parent> dcmRateToParent      = get_dcm_rate_impl<frame, parent>(date);
        const DcmRate<parent, root> dcmRateParentToRoot   = get_dcm_rate_to_root_frame<parent, root>(date);
        const DcmAccel<frame, parent> dcmAccelToParent    = get_dcm_accel_impl<frame, parent>(date);
        const DcmAccel<parent, root> dcmAccelParentToRoot = get_dcm_accel_to_root_frame<parent, root>(date);

        // Dcm<grandparent, parent> * DCM<parent, child> = DCM<grandparent, child>
        // DcmRate<grandparent, parent> * DCM<parent, child> + Dcm<grandparent, parent> * DcmRate<parent, child> = DcmRate<grandparent, child>
        // DcmAccel<grandparent, parent> * DCM<parent, child> + 2 * DcmRate<grandparent, parent> * DcmRate<parent, child> + Dcm<grandparent, parent> * DcmAccel<parent, child> = DcmAccel<grandparent, child>
        return dcmToParent * dcmAccelParentToRoot + 2.0 * dcmRateParentToRoot * dcmRateToParent + dcmParentToRoot * dcmAccelToParent;
    }
    else {
        return DcmAccel<root, frame>::zero();
    }
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) between two frames at a given date.
 *
 * This function retrieves the DCM that transforms vectors from frame to frame_u.
 * If the DCM is not directly defined, it attempts to use the inverse DCM if available. If neither is available, it
 * checks for a common ancestor frame and composes the DCMs to and from the common ancestor. If no valid transformation
 * can be found, a compile-time error is triggered.
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

/**
 * @brief Get the Direction Cosine Matrix (DCM) rate between two frames at a given date.
 *
 * This function retrieves the DCM rate that transforms vectors from frame to frame_u.
 * If the DCM rate is not directly defined, it attempts to use the inverse DCM rate if available. If neither is
 * available, it checks for a common ancestor frame and composes the DCM rates to and from the common ancestor. If no
 * valid transformation can be found, it is assumed that the DCM rate is zero
 *
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param date The date at which to retrieve the DCM rate.
 * @return DcmRate<frame, frame_u> The Direction Cosine Matrix rate from frame to frame_u.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmRate<frame, frame_u> get_dcm_rate_impl(const Date& date)
{
    if constexpr (equivalent(frame.axis, frame_u.axis)) { return DcmRate<frame, frame_u>::zero(); }
    else if constexpr (HasDcmRate<frame, frame_u>) {
        return get_dcm_rate<frame, frame_u>(date);
    }
    else if constexpr (HasDcmRate<frame_u, frame>) {
        return get_dcm_rate<frame_u, frame>(date).transpose();
    }
    else if constexpr (HasCommonAncestor<frame.axis, frame_u.axis>) {
        // If no direct DCM defined but common ancestor exists, we can get the DCMs to the common ancestor and compose them
        static constexpr auto root_axis = find_common_ancestor(frame.axis, frame_u.axis);
        static constexpr auto root      = make_frame(frame.origin, root_axis);

        const DCM<frame, root> dcm1           = get_dcm_to_root_frame<frame, root>(date);
        const DCM<frame_u, root> dcm2         = get_dcm_to_root_frame<frame_u, root>(date);
        const DcmRate<frame, root> dcmRate1   = get_dcm_rate_to_root_frame<frame, root>(date);
        const DcmRate<frame_u, root> dcmRate2 = get_dcm_rate_to_root_frame<frame_u, root>(date);

        // DCM_frame->frame_u = DCM_root->frame_u * DCM_frame->root
        // DCM_rate_frame->frame_u = DCM_rate_frame->root * DCM_root->frame_u + DCM_frame->root * DCM_rate_root->frame_u
        return dcmRate1 * dcm2.transpose() + dcm1 * dcmRate2.transpose();
    }
    else {
        // TODO: Trigger warning?
        return DcmRate<frame, frame_u>::zero();
    }
}

/**
 * @brief Get the Direction Cosine Matrix (DCM) acceleration between two frames at a given date.
 *
 * This function retrieves the DCM acceleration that transforms vectors from frame to frame_u.
 * If the DCM acceleration is not directly defined, it attempts to use the inverse DCM acceleration if available. If
 * neither is available, it checks for a common ancestor frame and composes the DCM accelerations to and from the common
 * ancestor. If no valid transformation can be found, it is assumed that the DCM acceleration is zero
 *
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param date The date at which to retrieve the DCM acceleration.
 * @return DcmAccel<frame, frame_u> The Direction Cosine Matrix acceleration from frame to frame_u.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
inline constexpr DcmAccel<frame, frame_u> get_dcm_accel_impl(const Date& date)
{
    if constexpr (equivalent(frame.axis, frame_u.axis)) { return DcmAccel<frame, frame_u>::zero(); }
    else if constexpr (HasDcmAccel<frame, frame_u>) {
        return get_dcm_accel<frame, frame_u>(date);
    }
    else if constexpr (HasDcmAccel<frame_u, frame>) {
        return get_dcm_accel<frame_u, frame>(date).transpose();
    }
    else if constexpr (HasCommonAncestor<frame.axis, frame_u.axis>) {
        // If no direct DCM defined but common ancestor exists, we can get the DCMs to the common ancestor and compose them
        static constexpr auto root_axis = find_common_ancestor(frame.axis, frame_u.axis);
        static constexpr auto root      = make_frame(frame.origin, root_axis);

        const DCM<frame, root> dcm1             = get_dcm_to_root_frame<frame, root>(date);
        const DCM<frame_u, root> dcm2           = get_dcm_to_root_frame<frame_u, root>(date);
        const DcmRate<frame, root> dcmRate1     = get_dcm_rate_to_root_frame<frame, root>(date);
        const DcmRate<frame_u, root> dcmRate2   = get_dcm_rate_to_root_frame<frame_u, root>(date);
        const DcmAccel<frame, root> dcmAccel1   = get_dcm_accel_to_root_frame<frame, root>(date);
        const DcmAccel<frame_u, root> dcmAccel2 = get_dcm_accel_to_root_frame<frame_u, root>(date);

        // DCM_frame->frame_u = DCM_root->frame_u * DCM_frame->root
        // DCM_rate_frame->frame_u = DCM_rate_frame->root * DCM_root->frame_u + DCM_frame->root * DCM_rate_root->frame_u
        // DCM_accel_frame->frame_u = DCM_accel_frame->root * DCM_root->frame_u + 2 * DCM_rate_frame->root * DCM_rate_root->frame_u + DCM_frame->root * DCM_accel_root->frame_u
        return dcmAccel1 * dcm2.transpose() + 2 * dcmRate1 * dcmRate2.transpose() + dcm1 * dcmAccel2.transpose();
    }
    else {
        // TODO: Trigger warning?
        return DcmAccel<frame, frame_u>::zero();
    }
}

/**
 * @brief Get the center offset between two frames at a given date.
 *
 * This function calculates the offset between the origins of two frames by chaining translations. Works for position,
 * velocity, and acceleration for offsets between celestial references, and position offsets for fixed offset frames. Velocity
 * and acceleration offsets for fixed offset frames are not currently supported.
 *
 * @tparam Value_T The type of the offset vector components (e.g., Distance, Velocity, Acceleration).
 * @tparam frame The first frame type.
 * @tparam frame_u The second frame type.
 * @param date The date at which to calculate the offset.
 * @return CartesianVector<Value_T, frame_u> The offset vector from frame to frame_u.
 * @throws std::logic_error If the offset cannot be determined due to lack of common reference or unsupported frame types.
 */
template <typename Value_T, IsFrame auto frame, IsFrame auto frame_u>
inline constexpr CartesianVector<Value_T, frame_u> get_offset_impl(const Date& date)
{
    static_assert(
        std::is_same_v<Value_T, Distance> || std::is_same_v<Value_T, Velocity> || std::is_same_v<Value_T, Acceleration>,
        "translate_vector_into_frame: Value_T must be Distance, Velocity, or Acceleration."
    );

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
        else if constexpr (std::is_same_v<Value_T, Acceleration>) {
            return get_relative_acceleration<origin, origin_u>(date).template force_frame_conversion<frame_u>();
        }
    }
    else if constexpr (IsFixedOffsetFrame<decltype(frame)> || IsFixedOffsetFrame<decltype(frame_u)>) {
        if constexpr (!std::is_same_v<Value_T, Distance>) {
            // We can only calculate velocity offsets for celestial references since we rely on the ephemeris system for the relative velocity
            throw std::logic_error("Fixed velocity and acceleration offsets are not currently supported.");
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

/**
 * @brief Concept to determine if a valid frame transformation (DCM) can be obtained between two frames at a given date, either through a direct DCM or an inverse DCM.
 *
 * @tparam frame The first frame type to check.
 * @tparam frame_u The second frame type to check.
 * @param date The date at which to obtain the DCM.
 * @return true if a valid DCM can be obtained between the two frames, false otherwise.
 */
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
template <IsFrame auto frame, IsFrame auto frame_u>
    requires(IsStaticFrame<decltype(frame)> && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Distance, frame_u>
    transform_vector_into_frame(const CartesianVector<Distance, frame>& vec, const Date& date)
{
    // Same axis: translation only
    if constexpr (equivalent(frame.axis, frame_u.axis)) {
        return translate_vector_into_frame<Distance, frame, frame_u>(vec, date);
    }
    // Same origin: rotation only
    else if constexpr (equivalent(frame.origin, frame_u.origin)) {
        return rotate_vector_into_frame<Distance, frame, frame_u>(vec, date);
    }

    // Translation + rotation case
    const CartesianVector<Distance, frame_u> offset = get_offset_impl<Distance, frame, frame_u>(date);
    const auto dcm                                  = get_dcm_impl<frame, frame_u>(date);

    // r_2 = DCM * r_1 + r_o
    return dcm * vec + offset;
}

/**
 * @brief Transform a velocity vector from one frame to another at a given date, accounting for both rotation and translation.
 *
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param vec The velocity vector to transform.
 * @param date The date at which to perform the transformation.
 * @param position The position vector in the source frame.
 * @return CartesianVector<Velocity, frame_u> A new velocity vector in the target frame.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
    requires(IsStaticFrame<decltype(frame)> && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Velocity, frame_u>
    transform_vector_into_frame(const CartesianVector<Velocity, frame>& vec, const Date& date, const CartesianVector<Distance, frame>& position)
{
    // Same axis: translation only
    if constexpr (equivalent(frame.axis, frame_u.axis)) {
        return translate_vector_into_frame<Velocity, frame, frame_u>(vec, date);
    }
    // Same origin: rotation only
    else if constexpr (equivalent(frame.origin, frame_u.origin)) {
        return rotate_vector_into_frame<Velocity, frame, frame_u>(vec, date);
    }

    // Translation + rotation case
    const CartesianVector<Velocity, frame_u> offset = get_offset_impl<Velocity, frame, frame_u>(date);
    const auto dcm                                  = get_dcm_impl<frame, frame_u>(date);
    const auto dcmRate                              = get_dcm_rate_impl<frame, frame_u>(date);

    // v_2 = DCM * v_1 + DCM_dot * r_1 + v_o
    return dcmRate * position + dcm * vec + offset;
}

/**
 * @brief Transform an acceleration vector from one frame to another at a given date, accounting for both rotation and translation.
 *
 * @tparam frame The source frame type.
 * @tparam frame_u The target frame type.
 * @param vec The acceleration vector to transform.
 * @param date The date at which to perform the transformation.
 * @param position The position vector in the source frame.
 * @param velocity The velocity vector in the source frame.
 * @return CartesianVector<Acceleration, frame_u> A new acceleration vector in the target frame.
 */
template <IsFrame auto frame, IsFrame auto frame_u>
    requires(IsStaticFrame<decltype(frame)> && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Acceleration, frame_u> transform_vector_into_frame(
    const CartesianVector<Acceleration, frame>& vec,
    const Date& date,
    const CartesianVector<Distance, frame>& position,
    const CartesianVector<Velocity, frame>& velocity
)
{
    // Same axis: translation only
    if constexpr (equivalent(frame.axis, frame_u.axis)) {
        return translate_vector_into_frame<Acceleration, frame, frame_u>(vec, date);
    }
    // Same origin: rotation only
    else if constexpr (equivalent(frame.origin, frame_u.origin)) {
        return rotate_vector_into_frame<Acceleration, frame, frame_u>(vec, date);
    }

    // Translation + rotation case
    const CartesianVector<Acceleration, frame_u> offset = get_offset_impl<Acceleration, frame, frame_u>(date);
    const auto dcm                                      = get_dcm_impl<frame, frame_u>(date);
    const auto dcmRate                                  = get_dcm_rate_impl<frame, frame_u>(date);
    const auto dcmAccel                                 = get_dcm_accel_impl<frame, frame_u>(date);

    // a_2 = DCM * a_1 + 2 * DCM_dot * v_1 + DCM_ddot * r_1 + a_o
    return dcmAccel * position + 2.0 * dcmRate * velocity + dcm * vec + offset;
}


} // namespace frames

template <typename Value_T, IsFrame auto _frame_>
template <IsFrame auto frame_u>
    requires(std::is_same_v<Value_T, Distance> && _frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Distance, frame_u> CartesianVector<Value_T, _frame_>::in_frame(const Date& date) const
{
    return frames::transform_vector_into_frame<_frame_, frame_u>(*this, date);
}


template <typename Value_T, IsFrame auto _frame_>
template <IsFrame auto frame_u>
    requires(std::is_same_v<Value_T, Velocity> && _frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Velocity, frame_u>
    CartesianVector<Value_T, _frame_>::in_frame(const Date& date, const CartesianVector<Distance, _frame_>& position) const
{
    return frames::transform_vector_into_frame<_frame_, frame_u>(*this, date, position);
}

template <typename Value_T, IsFrame auto _frame_>
template <IsFrame auto frame_u>
    requires(std::is_same_v<Value_T, Acceleration> && _frame_ != frame_u && IsStaticFrame<decltype(frame_u)>)
inline constexpr CartesianVector<Acceleration, frame_u> CartesianVector<Value_T, _frame_>::in_frame(
    const Date& date,
    const CartesianVector<Distance, _frame_>& position,
    const CartesianVector<Velocity, _frame_>& velocity
) const
{
    return frames::transform_vector_into_frame<_frame_, frame_u>(*this, date, position, velocity);
}

} // namespace astro
} // namespace astrea