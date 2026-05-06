/**
 * @file Frame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Frame in astrea.
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

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct FrameBase {};

template <CelestialBodyId _origin, FrameAxis _axis>
struct FrameInterface : FrameBase {
    static constexpr CelestialBodyId origin = _origin; //!< The central body associated with the frame.
    static constexpr FrameAxis axis         = _axis;   //!< The axis type of the frame.
};

} // namespace detail

template <CelestialBodyId _origin, FrameAxis _axis, typename _parent = void>
struct Frame;

template <CelestialBodyId _origin, FrameAxis _axis, IsFrame _parent>
struct Frame<_origin, _axis, _parent> : detail::FrameInterface<_origin, _axis> {
    using parent = _parent; //!< The parent frame of this frame.
};

template <CelestialBodyId _origin, FrameAxis _axis>
struct Frame<_origin, _axis, void> : detail::FrameInterface<_origin, _axis> {};

template <utilities::fixed_string _name, CelestialBodyId _origin, FrameAxis _axis, typename _parent = void>
struct NamedFrame : Frame<_origin, _axis, _parent> {
    static constexpr utilities::fixed_string name = _name; //!< The name of the frame.
};


} // namespace astro
} // namespace astrea