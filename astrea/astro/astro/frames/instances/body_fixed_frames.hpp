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

#include <astro/frames/Frame.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury {
using mercury_fixed = BodyFixedFrame<CelestialBodyId::MERCURY>;
} // namespace mercury

namespace venus {
using venus_fixed = BodyFixedFrame<CelestialBodyId::VENUS>;
} // namespace venus

namespace earth {

using earth_fixed = NamedFrame<"ecef", CelestialBodyId::EARTH, FrameAxis::FIXED_ROTATING>;

} // namespace earth

namespace moon {
using moon_fixed = BodyFixedFrame<CelestialBodyId::MOON>;
} // namespace moon

namespace mars {
using mars_fixed = BodyFixedFrame<CelestialBodyId::MARS>;
} // namespace mars

namespace phobos {
using phobos_fixed = BodyFixedFrame<CelestialBodyId::PHOBOS>;
} // namespace phobos

namespace deimos {
using deimos_fixed = BodyFixedFrame<CelestialBodyId::DEIMOS>;
} // namespace deimos

namespace jupiter {
using jupiter_fixed = BodyFixedFrame<CelestialBodyId::JUPITER>;
} // namespace jupiter

namespace ganymede {
using ganymede_fixed = BodyFixedFrame<CelestialBodyId::GANYMEDE>;
} // namespace ganymede

namespace callisto {
using callisto_fixed = BodyFixedFrame<CelestialBodyId::CALLISTO>;
} // namespace callisto

namespace io {
using io_fixed = BodyFixedFrame<CelestialBodyId::IO>;
} // namespace io

namespace europa {
using europa_fixed = BodyFixedFrame<CelestialBodyId::EUROPA>;
} // namespace europa

namespace saturn {
using saturn_fixed = BodyFixedFrame<CelestialBodyId::SATURN>;
} // namespace saturn

namespace titan {
using titan_fixed = BodyFixedFrame<CelestialBodyId::TITAN>;
} // namespace titan

namespace rhea {
using rhea_fixed = BodyFixedFrame<CelestialBodyId::RHEA>;
} // namespace rhea

namespace iapetus {
using iapetus_fixed = BodyFixedFrame<CelestialBodyId::IAPETUS>;
} // namespace iapetus

namespace uranus {
using uranus_fixed = BodyFixedFrame<CelestialBodyId::URANUS>;
} // namespace uranus

namespace titania {
using titania_fixed = BodyFixedFrame<CelestialBodyId::TITANIA>;
} // namespace titania

namespace oberon {
using oberon_fixed = BodyFixedFrame<CelestialBodyId::OBERON>;
} // namespace oberon

namespace neptune {
using neptune_fixed = BodyFixedFrame<CelestialBodyId::NEPTUNE>;
} // namespace neptune

namespace triton {
using triton_fixed = BodyFixedFrame<CelestialBodyId::TRITON>;
} // namespace triton

} // namespace frames
} // namespace astro
} // namespace astrea