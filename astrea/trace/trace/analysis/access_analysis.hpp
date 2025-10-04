/**
 * @file access_analysis.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for access analysis functions in the astrea access library.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/astro.fwd.hpp>
#include <units/units.hpp>
#include <utilities/ProgressBar.hpp>

#include <trace/risesets/AccessArray.hpp>
#include <trace/risesets/RiseSetArray.hpp>
#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Type alias for a vector of time values.
 */
using TimeVector = std::vector<Time>;

/**
 * @brief Type alias for a constellation of Viewer objects.
 */
using ViewerConstellation = astro::Constellation<Viewer>;

/**
 * @brief Struct to hold access information between two objects.
 */
struct AccessInfo;

/**
 * @brief Find accesses between a constellation of viewers.
 *
 * @param constel The constellation of viewers.
 * @param resolution The time resolution for access calculations.
 * @param sys The astrodynamics system used for calculations.
 * @return AccessArray A collection of accesses between viewers.
 */
AccessArray find_internal_accesses(ViewerConstellation& constel, const Time& resolution, const astro::Date& epoch, const astro::AstrodynamicsSystem& sys);

/**
 * @brief Find accesses between a constellation of viewers and a ground architecture.
 *
 * @param constel The constellation of viewers.
 * @param grounds The ground architecture containing ground stations.
 * @param resolution The time resolution for access calculations.
 * @param epoch The epoch date for the analysis.
 * @param sys The astrodynamics system used for calculations.
 * @return AccessArray A collection of accesses between viewers and ground stations.
 */
AccessArray
    find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const Time& resolution, const astro::Date& epoch, const astro::AstrodynamicsSystem& sys);


/**
 * @brief Create a time vector from a state history.
 *
 * @param states The state history from which to create the time vector.
 * @param resolution The time resolution for the vector.
 * @return TimeVector A vector of times corresponding to the state history.
 */
TimeVector create_time_vector(const Time& start, const Time& end, const Time& resolution);

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

template <typename T, typename U>
    requires IsPlatformContainer<T> && IsPlatformContainer<U> //
AccessArray find_accesses(
    T& platformContainer1,
    U& platformContainer2,
    const Time& start,
    const Time& end,
    const Time& resolution,
    const astro::Date& epoch,
    const astro::AstrodynamicsSystem& sys
)
{
    // Create time array
    TimeVector times = create_time_vector(start, end, resolution); // TODO: Check all state histories for common time frame

    // For each sat
    // AccessArray allAccesses = find_accesses(platformContainer1, resolution, sys); // Do sat-sat first?

    // Loop over each container
    AccessArray allAccesses;
    utilities::ProgressBar progressBar(platformContainer1.size(), "\tAccess");
    for (std::size_t iPlatform1 = 0; iPlatform1 < platformContainer1.size(); ++iPlatform1) {
        // Extract first platform
        auto& platform1       = platformContainer1[iPlatform1];
        const std::size_t id1 = platform1.get_id();

        for (std::size_t iPlatform2 = 0; iPlatform2 < platformContainer2.size(); ++iPlatform2) {

            // Extract second platform
            auto& platform2       = platformContainer2[iPlatform2];
            const std::size_t id2 = platform2.get_id();

            // Satellite-level access for platform1 -> platform2
            RiseSetArray access = find_platform_to_platform_accesses(&platform1, &platform2, times, sys, epoch);

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
 * @param sys The astrodynamics system used for calculations.
 * @return true If the two states are occulting each other.
 * @return false If the two states are not occulting each other.
 */
bool is_earth_occulting(
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& position1,
    const astro::CartesianVector<Distance, astro::frames::earth::icrf>& position2,
    const astro::AstrodynamicsSystem& sys
);

/**
 * @brief Find accesses between two sensor platforms.
 *
 * @param platform1 The first sensor platform.
 * @param platform2 The second sensor platform.
 * @param times The times at which to check for accesses.
 * @param sys The astrodynamics system used for calculations.
 * @param epoch The epoch date for the analysis.
 * @param twoWay Flag indicating if the access should be two-way (default is false).
 * @return RiseSetArray A collection of rise/set pairs representing the accesses.
 */
RiseSetArray find_platform_to_platform_accesses(
    astro::PayloadPlatform<Sensor>* platform1,
    astro::PayloadPlatform<Sensor>* platform2,
    const TimeVector& times,
    const astro::AstrodynamicsSystem& sys,
    const astro::Date& epoch,
    const bool& twoWay = false
);

/**
 * @brief Find accesses between a sensor and another sensor.
 *
 * @param accessInfo A vector of AccessInfo objects containing trace information.
 * @param sensor1 The first sensor for which to find accesses.
 * @param sensor2 The second sensor to check for accesses.
 * @param twoWay Flag indicating if the access should be two-way (default is false).
 * @return RiseSetArray A collection of rise/set pairs representing the accesses.
 */
RiseSetArray find_sensor_to_sensor_accesses(
    const std::vector<AccessInfo>& accessInfo,
    const Sensor& sensor1,
    const Sensor& sensor2,
    const bool& twoWay,
    const astro::Date& epoch
);

} // namespace trace
} // namespace astrea