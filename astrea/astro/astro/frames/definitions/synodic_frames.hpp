/**
 * @file synodic_frames.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for synodic frames.
 * @date 2026-08-05
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

#include <astro/frames/framework/BodyFixedFrame.hpp>
#include <astro/systems/celestial_bodies.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace mercury_sun_barycenter {
inline constexpr struct mss final
    : SynodicFrame<"Mercury-Sun Synodic Frame", barycenters::MercurySunBarycenter, planets::Mercury, suns::Sun> {
} mss;
} // namespace mercury_sun_barycenter

namespace venus_sun_barycenter {
inline constexpr struct vss final
    : SynodicFrame<"Venus-Sun Synodic Frame", barycenters::VenusSunBarycenter, planets::Venus, suns::Sun> {
} vss;
} // namespace venus_sun_barycenter

namespace earth_sun_barycenter {
inline constexpr struct ess final
    : SynodicFrame<"Earth-Sun Synodic Frame", barycenters::EarthSunBarycenter, planets::Earth, suns::Sun> {
} ess;
} // namespace earth_sun_barycenter

namespace earth_moon_barycenter {
inline constexpr struct ems final
    : SynodicFrame<"Earth-Moon Synodic Frame", barycenters::EarthMoonBarycenter, planets::Earth, moons::Moon> {
} ems;
} // namespace earth_moon_barycenter

namespace mars_sun_barycenter {
inline constexpr struct mss final
    : SynodicFrame<"Mars-Sun Synodic Frame", barycenters::MarsSunBarycenter, planets::Mars, suns::Sun> {
} mss;
} // namespace mars_sun_barycenter

namespace jupiter_sun_barycenter {
inline constexpr struct jss final
    : SynodicFrame<"Jupiter-Sun Synodic Frame", barycenters::JupiterSunBarycenter, planets::Jupiter, suns::Sun> {
} jss;
} // namespace jupiter_sun_barycenter

namespace saturn_sun_barycenter {
inline constexpr struct sss final
    : SynodicFrame<"Saturn-Sun Synodic Frame", barycenters::SaturnSunBarycenter, planets::Saturn, suns::Sun> {
} sss;
} // namespace saturn_sun_barycenter

namespace uranus_sun_barycenter {
inline constexpr struct uss final
    : SynodicFrame<"Uranus-Sun Synodic Frame", barycenters::UranusSunBarycenter, planets::Uranus, suns::Sun> {
} uss;
} // namespace uranus_sun_barycenter

namespace neptune_sun_barycenter {
inline constexpr struct nss final
    : SynodicFrame<"Neptune-Sun Synodic Frame", barycenters::NeptuneSunBarycenter, planets::Neptune, suns::Sun> {
} nss;
} // namespace neptune_sun_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea