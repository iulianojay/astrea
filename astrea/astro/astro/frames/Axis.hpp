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

#include <mp-units/ext/fixed_string.h>

#include <units/units.hpp>

#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct CoordinateLineBase {};
struct AxisBase {};

template <typename T>
concept IsAxisProperty = (!IsAxis<T>);

} // namespace detail

enum class Coordinate { X, Y, Z };

template <mp_units::basic_fixed_string _description_, Coordinate _coordinate_>
struct CoordinateLine : detail::CoordinateLineBase {
    static constexpr auto description = _description_; //!< A description of the coordinate line (e.g., "X-axis", "Y-axis", "Z-axis").
    static constexpr auto coordinate = _coordinate_; //!< The coordinate of the line (X, Y, or Z).
};


template <mp_units::basic_fixed_string _name_, IsCoordinateLine auto _a1_, IsCoordinateLine auto _a2_>
struct Axis<_name_, _a1_, _a2_> : detail::AxisBase {
    static constexpr auto a1 = _a1_; //!< The description of the first coordinate line.
    static constexpr auto a2 = _a2_; //!< The description of the second coordinate line.
    // the third axis is always implied
};


template <mp_units::basic_fixed_string _name_, IsAxis auto _reference_axis_, Coordinate _rotation_coordinate_>
struct FixedRotatingAxis {
    static constexpr auto name                = _name_;                //!< The name of the axis.
    static constexpr auto reference_axis      = _reference_axis_;      //!< The reference axis of the frame.
    static constexpr auto rotation_coordinate = _rotation_coordinate_; //!< The coordinate the axis rotates about.
};


namespace axes {

inline constexpr struct j2000_x : CoordinateLine<"Vernal equinox at J2000", Coordinate::X> {
} j2000_x;
inline constexpr struct j2000_z : CoordinateLine<"Normal to the mean equator of date at J2000", Coordinate::Z> {
} j2000_z;
inline constexpr struct j2000 : Axis<"J2000", j2000_x, j2000_z> {
} j2000;

inline constexpr struct icrf_x : CoordinateLine<"ICRF X-axis, made to coincide with the mean equinox of J2000", Coordinate::X> {
} icrf_x;
inline constexpr struct icrf_z : CoordinateLine<"ICRF Z-axis, made to coincide with the mean pole of J2000", Coordinate::Z> {
} icrf_z;
inline constexpr struct icrf : Axis<"ICRF", icrf_x, icrf_z> {
} icrf;

} // namespace axes


} // namespace astro
} // namespace astrea