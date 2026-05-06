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
using icrf  = NamedFrame<"sun_icrf", CelestialBodyId::SUN, FrameAxis::ICRF>;
using j2000 = NamedFrame<"sun_j2000", CelestialBodyId::SUN, FrameAxis::J2000>;
} // namespace sun

namespace mercury {
using icrf  = NamedFrame<"mercury_icrf", CelestialBodyId::MERCURY, FrameAxis::ICRF>;
using j2000 = NamedFrame<"mercury_j2000", CelestialBodyId::MERCURY, FrameAxis::J2000>;
} // namespace mercury

namespace venus {
using icrf  = NamedFrame<"venus_icrf", CelestialBodyId::VENUS, FrameAxis::ICRF>;
using j2000 = NamedFrame<"venus_j2000", CelestialBodyId::VENUS, FrameAxis::J2000>;
} // namespace venus

namespace earth {
using icrf  = NamedFrame<"gcrf", CelestialBodyId::EARTH, FrameAxis::ICRF>;     // sometimes ECI
using j2000 = NamedFrame<"eme2000", CelestialBodyId::EARTH, FrameAxis::J2000>; // sometimes ECI
} // namespace earth

namespace moon {
using icrf  = NamedFrame<"moon_icrf", CelestialBodyId::MOON, FrameAxis::ICRF>;
using j2000 = NamedFrame<"moon_j2000", CelestialBodyId::MOON, FrameAxis::J2000>;
} // namespace moon

namespace mars {
using icrf  = NamedFrame<"mars_icrf", CelestialBodyId::MARS, FrameAxis::ICRF>;
using j2000 = NamedFrame<"mars_j2000", CelestialBodyId::MARS, FrameAxis::J2000>;
} // namespace mars

namespace phobos {
using icrf  = NamedFrame<"phobos_icrf", CelestialBodyId::PHOBOS, FrameAxis::ICRF>;
using j2000 = NamedFrame<"phobos_j2000", CelestialBodyId::PHOBOS, FrameAxis::J2000>;
} // namespace phobos

namespace deimos {
using icrf  = NamedFrame<"deimos_icrf", CelestialBodyId::DEIMOS, FrameAxis::ICRF>;
using j2000 = NamedFrame<"deimos_j2000", CelestialBodyId::DEIMOS, FrameAxis::J2000>;
} // namespace deimos

namespace jupiter {
using icrf  = NamedFrame<"jupiter_icrf", CelestialBodyId::JUPITER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"jupiter_j2000", CelestialBodyId::JUPITER, FrameAxis::J2000>;
} // namespace jupiter

namespace ganymede {
using icrf  = NamedFrame<"ganymede_icrf", CelestialBodyId::GANYMEDE, FrameAxis::ICRF>;
using j2000 = NamedFrame<"ganymede_j2000", CelestialBodyId::GANYMEDE, FrameAxis::J2000>;
} // namespace ganymede

namespace callisto {
using icrf  = NamedFrame<"callisto_icrf", CelestialBodyId::CALLISTO, FrameAxis::ICRF>;
using j2000 = NamedFrame<"callisto_j2000", CelestialBodyId::CALLISTO, FrameAxis::J2000>;
} // namespace callisto

namespace io {
using icrf  = NamedFrame<"io_icrf", CelestialBodyId::IO, FrameAxis::ICRF>;
using j2000 = NamedFrame<"io_j2000", CelestialBodyId::IO, FrameAxis::J2000>;
} // namespace io

namespace europa {
using icrf  = NamedFrame<"europa_icrf", CelestialBodyId::EUROPA, FrameAxis::ICRF>;
using j2000 = NamedFrame<"europa_j2000", CelestialBodyId::EUROPA, FrameAxis::J2000>;
} // namespace europa

namespace saturn {
using icrf  = NamedFrame<"saturn_icrf", CelestialBodyId::SATURN, FrameAxis::ICRF>;
using j2000 = NamedFrame<"saturn_j2000", CelestialBodyId::SATURN, FrameAxis::J2000>;
} // namespace saturn

namespace titan {
using icrf  = NamedFrame<"titan_icrf", CelestialBodyId::TITAN, FrameAxis::ICRF>;
using j2000 = NamedFrame<"titan_j2000", CelestialBodyId::TITAN, FrameAxis::J2000>;
} // namespace titan

namespace rhea {
using icrf  = NamedFrame<"rhea_icrf", CelestialBodyId::RHEA, FrameAxis::ICRF>;
using j2000 = NamedFrame<"rhea_j2000", CelestialBodyId::RHEA, FrameAxis::J2000>;
} // namespace rhea

namespace iapetus {
using icrf  = NamedFrame<"iapetus_icrf", CelestialBodyId::IAPETUS, FrameAxis::ICRF>;
using j2000 = NamedFrame<"iapetus_j2000", CelestialBodyId::IAPETUS, FrameAxis::J2000>;
} // namespace iapetus

namespace uranus {
using icrf  = NamedFrame<"uranus_icrf", CelestialBodyId::URANUS, FrameAxis::ICRF>;
using j2000 = NamedFrame<"uranus_j2000", CelestialBodyId::URANUS, FrameAxis::J2000>;
} // namespace uranus

namespace titania {
using icrf  = NamedFrame<"titania_icrf", CelestialBodyId::TITANIA, FrameAxis::ICRF>;
using j2000 = NamedFrame<"titania_j2000", CelestialBodyId::TITANIA, FrameAxis::J2000>;
} // namespace titania

namespace oberon {
using icrf  = NamedFrame<"oberon_icrf", CelestialBodyId::OBERON, FrameAxis::ICRF>;
using j2000 = NamedFrame<"oberon_j2000", CelestialBodyId::OBERON, FrameAxis::J2000>;
} // namespace oberon

namespace neptune {
using icrf  = NamedFrame<"neptune_icrf", CelestialBodyId::NEPTUNE, FrameAxis::ICRF>;
using j2000 = NamedFrame<"neptune_j2000", CelestialBodyId::NEPTUNE, FrameAxis::J2000>;
} // namespace neptune

namespace triton {
using icrf  = NamedFrame<"triton_icrf", CelestialBodyId::TRITON, FrameAxis::ICRF>;
using j2000 = NamedFrame<"triton_j2000", CelestialBodyId::TRITON, FrameAxis::J2000>;
} // namespace triton

namespace solar_system_barycenter {
using icrf = NamedFrame<"ssbc_icrf", CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF>; // Generally, the ICRF frame
using j2000 = NamedFrame<"ssbc_j2000", CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000>;
} // namespace solar_system_barycenter

namespace mercury_barycenter {
using icrf  = NamedFrame<"mercury_bc_icrf", CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"mercury_bc_j2000", CelestialBodyId::MERCURY_BARYCENTER, FrameAxis::J2000>;
} // namespace mercury_barycenter

namespace venus_barycenter {
using icrf  = NamedFrame<"vbc_icrf", CelestialBodyId::VENUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"vbc_j2000", CelestialBodyId::VENUS_BARYCENTER, FrameAxis::J2000>;
} // namespace venus_barycenter

namespace earth_barycenter {
using icrf  = NamedFrame<"embc_icrf", CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"embc_j2000", CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000>;
} // namespace earth_barycenter

namespace mars_barycenter {
using icrf  = NamedFrame<"mars_bc_icrf", CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"mars_bc_j2000", CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000>;
} // namespace mars_barycenter

namespace jupiter_barycenter {
using icrf  = NamedFrame<"jbc_icrf", CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"jbc_j2000", CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000>;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
using icrf  = NamedFrame<"saturn_bc_icrf", CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"saturn_bc_j2000", CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000>;
} // namespace saturn_barycenter

namespace uranus_barycenter {
using icrf  = NamedFrame<"ubc_icrf", CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"ubc_j2000", CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000>;
} // namespace uranus_barycenter

namespace neptune_barycenter {
using icrf  = NamedFrame<"nbc_icrf", CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF>;
using j2000 = NamedFrame<"nbc_j2000", CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000>;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea