/**
 * @file body_centered_inertial_frames.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for all (most? common?) body-centered inertial frames.
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

namespace sun {
using icrf  = Frame<CelestialBodyId::SUN, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::SUN, FrameAxis::J2000>;
} // namespace sun

namespace mercury {
using icrf  = Frame<CelestialBodyId::MERCURY, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::MERCURY, FrameAxis::J2000>;
} // namespace mercury

namespace venus {
using icrf  = Frame<CelestialBodyId::VENUS, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::VENUS, FrameAxis::J2000>;
} // namespace venus

namespace earth {
using icrf  = NamedFrame<"gcrf", CelestialBodyId::EARTH, FrameAxis::ICRF>;     // GCRF frame, sometimes ECI
using j2000 = NamedFrame<"eme2000", CelestialBodyId::EARTH, FrameAxis::J2000>; // EME2000 frame, sometimes ECI
} // namespace earth

namespace moon {
using icrf  = Frame<CelestialBodyId::MOON, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::MOON, FrameAxis::J2000>;
} // namespace moon

namespace mars {
using icrf  = Frame<CelestialBodyId::MARS, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::MARS, FrameAxis::J2000>;
} // namespace mars

namespace phobos {
using icrf  = Frame<CelestialBodyId::PHOBOS, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::PHOBOS, FrameAxis::J2000>;
} // namespace phobos

namespace deimos {
using icrf  = Frame<CelestialBodyId::DEIMOS, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::DEIMOS, FrameAxis::J2000>;
} // namespace deimos

namespace jupiter {
using icrf  = Frame<CelestialBodyId::JUPITER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::JUPITER, FrameAxis::J2000>;
} // namespace jupiter

namespace ganymede {
using icrf  = Frame<CelestialBodyId::GANYMEDE, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::GANYMEDE, FrameAxis::J2000>;
} // namespace ganymede

namespace callisto {
using icrf  = Frame<CelestialBodyId::CALLISTO, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::CALLISTO, FrameAxis::J2000>;
} // namespace callisto

namespace io {
using icrf  = Frame<CelestialBodyId::IO, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::IO, FrameAxis::J2000>;
} // namespace io

namespace europa {
using icrf  = Frame<CelestialBodyId::EUROPA, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::EUROPA, FrameAxis::J2000>;
} // namespace europa

namespace saturn {
using icrf  = Frame<CelestialBodyId::SATURN, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::SATURN, FrameAxis::J2000>;
} // namespace saturn

namespace titan {
using icrf  = Frame<CelestialBodyId::TITAN, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::TITAN, FrameAxis::J2000>;
} // namespace titan

namespace rhea {
using icrf  = Frame<CelestialBodyId::RHEA, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::RHEA, FrameAxis::J2000>;
} // namespace rhea

namespace iapetus {
using icrf  = Frame<CelestialBodyId::IAPETUS, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::IAPETUS, FrameAxis::J2000>;
} // namespace iapetus

namespace uranus {
using icrf  = Frame<CelestialBodyId::URANUS, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::URANUS, FrameAxis::J2000>;
} // namespace uranus

namespace titania {
using icrf  = Frame<CelestialBodyId::TITANIA, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::TITANIA, FrameAxis::J2000>;
} // namespace titania

namespace oberon {
using icrf  = Frame<CelestialBodyId::OBERON, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::OBERON, FrameAxis::J2000>;
} // namespace oberon

namespace neptune {
using icrf  = Frame<CelestialBodyId::NEPTUNE, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::NEPTUNE, FrameAxis::J2000>;
} // namespace neptune

namespace triton {
using icrf  = Frame<CelestialBodyId::TRITON, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::TRITON, FrameAxis::J2000>;
} // namespace triton

namespace solar_system_barycenter {
using icrf  = Frame<CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF>; // Generally, the ICRF frame
using j2000 = Frame<CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000>;
} // namespace solar_system_barycenter

namespace mercury_barycenter {
using icrf  = Frame<CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::J2000>;
} // namespace mercury_barycenter

namespace venus_barycenter {
using icrf  = Frame<CelestialBodyId::VENUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::VENUS_BARYCENTER, FrameAxis::J2000>;
} // namespace venus_barycenter

namespace earth_barycenter {
using icrf  = Frame<CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000>;
} // namespace earth_barycenter

namespace mars_barycenter {
using icrf  = Frame<CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000>;
} // namespace mars_barycenter

namespace jupiter_barycenter {
using icrf  = Frame<CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000>;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
using icrf  = Frame<CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000>;
} // namespace saturn_barycenter

namespace uranus_barycenter {
using icrf  = Frame<CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000>;
} // namespace uranus_barycenter

namespace neptune_barycenter {
using icrf  = Frame<CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000>;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea