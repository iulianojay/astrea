/**
 * @file FixedOffsetFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a FixedOffsetFrame in astrea.
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

#include <type_traits>

#include <mp-units/core.h>
#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Helper function to convert a double value to a fixed string at compile time. This is used for generating frame
 * names that include the offset values.
 *
 * @tparam _N_ The double value to convert to a fixed string, wrapped in a double_wrapper for constexpr processing.
 * @return A basic_fixed_string representing the double value as a string, suitable for use in frame names. The string
 * will include the numerical value with a specified precision, and will be null-terminated.
 */
template <utilities::double_wrapper _N_>
inline consteval auto f_to_fixed_string()
{
    constexpr auto s          = utilities::f_to_string<_N_>;
    constexpr std::size_t len = s.size() - 1; // exclude null terminator
    return mp_units::symbol_text(mp_units::fixed_string<len>(s.begin(), s.end() - 1));
}

/**
 * @brief Helper function to convert a quantity to a fixed string at compile time, including its numerical value and
 * unit symbol. This is used for generating frame names that include the offset values.
 *
 * @tparam _q_ The quantity to convert to a fixed string. The quantity must have a unit with a defined symbol.
 * @return A basic_fixed_string representing the quantity as a string, including its numerical value and unit symbol,
 * suitable for use in frame names. The string will be null-terminated.
 */
template <auto _q_>
inline consteval auto quantity_to_fixed_string()
{
    return f_to_fixed_string<_q_.numerical_value_in(_q_.unit)>() + mp_units::symbol_text{ " " } +
           mp_units::symbol_text(_q_.unit._symbol_.portable());
}

/**
 * @brief Helper function to convert a list of quantities to a comma-separated fixed string at compile time. This is
 * used for generating frame names that include multiple offset values.
 *
 * @tparam _first_ The first quantity in the list to convert to a fixed string.
 * @tparam _rest_ The remaining quantities in the list to convert to fixed strings.
 * @return A basic_fixed_string representing the list of quantities as a comma-separated string, suitable for use in frame names. The string will be null-terminated.
 */
template <auto _first_, auto... _rest_>
inline consteval auto quantity_list_to_fixed_string()
{
    if constexpr (sizeof...(_rest_) == 0)
        return quantity_to_fixed_string<_first_>();
    else
        return quantity_to_fixed_string<_first_>() + mp_units::symbol_text{ ", " } + quantity_list_to_fixed_string<_rest_...>();
}

/**
 * @brief Helper function to compose the name of a FixedOffsetFrame based on its parent frame's name and its offset
 * values. This generates a descriptive name that includes the parent frame and the specific offsets applied.
 *
 * @tparam _parent_name_ The name of the parent frame.
 * @tparam _x_ The fixed offset in the x direction.
 * @tparam _y_ The fixed offset in the y direction.
 * @tparam _z_ The fixed offset in the z direction.
 * @return A basic_fixed_string representing the composed name of the FixedOffsetFrame, including the parent frame's name and the offset values.
 */
template <mp_units::symbol_text _parent_name_, Distance _x_, Distance _y_, Distance _z_>
inline consteval auto compose_name()
{
    return _parent_name_ + mp_units::symbol_text{ " + [" } + quantity_list_to_fixed_string<_x_, _y_, _z_>() +
           mp_units::symbol_text{ "]" };
}

/**
 * @brief Helper function to compose the name of a FixedOffsetFrame with ONLY angular offsets based on its parent frame's name and its offset
 * values. This generates a descriptive name that includes the parent frame and the specific angular offsets applied.
 *
 * @tparam _parent_name_ The name of the parent frame.
 * @tparam _phi_ The fixed offset angle around the x-axis.
 * @tparam _theta_ The fixed offset angle around the y-axis.
 * @return A basic_fixed_string representing the composed name of the FixedOffsetFrame, including the parent frame's name and the angular offset values.
 */
template <mp_units::symbol_text _parent_name_, Angle _phi_, Angle _theta_, Angle _psi_>
inline consteval auto compose_name()
{
    return _parent_name_ + mp_units::symbol_text{ " + [" } + quantity_list_to_fixed_string<_phi_, _theta_, _psi_>() +
           mp_units::symbol_text{ "]" };
}

/**
 * @brief Helper function to compose the name of a FixedOffsetFrame with both spatial and angular offsets based on its parent frame's name and its offset
 * values. This generates a descriptive name that includes the parent frame and the specific spatial and angular offsets applied.
 *
 * @tparam _parent_name_ The name of the parent frame.
 * @tparam _x_ The fixed offset in the x direction.
 * @tparam _y_ The fixed offset in the y direction.
 * @tparam _z_ The fixed offset in the z direction.
 * @tparam _phi_ The fixed offset angle around the x-axis.
 * @tparam _theta_ The fixed offset angle around the y-axis.
 * @tparam _psi_ The fixed offset angle around the z-axis.
 * @return A basic_fixed_string representing the composed name of the FixedOffsetFrame, including the parent frame's name and the spatial and angular offset values.
 */
template <mp_units::symbol_text _parent_name_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_>
inline consteval auto compose_name()
{
    return _parent_name_ + mp_units::symbol_text{ " + [" } + quantity_list_to_fixed_string<_x_, _y_, _z_>() +
           mp_units::symbol_text{ "; " } + quantity_list_to_fixed_string<_phi_, _theta_, _psi_>() + mp_units::symbol_text{ "]" };
}

namespace detail {

} // namespace detail

template <IsOrigin auto _parent_, Distance _x_, Distance _y_, Distance _z_>
struct FixedOffsetOrigin : Origin<"fixed offset", _parent_> {
    struct Offset {
        Distance x;
        Distance y;
        Distance z;
    };
    static constexpr Offset offset{ _x_, _y_, _z_ }; //!< The fixed offset vector from the parent frame to this frame.
};

template <IsAxis auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_>
struct FixedOffsetAxis : Axis<"fixed offset", _parent_> {
    static constexpr auto sequence = _sequence_; //!< The rotation sequence for the angular offset.
    struct Misalignment {
        Angle phi;
        Angle theta;
        Angle psi;
    };
    static constexpr Misalignment misalignment{ _phi_, _theta_, _psi_ }; //!< The fixed angular offset from the parent frame to this frame.
};

template <IsOrigin Origin_T>
    requires(HasSpatialOffset<Origin_T>)
[[nodiscard]] consteval bool offset_is_zero(Origin_T origin)
{
    using mp_units::is_eq_zero;
    return is_eq_zero(origin.offset.x) && is_eq_zero(origin.offset.y) && is_eq_zero(origin.offset.z);
}

template <IsAxis Axis_T>
    requires(HasAngularOffset<Axis_T>)
[[nodiscard]] consteval bool misalignment_is_zero(Axis_T axis)
{
    using mp_units::is_eq_zero;
    return is_eq_zero(axis.misalignment.phi) && is_eq_zero(axis.misalignment.theta) && is_eq_zero(axis.misalignment.psi);
}


template <IsOrigin Lhs, IsOrigin Rhs>
    requires(HasSpatialOffset<Lhs> || HasSpatialOffset<Rhs>)
[[nodiscard]] consteval bool equivalent(Lhs lhs, Rhs rhs)
{
    if constexpr (HasSpatialOffset<Lhs> && !HasSpatialOffset<Rhs>) {
        return equivalent(lhs.parent, rhs) && offset_is_zero(lhs);
    }
    else if constexpr (!HasSpatialOffset<Lhs> && HasSpatialOffset<Rhs>) {
        return equivalent(lhs, rhs.parent) && offset_is_zero(rhs);
    }
    else {
        // Offset numbers are baked into the type so don't need to check them directly
        return std::is_same_v<Lhs, Rhs>;
    }
}

template <IsAxis Lhs, IsAxis Rhs>
    requires(HasAngularOffset<Lhs> || HasAngularOffset<Rhs>)
[[nodiscard]] consteval bool equivalent(Lhs lhs, Rhs rhs)
{
    if constexpr (HasAngularOffset<Lhs> && !HasAngularOffset<Rhs>) {
        return equivalent(lhs.parent, rhs) && misalignment_is_zero(lhs);
    }
    else if constexpr (!HasAngularOffset<Lhs> && HasAngularOffset<Rhs>) {
        return equivalent(lhs, rhs.parent) && misalignment_is_zero(rhs);
    }
    else {
        // Offset numbers are baked into the type so don't need to check them directly
        return std::is_same_v<Lhs, Rhs>;
    }
}

/**
 * @brief Class representing a fixed offset frame, which is defined by a fixed spatial and/or angular offset from a parent frame.
 *
 * This class allows for the definition of frames that are not aligned with their parent frame, such as a spacecraft body frame that is offset from an inertial frame.
 *
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam Args A variadic list of template parameters that define the spatial and/or angular offsets. These can be distances
 * for spatial offsets or angles for angular offsets, along with an optional rotation sequence for the angular offsets.
 */
template <auto...>
struct FixedOffsetFrame;

/**
 * @brief Specialization of FixedOffsetFrame for a pure spatial offset (no angular misalignment).
 *
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam _x_ The fixed offset in the x direction from the parent frame.
 * @tparam _y_ The fixed offset in the y direction from the parent frame.
 * @tparam _z_ The fixed offset in the z direction from the parent frame.
 * @tparam Args Additional template parameters (not used in this specialization).
 */
template <IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, auto... Args>
struct FixedOffsetFrame<_parent_, _x_, _y_, _z_, Args...>
    : Frame<compose_name<_parent_.name, _x_, _y_, _z_>(), FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{}, _parent_.axis, _parent_> {
};

/**
 * @brief Specialization of FixedOffsetFrame for a pure angular offset (no spatial offset).
 *
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam _phi_ The fixed offset angle around the x-axis from the parent frame.
 * @tparam _theta_ The fixed offset angle around the y-axis from the parent frame.
 * @tparam _psi_ The fixed offset angle around the z-axis from the parent frame.
 * @tparam _sequence_ The rotation sequence for applying the angular offsets.
 * @tparam Args Additional template parameters (not used in this specialization).
 */
template <IsFrame auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_parent_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<compose_name<_parent_.name, _phi_, _theta_, _psi_>(), _parent_.origin, FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{}, _parent_> {
};

/**
 * @brief Specialization of FixedOffsetFrame for a combined spatial and angular offset.
 *
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam _x_ The fixed offset in the x direction from the parent frame.
 * @tparam _y_ The fixed offset in the y direction from the parent frame.
 * @tparam _z_ The fixed offset in the z direction from the parent frame.
 * @tparam _phi_ The fixed offset angle around the x-axis from the parent frame.
 * @tparam _theta_ The fixed offset angle around the y-axis from the parent frame.
 * @tparam _psi_ The fixed offset angle around the z-axis from the parent frame.
 * @tparam _sequence_ The rotation sequence for applying the angular offsets.
 */
template <IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_parent_, _x_, _y_, _z_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<
          compose_name<_parent_.name, _x_, _y_, _z_, _phi_, _theta_, _psi_>(),
          FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{},
          FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{},
          _parent_> {};

/**
 * @brief Specialization of FixedOffsetFrame for a spatial offset with no angular misalignment that lets the name be specified.
 *
 * @tparam _name_ The name of the frame.
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam _x_ The fixed offset in the x direction from the parent frame.
 * @tparam _y_ The fixed offset in the y direction from the parent frame.
 * @tparam _z_ The fixed offset in the z direction from the parent frame.
 */
template <mp_units::symbol_text _name_, IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, auto... Args>
struct FixedOffsetFrame<_name_, _parent_, _x_, _y_, _z_, Args...>
    : Frame<_name_, FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{}, _parent_.axis, _parent_> {};

/**
 * @brief Specialization of FixedOffsetFrame for an angular offset with no spatial misalignment that lets the name be specified.
 *
 * @tparam _name_ The name of the frame.
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam _phi_ The fixed offset angle around the x-axis from the parent frame.
 * @tparam _theta_ The fixed offset angle around the y-axis from the parent frame.
 * @tparam _psi_ The fixed offset angle around the z-axis from the parent frame.
 * @tparam _sequence_ The rotation sequence for applying the angular offsets.
 */
template <mp_units::symbol_text _name_, IsFrame auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_name_, _parent_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<_name_, _parent_.origin, FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{}, _parent_> {};

/**
 * @brief Specialization of FixedOffsetFrame for a combined spatial and angular offset that lets the name be specified.
 *
 * @tparam _name_ The name of the frame.
 * @tparam _parent_ The parent frame from which this frame is derived. Must satisfy the IsFrame concept.
 * @tparam _x_ The fixed offset in the x direction from the parent frame.
 * @tparam _y_ The fixed offset in the y direction from the parent frame.
 * @tparam _z_ The fixed offset in the z direction from the parent frame.
 * @tparam _phi_ The fixed offset angle around the x-axis from the parent frame.
 * @tparam _theta_ The fixed offset angle around the y-axis from the parent frame.
 * @tparam _psi_ The fixed offset angle around the z-axis from the parent frame.
 * @tparam _sequence_ The rotation sequence for applying the angular offsets.
 */
template <mp_units::symbol_text _name_, IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_name_, _parent_, _x_, _y_, _z_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<_name_, FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{}, FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{}, _parent_> {
};

/**
 * @brief Checks if a fixed offset frame is aligned with its parent frame.
 *
 * @tparam Frame_T The type of the fixed offset frame.
 * @param frame The fixed offset frame instance.
 * @return true if the frame is aligned with its parent, false otherwise.
 */
template <IsFixedOffsetFrame Frame_T>
consteval bool is_aligned_with_parent(Frame_T frame)
{
    if constexpr (HasSpatialOffset<Frame_T> && !HasAngularOffset<Frame_T>) { return offset_is_zero(frame.origin); }
    else if constexpr (!HasSpatialOffset<Frame_T> && HasAngularOffset<Frame_T>) {
        return misalignment_is_zero(frame.axis);
    }
    else if constexpr (HasSpatialOffset<Frame_T> && HasAngularOffset<Frame_T>) {
        return offset_is_zero(frame.origin) && misalignment_is_zero(frame.axis);
    }
    throw std::logic_error("Invalid frame configuration: Frame must have at least a spatial or angular offset to be considered a FixedOffsetFrame.");
}

/**
 * @brief Checks if two fixed offset frames have the same spatial offsets.
 *
 * @tparam Lhs The type of the left-hand side fixed offset frame.
 * @tparam Rhs The type of the right-hand side fixed offset frame.
 * @param lhs The left-hand side fixed offset frame instance.
 * @param rhs The right-hand side fixed offset frame instance.
 * @return true if both frames have the same spatial offsets, false otherwise.
 */
template <IsFixedOffsetFrame Lhs, IsFixedOffsetFrame Rhs>
[[nodiscard]] consteval bool have_same_offsets(Lhs lhs, Rhs rhs)
{
    if constexpr (HasSpatialOffset<Lhs> && HasSpatialOffset<Rhs>) {
        return std::is_same_v<decltype(lhs.origin.offset), decltype(rhs.origin.offset)>;
    }
    else if constexpr (HasSpatialOffset<Lhs> || HasSpatialOffset<Rhs>) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Checks if two fixed offset frames have the same angular misalignment.
 *
 * @tparam Lhs The type of the left-hand side fixed offset frame.
 * @tparam Rhs The type of the right-hand side fixed offset frame.
 * @param lhs The left-hand side fixed offset frame instance.
 * @param rhs The right-hand side fixed offset frame instance.
 * @return true if both frames have the same angular misalignment, false otherwise.
 */
template <IsFixedOffsetFrame Lhs, IsFixedOffsetFrame Rhs>
[[nodiscard]] consteval bool have_same_misalignment(Lhs lhs, Rhs rhs)
{
    if constexpr (HasAngularOffset<Lhs> && HasAngularOffset<Rhs>) {
        return std::is_same_v<decltype(lhs.axis.misalignment), decltype(rhs.axis.misalignment)>;
    }
    else if constexpr (HasAngularOffset<Lhs> || HasAngularOffset<Rhs>) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Checks if two frames are equivalent, considering their parent frames and any fixed offsets (spatial or angular).
 *
 * @tparam Lhs The type of the left-hand side frame.
 * @tparam Rhs The type of the right-hand side frame.
 * @param lhs The left-hand side frame instance.
 * @param rhs The right-hand side frame instance.
 * @return true if both frames are equivalent, false otherwise.
 */
template <IsFrame Lhs, IsFrame Rhs>
    requires(IsFixedOffsetFrame<Lhs> || IsFixedOffsetFrame<Rhs>)
[[nodiscard]] consteval bool equivalent(Lhs lhs, Rhs rhs)
{
    if constexpr (IsFixedOffsetFrame<Lhs> && !IsFixedOffsetFrame<Rhs>) {
        return equivalent(lhs.parent, rhs) && is_aligned_with_parent(lhs);
    }
    else if constexpr (!IsFixedOffsetFrame<Lhs> && IsFixedOffsetFrame<Rhs>) {
        return equivalent(lhs, rhs.parent) && is_aligned_with_parent(rhs);
    }
    else if constexpr (IsFixedOffsetFrame<Lhs> && IsFixedOffsetFrame<Rhs>) {
        return equivalent(lhs.parent, rhs.parent) && have_same_offsets(lhs, rhs) && have_same_misalignment(lhs, rhs);
    }
}

/**
 * @brief Retrieves the root frame of a given fixed offset frame by recursively traversing the parent chain.
 *
 * @tparam frame The fixed offset frame.
 * @return The root frame of the given fixed offset frame.
 */
template <IsFixedOffsetFrame auto frame>
consteval auto get_root_frame()
{
    if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) { return get_root_frame<frame.parent>(); }
    else {
        return frame.parent;
    }
}

/**
 * @brief Retrieves the fixed spatial offset from the parent frame to the given FixedOffsetFrame.
 */
template <IsFixedOffsetFrame auto frame>
inline constexpr auto get_offset_from_frame()
{
    if constexpr (HasSpatialOffset<decltype(frame)>) {
        constexpr auto& off = frame.origin.offset;
        return CartesianVector<Distance, frame.parent>(off.x, off.y, off.z);
    }
    else {
        return CartesianVector<Distance, frame.parent>{};
    }
}

/**
 * @brief Retrieves the accumulated fixed spatial offset from the root frame to the given FixedOffsetFrame by recursively summing the offsets along the parent chain.
 */
template <IsFixedOffsetFrame auto frame>
inline constexpr auto get_offset_from_root_frame()
{
    if constexpr (HasSpatialOffset<decltype(frame)>) {
        if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) {
            // r_grandparent->parent + r_parent->child = r_grandparent->child
            // Force-convert the accumulated parent offset into frame::parent's frame type so
            // both operands of operator+ share the same CartesianVector frame parameter.
            return get_offset_from_root_frame<frame.parent>().template force_frame_conversion<frame.parent>() +
                   get_offset_from_frame<frame>();
        }
        else {
            return get_offset_from_frame<frame>();
        }
    }
    else {
        return CartesianVector<Distance, frame.parent>{};
    }
}

/**
 * @brief Retrieves the accumulated direction cosine matrix from the root frame to the given FixedOffsetFrame by recursively composing the DCMs along the parent chain.
 */
template <IsFixedOffsetFrame auto frame>
inline constexpr auto get_dcm_from_root_frame()
{
    static constexpr Date dummyDate;
    if constexpr (HasAngularOffset<std::remove_cv_t<decltype(frame)>>) {
        if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) {
            // DCM<grandparent, parent> * DCM<parent, child> = DCM<grandparent, child>
            return get_dcm_from_root_frame<frame.parent>() * get_dcm<frame.parent, frame>(dummyDate);
        }
        else {
            return get_dcm<frame.parent, frame>(dummyDate);
        }
    }
    else {
        if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) {
            return get_dcm_from_root_frame<frame.parent>();
        }
        else {
            return DCM<frame.parent, frame>::identity();
        }
    }
}

} // namespace astro
} // namespace astrea