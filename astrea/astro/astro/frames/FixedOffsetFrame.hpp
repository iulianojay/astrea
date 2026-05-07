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

#include <mp-units/ext/fixed_string.h>

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/frame_concepts.hpp>

namespace astrea {
namespace astro {

template <utilities::double_wrapper N>
consteval auto f_to_fixed_string()
{
    constexpr auto s          = utilities::f_to_string<N>;
    constexpr std::size_t len = s.size() - 1; // exclude null terminator
    return mp_units::basic_fixed_string<char, len>(s.begin(), s.end() - 1);
}

template <mp_units::basic_fixed_string ParentName, Distance x, Distance y, Distance z>
inline consteval auto compose_name()
{
    return ParentName + " + [" + f_to_fixed_string<x.numerical_value_in(x.unit)>() + ", " +
           f_to_fixed_string<y.numerical_value_in(y.unit)>() + ", " + f_to_fixed_string<z.numerical_value_in(z.unit)>() + "]";
}

template <typename Frame_T, Distance x = Distance::zero(), Distance y = Distance::zero(), Distance z = Distance::zero()>
struct FixedOffsetFrame : Frame<compose_name<Frame_T::name, x, y, z>(), CelestialBodyId::FIXED_OFFSET, Frame_T::axis, Frame_T> {
    static constexpr CartesianVector<Distance, Frame_T> offset = { x, y, z }; //!< The fixed offset vector from the parent frame to this frame.
};

} // namespace astro
} // namespace astrea