/**
 * @file AccessAnalyzer.hpp
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

#include <gtl/phmap.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>
#include <utilities/ProgressBar.hpp>

#include <trace/analysis/PositionCache.hpp>
#include <trace/analysis/SpatialIndex.hpp>
#include <trace/platforms/sensors/Sensor.hpp>
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
    { &t[0] } -> std::convertible_to<std::shared_ptr<astro::PayloadPlatform<Sensor>>>;
};


template <typename T>
concept IsPlatformContainer = HasSize<T> && HasSubscriptOperator<T>;

class AccessAnalyzer {

  public:
    /**
     * @brief Constructor for AccessAnalyzer with specified resolution and date range.
     *
     * @param resolution The time resolution for access calculations.
     * @param startDate The start date for the analysis.
     * @param endDate The end date for the analysis.
     * @param printProgress Flag indicating whether to print progress during calculations.
     */
    AccessAnalyzer(const Time& resolution, const astro::Date& startDate, const astro::Date& endDate, const bool printProgress = false) :
        _resolution(resolution),
        _startDate(startDate),
        _endDate(endDate),
        _printProgress(printProgress)
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
    AccessArray find_accesses(ViewerConstellation& constel, GroundArchitecture<astro::planets::Earth>& grounds, const bool includeInternalAccesses = false);

    /**
     * @brief Find accesses between a constellation of viewers and a ground architecture.
     *
     * @param constel The constellation of viewers.
     * @param grid The grid containing ground points.
     * @return AccessArray A collection of accesses between viewers and ground stations.
     */
    AccessArray find_accesses(ViewerConstellation& constel, Grid<astro::planets::Earth>& grid, const bool includeInternalAccesses = false);

  private:
    Time _resolution;             //!< Time resolution for access calculations
    astro::Date _startDate;       //!< Start date for access analysis
    astro::Date _endDate;         //!< End date for access analysis
    DateVector _dates;            //!< Vector of dates, created from startDate, endDate, and resolution
    PositionCache _positionCache; //!< Optimized contiguous cache for platform positions
    bool _printProgress;          //!< Flag to indicate whether to print progress during calculations

    // This isn't doing anything currently, but I'm not convinced it's a terrible idea to speed up the pre-checks by
    // binning the ground points using the spatial index and only checking the corners for very dense grids.
    // SpatialIndex _spatialIndex; //!< Spatial index for ground points

    /**
     * @brief Create a date vector from input start date, end date, and resolution.
     *
     * @return DateVector A vector of dates corresponding to the state history.
     */
    void create_date_vector();

    /**
     * @brief Check if two states are occulting each other.
     *
     * @param state1 The first state to check.
     * @param state2 The second state to check.
     * @param atmosphereBlocks Flag indicating if the atmosphere should be considered as blocking access.
     * @return true If the two states are occulting each other.
     * @return false If the two states are not occulting each other.
     */
    bool is_central_body_occulting(const EcefRadiusVec& position1, const EcefRadiusVec& position2, const bool atmosphereBlocks) const;

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
    RiseSetArray find_platform_to_platform_accesses(
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform1,
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform2,
        const bool twoWay = false
    ) const;

    /**
     * @brief Find accesses between a sensor platform and a ground point.
     *
     * @param platform The sensor platform for which to find accesses.
     * @param groundPoint The ground point to check for accesses.
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray find_platform_to_ground_point_accesses(
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform,
        const std::shared_ptr<GroundPoint<astro::planets::Earth>> groundPoint
    ) const;

    /**
     * @brief Find accesses between a sensor and another sensor.
     *
     * @param accessInfo A vector of AccessInfo objects containing trace information.
     * @param sensor1 The first sensor for which to find accesses.
     * @param sensor2 The second sensor to check for accesses.
     * @param twoWay Flag indicating if the access should be two-way (default is false).
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray find_sensor_accesses(
        const std::vector<AccessInfo>& accessInfo,
        const Sensor& sensor1,
        const std::optional<Sensor> sensor2 = std::nullopt,
        const bool twoWay                   = false
    ) const;

    /**
     * @brief Check if a satellite can access a ground point based on Earth occulating.
     *
     * @param id1 The id of the first object.
     * @param id2 The id of the second object.
     * @param atmosphereBlocks Flag indicating if the atmosphere should be considered as blocking access.
     * @return true If the objects can access each other.
     * @return false If the objects never access each other.
     */
    bool can_objects_ever_access_each_other(const std::size_t& id1, const std::size_t& id2, const bool atmosphereBlocks) const;

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
    GroundStationRefVec cache_ground_points(GroundArchitecture<astro::planets::Earth>& grounds);

    /**
     * @brief Cache the inertial positions of ground points in a grid for all time steps.
     *
     * @param grid The grid containing the ground points to cache.
     * @return GroundPointRefVec A vector of pointers to the ground points in the grid, in the same order as the position cache entries.
     */
    GroundPointRefVec cache_ground_points(Grid<astro::planets::Earth>& grid);

    /**
     * @brief Build access information for a pair of objects based on their cached positions.
     *        Uses the full is_central_body_occulting check; prefer build_ground_access_info
     *        when id2 refers to a surface-fixed ground point.
     */
    std::vector<AccessInfo> build_access_info(const std::size_t& id1, const std::size_t& id2) const;

    /**
     * @brief Fast-path access info builder for satellite-to-ground-point pairs.
     *        Replaces the asin/acos occlusion test with a single dot-product elevation check,
     *        valid because the ground position is fixed on Earth's surface.
     */
    std::vector<AccessInfo> build_ground_access_info(const std::size_t& satId, const std::size_t& gpId) const;

    /**
     * @brief For each viewer, find all ground-point indices (by position in groundPoints)
     *        reachable at any timestep given the sensor footprints and satellite ground track.
     *
     * @param viewers       The satellite platforms.
     * @param spatialIndex  Pre-built spatial index of the ground points.
     * @return Per-viewer vector of reachable ground-point indices.
     */
    std::vector<std::vector<std::size_t>>
        compute_candidate_ground_points(const ViewerRefVec& viewers, const SpatialIndex& spatialIndex) const;

    /**
     * @brief Pre-compute ECI boresight vectors for every sensor on a platform at every timestep.
     *
     * Hoists the RIC-frame construction and boresight rotation out of the inner
     * ground-point loop so the cost is O(N_sensors * N_time) instead of
     * O(N_sensors * N_time * N_groundPoints).
     *
     * @param platform The sensor platform.
     * @return BoresightTable boresights[sensor_idx][time_idx] in ECI.
     */
    BoresightTable compute_sensor_boresights(std::shared_ptr<astro::PayloadPlatform<Sensor>> platform) const;

    /**
     * @brief Find sensor accesses using a pre-computed ECI boresight table.
     *
     * Replaces the per-timestep sensor.contains() call (which rebuilds the RIC
     * frame) with a direct fov->contains() using a pre-computed boresight vector.
     *
     * @param accessInfo Per-timestep geometry and occlusion data.
     * @param boresightEci Pre-computed ECI boresight vector for this sensor, indexed by time.
     * @param fov Field of view to check against.
     * @return RiseSetArray Access windows for this sensor.
     */
    RiseSetArray
        find_sensor_accesses_precomputed(const std::vector<AccessInfo>& accessInfo, const std::vector<EciRadiusVec>& boresightEci, const FieldOfView* fov) const;
};

} // namespace trace
} // namespace astrea