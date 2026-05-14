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
#include <astro/systems/planets.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace sun {
inline constexpr struct icrf : Frame<"sun_icrf", planets::Sun, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"sun_j2000", planets::Sun, axes::j2000> {
} j2000;
} // namespace sun

namespace mercury {
inline constexpr struct icrf : Frame<"mercury_icrf", planets::Mercury, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mercury_j2000", planets::Mercury, axes::j2000> {
} j2000;
} // namespace mercury

namespace venus {
inline constexpr struct icrf : Frame<"venus_icrf", planets::Venus, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"venus_j2000", planets::Venus, axes::j2000> {
} j2000;
} // namespace venus

namespace earth {
inline constexpr struct icrf : Frame<"gcrf", planets::Earth, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"eme2000", planets::Earth, axes::j2000> {
} j2000;
} // namespace earth

namespace moon {
inline constexpr struct icrf : Frame<"moon_icrf", planets::Moon, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"moon_j2000", planets::Moon, axes::j2000> {
} j2000;
} // namespace moon

namespace mars {
inline constexpr struct icrf : Frame<"mars_icrf", planets::Mars, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mars_j2000", planets::Mars, axes::j2000> {
} j2000;
} // namespace mars

namespace phobos {
inline constexpr struct icrf : Frame<"phobos_icrf", planets::Phobos, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"phobos_j2000", planets::Phobos, axes::j2000> {
} j2000;
} // namespace phobos

namespace deimos {
inline constexpr struct icrf : Frame<"deimos_icrf", planets::Deimos, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"deimos_j2000", planets::Deimos, axes::j2000> {
} j2000;
} // namespace deimos

namespace jupiter {
inline constexpr struct icrf : Frame<"jupiter_icrf", planets::Jupiter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"jupiter_j2000", planets::Jupiter, axes::j2000> {
} j2000;
} // namespace jupiter

namespace ganymede {
inline constexpr struct icrf : Frame<"ganymede_icrf", planets::Ganymede, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"ganymede_j2000", planets::Ganymede, axes::j2000> {
} j2000;
} // namespace ganymede

namespace callisto {
inline constexpr struct icrf : Frame<"callisto_icrf", planets::Callisto, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"callisto_j2000", planets::Callisto, axes::j2000> {
} j2000;
} // namespace callisto

namespace io {
inline constexpr struct icrf : Frame<"io_icrf", planets::Io, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"io_j2000", planets::Io, axes::j2000> {
} j2000;
} // namespace io

namespace europa {
inline constexpr struct icrf : Frame<"europa_icrf", planets::Europa, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"europa_j2000", planets::Europa, axes::j2000> {
} j2000;
} // namespace europa

namespace saturn {
inline constexpr struct icrf : Frame<"saturn_icrf", planets::Saturn, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"saturn_j2000", planets::Saturn, axes::j2000> {
} j2000;
} // namespace saturn

namespace titan {
inline constexpr struct icrf : Frame<"titan_icrf", planets::Titan, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"titan_j2000", planets::Titan, axes::j2000> {
} j2000;
} // namespace titan

namespace rhea {
inline constexpr struct icrf : Frame<"rhea_icrf", planets::Rhea, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"rhea_j2000", planets::Rhea, axes::j2000> {
} j2000;
} // namespace rhea

namespace iapetus {
inline constexpr struct icrf : Frame<"iapetus_icrf", planets::Iapetus, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"iapetus_j2000", planets::Iapetus, axes::j2000> {
} j2000;
} // namespace iapetus

namespace uranus {
inline constexpr struct icrf : Frame<"uranus_icrf", planets::Uranus, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"uranus_j2000", planets::Uranus, axes::j2000> {
} j2000;
} // namespace uranus

namespace titania {
inline constexpr struct icrf : Frame<"titania_icrf", planets::Titania, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"titania_j2000", planets::Titania, axes::j2000> {
} j2000;
} // namespace titania

namespace oberon {
inline constexpr struct icrf : Frame<"oberon_icrf", planets::Oberon, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"oberon_j2000", planets::Oberon, axes::j2000> {
} j2000;
} // namespace oberon

namespace neptune {
inline constexpr struct icrf : Frame<"neptune_icrf", planets::Neptune, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"neptune_j2000", planets::Neptune, axes::j2000> {
} j2000;
} // namespace neptune

namespace triton {
inline constexpr struct icrf : Frame<"triton_icrf", planets::Triton, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"triton_j2000", planets::Triton, axes::j2000> {
} j2000;
} // namespace triton

namespace solar_system_barycenter {
inline constexpr struct icrf : Frame<"ssbc_icrf", barycenters::SolarSystemBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"ssbc_j2000", barycenters::SolarSystemBarycenter, axes::j2000> {
} j2000; // Generally, the icrf frame
} // namespace solar_system_barycenter

namespace mercury_barycenter {
inline constexpr struct icrf : Frame<"mercury_bc_icrf", barycenters::MercuryBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mercury_bc_j2000", barycenters::MercuryBarycenter, axes::j2000> {
} j2000;
} // namespace mercury_barycenter

namespace venus_barycenter {
inline constexpr struct icrf : Frame<"vbc_icrf", barycenters::VenusBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"vbc_j2000", barycenters::VenusBarycenter, axes::j2000> {
} j2000;
} // namespace venus_barycenter

namespace earth_barycenter {
inline constexpr struct icrf : Frame<"embc_icrf", barycenters::EarthBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"embc_j2000", barycenters::EarthBarycenter, axes::j2000> {
} j2000;
} // namespace earth_barycenter

namespace mars_barycenter {
inline constexpr struct icrf : Frame<"mars_bc_icrf", barycenters::MarsBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"mars_bc_j2000", barycenters::MarsBarycenter, axes::j2000> {
} j2000;
} // namespace mars_barycenter

namespace jupiter_barycenter {
inline constexpr struct icrf : Frame<"jbc_icrf", barycenters::JupiterBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"jbc_j2000", barycenters::JupiterBarycenter, axes::j2000> {
} j2000;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
inline constexpr struct icrf : Frame<"saturn_bc_icrf", barycenters::SaturnBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"saturn_bc_j2000", barycenters::SaturnBarycenter, axes::j2000> {
} j2000;
} // namespace saturn_barycenter

namespace uranus_barycenter {
inline constexpr struct icrf : Frame<"ubc_icrf", barycenters::UranusBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"ubc_j2000", barycenters::UranusBarycenter, axes::j2000> {
} j2000;
} // namespace uranus_barycenter

namespace neptune_barycenter {
inline constexpr struct icrf : Frame<"nbc_icrf", barycenters::NeptuneBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 : Frame<"nbc_j2000", barycenters::NeptuneBarycenter, axes::j2000> {
} j2000;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea