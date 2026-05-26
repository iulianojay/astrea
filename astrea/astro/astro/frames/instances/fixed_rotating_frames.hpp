/**
 * @file fixed_rotating_frames.hpp
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

#include <astro/frames/Frame.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/systems/planets.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury {
inline constexpr struct mercury_fixed final : FixedRotatingFrame<"mercury_fixed", planets::Mercury, axes::icrf, Coordinate::Z> {
} mercury_fixed;
} // namespace mercury

namespace venus {
inline constexpr struct venus_fixed final : FixedRotatingFrame<"venus_fixed", planets::Venus, axes::icrf, Coordinate::Z> {
} venus_fixed;
} // namespace venus

namespace earth {
inline constexpr struct earth_fixed final : FixedRotatingFrame<"ecef", planets::Earth, axes::icrf, Coordinate::Z, icrf> {
} earth_fixed;
inline constexpr struct ems_fixed final
    : FixedRotatingFrame<"ems_fixed", barycenters::EarthMoonBarycenter, axes::icrf, Coordinate::Z> {
} ems_fixed;
} // namespace earth

namespace moon {
inline constexpr struct moon_fixed final : FixedRotatingFrame<"moon_fixed", moons::Moon, axes::icrf, Coordinate::Z> {
} moon_fixed;
} // namespace moon

namespace mars {
inline constexpr struct mars_fixed final : FixedRotatingFrame<"mars_fixed", planets::Mars, axes::icrf, Coordinate::Z> {
} mars_fixed;
} // namespace mars

namespace phobos {
inline constexpr struct phobos_fixed final : FixedRotatingFrame<"phobos_fixed", moons::Phobos, axes::icrf, Coordinate::Z> {
} phobos_fixed;
} // namespace phobos

namespace deimos {
inline constexpr struct deimos_fixed final : FixedRotatingFrame<"deimos_fixed", moons::Deimos, axes::icrf, Coordinate::Z> {
} deimos_fixed;
} // namespace deimos

namespace jupiter {
inline constexpr struct jupiter_fixed final : FixedRotatingFrame<"jupiter_fixed", planets::Jupiter, axes::icrf, Coordinate::Z> {
} jupiter_fixed;
} // namespace jupiter

namespace ganymede {
inline constexpr struct ganymede_fixed final : FixedRotatingFrame<"ganymede_fixed", moons::Ganymede, axes::icrf, Coordinate::Z> {
} ganymede_fixed;
} // namespace ganymede

namespace callisto {
inline constexpr struct callisto_fixed final : FixedRotatingFrame<"callisto_fixed", moons::Callisto, axes::icrf, Coordinate::Z> {
} callisto_fixed;
} // namespace callisto

namespace io {
inline constexpr struct io_fixed final : FixedRotatingFrame<"io_fixed", moons::Io, axes::icrf, Coordinate::Z> {
} io_fixed;
} // namespace io

namespace europa {
inline constexpr struct europa_fixed final : FixedRotatingFrame<"europa_fixed", moons::Europa, axes::icrf, Coordinate::Z> {
} europa_fixed;
} // namespace europa

namespace saturn {
inline constexpr struct saturn_fixed final : FixedRotatingFrame<"saturn_fixed", planets::Saturn, axes::icrf, Coordinate::Z> {
} saturn_fixed;
} // namespace saturn

namespace titan {
inline constexpr struct titan_fixed final : FixedRotatingFrame<"titan_fixed", moons::Titan, axes::icrf, Coordinate::Z> {
} titan_fixed;
} // namespace titan

namespace rhea {
inline constexpr struct rhea_fixed final : FixedRotatingFrame<"rhea_fixed", moons::Rhea, axes::icrf, Coordinate::Z> {
} rhea_fixed;
} // namespace rhea

namespace iapetus {
inline constexpr struct iapetus_fixed final : FixedRotatingFrame<"iapetus_fixed", moons::Iapetus, axes::icrf, Coordinate::Z> {
} iapetus_fixed;
} // namespace iapetus

namespace uranus {
inline constexpr struct uranus_fixed final : FixedRotatingFrame<"uranus_fixed", planets::Uranus, axes::icrf, Coordinate::Z> {
} uranus_fixed;
} // namespace uranus

namespace titania {
inline constexpr struct titania_fixed final : FixedRotatingFrame<"titania_fixed", moons::Titania, axes::icrf, Coordinate::Z> {
} titania_fixed;
} // namespace titania

namespace oberon {
inline constexpr struct oberon_fixed final : FixedRotatingFrame<"oberon_fixed", moons::Oberon, axes::icrf, Coordinate::Z> {
} oberon_fixed;
} // namespace oberon

namespace neptune {
inline constexpr struct neptune_fixed final : FixedRotatingFrame<"neptune_fixed", planets::Neptune, axes::icrf, Coordinate::Z> {
} neptune_fixed;
} // namespace neptune

namespace triton {
inline constexpr struct triton_fixed final : FixedRotatingFrame<"triton_fixed", moons::Triton, axes::icrf, Coordinate::Z> {
} triton_fixed;
} // namespace triton

} // namespace frames
} // namespace astro
} // namespace astrea