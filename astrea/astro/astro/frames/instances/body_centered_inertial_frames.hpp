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
inline constexpr struct icrf : Frame<"sun_icrf", origins::Sun, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"sun_j2000", origins::Sun, axes::j2000> {
} j2000;
} // namespace sun

namespace mercury {
inline constexpr struct icrf : Frame<"mercury_icrf", origins::Mercury, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mercury_j2000", origins::Mercury, axes::j2000> {
} j2000;
} // namespace mercury

namespace venus {
inline constexpr struct icrf : Frame<"venus_icrf", origins::Venus, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"venus_j2000", origins::Venus, axes::j2000> {
} j2000;
} // namespace venus

namespace earth {
inline constexpr struct icrf : Frame<"gcrf", origins::Earth, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"eme2000", origins::Earth, axes::j2000> {
} j2000;
} // namespace earth

namespace moon {
inline constexpr struct icrf : Frame<"moon_icrf", origins::Moon, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"moon_j2000", origins::Moon, axes::j2000> {
} j2000;
} // namespace moon

namespace mars {
inline constexpr struct icrf : Frame<"mars_icrf", origins::Mars, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mars_j2000", origins::Mars, axes::j2000> {
} j2000;
} // namespace mars

namespace phobos {
inline constexpr struct icrf : Frame<"phobos_icrf", origins::Phobos, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"phobos_j2000", origins::Phobos, axes::j2000> {
} j2000;
} // namespace phobos

namespace deimos {
inline constexpr struct icrf : Frame<"deimos_icrf", origins::Deimos, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"deimos_j2000", origins::Deimos, axes::j2000> {
} j2000;
} // namespace deimos

namespace jupiter {
inline constexpr struct icrf : Frame<"jupiter_icrf", origins::Jupiter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"jupiter_j2000", origins::Jupiter, axes::j2000> {
} j2000;
} // namespace jupiter

namespace ganymede {
inline constexpr struct icrf : Frame<"ganymede_icrf", origins::Ganymede, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"ganymede_j2000", origins::Ganymede, axes::j2000> {
} j2000;
} // namespace ganymede

namespace callisto {
inline constexpr struct icrf : Frame<"callisto_icrf", origins::Callisto, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"callisto_j2000", origins::Callisto, axes::j2000> {
} j2000;
} // namespace callisto

namespace io {
inline constexpr struct icrf : Frame<"io_icrf", origins::Io, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"io_j2000", origins::Io, axes::j2000> {
} j2000;
} // namespace io

namespace europa {
inline constexpr struct icrf : Frame<"europa_icrf", origins::Europa, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"europa_j2000", origins::Europa, axes::j2000> {
} j2000;
} // namespace europa

namespace saturn {
inline constexpr struct icrf : Frame<"saturn_icrf", origins::Saturn, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"saturn_j2000", origins::Saturn, axes::j2000> {
} j2000;
} // namespace saturn

namespace titan {
inline constexpr struct icrf : Frame<"titan_icrf", origins::Titan, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"titan_j2000", origins::Titan, axes::j2000> {
} j2000;
} // namespace titan

namespace rhea {
inline constexpr struct icrf : Frame<"rhea_icrf", origins::Rhea, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"rhea_j2000", origins::Rhea, axes::j2000> {
} j2000;
} // namespace rhea

namespace iapetus {
inline constexpr struct icrf : Frame<"iapetus_icrf", origins::Iapetus, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"iapetus_j2000", origins::Iapetus, axes::j2000> {
} j2000;
} // namespace iapetus

namespace uranus {
inline constexpr struct icrf : Frame<"uranus_icrf", origins::Uranus, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"uranus_j2000", origins::Uranus, axes::j2000> {
} j2000;
} // namespace uranus

namespace titania {
inline constexpr struct icrf : Frame<"titania_icrf", origins::Titania, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"titania_j2000", origins::Titania, axes::j2000> {
} j2000;
} // namespace titania

namespace oberon {
inline constexpr struct icrf : Frame<"oberon_icrf", origins::Oberon, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"oberon_j2000", origins::Oberon, axes::j2000> {
} j2000;
} // namespace oberon

namespace neptune {
inline constexpr struct icrf : Frame<"neptune_icrf", origins::Neptune, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"neptune_j2000", origins::Neptune, axes::j2000> {
} j2000;
} // namespace neptune

namespace triton {
inline constexpr struct icrf : Frame<"triton_icrf", origins::Triton, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"triton_j2000", origins::Triton, axes::j2000> {
} j2000;
} // namespace triton

namespace solar_system_barycenter {
inline constexpr struct icrf : Frame<"ssbc_icrf", origins::SolarSystemBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"ssbc_j2000", origins::SolarSystemBarycenter, axes::j2000> {
} j2000; // Generally, the icrf frame
} // namespace solar_system_barycenter

namespace mercury_barycenter {
inline constexpr struct icrf : Frame<"mercury_bc_icrf", origins::MercuryBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mercury_bc_j2000", origins::MercuryBarycenter, axes::j2000> {
} j2000;
} // namespace mercury_barycenter

namespace venus_barycenter {
inline constexpr struct icrf : Frame<"vbc_icrf", origins::VenusBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"vbc_j2000", origins::VenusBarycenter, axes::j2000> {
} j2000;
} // namespace venus_barycenter

namespace earth_barycenter {
inline constexpr struct icrf : Frame<"embc_icrf", origins::EarthBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"embc_j2000", origins::EarthBarycenter, axes::j2000> {
} j2000;
} // namespace earth_barycenter

namespace mars_barycenter {
inline constexpr struct icrf : Frame<"mars_bc_icrf", origins::MarsBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mars_bc_j2000", origins::MarsBarycenter, axes::j2000> {
} j2000;
} // namespace mars_barycenter

namespace jupiter_barycenter {
inline constexpr struct icrf : Frame<"jbc_icrf", origins::JupiterBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"jbc_j2000", origins::JupiterBarycenter, axes::j2000> {
} j2000;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
inline constexpr struct icrf : Frame<"saturn_bc_icrf", origins::SaturnBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"saturn_bc_j2000", origins::SaturnBarycenter, axes::j2000> {
} j2000;
} // namespace saturn_barycenter

namespace uranus_barycenter {
inline constexpr struct icrf : Frame<"ubc_icrf", origins::UranusBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"ubc_j2000", origins::UranusBarycenter, axes::j2000> {
} j2000;
} // namespace uranus_barycenter

namespace neptune_barycenter {
inline constexpr struct icrf : Frame<"nbc_icrf", origins::NeptuneBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"nbc_j2000", origins::NeptuneBarycenter, axes::j2000> {
} j2000;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea