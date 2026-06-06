/**
 * @file body_fixed_frames.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for body-fixed frames. Just ECEF right now.
 * @date 2025-08-05
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

#include <astro/frames/framework/BodyFixedFrame.hpp>
#include <astro/systems/celestial_bodies.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury {
inline constexpr struct mercury_fixed final : BodyFixedFrame<"Mercury Fixed Frame", planets::Mercury> {
} mercury_fixed;
} // namespace mercury

namespace venus {
inline constexpr struct venus_fixed final : BodyFixedFrame<"Venus Fixed Frame", planets::Venus> {
} venus_fixed;
} // namespace venus

namespace earth {
inline constexpr struct earth_fixed final : BodyFixedFrame<"Earth Fixed Frame", planets::Earth> {
} earth_fixed;
} // namespace earth

namespace moon {
inline constexpr struct moon_fixed final : BodyFixedFrame<"Moon Fixed Frame", moons::Moon> {
} moon_fixed;
} // namespace moon

namespace mars {
inline constexpr struct mars_fixed final : BodyFixedFrame<"Mars Fixed Frame", planets::Mars> {
} mars_fixed;
} // namespace mars

namespace phobos {
inline constexpr struct phobos_fixed final : BodyFixedFrame<"Phobos Fixed Frame", moons::Phobos> {
} phobos_fixed;
} // namespace phobos

namespace deimos {
inline constexpr struct deimos_fixed final : BodyFixedFrame<"Deimos Fixed Frame", moons::Deimos> {
} deimos_fixed;
} // namespace deimos

namespace jupiter {
inline constexpr struct jupiter_fixed final : BodyFixedFrame<"Jupiter Fixed Frame", planets::Jupiter> {
} jupiter_fixed;
} // namespace jupiter

namespace ganymede {
inline constexpr struct ganymede_fixed final : BodyFixedFrame<"Ganymede Fixed Frame", moons::Ganymede> {
} ganymede_fixed;
} // namespace ganymede

namespace callisto {
inline constexpr struct callisto_fixed final : BodyFixedFrame<"Callisto Fixed Frame", moons::Callisto> {
} callisto_fixed;
} // namespace callisto

namespace io {
inline constexpr struct io_fixed final : BodyFixedFrame<"Io Fixed Frame", moons::Io> {
} io_fixed;
} // namespace io

namespace europa {
inline constexpr struct europa_fixed final : BodyFixedFrame<"Europa Fixed Frame", moons::Europa> {
} europa_fixed;
} // namespace europa

namespace saturn {
inline constexpr struct saturn_fixed final : BodyFixedFrame<"Saturn Fixed Frame", planets::Saturn> {
} saturn_fixed;
} // namespace saturn

namespace titan {
inline constexpr struct titan_fixed final : BodyFixedFrame<"Titan Fixed Frame", moons::Titan> {
} titan_fixed;
} // namespace titan

namespace rhea {
inline constexpr struct rhea_fixed final : BodyFixedFrame<"Rhea Fixed Frame", moons::Rhea> {
} rhea_fixed;
} // namespace rhea

namespace iapetus {
inline constexpr struct iapetus_fixed final : BodyFixedFrame<"Iapetus Fixed Frame", moons::Iapetus> {
} iapetus_fixed;
} // namespace iapetus

namespace uranus {
inline constexpr struct uranus_fixed final : BodyFixedFrame<"Uranus Fixed Frame", planets::Uranus> {
} uranus_fixed;
} // namespace uranus

namespace titania {
inline constexpr struct titania_fixed final : BodyFixedFrame<"Titania Fixed Frame", moons::Titania> {
} titania_fixed;
} // namespace titania

namespace oberon {
inline constexpr struct oberon_fixed final : BodyFixedFrame<"Oberon Fixed Frame", moons::Oberon> {
} oberon_fixed;
} // namespace oberon

namespace neptune {
inline constexpr struct neptune_fixed final : BodyFixedFrame<"Neptune Fixed Frame", planets::Neptune> {
} neptune_fixed;
} // namespace neptune

namespace triton {
inline constexpr struct triton_fixed final : BodyFixedFrame<"Triton Fixed Frame", moons::Triton> {
} triton_fixed;
} // namespace triton

} // namespace frames
} // namespace astro
} // namespace astrea