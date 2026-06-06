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

#include <astro/frames/framework/Frame.hpp>
#include <astro/systems/celestial_bodies.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace sun {
inline constexpr struct icrf final : Frame<"Sun ICRF", star::Sun, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Sun J2000", star::Sun, axes::j2000> {
} j2000;
} // namespace sun

namespace mercury {
inline constexpr struct icrf final : Frame<"Mercury ICRF", planets::Mercury, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Mercury J2000", planets::Mercury, axes::j2000> {
} j2000;
} // namespace mercury

namespace venus {
inline constexpr struct icrf final : Frame<"Venus ICRF", planets::Venus, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Venus J2000", planets::Venus, axes::j2000> {
} j2000;
} // namespace venus

namespace earth {
inline constexpr struct icrf final : Frame<"GCRF", planets::Earth, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"EME2000", planets::Earth, axes::j2000> {
} j2000;
} // namespace earth

namespace moon {
inline constexpr struct icrf final : Frame<"Moon ICRF", moons::Moon, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Moon J2000", moons::Moon, axes::j2000> {
} j2000;
} // namespace moon

namespace mars {
inline constexpr struct icrf final : Frame<"Mars ICRF", planets::Mars, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Mars J2000", planets::Mars, axes::j2000> {
} j2000;
} // namespace mars

namespace phobos {
inline constexpr struct icrf final : Frame<"Phobos ICRF", moons::Phobos, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Phobos J2000", moons::Phobos, axes::j2000> {
} j2000;
} // namespace phobos

namespace deimos {
inline constexpr struct icrf final : Frame<"Deimos ICRF", moons::Deimos, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Deimos J2000", moons::Deimos, axes::j2000> {
} j2000;
} // namespace deimos

namespace jupiter {
inline constexpr struct icrf final : Frame<"Jupiter ICRF", planets::Jupiter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Jupiter J2000", planets::Jupiter, axes::j2000> {
} j2000;
} // namespace jupiter

namespace ganymede {
inline constexpr struct icrf final : Frame<"Ganymede ICRF", moons::Ganymede, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Ganymede J2000", moons::Ganymede, axes::j2000> {
} j2000;
} // namespace ganymede

namespace callisto {
inline constexpr struct icrf final : Frame<"Callisto ICRF", moons::Callisto, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Callisto J2000", moons::Callisto, axes::j2000> {
} j2000;
} // namespace callisto

namespace io {
inline constexpr struct icrf final : Frame<"Io ICRF", moons::Io, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Io J2000", moons::Io, axes::j2000> {
} j2000;
} // namespace io

namespace europa {
inline constexpr struct icrf final : Frame<"Europa ICRF", moons::Europa, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Europa J2000", moons::Europa, axes::j2000> {
} j2000;
} // namespace europa

namespace saturn {
inline constexpr struct icrf final : Frame<"Saturn ICRF", planets::Saturn, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Saturn J2000", planets::Saturn, axes::j2000> {
} j2000;
} // namespace saturn

namespace titan {
inline constexpr struct icrf final : Frame<"Titan ICRF", moons::Titan, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Titan J2000", moons::Titan, axes::j2000> {
} j2000;
} // namespace titan

namespace rhea {
inline constexpr struct icrf final : Frame<"Rhea ICRF", moons::Rhea, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Rhea J2000", moons::Rhea, axes::j2000> {
} j2000;
} // namespace rhea

namespace iapetus {
inline constexpr struct icrf final : Frame<"Iapetus ICRF", moons::Iapetus, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Iapetus J2000", moons::Iapetus, axes::j2000> {
} j2000;
} // namespace iapetus

namespace uranus {
inline constexpr struct icrf final : Frame<"Uranus ICRF", planets::Uranus, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Uranus J2000", planets::Uranus, axes::j2000> {
} j2000;
} // namespace uranus

namespace titania {
inline constexpr struct icrf final : Frame<"Titania ICRF", moons::Titania, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Titania J2000", moons::Titania, axes::j2000> {
} j2000;
} // namespace titania

namespace oberon {
inline constexpr struct icrf final : Frame<"Oberon ICRF", moons::Oberon, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Oberon J2000", moons::Oberon, axes::j2000> {
} j2000;
} // namespace oberon

namespace neptune {
inline constexpr struct icrf final : Frame<"Neptune ICRF", planets::Neptune, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Neptune J2000", planets::Neptune, axes::j2000> {
} j2000;
} // namespace neptune

namespace triton {
inline constexpr struct icrf final : Frame<"Triton ICRF", moons::Triton, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Triton J2000", moons::Triton, axes::j2000> {
} j2000;
} // namespace triton

namespace solar_system_barycenter {
inline constexpr struct icrf final : Frame<"Solar System Barycenter ICRF", barycenters::SolarSystemBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Solar System Barycenter J2000", barycenters::SolarSystemBarycenter, axes::j2000> {
} j2000; // Generally, the icrf frame
} // namespace solar_system_barycenter

namespace mercury_barycenter {
inline constexpr struct icrf final : Frame<"Mercury-Sun Barycenter ICRF", barycenters::MercurySunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Mercury-Sun Barycenter J2000", barycenters::MercurySunBarycenter, axes::j2000> {
} j2000;
} // namespace mercury_barycenter

namespace venus_barycenter {
inline constexpr struct icrf final : Frame<"Venus-Sun Barycenter ICRF", barycenters::VenusSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Venus-Sun Barycenter J2000", barycenters::VenusSunBarycenter, axes::j2000> {
} j2000;
} // namespace venus_barycenter

namespace earth_barycenter {
inline constexpr struct icrf final : Frame<"Earth-Sun Barycenter ICRF", barycenters::EarthSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Earth-Sun Barycenter J2000", barycenters::EarthSunBarycenter, axes::j2000> {
} j2000;
} // namespace earth_barycenter

namespace mars_barycenter {
inline constexpr struct icrf final : Frame<"Mars-Sun Barycenter ICRF", barycenters::MarsSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Mars-Sun Barycenter J2000", barycenters::MarsSunBarycenter, axes::j2000> {
} j2000;
} // namespace mars_barycenter

namespace jupiter_barycenter {
inline constexpr struct icrf final : Frame<"Jupiter-Sun Barycenter ICRF", barycenters::JupiterSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Jupiter-Sun Barycenter J2000", barycenters::JupiterSunBarycenter, axes::j2000> {
} j2000;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
inline constexpr struct icrf final : Frame<"Saturn-Sun Barycenter ICRF", barycenters::SaturnSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Saturn-Sun Barycenter J2000", barycenters::SaturnSunBarycenter, axes::j2000> {
} j2000;
} // namespace saturn_barycenter

namespace uranus_barycenter {
inline constexpr struct icrf final : Frame<"Uranus-Sun Barycenter ICRF", barycenters::UranusSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Uranus-Sun Barycenter J2000", barycenters::UranusSunBarycenter, axes::j2000> {
} j2000;
} // namespace uranus_barycenter

namespace neptune_barycenter {
inline constexpr struct icrf final : Frame<"Neptune-Sun Barycenter ICRF", barycenters::NeptuneSunBarycenter, axes::icrf> {
} icrf;
inline constexpr struct j2000 final : Frame<"Neptune-Sun Barycenter J2000", barycenters::NeptuneSunBarycenter, axes::j2000> {
} j2000;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea