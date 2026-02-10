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

#include <vector>

#include <gtl/btree.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/time/Date.hpp>
#include <units/units.hpp>
#include <utilities/ProgressBar.hpp>

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
    AccessArray find_internal_accesses(ViewerConstellation& constel);

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
    gtl::btree_map<std::pair<std::size_t, astro::Date>, EciRadiusVec> _positionHistory; //!< B-tree map storing the state history of platforms at each date for efficient access calculations

    /**
     * @brief Create a date vector from input start date, end date, and resolution.
     *
     * @return DateVector A vector of dates corresponding to the state history.
     */
    void create_date_vector();

    /**
     * @brief Find accesses between two containers of platforms.
     *
     * @tparam T The type of the first platform container, which must satisfy the IsPlatformContainer concept.
     * @tparam U The type of the second platform container, which must satisfy the IsPlatformContainer concept.
     * @param platformContainer1 The first container of platforms for which to find accesses.
     * @param platformContainer2 The second container of platforms for which to find accesses.
     * @param includeInternalAccesses Flag indicating whether to include internal accesses within the first container (default is false).
     * @return AccessArray A collection of accesses between platforms in the two containers.
     */
    template <typename T, typename U>
        requires IsPlatformContainer<T> && IsPlatformContainer<U> //
    AccessArray find_accesses(T& platformContainer1, U& platformContainer2, const bool includeInternalAccesses = false)
    {
        _positionHistory.clear();
        for (const auto& date : _dates) {
            for (auto& platform : platformContainer1) {
                const std::size_t platformId           = platform.get_id();
                _positionHistory[{ platformId, date }] = platform.get_inertial_position(date);
            }
            for (auto& platform : platformContainer2) {
                const std::size_t platformId           = platform.get_id();
                _positionHistory[{ platformId, date }] = platform.get_inertial_position(date);
            }
        }

        // For each sat
        AccessArray allAccesses;
        if (includeInternalAccesses) {
            allAccesses = find_internal_accesses(platformContainer1);
            allAccesses | find_internal_accesses(platformContainer2);
        }

        // Loop over each container
        utilities::ProgressBar progressBar(platformContainer1.size() * platformContainer2.size(), "\tAccess");
        for (std::size_t iPlatform1 = 0; iPlatform1 < platformContainer1.size(); ++iPlatform1) {
            // Extract first platform
            auto& platform1       = platformContainer1[iPlatform1];
            const std::size_t id1 = platform1.get_id();

            for (std::size_t iPlatform2 = 0; iPlatform2 < platformContainer2.size(); ++iPlatform2) {

                // Extract second platform
                auto& platform2       = platformContainer2[iPlatform2];
                const std::size_t id2 = platform2.get_id();

                // Satellite-level access for platform1 -> platform2
                RiseSetArray access = find_platform_to_platform_accesses(&platform1, &platform2);

                // Store
                if (access.size() > 0) {
                    platform1.add_access(id2, access);
                    platform2.add_access(id1, access);
                    allAccesses[id1, id2] = access; // TODO: Consider id2->id1 as well?
                }

                progressBar();
            }
        }

        return allAccesses;
    }

    /**
     * @brief Check if two states are occulting each other.
     *
     * @param state1 The first state to check.
     * @param state2 The second state to check.
     * @return true If the two states are occulting each other.
     * @return false If the two states are not occulting each other.
     */
    bool is_earth_occulting(const EciRadiusVec& position1, const EciRadiusVec& position2);

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
};

} // namespace trace
} // namespace astrea