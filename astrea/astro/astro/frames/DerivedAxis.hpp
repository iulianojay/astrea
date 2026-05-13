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

#include <astro/frames/CartesianVector.hpp>
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

template <IsAxis auto _parent_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_>
struct DerivedAxis : detail::AxisBase {
    static constexpr auto name                = _name_;                //!< The name of the axis.
    static constexpr auto reference_axis      = _reference_axis_;      //!< The reference axis of the frame.
    static constexpr auto rotation_coordinate = _rotation_coordinate_; //!< The coordinate the axis rotates about.
};
struct FixedOffsetFrame<Parent, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<compose_name<Parent::name, _phi_, _theta_, _psi_>(), CelestialBodyId::FIXED_OFFSET, Parent::axis, Parent> {
    static constexpr auto sequence = _sequence_; //!< The rotation sequence for the angular offset.
    static constexpr CartesianVector<Angle, Parent> misalignment = { _phi_, _theta_, _psi_ }; //!< The fixed angular offset dcm from the parent frame to this frame.
};


namespace axes {


} // namespace axes


} // namespace astro
} // namespace astrea