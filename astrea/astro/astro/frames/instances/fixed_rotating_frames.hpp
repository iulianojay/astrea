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
inline constexpr struct mercury_fixed
    : FixedRotatingFrame<"mercury_fixed", planets::Mercury, axes::icrf, Coordinate::Z, planets::Mercury::rotation_rate> {
} mercury_fixed;
} // namespace mercury

namespace venus {
inline constexpr struct venus_fixed
    : FixedRotatingFrame<"venus_fixed", planets::Venus, axes::icrf, Coordinate::Z, planets::Venus::rotation_rate> {
} venus_fixed;
} // namespace venus

namespace earth {

inline constexpr struct earth_fixed
    : FixedRotatingFrame<"ecef", planets::Earth, axes::icrf, Coordinate::Z, planets::Earth::rotation_rate> {
} earth_fixed;
inline constexpr struct ems_fixed
    : FixedRotatingFrame<"ems_fixed", barycenters::Earth, axes::icrf, Coordinate::Z, planets::Earth::rotation_rate> {
} ems_fixed;
} // namespace earth

namespace moon {
inline constexpr struct moon_fixed
    : FixedRotatingFrame<"moon_fixed", planets::Moon, axes::icrf, Coordinate::Z, planets::Moon::rotation_rate> {
} moon_fixed;
} // namespace moon

namespace mars {
inline constexpr struct mars_fixed
    : FixedRotatingFrame<"mars_fixed", planets::Mars, axes::icrf, Coordinate::Z, planets::Mars::rotation_rate> {
} mars_fixed;
} // namespace mars

namespace phobos {
inline constexpr struct phobos_fixed
    : FixedRotatingFrame<"phobos_fixed", planets::Phobos, axes::icrf, Coordinate::Z, planets::Phobos::rotation_rate> {
} phobos_fixed;
} // namespace phobos

namespace deimos {
inline constexpr struct deimos_fixed
    : FixedRotatingFrame<"deimos_fixed", planets::Deimos, axes::icrf, Coordinate::Z, planets::Deimos::rotation_rate> {
} deimos_fixed;
} // namespace deimos

namespace jupiter {
inline constexpr struct jupiter_fixed
    : FixedRotatingFrame<"jupiter_fixed", planets::Jupiter, axes::icrf, Coordinate::Z, planets::Jupiter::rotation_rate> {
} jupiter_fixed;
} // namespace jupiter

namespace ganymede {
inline constexpr struct ganymede_fixed
    : FixedRotatingFrame<"ganymede_fixed", planets::Ganymede, axes::icrf, Coordinate::Z, planets::Ganymede::rotation_rate> {
} ganymede_fixed;
} // namespace ganymede

namespace callisto {
inline constexpr struct callisto_fixed
    : FixedRotatingFrame<"callisto_fixed", planets::Callisto, axes::icrf, Coordinate::Z, planets::Callisto::rotation_rate> {
} callisto_fixed;
} // namespace callisto

namespace io {
inline constexpr struct io_fixed
    : FixedRotatingFrame<"io_fixed", planets::Io, axes::icrf, Coordinate::Z, planets::Io::rotation_rate> {
} io_fixed;
} // namespace io

namespace europa {
inline constexpr struct europa_fixed
    : FixedRotatingFrame<"europa_fixed", planets::Europa, axes::icrf, Coordinate::Z, planets::Europa::rotation_rate> {
} europa_fixed;
} // namespace europa

namespace saturn {
inline constexpr struct saturn_fixed
    : FixedRotatingFrame<"saturn_fixed", planets::Saturn, axes::icrf, Coordinate::Z, planets::Saturn::rotation_rate> {
} saturn_fixed;
} // namespace saturn

namespace titan {
inline constexpr struct titan_fixed
    : FixedRotatingFrame<"titan_fixed", planets::Titan, axes::icrf, Coordinate::Z, planets::Titan::rotation_rate> {
} titan_fixed;
} // namespace titan

namespace rhea {
inline constexpr struct rhea_fixed
    : FixedRotatingFrame<"rhea_fixed", planets::Rhea, axes::icrf, Coordinate::Z, planets::Rhea::rotation_rate> {
} rhea_fixed;
} // namespace rhea

namespace iapetus {
inline constexpr struct iapetus_fixed
    : FixedRotatingFrame<"iapetus_fixed", planets::Iapetus, axes::icrf, Coordinate::Z, planets::Iapetus::rotation_rate> {
} iapetus_fixed;
} // namespace iapetus

namespace uranus {
inline constexpr struct uranus_fixed
    : FixedRotatingFrame<"uranus_fixed", planets::Uranus, axes::icrf, Coordinate::Z, planets::Uranus::rotation_rate> {
} uranus_fixed;
} // namespace uranus

namespace titania {
inline constexpr struct titania_fixed
    : FixedRotatingFrame<"titania_fixed", planets::Titania, axes::icrf, Coordinate::Z, planets::Titania::rotation_rate> {
} titania_fixed;
} // namespace titania

namespace oberon {
inline constexpr struct oberon_fixed
    : FixedRotatingFrame<"oberon_fixed", planets::Oberon, axes::icrf, Coordinate::Z, planets::Oberon::rotation_rate> {
} oberon_fixed;
} // namespace oberon

namespace neptune {
inline constexpr struct neptune_fixed
    : FixedRotatingFrame<"neptune_fixed", planets::Neptune, axes::icrf, Coordinate::Z, planets::Neptune::rotation_rate> {
} neptune_fixed;
} // namespace neptune

namespace triton {
inline constexpr struct triton_fixed
    : FixedRotatingFrame<"triton_fixed", planets::Triton, axes::icrf, Coordinate::Z, planets::Triton::rotation_rate> {
} triton_fixed;
} // namespace triton

} // namespace frames
} // namespace astro
} // namespace astrea