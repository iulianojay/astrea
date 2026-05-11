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

#include <astro/frames/FixedRotatingFrame.hpp>
#include <astro/frames/instances/body_centered_inertial_frames.hpp>
#include <astro/systems/planetary_bodies/planetary_bodies.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury {
inline constexpr struct mercury_fixed
    : FixedRotatingFrame<"mercury_fixed", origins::Mercury, axes::icrf, Coordinate::Z, planetary_bodies::Mercury::rotation_rate> {
} mercury_fixed;
} // namespace mercury

namespace venus {
inline constexpr struct venus_fixed
    : FixedRotatingFrame<"venus_fixed", origins::Venus, axes::icrf, Coordinate::Z, planetary_bodies::Venus::rotation_rate> {
} venus_fixed;
} // namespace venus

namespace earth {

using ems = Frame<"earth-moon synodic", CelestialBodyId::EARTH_BARYCENTER, FrameAxis::FIXED_ROTATING, earth::icrf>; // Earth-Moon Synodic frame, with x-axis pointing towards the Moon

inline constexpr struct earth_fixed
    : FixedRotatingFrame<"ecef", origins::Earth, axes::icrf, Coordinate::Z, planetary_bodies::Earth::rotation_rate> {
} earth_fixed;
} // namespace earth

namespace moon {
inline constexpr struct moon_fixed
    : FixedRotatingFrame<"moon_fixed", origins::Moon, axes::icrf, Coordinate::Z, planetary_bodies::Moon::rotation_rate> {
} moon_fixed;
} // namespace moon

namespace mars {
inline constexpr struct mars_fixed
    : FixedRotatingFrame<"mars_fixed", origins::Mars, axes::icrf, Coordinate::Z, planetary_bodies::Mars::rotation_rate> {
} mars_fixed;
} // namespace mars

namespace phobos {
inline constexpr struct phobos_fixed
    : FixedRotatingFrame<"phobos_fixed", origins::Phobos, axes::icrf, Coordinate::Z, planetary_bodies::Phobos::rotation_rate> {
} phobos_fixed;
} // namespace phobos

namespace deimos {
inline constexpr struct deimos_fixed
    : FixedRotatingFrame<"deimos_fixed", origins::Deimos, axes::icrf, Coordinate::Z, planetary_bodies::Deimos::rotation_rate> {
} deimos_fixed;
} // namespace deimos

namespace jupiter {
inline constexpr struct jupiter_fixed
    : FixedRotatingFrame<"jupiter_fixed", origins::Jupiter, axes::icrf, Coordinate::Z, planetary_bodies::Jupiter::rotation_rate> {
} jupiter_fixed;
} // namespace jupiter

namespace ganymede {
inline constexpr struct ganymede_fixed
    : FixedRotatingFrame<"ganymede_fixed", origins::Ganymede, axes::icrf, Coordinate::Z, planetary_bodies::Ganymede::rotation_rate> {
} ganymede_fixed;
} // namespace ganymede

namespace callisto {
inline constexpr struct callisto_fixed
    : FixedRotatingFrame<"callisto_fixed", origins::Callisto, axes::icrf, Coordinate::Z, planetary_bodies::Callisto::rotation_rate> {
} callisto_fixed;
} // namespace callisto

namespace io {
inline constexpr struct io_fixed
    : FixedRotatingFrame<"io_fixed", origins::Io, axes::icrf, Coordinate::Z, planetary_bodies::Io::rotation_rate> {
} io_fixed;
} // namespace io

namespace europa {
inline constexpr struct europa_fixed
    : FixedRotatingFrame<"europa_fixed", origins::Europa, axes::icrf, Coordinate::Z, planetary_bodies::Europa::rotation_rate> {
} europa_fixed;
} // namespace europa

namespace saturn {
inline constexpr struct saturn_fixed
    : FixedRotatingFrame<"saturn_fixed", origins::Saturn, axes::icrf, Coordinate::Z, planetary_bodies::Saturn::rotation_rate> {
} saturn_fixed;
} // namespace saturn

namespace titan {
inline constexpr struct titan_fixed
    : FixedRotatingFrame<"titan_fixed", origins::Titan, axes::icrf, Coordinate::Z, planetary_bodies::Titan::rotation_rate> {
} titan_fixed;
} // namespace titan

namespace rhea {
inline constexpr struct rhea_fixed
    : FixedRotatingFrame<"rhea_fixed", origins::Rhea, axes::icrf, Coordinate::Z, planetary_bodies::Rhea::rotation_rate> {
} rhea_fixed;
} // namespace rhea

namespace iapetus {
inline constexpr struct iapetus_fixed
    : FixedRotatingFrame<"iapetus_fixed", origins::Iapetus, axes::icrf, Coordinate::Z, planetary_bodies::Iapetus::rotation_rate> {
} iapetus_fixed;
} // namespace iapetus

namespace uranus {
inline constexpr struct uranus_fixed
    : FixedRotatingFrame<"uranus_fixed", origins::Uranus, axes::icrf, Coordinate::Z, planetary_bodies::Uranus::rotation_rate> {
} uranus_fixed;
} // namespace uranus

namespace titania {
inline constexpr struct titania_fixed
    : FixedRotatingFrame<"titania_fixed", origins::Titania, axes::icrf, Coordinate::Z, planetary_bodies::Titania::rotation_rate> {
} titania_fixed;
} // namespace titania

namespace oberon {
inline constexpr struct oberon_fixed
    : FixedRotatingFrame<"oberon_fixed", origins::Oberon, axes::icrf, Coordinate::Z, planetary_bodies::Oberon::rotation_rate> {
} oberon_fixed;
} // namespace oberon

namespace neptune {
inline constexpr struct neptune_fixed
    : FixedRotatingFrame<"neptune_fixed", origins::Neptune, axes::icrf, Coordinate::Z, planetary_bodies::Neptune::rotation_rate> {
} neptune_fixed;
} // namespace neptune

namespace triton {
inline constexpr struct triton_fixed
    : FixedRotatingFrame<"triton_fixed", origins::Triton, axes::icrf, Coordinate::Z, planetary_bodies::Triton::rotation_rate> {
} triton_fixed;
} // namespace triton

} // namespace frames
} // namespace astro
} // namespace astrea