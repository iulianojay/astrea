/**
 * @file typedefs.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Contains type definitions for the astrea access library.
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <cstdint>

#include <astro/astro.fwd.hpp>
#include <astro/frames.hpp>
#include <astro/systems.hpp>

#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Type definition for enumeration types.
 */
using EnumType = uint32_t;

/**
 * @brief Latitude/Longitude coordinate pair.
 *
 * This type is used to represent a geographic location on the Earth's surface.
 */
using LatLon = std::pair<Angle, Angle>;

/**
 * @brief Latitude range pair.
 *
 * This type is used to represent a range of latitudes for ground coverage analysis.
 */
using LatRange = std::pair<Angle, Angle>;

/**
 * @brief Longitude range pair.
 *
 * This type is used to represent a range of longitudes for ground coverage analysis.
 */
using LonRange = std::pair<Angle, Angle>;

/**
 * @brief Type definition for ECI radius vectors.
 */
using EciRadiusVec = astro::CartesianVector<Distance, astro::frames::earth::icrf>;

/**
 * @brief Type definition for ECEF radius vectors.
 */
using EcefRadiusVec = astro::CartesianVector<Distance, astro::frames::earth::earth_fixed>;

/**
 * @brief Type alias for a vector of time values.
 */
using DateVector = std::vector<astro::Date>;

/**
 * @brief Type alias for a constellation of Viewer objects.
 */
using ViewerConstellation = astro::Constellation<Viewer>;

/**
 * @brief Type alias for a vector of Viewer references.
 */
using ViewerRefVec = std::vector<std::shared_ptr<Viewer>>;

/**
 * @brief Type alias for a vector of GroundStation references.
 */
using GroundStationRefVec = std::vector<std::shared_ptr<GroundStation<astro::planets::Earth>>>;

/**
 * @brief Type definition for a vector of ground point references.
 *
 * This type is used to store references to ground points in the access analysis.
 */
using GroundPointRefVec = std::vector<std::shared_ptr<GroundPoint<astro::planets::Earth>>>;

/**
 * @brief Type alias for a vector of pairs of size_t values.
 */
using PairVec = std::vector<std::pair<std::size_t, std::size_t>>;

/**
 * @brief Pre-computed ECI boresight vectors per sensor per timestep.
 *
 * Indexed as BoresightTable[sensor_idx][time_idx].
 * Computed once per satellite before the ground-point loop to avoid
 * rebuilding the RIC frame for every (viewer, ground point) pair.
 */
using BoresightTable = std::vector<std::vector<EciRadiusVec>>;

} // namespace trace
} // namespace astrea