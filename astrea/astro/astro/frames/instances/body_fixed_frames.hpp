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
#include <astro/frames/instances/body_centered_inertial_frames.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury {
using mercury_fixed = NamedFrame<"mercury_fixed", CelestialBodyId::MERCURY, FrameAxis::FIXED_ROTATING, mercury::icrf>;
} // namespace mercury

namespace venus {
using venus_fixed = NamedFrame<"venus_fixed", CelestialBodyId::VENUS, FrameAxis::FIXED_ROTATING, venus::icrf>;
} // namespace venus

namespace earth {

using earth_fixed = NamedFrame<"ecef", CelestialBodyId::EARTH, FrameAxis::FIXED_ROTATING, earth::icrf>;

} // namespace earth

namespace moon {
using moon_fixed = NamedFrame<"moon_fixed", CelestialBodyId::MOON, FrameAxis::FIXED_ROTATING, moon::icrf>;
} // namespace moon

namespace mars {
using mars_fixed = NamedFrame<"mars_fixed", CelestialBodyId::MARS, FrameAxis::FIXED_ROTATING, mars::icrf>;
} // namespace mars

namespace phobos {
using phobos_fixed = NamedFrame<"phobos_fixed", CelestialBodyId::PHOBOS, FrameAxis::FIXED_ROTATING, phobos::icrf>;
} // namespace phobos

namespace deimos {
using deimos_fixed = NamedFrame<"deimos_fixed", CelestialBodyId::DEIMOS, FrameAxis::FIXED_ROTATING, deimos::icrf>;
} // namespace deimos

namespace jupiter {
using jupiter_fixed = NamedFrame<"jupiter_fixed", CelestialBodyId::JUPITER, FrameAxis::FIXED_ROTATING, jupiter::icrf>;
} // namespace jupiter

namespace ganymede {
using ganymede_fixed = NamedFrame<"ganymede_fixed", CelestialBodyId::GANYMEDE, FrameAxis::FIXED_ROTATING, ganymede::icrf>;
} // namespace ganymede

namespace callisto {
using callisto_fixed = NamedFrame<"callisto_fixed", CelestialBodyId::CALLISTO, FrameAxis::FIXED_ROTATING, callisto::icrf>;
} // namespace callisto

namespace io {
using io_fixed = NamedFrame<"io_fixed", CelestialBodyId::IO, FrameAxis::FIXED_ROTATING, io::icrf>;
} // namespace io

namespace europa {
using europa_fixed = NamedFrame<"europa_fixed", CelestialBodyId::EUROPA, FrameAxis::FIXED_ROTATING, europa::icrf>;
} // namespace europa

namespace saturn {
using saturn_fixed = NamedFrame<"saturn_fixed", CelestialBodyId::SATURN, FrameAxis::FIXED_ROTATING, saturn::icrf>;
} // namespace saturn

namespace titan {
using titan_fixed = NamedFrame<"titan_fixed", CelestialBodyId::TITAN, FrameAxis::FIXED_ROTATING, titan::icrf>;
} // namespace titan

namespace rhea {
using rhea_fixed = NamedFrame<"rhea_fixed", CelestialBodyId::RHEA, FrameAxis::FIXED_ROTATING, rhea::icrf>;
} // namespace rhea

namespace iapetus {
using iapetus_fixed = NamedFrame<"iapetus_fixed", CelestialBodyId::IAPETUS, FrameAxis::FIXED_ROTATING, iapetus::icrf>;
} // namespace iapetus

namespace uranus {
using uranus_fixed = NamedFrame<"uranus_fixed", CelestialBodyId::URANUS, FrameAxis::FIXED_ROTATING, uranus::icrf>;
} // namespace uranus

namespace titania {
using titania_fixed = NamedFrame<"titania_fixed", CelestialBodyId::TITANIA, FrameAxis::FIXED_ROTATING, titania::icrf>;
} // namespace titania

namespace oberon {
using oberon_fixed = NamedFrame<"oberon_fixed", CelestialBodyId::OBERON, FrameAxis::FIXED_ROTATING, oberon::icrf>;
} // namespace oberon

namespace neptune {
using neptune_fixed = NamedFrame<"neptune_fixed", CelestialBodyId::NEPTUNE, FrameAxis::FIXED_ROTATING, neptune::icrf>;
} // namespace neptune

namespace triton {
using triton_fixed = NamedFrame<"triton_fixed", CelestialBodyId::TRITON, FrameAxis::FIXED_ROTATING, triton::icrf>;
} // namespace triton

} // namespace frames
} // namespace astro
} // namespace astrea