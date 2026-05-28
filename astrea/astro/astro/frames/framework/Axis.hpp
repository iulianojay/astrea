/**
 * @file Axis.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Axis in astrea.
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

#include <astro/frames/framework/frame_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct CoordinateLineBase {};
struct AxisBase { 
  template<IsAxis Lhs, IsAxis Rhs>
  [[nodiscard]] friend consteval bool operator==(Lhs, Rhs)
  {
    return std::is_same_v<Lhs, Rhs>;
  }
};

template <typename T>
concept IsAxisProperty = (!IsAxis<T>);

} // namespace detail

enum class Coordinate { X, Y, Z };


template <mp_units::symbol_text _name_>
struct Axis : detail::AxisBase {
    static constexpr auto name = _name_; //!< The name of the axis.
};


template <IsAxis auto _reference_axis_, Coordinate _rotation_coordinate_>
struct FixedRotatingAxis : Axis<decltype(_reference_axis_)::name + mp_units::symbol_text{ "_fixed_rotating" }> {
    static constexpr auto reference_axis      = _reference_axis_;      //!< The reference axis of the frame.
    static constexpr auto rotation_coordinate = _rotation_coordinate_; //!< The coordinate the axis rotates about.
};

struct DynamicAxis : Axis<"dynamic"> {};

template <IsFrame Frame_T, IsAxis Axis_T>
inline consteval auto has_axis(Frame_T, Axis_T)
{
    return std::is_same_v<decltype(Frame_T::axis), Axis_T>;
}

/**
 * @brief Concept to determine if two frames share the same axis.
 *
 * @tparam T The first frame type to check.
 * @tparam U The second frame type to check.
 * @return true if both frames share the same axis, false otherwise.
 */
template <IsFrame T, IsFrame U>
consteval bool has_same_axis(T t, U u)
{
    return T::axis == U::axis;
}

namespace axes {

inline constexpr struct j2000 final : Axis<"EME2000"> {
    // x - mean equator and equinox of date at J2000
    // z - mean pole of date at J2000
} j2000;

inline constexpr struct icrf final : Axis<"ICRF"> {
    // x - Measured, meant to coincide with EME2000 X-axis at J2000
    // z - Measured, meant to coincide with EME2000 Z-axis at J2000
} icrf;

} // namespace axes


} // namespace astro
} // namespace astrea