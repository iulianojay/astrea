

# File FixedOffsetFrame.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**frames**](dir_45ba6462728f0c3fdeb841915d341ea3.md) **>** [**framework**](dir_aa3952657448f7008c08b8ed45c303ac.md) **>** [**FixedOffsetFrame.hpp**](FixedOffsetFrame_8hpp.md)

[Go to the documentation of this file](FixedOffsetFrame_8hpp.md)


```C++

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

template <utilities::double_wrapper _N_>
inline consteval auto f_to_fixed_string()
{
    constexpr auto s          = utilities::f_to_string<_N_>;
    constexpr std::size_t len = s.size() - 1; // exclude null terminator
    return mp_units::symbol_text(mp_units::fixed_string<len>(s.begin(), s.end() - 1));
}

template <auto _q_>
inline consteval auto quantity_to_fixed_string()
{
    return f_to_fixed_string<_q_.numerical_value_in(_q_.unit)>() + mp_units::symbol_text{ " " } +
           mp_units::symbol_text(_q_.unit._symbol_.portable());
}

template <auto _first_, auto... _rest_>
inline consteval auto quantity_list_to_fixed_string()
{
    if constexpr (sizeof...(_rest_) == 0)
        return quantity_to_fixed_string<_first_>();
    else
        return quantity_to_fixed_string<_first_>() + mp_units::symbol_text{ ", " } + quantity_list_to_fixed_string<_rest_...>();
}

template <mp_units::symbol_text _parent_name_, Distance _x_, Distance _y_, Distance _z_>
inline consteval auto compose_name()
{
    return _parent_name_ + mp_units::symbol_text{ " + [" } + quantity_list_to_fixed_string<_x_, _y_, _z_>() +
           mp_units::symbol_text{ "]" };
}

template <mp_units::symbol_text _parent_name_, Angle _phi_, Angle _theta_, Angle _psi_>
inline consteval auto compose_name()
{
    return _parent_name_ + mp_units::symbol_text{ " + [" } + quantity_list_to_fixed_string<_phi_, _theta_, _psi_>() +
           mp_units::symbol_text{ "]" };
}

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
    static constexpr Offset offset{ _x_, _y_, _z_ }; 
};

template <IsAxis auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_>
struct FixedOffsetAxis : Axis<"fixed offset", _parent_> {
    static constexpr auto sequence = _sequence_; 
    struct Misalignment {
        Angle phi;
        Angle theta;
        Angle psi;
    };
    static constexpr Misalignment misalignment{ _phi_, _theta_, _psi_ }; 
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

template <auto...>
struct FixedOffsetFrame;

template <IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, auto... Args>
struct FixedOffsetFrame<_parent_, _x_, _y_, _z_, Args...>
    : Frame<compose_name<_parent_.name, _x_, _y_, _z_>(), FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{}, _parent_.axis, _parent_> {
};

template <IsFrame auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_parent_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<compose_name<_parent_.name, _phi_, _theta_, _psi_>(), _parent_.origin, FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{}, _parent_> {
};

template <IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_parent_, _x_, _y_, _z_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<
          compose_name<_parent_.name, _x_, _y_, _z_, _phi_, _theta_, _psi_>(),
          FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{},
          FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{},
          _parent_> {};

template <mp_units::symbol_text _name_, IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, auto... Args>
struct FixedOffsetFrame<_name_, _parent_, _x_, _y_, _z_, Args...>
    : Frame<_name_, FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{}, _parent_.axis, _parent_> {};

template <mp_units::symbol_text _name_, IsFrame auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_name_, _parent_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<_name_, _parent_.origin, FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{}, _parent_> {};

template <mp_units::symbol_text _name_, IsFrame auto _parent_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<_name_, _parent_, _x_, _y_, _z_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<_name_, FixedOffsetOrigin<_parent_.origin, _x_, _y_, _z_>{}, FixedOffsetAxis<_parent_.axis, _phi_, _theta_, _psi_, _sequence_>{}, _parent_> {
};

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

template <IsFixedOffsetFrame auto frame>
consteval auto get_root_frame()
{
    if constexpr (IsDerivedFrame<std::remove_cv_t<decltype(frame.parent)>>) { return get_root_frame<frame.parent>(); }
    else {
        return frame.parent;
    }
}

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
```


