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

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/framework/Frame.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct BodyFixedFrameBase {};

} // namespace detail

/**
 * @brief Fixed rotating frame .
 */
template <mp_units::symbol_text _name_, IsCelestialBody auto _origin_, IsAxis auto _axis_ = _origin_.reference_axes>
struct BodyFixedFrame : Frame<_name_, _origin_, _axis_>, detail::BodyFixedFrameBase {};

template <IsCelestialBody auto _body1_, IsCelestialBody auto _body2_>
struct SynodicAxis
    : Axis<_body1_.name + mp_units::symbol_text{ "-" } + _body2_.name + mp_units::symbol_text{ " synodic axis" }> {};

template <mp_units::symbol_text _name_, IsBarycenter auto _origin_, IsCelestialBody auto _body1_, IsCelestialBody auto _body2_>
struct SynodicFrame : Frame<_name_, _origin_, SynodicAxis<_body1_, _body2_>{}> {};

} // namespace astro
} // namespace astrea