/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <trace/analysis/AccessAnalyzer.hpp>

#include <algorithm>
#include <execution>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

#include <trace/analysis/PositionCache.hpp>
#include <trace/analysis/SpatialIndex.hpp>
#include <trace/platforms/ground/Grid.hpp>
#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/ground/GroundStation.hpp>
#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/platforms/vehicles/Viewer.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {

using namespace astro::frames;
using astro::AstrodynamicsSystem;
using astro::Cartesian;
using astro::CelestialBodyId;
using astro::Date;
using astro::Keplerian;
using astro::RadiusVector;
using astro::State;
using astro::StateHistory;
using astro::VelocityVector;

namespace trace {

using namespace mp_units;
using namespace mp_units::angular;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;


struct AccessInfo {
    Time time;               // Time of access
    EciRadiusVec radius1to2; // Vector from the first object to the second object at the time of access
    bool isOcculted;         // Flag indicating if the access is occulted
};


ViewerRefVec AccessAnalyzer::cache_viewers(ViewerConstellation& constel)
{
    std::cout << "\tCaching satellite positions..." << std::endl;

    const std::size_t nTimesteps = _dates.size();
    ViewerRefVec viewers;
    viewers.reserve(constel.size());
    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (Viewer& viewer : plane.get_all_spacecraft()) {
                viewers.push_back(std::make_shared<Viewer>(viewer));
                const std::size_t platformIdx = _positionCache.add_platform(viewer.get_id(), nTimesteps);

                for (std::size_t iTime = 0; iTime < nTimesteps; ++iTime) {
                    _positionCache.set_position(platformIdx, iTime, viewer.get_inertial_position(_dates[iTime]));
                }
            }
        }
    }
    return viewers;
}

GroundStationRefVec AccessAnalyzer::cache_ground_points(GroundArchitecture& grounds)
{
    std::cout << "\tCaching ground station positions..." << std::endl;
    const std::size_t nTimesteps = _dates.size();
    GroundStationRefVec groundStations;
    groundStations.reserve(grounds.size());
    for (auto& ground : grounds) {
        groundStations.push_back(std::make_shared<GroundStation>(ground));
        const std::size_t platformIdx = _positionCache.add_platform(ground.get_id(), nTimesteps);

        for (std::size_t iTime = 0; iTime < nTimesteps; ++iTime) {
            _positionCache.set_position(platformIdx, iTime, ground.get_inertial_position(_dates[iTime]));
        }
    }
    return groundStations;
}

GroundPointRefVec AccessAnalyzer::cache_ground_points(Grid& grid)
{
    std::cout << "\tCaching ground grid positions..." << std::endl;
    const std::size_t nTimesteps = _dates.size();

    GroundPointRefVec groundPoints;
    groundPoints.reserve(grid.size());
    std::size_t gpIdx = 0;
    for (auto& groundPoint : grid) {
        groundPoints.push_back(std::make_shared<GroundPoint>(groundPoint));
        _spatialIndex.add_ground_point(gpIdx, groundPoint.get_latitude(), groundPoint.get_longitude());

        const std::size_t platformIdx = _positionCache.add_platform(groundPoint.get_id(), nTimesteps);

        for (std::size_t iTime = 0; iTime < nTimesteps; ++iTime) {
            _positionCache.set_position(platformIdx, iTime, groundPoint.get_inertial_position(_dates[iTime]));
        }
        gpIdx++;
    }
    return groundPoints;
}


PairVec AccessAnalyzer::filter_impossible_pairs(const ViewerRefVec& viewers) const
{
    std::cout << "\tFiltering impossible sat-to-sat pairs..." << std::flush;

    const std::size_t nViewers = viewers.size();

    PairVec validPairs;
    for (std::size_t ii = 0; ii < nViewers; ++ii) {
        for (std::size_t jj = ii + 1; jj < nViewers; ++jj) {
            if (can_objects_ever_access_each_other(viewers[ii]->get_id(), viewers[jj]->get_id())) {
                validPairs.emplace_back(ii, jj);
            }
        }
    }

    std::cout << " kept " << validPairs.size() << " / " << (nViewers * (nViewers - 1) / 2) << " pairs ("
              << (100.0 * validPairs.size() / (nViewers * (nViewers - 1) / 2)) << "%)" << std::endl;

    return validPairs;
}


AccessArray AccessAnalyzer::find_internal_accesses(ViewerConstellation& constel, const bool clearPositionCache)
{
    const std::size_t nViewers   = constel.size();
    const std::size_t nTimesteps = _dates.size();

    // Build position cache
    if (clearPositionCache) {
        _positionCache.clear();
        _positionCache.reserve(nViewers, nTimesteps);
    }
    ViewerRefVec viewers = cache_viewers(constel);

    // Pre-filter impossible pairs using geometric tests
    const auto validPairs = filter_impossible_pairs(viewers);

    // Process access checks in parallel
    AccessArray allAccesses;
    std::cout << std::endl;
    utilities::ProgressBar progressBar(validPairs.size(), "\tSat->Sat Access");

    // Note: Parallel execution requires thread-safe access storage
    for (const auto& [iViewer, jViewer] : validPairs) {
        auto& viewer1 = viewers[iViewer];
        auto& viewer2 = viewers[jViewer];

        const RiseSetArray satAccess = find_platform_to_platform_accesses(viewer1, viewer2);

        if (satAccess.size() > 0) {
            const std::size_t id1 = viewer1->get_id();
            const std::size_t id2 = viewer2->get_id();

            viewer1->add_access(id2, satAccess);
            viewer2->add_access(id1, satAccess);
            allAccesses[id1, id2] = satAccess;
            allAccesses[id2, id1] = satAccess;
        }
        progressBar();
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const bool includeInternalAccesses)
{
    const std::size_t nViewers   = constel.size();
    const std::size_t nGrounds   = grounds.size();
    const std::size_t nTimesteps = _dates.size();

    // Build position cache
    _positionCache.clear();
    _positionCache.reserve(nViewers + nGrounds, nTimesteps);

    ViewerRefVec viewers               = cache_viewers(constel);
    GroundStationRefVec groundStations = cache_ground_points(grounds);

    // Pre-filter impossible pairs
    const auto validPairs = filter_impossible_pairs(viewers, groundStations);

    // Internal accesses if requested
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel, false) : AccessArray();

    std::cout << std::endl;
    utilities::ProgressBar progressBar(validPairs.size(), "\tSat->Ground Access");

    for (const auto& [iViewer, iGround] : validPairs) {
        auto& viewer        = viewers[iViewer];
        auto& groundStation = groundStations[iGround];

        // If the ground station has Sensors, treat it as a SensorPlatform, otherwise, treat it as a GroundPoint
        const bool groundHasSensors  = (groundStation->get_payloads().size() > 0);
        const RiseSetArray satAccess = groundHasSensors ? find_platform_to_platform_accesses(viewer, groundStation) :
                                                          find_platform_to_ground_point_accesses(viewer, groundStation);

        if (satAccess.size() > 0) {
            const std::size_t viewerId = viewer->get_id();
            const std::size_t groundId = groundStation->get_id();

            viewer->add_access(groundId, satAccess);
            groundStation->add_access(viewerId, satAccess);
            allAccesses[viewerId, groundId] = satAccess;
            if (groundHasSensors) { allAccesses[groundId, viewerId] = satAccess; }
        }
        progressBar();
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, Grid& grid, const bool includeInternalAccesses)
{
    const std::size_t nViewers   = constel.size();
    const std::size_t nGrounds   = grid.size();
    const std::size_t nTimesteps = _dates.size();

    // Build spatial index and position cache
    _spatialIndex.clear();
    _positionCache.clear();
    _positionCache.reserve(nViewers + nGrounds, nTimesteps);

    ViewerRefVec viewers           = cache_viewers(constel);
    GroundPointRefVec groundPoints = cache_ground_points(grid);

    // Pre-filter and build pairs using spatial indexing
    const auto validPairs = filter_impossible_pairs(viewers, groundPoints);

    // Internal accesses if requested
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel, false) : AccessArray();

    std::cout << std::endl;
    utilities::ProgressBar progressBar(validPairs.size(), "\tSat->Grid Access");

    for (const auto& [iViewer, iGround] : validPairs) {
        auto& viewer      = viewers[iViewer];
        auto& groundPoint = groundPoints[iGround];

        const RiseSetArray satAccess = find_platform_to_ground_point_accesses(viewer, groundPoint);

        if (satAccess.size() > 0) {
            const std::size_t viewerId = viewer->get_id();
            const std::size_t groundId = groundPoint->get_id();

            viewer->add_access(groundId, satAccess);
            groundPoint->add_access(viewerId, satAccess);
            allAccesses[viewerId, groundId] = satAccess;
        }
        progressBar();
    }

    return allAccesses;
}

void AccessAnalyzer::create_date_vector()
{
    // Fill
    Time time = 0.0 * s;
    _dates.clear();
    _dates.emplace_back(_startDate);
    while (_startDate + time < _endDate) {
        if (_startDate + time + _resolution >= _endDate) { time = _endDate - _startDate; }
        else {
            time += _resolution;
        }
        _dates.emplace_back(_startDate + time);
    }
}

RiseSetArray
    AccessAnalyzer::find_platform_to_platform_accesses(std::shared_ptr<SensorPlatform> platform1, std::shared_ptr<SensorPlatform> platform2, const bool twoWay)
{
    const std::size_t id1 = platform1->get_id();
    const std::size_t id2 = platform2->get_id();

    // Get position vectors (cached, contiguous memory)
    const auto& positions1 = _positionCache.get_platform_positions_by_id(id1);
    const auto& positions2 = _positionCache.get_platform_positions_by_id(id2);

    // Build access info only for potential access windows
    std::vector<AccessInfo> accessInfo;
    accessInfo.reserve(_dates.size());
    for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
        AccessInfo info;
        info.time       = _dates[ii] - _startDate;
        info.radius1to2 = positions2[ii] - positions1[ii];
        info.isOcculted = is_earth_occulting(positions1[ii], positions2[ii]);
        accessInfo.push_back(info);
    }

    // Determine access sensor by sensor
    RiseSetArray platformToPlatformAccesses;
    for (auto& sensor1 : platform1->get_payloads()) {
        for (auto& sensor2 : platform2->get_payloads()) {
            const RiseSetArray sensorAccess = find_sensor_to_sensor_accesses(accessInfo, sensor1, sensor2, twoWay);

            // Store
            if (sensorAccess.size() > 0) {
                platformToPlatformAccesses |= sensorAccess;
                sensor1.add_access(sensor2.get_id(), sensorAccess);
                sensor2.add_access(sensor1.get_id(), sensorAccess);
            }
        }
    }

    return platformToPlatformAccesses;
}

RiseSetArray AccessAnalyzer::find_platform_to_ground_point_accesses(std::shared_ptr<SensorPlatform> platform, const std::shared_ptr<GroundPoint> groundPoint)
{
    const std::size_t id1 = platform->get_id();
    const std::size_t id2 = groundPoint->get_id();

    // Get position vectors (cached, contiguous memory)
    const auto& positions1 = _positionCache.get_platform_positions_by_id(id1);
    const auto& positions2 = _positionCache.get_platform_positions_by_id(id2);

    // Build access info
    std::vector<AccessInfo> accessInfo;
    accessInfo.reserve(_dates.size());
    for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
        AccessInfo info;
        info.time       = _dates[ii] - _startDate;
        info.radius1to2 = positions2[ii] - positions1[ii];
        info.isOcculted = is_earth_occulting(positions1[ii], positions2[ii]);
        accessInfo.push_back(info);
    }

    // Determine access sensor by sensor
    RiseSetArray platformToGroundAccesses;
    for (auto& sensor : platform->get_payloads()) {
        const RiseSetArray sensorAccess = find_sensor_to_ground_point_accesses(accessInfo, sensor, *groundPoint);

        // Store
        if (sensorAccess.size() > 0) {
            platformToGroundAccesses |= sensorAccess;
            sensor.add_access(groundPoint->get_id(), sensorAccess);
            groundPoint->add_access(sensor.get_id(), sensorAccess);
        }
    }

    return platformToGroundAccesses;
}

RiseSetArray
    AccessAnalyzer::find_sensor_to_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor1, const Sensor& sensor2, const bool twoWay)
{
    Time rise, set;
    bool insideAccessInterval = false;
    RiseSetArray access;
    const Time start = accessInfo.front().time;
    const Time end   = accessInfo.back().time;
    for (const auto& specificAccessInfo : accessInfo) {
        // Extract
        const Time& time               = specificAccessInfo.time;
        const EciRadiusVec& radius1to2 = specificAccessInfo.radius1to2;
        const EciRadiusVec radius2to1  = -radius1to2;
        const bool& isOcculted         = specificAccessInfo.isOcculted;

        // Check if they can see each other
        const Date date = _startDate + time;
        bool sensorsInView;
        if (isOcculted) { sensorsInView = false; }
        else if (twoWay) {
            sensorsInView = sensor1.contains(radius1to2, date) && sensor2.contains(radius2to1, date);
        }
        else {
            sensorsInView = sensor1.contains(radius1to2, date) || sensor2.contains(radius2to1, date);
        }

        // Manage bookends
        if (time == start) {
            insideAccessInterval = sensorsInView;
            if (insideAccessInterval) // Consider the start time the initial rise
            {
                rise = start;
            }
            continue;
        }
        else if (time == end) {
            if (insideAccessInterval && sensorsInView) { // Consider the final time the last set
                access.append(rise, end);
                continue;
            }
            // NOTE: this ignores cases where the last time is a rise time -> access analyzed for [0, T)
        }

        // Check for rise/set times
        if (insideAccessInterval && !sensorsInView) { // previous time had access, this time does not -> last time was a set
            insideAccessInterval = false;
            if (rise == set) {
                // Ignore for now - TODO: Make this an input option
                continue;
                // throw std::runtime_error("Rise and set found at the same time. This is likely due to a large time resolution. Please rerun analysis with a finer resolution.")
            }
            access.append(rise, set);
        }
        else if (insideAccessInterval && sensorsInView) { // previous time had access, and so does this one -> store set time and continue
            set = time;
        }
        else if (!insideAccessInterval && sensorsInView) { // previous time didn't have access, this time does -> this time is a rise
            insideAccessInterval = true;
            rise                 = time;
            set                  = time; // to catch cases where (set - rise) < resolution
        }
    }
    return access;
}

RiseSetArray
    AccessAnalyzer::find_sensor_to_ground_point_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor, const GroundPoint& groundPoint)
{
    Time rise, set;
    bool insideAccessInterval = false;
    RiseSetArray access;
    const Time start = accessInfo.front().time;
    const Time end   = accessInfo.back().time;
    for (const auto& specificAccessInfo : accessInfo) {
        // Extract
        const Time& time               = specificAccessInfo.time;
        const EciRadiusVec& radius1to2 = specificAccessInfo.radius1to2;
        const bool& isOcculted         = specificAccessInfo.isOcculted;

        // Check if they can see each other
        const Date date          = _startDate + time;
        const bool sensorsInView = isOcculted ? false : sensor.contains(radius1to2, date);

        // Manage bookends
        if (time == start) {
            insideAccessInterval = sensorsInView;
            if (insideAccessInterval) // Consider the start time the initial rise
            {
                rise = start;
            }
            continue;
        }
        else if (time == end) {
            if (insideAccessInterval && sensorsInView) { // Consider the final time the last set
                access.append(rise, end);
                continue;
            }
            // NOTE: this ignores cases where the last time is a rise time -> access analyzed for [0, T)
        }

        // Check for rise/set times
        if (insideAccessInterval && !sensorsInView) { // previous time had access, this time does not -> last time was a set
            insideAccessInterval = false;
            if (rise == set) {
                // Ignore for now - TODO: Make this an input option
                continue;
                // throw std::runtime_error("Rise and set found at the same time. This is likely due to a large time resolution. Please rerun analysis with a finer resolution.")
            }
            access.append(rise, set);
        }
        else if (insideAccessInterval && sensorsInView) { // previous time had access, and so does this one -> store set time and continue
            set = time;
        }
        else if (!insideAccessInterval && sensorsInView) { // previous time didn't have access, this time does -> this time is a rise
            insideAccessInterval = true;
            rise                 = time;
            set                  = time; // to catch cases where (set - rise) < resolution
        }
    }
    return access;
}

bool AccessAnalyzer::is_earth_occulting(const EciRadiusVec& position1, const EciRadiusVec& position2) const
{
    // NOTE: Only checking one direction. Blocking 1->2 automatically means blocking 2->1
    // NOTE: Assumes Earth-centered
    // NOTE: Assumes spherical Earth

    // Also make EciRadiusVec a class with utilities like magnitude, etc.
    const EciRadiusVec nadir1 = -position1;
    const Distance nadir1Mag  = nadir1.norm();

    // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
    const EciRadiusVec radius1to2 = position2 - position1;

    // Get edge angle of Earth
    static const Distance atmosphereHeight = 100.0 * km; // TODO: Generalize for any body?
    static const Distance& radiusEarthMag = _sys->get_body(CelestialBodyId::EARTH)->get_equitorial_radius() + atmosphereHeight;
    const Angle earthLimbAngle = asin(radiusEarthMag / nadir1Mag); // Assume this is good for all angles (circular Earth) - TODO: Fix

    // Get angle from boresight and sat to nadir
    const Angle satelliteNadirAngle = nadir1.offset_angle(radius1to2);

    // If nadir->object angle greater than Earth limb, Earth cannot block
    if (satelliteNadirAngle <= earthLimbAngle) {
        // Satellite is within Earth limb, check which is closer
        const Distance radius1to2Mag  = radius1to2.norm();
        const Distance earthLimbRange = nadir1Mag * cos(earthLimbAngle);

        // If outside farthest Earth limb distance - Earth must be blocking
        if (radius1to2Mag > earthLimbRange + 10.0 * km) { return true; }
    }
    return false;
}


bool AccessAnalyzer::can_objects_ever_access_each_other(const std::size_t& id1, const std::size_t& id2) const
{
    const auto& positions1 = _positionCache.get_platform_positions_by_id(id1);
    const auto& positions2 = _positionCache.get_platform_positions_by_id(id2);

    for (std::size_t ii = 0; ii < positions1.size(); ++ii) {
        if (!is_earth_occulting(positions1[ii], positions2[ii])) { return true; }
    }
    return false;
}

} // namespace trace
} // namespace astrea