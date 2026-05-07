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
using icrf  = Frame<"sun_icrf", CelestialBodyId::SUN, FrameAxis::ICRF>;
using j2000 = Frame<"sun_j2000", CelestialBodyId::SUN, FrameAxis::J2000>;
} // namespace sun

namespace mercury {
using icrf  = Frame<"mercury_icrf", CelestialBodyId::MERCURY, FrameAxis::ICRF>;
using j2000 = Frame<"mercury_j2000", CelestialBodyId::MERCURY, FrameAxis::J2000>;
} // namespace mercury

namespace venus {
using icrf  = Frame<"venus_icrf", CelestialBodyId::VENUS, FrameAxis::ICRF>;
using j2000 = Frame<"venus_j2000", CelestialBodyId::VENUS, FrameAxis::J2000>;
} // namespace venus

namespace earth {
using icrf  = Frame<"gcrf", CelestialBodyId::EARTH, FrameAxis::ICRF>;     // sometimes ECI
using j2000 = Frame<"eme2000", CelestialBodyId::EARTH, FrameAxis::J2000>; // sometimes ECI
} // namespace earth

namespace moon {
using icrf  = Frame<"moon_icrf", CelestialBodyId::MOON, FrameAxis::ICRF>;
using j2000 = Frame<"moon_j2000", CelestialBodyId::MOON, FrameAxis::J2000>;
} // namespace moon

namespace mars {
using icrf  = Frame<"mars_icrf", CelestialBodyId::MARS, FrameAxis::ICRF>;
using j2000 = Frame<"mars_j2000", CelestialBodyId::MARS, FrameAxis::J2000>;
} // namespace mars

namespace phobos {
using icrf  = Frame<"phobos_icrf", CelestialBodyId::PHOBOS, FrameAxis::ICRF>;
using j2000 = Frame<"phobos_j2000", CelestialBodyId::PHOBOS, FrameAxis::J2000>;
} // namespace phobos

namespace deimos {
using icrf  = Frame<"deimos_icrf", CelestialBodyId::DEIMOS, FrameAxis::ICRF>;
using j2000 = Frame<"deimos_j2000", CelestialBodyId::DEIMOS, FrameAxis::J2000>;
} // namespace deimos

namespace jupiter {
using icrf  = Frame<"jupiter_icrf", CelestialBodyId::JUPITER, FrameAxis::ICRF>;
using j2000 = Frame<"jupiter_j2000", CelestialBodyId::JUPITER, FrameAxis::J2000>;
} // namespace jupiter

namespace ganymede {
using icrf  = Frame<"ganymede_icrf", CelestialBodyId::GANYMEDE, FrameAxis::ICRF>;
using j2000 = Frame<"ganymede_j2000", CelestialBodyId::GANYMEDE, FrameAxis::J2000>;
} // namespace ganymede

namespace callisto {
using icrf  = Frame<"callisto_icrf", CelestialBodyId::CALLISTO, FrameAxis::ICRF>;
using j2000 = Frame<"callisto_j2000", CelestialBodyId::CALLISTO, FrameAxis::J2000>;
} // namespace callisto

namespace io {
using icrf  = Frame<"io_icrf", CelestialBodyId::IO, FrameAxis::ICRF>;
using j2000 = Frame<"io_j2000", CelestialBodyId::IO, FrameAxis::J2000>;
} // namespace io

namespace europa {
using icrf  = Frame<"europa_icrf", CelestialBodyId::EUROPA, FrameAxis::ICRF>;
using j2000 = Frame<"europa_j2000", CelestialBodyId::EUROPA, FrameAxis::J2000>;
} // namespace europa

namespace saturn {
using icrf  = Frame<"saturn_icrf", CelestialBodyId::SATURN, FrameAxis::ICRF>;
using j2000 = Frame<"saturn_j2000", CelestialBodyId::SATURN, FrameAxis::J2000>;
} // namespace saturn

namespace titan {
using icrf  = Frame<"titan_icrf", CelestialBodyId::TITAN, FrameAxis::ICRF>;
using j2000 = Frame<"titan_j2000", CelestialBodyId::TITAN, FrameAxis::J2000>;
} // namespace titan

namespace rhea {
using icrf  = Frame<"rhea_icrf", CelestialBodyId::RHEA, FrameAxis::ICRF>;
using j2000 = Frame<"rhea_j2000", CelestialBodyId::RHEA, FrameAxis::J2000>;
} // namespace rhea

namespace iapetus {
using icrf  = Frame<"iapetus_icrf", CelestialBodyId::IAPETUS, FrameAxis::ICRF>;
using j2000 = Frame<"iapetus_j2000", CelestialBodyId::IAPETUS, FrameAxis::J2000>;
} // namespace iapetus

namespace uranus {
using icrf  = Frame<"uranus_icrf", CelestialBodyId::URANUS, FrameAxis::ICRF>;
using j2000 = Frame<"uranus_j2000", CelestialBodyId::URANUS, FrameAxis::J2000>;
} // namespace uranus

namespace titania {
using icrf  = Frame<"titania_icrf", CelestialBodyId::TITANIA, FrameAxis::ICRF>;
using j2000 = Frame<"titania_j2000", CelestialBodyId::TITANIA, FrameAxis::J2000>;
} // namespace titania

namespace oberon {
using icrf  = Frame<"oberon_icrf", CelestialBodyId::OBERON, FrameAxis::ICRF>;
using j2000 = Frame<"oberon_j2000", CelestialBodyId::OBERON, FrameAxis::J2000>;
} // namespace oberon

namespace neptune {
using icrf  = Frame<"neptune_icrf", CelestialBodyId::NEPTUNE, FrameAxis::ICRF>;
using j2000 = Frame<"neptune_j2000", CelestialBodyId::NEPTUNE, FrameAxis::J2000>;
} // namespace neptune

namespace triton {
using icrf  = Frame<"triton_icrf", CelestialBodyId::TRITON, FrameAxis::ICRF>;
using j2000 = Frame<"triton_j2000", CelestialBodyId::TRITON, FrameAxis::J2000>;
} // namespace triton

namespace solar_system_barycenter {
using icrf = Frame<"ssbc_icrf", CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF>; // Generally, the ICRF frame
using j2000 = Frame<"ssbc_j2000", CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000>;
} // namespace solar_system_barycenter

namespace mercury_barycenter {
using icrf  = Frame<"mercury_bc_icrf", CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"mercury_bc_j2000", CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::J2000>;
} // namespace mercury_barycenter

namespace venus_barycenter {
using icrf  = Frame<"vbc_icrf", CelestialBodyId::VENUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"vbc_j2000", CelestialBodyId::VENUS_BARYCENTER, FrameAxis::J2000>;
} // namespace venus_barycenter

namespace earth_barycenter {
using icrf  = Frame<"embc_icrf", CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"embc_j2000", CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000>;
} // namespace earth_barycenter

namespace mars_barycenter {
using icrf  = Frame<"mars_bc_icrf", CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"mars_bc_j2000", CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000>;
} // namespace mars_barycenter

namespace jupiter_barycenter {
using icrf  = Frame<"jbc_icrf", CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"jbc_j2000", CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000>;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
using icrf  = Frame<"saturn_bc_icrf", CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"saturn_bc_j2000", CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000>;
} // namespace saturn_barycenter

namespace uranus_barycenter {
using icrf  = Frame<"ubc_icrf", CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"ubc_j2000", CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000>;
} // namespace uranus_barycenter

namespace neptune_barycenter {
using icrf  = Frame<"nbc_icrf", CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF>;
using j2000 = Frame<"nbc_j2000", CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000>;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea