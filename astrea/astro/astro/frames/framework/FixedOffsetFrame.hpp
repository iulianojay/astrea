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

namespace detail {

template <Distance _x_, Distance _y_, Distance _z_>
struct FixedOffsetOrigin : Origin<"fixed offset"> {
    struct Offset {
        decltype(_x_) x;
        decltype(_y_) y;
        decltype(_z_) z;
    };
    static constexpr Offset offset{ _x_, _y_, _z_ }; //!< The fixed offset vector from the parent frame to this frame.
};

template <Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_>
struct FixedOffsetAxis : Axis<"fixed offset"> {
    static constexpr auto sequence = _sequence_; //!< The rotation sequence for the angular offset.
    struct Misalignment {
        decltype(_phi_) phi;
        decltype(_theta_) theta;
        decltype(_psi_) psi;
    };
    static constexpr Misalignment misalignment{ _phi_, _theta_, _psi_ }; //!< The fixed angular offset from the parent frame to this frame.
};

} // namespace detail

template <Distance _x_, Distance _y_, Distance _z_>
inline constexpr detail::FixedOffsetOrigin<_x_, _y_, _z_> FixedOffsetOrigin{};

template <Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_>
inline constexpr detail::FixedOffsetAxis<_phi_, _theta_, _psi_, _sequence_> FixedOffsetAxis{};

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
    : Frame<compose_name<_parent_.name, _x_, _y_, _z_>(), FixedOffsetOrigin<_x_, _y_, _z_>, _parent_.axis, _parent_> {};

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
    : Frame<compose_name<_parent_.name, _phi_, _theta_, _psi_>(), _parent_.origin, FixedOffsetAxis<_phi_, _theta_, _psi_, _sequence_>, _parent_> {
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
    : Frame<compose_name<_parent_.name, _x_, _y_, _z_, _phi_, _theta_, _psi_>(), FixedOffsetOrigin<_x_, _y_, _z_>, FixedOffsetAxis<_phi_, _theta_, _psi_, _sequence_>, _parent_> {
};

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
 * @brief Retrieves the direction cosine matrix representing the fixed angular offset from the parent frame to the given FixedOffsetFrame.
 */
template <IsFixedOffsetFrame auto frame>
inline constexpr DirectionCosineMatrix<frame.parent, frame> get_dcm_from_frame()
{
    if constexpr (HasAngularOffset<decltype(frame)>) {
        return DirectionCosineMatrix<frame.parent, frame>::template from_euler_angles<decltype(frame.axis)::sequence>(
            decltype(frame.axis)::misalignment.phi,
            decltype(frame.axis)::misalignment.theta,
            decltype(frame.axis)::misalignment.psi
        );
    }
    else {
        return DirectionCosineMatrix<frame.parent, frame>::identity();
    }
}

/**
 * @brief Retrieves the accumulated direction cosine matrix from the root frame to the given FixedOffsetFrame by recursively composing the DCMs along the parent chain.
 */
template <IsFixedOffsetFrame auto frame>
inline constexpr auto get_dcm_from_root_frame()
{
    if constexpr (HasAngularOffset<std::remove_cv_t<decltype(frame)>>) {
        if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) {
            // DCM<grandparent, parent> * DCM<parent, child> = DCM<grandparent, child>
            return get_dcm_from_root_frame<frame.parent>() * get_dcm_from_frame<frame>();
        }
        else {
            return get_dcm_from_frame<frame>();
        }
    }
    else {
        if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) {
            return get_dcm_from_root_frame<frame.parent>();
        }
        else {
            return DirectionCosineMatrix<frame.parent, frame>::identity();
        }
    }
}

} // namespace astro
} // namespace astrea