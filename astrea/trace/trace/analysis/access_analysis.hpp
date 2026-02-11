/**
 * @file access_analysis.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for access analysis functions in the astrea access library.
 * @date 2025-08-03
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

#include <memory>
#include <vector>

#include <gtl/btree.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>
#include <utilities/ProgressBar.hpp>

#include <trace/analysis/PositionCache.hpp>
#include <trace/analysis/SpatialIndex.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {


template <typename T>
concept HasSize = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept HasSubscriptOperator = requires(T t) {
    { &t[0] } -> std::convertible_to<astro::PayloadPlatform<Sensor>*>;
};


template <typename T>
concept IsPlatformContainer = HasSize<T> && HasSubscriptOperator<T>;

using EciRadiusVec = astro::RadiusVector<astro::frames::earth::icrf>;

/**
 * @brief Type alias for a vector of time values.
 */
using DateVector = std::vector<astro::Date>;

/**
 * @brief Type alias for a constellation of Viewer objects.
 */
using ViewerConstellation = astro::Constellation<Viewer>;


using ViewerRefVec = std::vector<std::shared_ptr<Viewer>>;

using GroundStationRefVec = std::vector<std::shared_ptr<GroundStation>>;

using GroundPointRefVec = std::vector<std::shared_ptr<GroundPoint>>;

using PairVec = std::vector<std::pair<std::size_t, std::size_t>>;


class AccessAnalyzer {

  public:
    /**
     * @brief Constructor for AccessAnalyzer with specified resolution and date range.
     *
     * @param resolution The time resolution for access calculations.
     * @param startDate The start date for the analysis.
     * @param endDate The end date for the analysis.
     * @param sys The astrodynamics system used for calculations.
     */
    AccessAnalyzer(const Time& resolution, const astro::Date& startDate, const astro::Date& endDate, const astro::AstrodynamicsSystem& sys) :
        _resolution(resolution),
        _startDate(startDate),
        _endDate(endDate),
        _sys(&sys)
    {
        create_date_vector();
    }

    /**
     * @brief Destructor for AccessAnalyzer.
     */
    ~AccessAnalyzer() = default;

    /**
     * @brief Find accesses between a constellation of viewers.
     *
     * @param constel The constellation of viewers.
     * @param sys The astrodynamics system used for calculations.
     * @return AccessArray A collection of accesses between viewers.
     */
    AccessArray find_internal_accesses(ViewerConstellation& constel, const bool clearPositionCache = true);

    /**
     * @brief Find accesses between a constellation of viewers and a ground architecture.
     *
     * @param constel The constellation of viewers.
     * @param grounds The ground architecture containing ground stations.
     * @param resolution The time resolution for access calculations.
     * @param startDate The start date for the analysis.
     * @param endDate The end date for the analysis.
     * @param sys The astrodynamics system used for calculations.
     * @return AccessArray A collection of accesses between viewers and ground stations.
     */
    AccessArray find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const bool includeInternalAccesses = false);

    /**
     * @brief Find accesses between a constellation of viewers and a ground architecture.
     *
     * @param constel The constellation of viewers.
     * @param grid The grid containing ground points.
     * @return AccessArray A collection of accesses between viewers and ground stations.
     */
    AccessArray find_accesses(ViewerConstellation& constel, Grid& grid, const bool includeInternalAccesses = false);

  private:
    Time _resolution;                       //!< Time resolution for access calculations
    astro::Date _startDate;                 //!< Start date for access analysis
    astro::Date _endDate;                   //!< End date for access analysis
    const astro::AstrodynamicsSystem* _sys; //!< Pointer to the astrodynamics system used for calculations
    DateVector _dates;                      //!< Vector of dates, created from startDate, endDate, and resolution
    PositionCache _positionCache;           //!< Optimized contiguous cache for platform positions
    SpatialIndex _spatialIndex;             //!< Spatial index for ground points

    /**
     * @brief Create a date vector from input start date, end date, and resolution.
     *
     * @return DateVector A vector of dates corresponding to the state history.
     */
    void create_date_vector();

    /**
     * @brief Check if coarse geometric access is possible (range and occultation only)
     */
    std::vector<bool> check_coarse_visibility(const std::vector<EciRadiusVec>& positions1, const std::vector<EciRadiusVec>& positions2);

    /**
     * @brief Batch check occultation for multiple position pairs
     */
    std::vector<bool> check_occultation_batch(const std::vector<EciRadiusVec>& positions1, const std::vector<EciRadiusVec>& positions2);

    /**
     * @brief Check if two states are occulting each other.
     *
     * @param state1 The first state to check.
     * @param state2 The second state to check.
     * @return true If the two states are occulting each other.
     * @return false If the two states are not occulting each other.
     */
    bool is_earth_occulting(const EciRadiusVec& position1, const EciRadiusVec& position2) const;

    /**
     * @brief Find accesses between two sensor platforms.
     *
     * @param platform1 The first sensor platform.
     * @param platform2 The second sensor platform.
     * @param dates The dates at which to check for accesses.
     * @param sys The astrodynamics system used for calculations.
     * @param twoWay Flag indicating if the access should be two-way (default is false).
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray
        find_platform_to_platform_accesses(astro::PayloadPlatform<Sensor>* platform1, astro::PayloadPlatform<Sensor>* platform2, const bool twoWay = false);

    /**
     * @brief Find accesses between a sensor platform and a ground point.
     *
     * @param platform The sensor platform for which to find accesses.
     * @param groundPoint The ground point to check for accesses.
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray find_platform_to_ground_point_accesses(astro::PayloadPlatform<Sensor>* platform, const GroundPoint& groundPoint);

    /**
     * @brief Find accesses between a sensor and another sensor.
     *
     * @param accessInfo A vector of AccessInfo objects containing trace information.
     * @param sensor1 The first sensor for which to find accesses.
     * @param sensor2 The second sensor to check for accesses.
     * @param twoWay Flag indicating if the access should be two-way (default is false).
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray
        find_sensor_to_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor1, const Sensor& sensor2, const bool twoWay);

    /**
     * @brief Find accesses between a sensor and a ground point.
     *
     * @param accessInfo A vector of AccessInfo objects containing trace information.
     * @param sensor The sensor for which to find accesses.
     * @param groundPoint The ground point to check for accesses.
     * @param epoch The epoch date corresponding to the accessInfo time values.
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray find_sensor_to_ground_point_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor, const GroundPoint& groundPoint);

    /**
     * @brief Check if a satellite can access a ground point based on their positions and the Earth's radius.
     *
     * @param satellite The viewer representing the satellite.
     * @param groundPoint The ground point to check for access.
     * @return true If the satellite can access the ground point.
     * @return false If the satellite cannot access the ground point.
     */
    bool can_satellite_access_ground_point(const Viewer& satellite, const GroundPoint& groundPoint) const;


    /**
     * @brief Fast check if a satellite orbit can access another satellite orbit
     *
     * @param sat1 The first satellite viewer.
     * @param sat2 The second satellite viewer.
     * @return true If the satellites can access each other.
     * @return false If the satellites cannot access each other.
     */
    bool can_satellites_access_each_other(const Viewer& sat1, const Viewer& sat2) const;


    /**
     * @brief Compute maximum possible sensor range based on altitude and Earth radius
     *
     * @param altitude The altitude of the satellite above Earth's surface.
     * @param earthRadius The radius of the Earth.
     * @return Distance The maximum slant range from the satellite to a point on the Earth's surface, assuming a spherical Earth and no atmospheric refraction.
     */
    inline Distance compute_max_slant_range(const Distance& altitude, const Distance& earthRadius)
    {
        using namespace mp_units;
        return sqrt(pow<2>(altitude + earthRadius) - pow<2>(earthRadius));
    }

    /**
     * @brief Fast check if two positions are definitely too far apart
     *
     * @param pos1 The first position vector.
     * @param pos2 The second position vector.
     * @param maxRange The maximum range for access.
     * @return true If the positions are too far apart to have access.
     * @return false If the positions are within the maximum range.
     */
    inline bool are_positions_too_far(const EciRadiusVec& pos1, const EciRadiusVec& pos2, const Distance& maxRange)
    {
        using namespace mp_units;

        // Quick bounding box check before computing actual distance
        const auto diff   = pos2 - pos1;
        const Distance dx = abs(diff[0]);
        const Distance dy = abs(diff[1]);
        const Distance dz = abs(diff[2]);

        // If any component exceeds max range, definitely too far
        if (dx > maxRange || dy > maxRange || dz > maxRange) { return true; }

        // Check actual distance
        const Distance distance = diff.norm();
        return distance > maxRange;
    }

    /**
     * @brief Cache the inertial positions of viewers in a constellation for all time steps.
     *
     * @param constel The constellation of viewers for which to cache positions.
     * @return ViewerRefVec A vector of pointers to the viewers in the constellation, in the same order as the position cache entries.
     */
    ViewerRefVec cache_viewers(ViewerConstellation& constel);

    /**
     * @brief Cache the inertial positions of ground stations in a ground architecture for all time steps.
     *
     * @param grounds The ground architecture containing the ground stations to cache.
     * @return GroundStationRefVec A vector of pointers to the ground stations in the
     * architecture, in the same order as the position cache entries.
     */
    GroundStationRefVec cache_ground_points(GroundArchitecture& grounds);

    /**
     * @brief Cache the inertial positions of ground points in a grid for all time steps.
     *
     * @param grid The grid containing the ground points to cache.
     * @return GroundPointRefVec A vector of pointers to the ground points in the grid, in the same order as the position cache entries.
     */
    GroundPointRefVec cache_ground_points(Grid& grid);

    /**
     * @brief Filter out impossible viewer-ground station pairs based on coarse geometric checks.
     *
     * @param viewers The vector of viewer pointers to check.
     * @param groundStations The vector of ground station pointers to check.
     * @return PairVec A vector of index pairs (iViewer, iGround) representing possible accesses.
     */
    PairVec filter_impossible_pairs(const ViewerRefVec& viewers) const;

    /**
     * @brief Filter out impossible viewer-ground station pairs based on coarse geometric checks.
     *
     * @param viewers The vector of viewer pointers to check.
     * @param groundStations The vector of ground station pointers to check.
     * @return PairVec A vector of index pairs (iViewer, iGround) representing possible accesses.
     */
    PairVec filter_impossible_pairs(const ViewerRefVec& viewers, const GroundStationRefVec& groundStations) const;

    /**
     * @brief Filter out impossible viewer-ground point pairs based on coarse geometric checks.
     *
     * @param viewers The vector of viewer pointers to check.
     * @param groundPoints The vector of ground point pointers to check.
     * @return PairVec A vector of index pairs (iViewer, iGround) representing possible accesses.
     */
    PairVec filter_impossible_pairs(const ViewerRefVec& viewers, const GroundPointRefVec& groundPoints) const;
};

} // namespace trace
} // namespace astrea