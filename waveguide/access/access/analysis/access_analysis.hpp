/**
 * @file access_analysis.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for access analysis functions in the waveguide access library.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/element_sets/CartesianVector.hpp>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <access/platforms/ground/GroundArchitecture.hpp>
#include <access/platforms/ground/GroundStation.hpp>
#include <access/platforms/vehicles/Viewer.hpp>
#include <access/risesets/RiseSetArray.hpp>
#include <access/types/typedefs.hpp>
#include <astro/frames/frames.hpp>


namespace waveguide {
namespace accesslib {

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
struct AccessInfo {
    Time time;                                 // Time of access
    astro::RadiusVector<astro::ECI> position1; // Position of the first object at the time of access
    astro::RadiusVector<astro::ECI> position2; // Position of the second object at the time of access
    std::size_t id1;                           // ID of the first object
    std::size_t id2;                           // ID of the second object
    bool isOcculted;                           // Flag indicating if the access is occulted
};

/**
 * @brief Find accesses between a constellation of viewers.
 *
 * @param constel The constellation of viewers.
 * @param resolution The time resolution for access calculations.
 * @param sys The astrodynamics system used for calculations.
 * @return AccessArray A collection of accesses between viewers.
 */
AccessArray find_accesses(ViewerConstellation& constel, const Time& resolution, const astro::Date& epoch, const astro::AstrodynamicsSystem& sys);

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
TimeVector create_time_vector(const astro::StateHistory& states, const Time& resolution);

/**
 * @brief Interpolate states for a vector of viewers at specified times.
 *
 * @param viewers The vector of viewers whose states are to be interpolated.
 * @param times The times at which to interpolate the states.
 */
void interpolate_states(std::vector<Viewer>& viewers, const TimeVector& times);

/**
 * @brief Check if two states are occulting each other.
 *
 * @param state1 The first state to check.
 * @param state2 The second state to check.
 * @param sys The astrodynamics system used for calculations.
 * @return true If the two states are occulting each other.
 * @return false If the two states are not occulting each other.
 */
bool is_earth_occulting(const astro::RadiusVector<astro::ECI>& position1, const astro::RadiusVector<astro::ECI>& position2, const astro::AstrodynamicsSystem& sys);


RiseSetArray find_platform_to_platform_accesses(
    SensorPlatform* platform1,
    SensorPlatform* platform2,
    const TimeVector& times,
    const astro::AstrodynamicsSystem& sys,
    const astro::Date& epoch,
    const bool& twoWay = false
);

/**
 * @brief Find accesses between a sensor and another sensor.
 *
 * @param accessInfo A vector of AccessInfo objects containing access information.
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

} // namespace accesslib
} // namespace waveguide