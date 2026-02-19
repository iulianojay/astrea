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
    { &t[0] } -> std::convertible_to<std::shared_ptr<astro::PayloadPlatform<Sensor>>>;
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

    // This isn't doing anything currently, but I'm not convinced it's a terrible idea to speed up the pre-checks by
    // binning the ground points using the spatial index and only checking the corners for very dense grids.
    SpatialIndex _spatialIndex; //!< Spatial index for ground points

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
    RiseSetArray find_platform_to_platform_accesses(
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform1,
        std::shared_ptr<astro::PayloadPlatform<Sensor>> platform2,
        const bool twoWay = false
    );

    /**
     * @brief Find accesses between a sensor platform and a ground point.
     *
     * @param platform The sensor platform for which to find accesses.
     * @param groundPoint The ground point to check for accesses.
     * @return RiseSetArray A collection of rise/set pairs representing the accesses.
     */
    RiseSetArray
        find_platform_to_ground_point_accesses(std::shared_ptr<astro::PayloadPlatform<Sensor>> platform, const std::shared_ptr<GroundPoint> groundPoint);

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
     * @brief Check if a satellite can access a ground point based on Earth occulating.
     *
     * @param id1 The id of the first object.
     * @param id2 The id of the second object.
     * @return true If the objects can access each other.
     * @return false If the objects never access each other.
     */
    bool can_objects_ever_access_each_other(const std::size_t& id1, const std::size_t& id2) const;

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
     * @brief Filter out impossible viewer-viewer pairs based on Earth occultation.
     *
     * @param viewers The vector of viewer pointers to check.
     * @return PairVec A vector of index pairs (iViewer, iGround) representing possible accesses.
     */
    PairVec filter_impossible_pairs(const ViewerRefVec& viewers) const;

    /**
     * @brief Filter out impossible viewer-ground pairs based on Earth occultation.
     *
     * @param objects1 The vector of object shared pointers to check.
     * @param objects2 The vector of object shared pointers to check.
     * @return PairVec A vector of index pairs (iViewer, iGround) representing possible accesses.
     */
    template <typename T, typename U>
        requires requires(T t) { t.get_id(); } && requires(U u) { u.get_id(); }
    PairVec filter_impossible_pairs(const std::vector<std::shared_ptr<T>>& objects1, const std::vector<std::shared_ptr<U>>& objects2) const
    {
        std::cout << "\tFiltering impossible pairs..." << std::flush;
        PairVec validPairs;
        for (std::size_t ii = 0; ii < objects1.size(); ++ii) {
            for (std::size_t jj = 0; jj < objects2.size(); ++jj) {
                if (can_objects_ever_access_each_other(objects1[ii]->get_id(), objects2[jj]->get_id())) {
                    validPairs.emplace_back(ii, jj);
                }
            }
        }

        std::cout << " kept " << validPairs.size() << " / " << (objects1.size() * objects2.size()) << " pairs ("
                  << (100.0 * validPairs.size() / (objects1.size() * objects2.size())) << "%)" << std::endl;
        return validPairs;
    }
};

} // namespace trace
} // namespace astrea