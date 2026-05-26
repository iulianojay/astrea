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
inline constexpr struct icrf final : Frame<"sun_icrf", star::Sun, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"sun_j2000", star::Sun, axes::j2000> {
} j2000;
} // namespace sun

namespace mercury {
inline constexpr struct icrf final : Frame<"mercury_icrf", planets::Mercury, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"mercury_j2000", planets::Mercury, axes::j2000> {
} j2000;
} // namespace mercury

namespace venus {
inline constexpr struct icrf final : Frame<"venus_icrf", planets::Venus, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"venus_j2000", planets::Venus, axes::j2000> {
} j2000;
} // namespace venus

namespace earth {
inline constexpr struct icrf final : Frame<"gcrf", planets::Earth, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"eme2000", planets::Earth, axes::j2000> {
} j2000;
} // namespace earth

namespace moon {
inline constexpr struct icrf final : Frame<"moon_icrf", moons::Moon, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"moon_j2000", moons::Moon, axes::j2000> {
} j2000;
} // namespace moon

namespace mars {
inline constexpr struct icrf final : Frame<"mars_icrf", planets::Mars, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"mars_j2000", planets::Mars, axes::j2000> {
} j2000;
} // namespace mars

namespace phobos {
inline constexpr struct icrf final : Frame<"phobos_icrf", moons::Phobos, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"phobos_j2000", moons::Phobos, axes::j2000> {
} j2000;
} // namespace phobos

namespace deimos {
inline constexpr struct icrf final : Frame<"deimos_icrf", moons::Deimos, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"deimos_j2000", moons::Deimos, axes::j2000> {
} j2000;
} // namespace deimos

namespace jupiter {
inline constexpr struct icrf final : Frame<"jupiter_icrf", planets::Jupiter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"jupiter_j2000", planets::Jupiter, axes::j2000> {
} j2000;
} // namespace jupiter

namespace ganymede {
inline constexpr struct icrf final : Frame<"ganymede_icrf", moons::Ganymede, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"ganymede_j2000", moons::Ganymede, axes::j2000> {
} j2000;
} // namespace ganymede

namespace callisto {
inline constexpr struct icrf final : Frame<"callisto_icrf", moons::Callisto, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"callisto_j2000", moons::Callisto, axes::j2000> {
} j2000;
} // namespace callisto

namespace io {
inline constexpr struct icrf final : Frame<"io_icrf", moons::Io, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"io_j2000", moons::Io, axes::j2000> {
} j2000;
} // namespace io

namespace europa {
inline constexpr struct icrf final : Frame<"europa_icrf", moons::Europa, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"europa_j2000", moons::Europa, axes::j2000> {
} j2000;
} // namespace europa

namespace saturn {
inline constexpr struct icrf final : Frame<"saturn_icrf", planets::Saturn, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"saturn_j2000", planets::Saturn, axes::j2000> {
} j2000;
} // namespace saturn

namespace titan {
inline constexpr struct icrf final : Frame<"titan_icrf", moons::Titan, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"titan_j2000", moons::Titan, axes::j2000> {
} j2000;
} // namespace titan

namespace rhea {
inline constexpr struct icrf final : Frame<"rhea_icrf", moons::Rhea, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"rhea_j2000", moons::Rhea, axes::j2000> {
} j2000;
} // namespace rhea

namespace iapetus {
inline constexpr struct icrf final : Frame<"iapetus_icrf", moons::Iapetus, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"iapetus_j2000", moons::Iapetus, axes::j2000> {
} j2000;
} // namespace iapetus

namespace uranus {
inline constexpr struct icrf final : Frame<"uranus_icrf", planets::Uranus, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"uranus_j2000", planets::Uranus, axes::j2000> {
} j2000;
} // namespace uranus

namespace titania {
inline constexpr struct icrf final : Frame<"titania_icrf", moons::Titania, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"titania_j2000", moons::Titania, axes::j2000> {
} j2000;
} // namespace titania

namespace oberon {
inline constexpr struct icrf final : Frame<"oberon_icrf", moons::Oberon, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"oberon_j2000", moons::Oberon, axes::j2000> {
} j2000;
} // namespace oberon

namespace neptune {
inline constexpr struct icrf final : Frame<"neptune_icrf", planets::Neptune, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"neptune_j2000", planets::Neptune, axes::j2000> {
} j2000;
} // namespace neptune

namespace triton {
inline constexpr struct icrf final : Frame<"triton_icrf", moons::Triton, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"triton_j2000", moons::Triton, axes::j2000> {
} j2000;
} // namespace triton

namespace solar_system_barycenter {
inline constexpr struct icrf final : Frame<"ssbc_icrf", barycenters::SolarSystemBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"ssbc_j2000", barycenters::SolarSystemBarycenter, axes::j2000> {
} j2000; // Generally, the icrf frame
} // namespace solar_system_barycenter

namespace mercury_barycenter {
inline constexpr struct icrf final : Frame<"mercury_bc_icrf", barycenters::MercuryBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"mercury_bc_j2000", barycenters::MercuryBarycenter, axes::j2000> {
} j2000;
} // namespace mercury_barycenter

namespace venus_barycenter {
inline constexpr struct icrf final : Frame<"vbc_icrf", barycenters::VenusBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"vbc_j2000", barycenters::VenusBarycenter, axes::j2000> {
} j2000;
} // namespace venus_barycenter

namespace earth_barycenter {
inline constexpr struct icrf final : Frame<"embc_icrf", barycenters::EarthBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"embc_j2000", barycenters::EarthBarycenter, axes::j2000> {
} j2000;
} // namespace earth_barycenter

namespace mars_barycenter {
inline constexpr struct icrf final : Frame<"mars_bc_icrf", barycenters::MarsBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"mars_bc_j2000", barycenters::MarsBarycenter, axes::j2000> {
} j2000;
} // namespace mars_barycenter

namespace jupiter_barycenter {
inline constexpr struct icrf final : Frame<"jbc_icrf", barycenters::JupiterBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"jbc_j2000", barycenters::JupiterBarycenter, axes::j2000> {
} j2000;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
inline constexpr struct icrf final : Frame<"saturn_bc_icrf", barycenters::SaturnBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"saturn_bc_j2000", barycenters::SaturnBarycenter, axes::j2000> {
} j2000;
} // namespace saturn_barycenter

namespace uranus_barycenter {
inline constexpr struct icrf final : Frame<"ubc_icrf", barycenters::UranusBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"ubc_j2000", barycenters::UranusBarycenter, axes::j2000> {
} j2000;
} // namespace uranus_barycenter

namespace neptune_barycenter {
inline constexpr struct icrf final : Frame<"nbc_icrf", barycenters::NeptuneBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"nbc_j2000", barycenters::NeptuneBarycenter, axes::j2000> {
} j2000;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea