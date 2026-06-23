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
#include <numeric>
#include <unordered_set>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

#include <trace/analysis/PositionCache.hpp>
#include <trace/analysis/SpatialIndex.hpp>
#include <trace/platforms/ground/Grid.hpp>
#include <trace/platforms/ground/GroundArchitecture.hpp>
#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/ground/GroundStation.hpp>
#include <trace/platforms/vehicles/Viewer.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {

using namespace astro::frames;
using astro::Cartesian;
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
    Time time;                // Time of access
    EcefRadiusVec radius1to2; // Vector from the first object to the second object at the time of access
    bool isOcculted;          // Flag indicating if the access is occulted
};


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

ViewerRefVec AccessAnalyzer::cache_viewers(ViewerConstellation& constel)
{
    const std::size_t nTimesteps = _dates.size();
    ViewerRefVec viewers;
    viewers.reserve(constel.size());
    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (Viewer& viewer : plane.get_all_spacecraft()) {
                viewers.push_back(std::make_shared<Viewer>(viewer));
                const std::size_t platformIdx = _positionCache.add_platform(viewer.get_id(), nTimesteps);

                for (std::size_t iTime = 0; iTime < nTimesteps; ++iTime) {
                    const auto rEcef = viewer.get_position(_dates[iTime]).in_frame<earth::earth_fixed>(_dates[iTime]);
                    _positionCache.set_position(platformIdx, iTime, rEcef);
                }
            }
        }
    }
    return viewers;
}

GroundStationRefVec AccessAnalyzer::cache_ground_points(GroundArchitecture<astro::planets::Earth>& grounds)
{
    GroundStationRefVec groundStations;
    groundStations.reserve(grounds.size());
    for (auto& ground : grounds) {
        groundStations.push_back(std::make_shared<GroundStation<astro::planets::Earth>>(ground));
        const std::size_t platformIdx = _positionCache.add_platform(ground.get_id(), 1);
        _positionCache.set_position(platformIdx, 0, ground.get_position());
    }
    return groundStations;
}

GroundPointRefVec AccessAnalyzer::cache_ground_points(Grid<astro::planets::Earth>& grid)
{
    GroundPointRefVec groundPoints;
    groundPoints.reserve(grid.size());
    std::size_t gpIdx = 0;
    for (auto& groundPoint : grid) {
        groundPoints.push_back(std::make_shared<GroundPoint<astro::planets::Earth>>(groundPoint));
        const std::size_t platformIdx = _positionCache.add_platform(groundPoint.get_id(), 1);
        _positionCache.set_position(platformIdx, 0, groundPoint.get_position());
        gpIdx++;
    }
    return groundPoints;
}


AccessArray AccessAnalyzer::find_internal_accesses(ViewerConstellation& constel, const bool clearPositionCache)
{
    const std::size_t nViewers = constel.size();

    // Build position cache
    if (clearPositionCache) {
        _positionCache.clear();
        _positionCache.reserve(nViewers);
    }
    ViewerRefVec viewers = cache_viewers(constel);

    // Process access checks in parallel
    AccessArray allAccesses;

    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(nViewers * (nViewers - 1) / 2, "\tSat->Sat Access");

    // Note: Parallel execution requires thread-safe access storage
    for (std::size_t iViewer = 0; iViewer < nViewers - 1; ++iViewer) {
        for (std::size_t jViewer = iViewer + 1; jViewer < nViewers; ++jViewer) {
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
            if (_printProgress) { progressBar(); }
        }
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, GroundArchitecture<astro::planets::Earth>& grounds, const bool includeInternalAccesses)
{
    // https://stackoverflow.com/questions/76230522/equation-for-the-intersection-between-a-cone-and-a-sphere

    const std::size_t nViewers = constel.size();
    const std::size_t nGrounds = grounds.size();

    // Build position cache
    _positionCache.clear();
    _positionCache.reserve(nViewers + nGrounds);

    ViewerRefVec viewers               = cache_viewers(constel);
    GroundStationRefVec groundStations = cache_ground_points(grounds);

    // Internal accesses if requested
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel, false) : AccessArray();

    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(nViewers * nGrounds, "\tSat->Ground Arch Access");

    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
            auto& viewer        = viewers[iViewer];
            auto& groundStation = groundStations[iGround];

            // If the ground station has Sensors, treat it as a SensorPlatform, otherwise, treat it as a GroundPoint
            const bool groundHasSensors = (groundStation->get_payloads().size() > 0);
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
            if (_printProgress) { progressBar(); }
        }
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, Grid<astro::planets::Earth>& grid, const bool includeInternalAccesses)
{
    const std::size_t nViewers = constel.size();
    const std::size_t nGrounds = grid.size();

    // Build spatial index and position cache
    _positionCache.clear();
    _positionCache.reserve(nViewers + nGrounds);

    ViewerRefVec viewers           = cache_viewers(constel);
    GroundPointRefVec groundPoints = cache_ground_points(grid);

    // Internal accesses if requested
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel, false) : AccessArray();

    // Pre-compute ECI boresight per viewer/sensor/timestep
    // Hoists RIC-frame construction out of the O(N_GP) inner loop.
    std::vector<BoresightTable> viewerBoresights(nViewers);
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        viewerBoresights[iViewer] = compute_sensor_boresights(viewers[iViewer]);
    }

    // Build SpatialIndex; skip ground points outside sensor footprint
    SpatialIndex spatialIndex;
    for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
        spatialIndex.add_ground_point(iGround, groundPoints[iGround]->get_latitude(), groundPoints[iGround]->get_longitude());
    }

    // For each viewer, union ground points reachable across all timesteps
    static const Distance rEqEarth = astrea::astro::get_equitorial_radius<astro::planets::Earth>();
    std::vector<std::vector<std::size_t>> viewerCandidates(nViewers);
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        Angle maxHalfAngle = 0.0 * deg;
        for (const auto& sensor : static_cast<SensorPlatform*>(viewers[iViewer].get())->get_payloads()) {
            const FieldOfView* fov = sensor.get_parameters().get_fov();
            if (fov) { maxHalfAngle = std::max(maxHalfAngle, fov->max_half_angle()); }
        }
        if (maxHalfAngle <= 0.0 * deg) { continue; } // no valid sensors

        std::unordered_set<std::size_t> candidateSet;
        const std::size_t viewerId = viewers[iViewer]->get_id();
        for (std::size_t iTime = 0; iTime < _dates.size(); ++iTime) {
            const auto& satPos  = _positionCache.get_position_by_id(viewerId, iTime);
            const Distance satR = satPos.norm();
            // Earth central angle of footprint: rho = asin(R_sat*sin(theta)/rEqEarth) - theta
            const Unitless sinArg       = satR / rEqEarth * sin(maxHalfAngle);
            const Angle footprintRadius = (sinArg >= 1.0 * mp_units::one) ?
                                              (std::numbers::pi / 2.0 * mp_units::angular::unit_symbols::rad) :
                                              (asin(sinArg) - maxHalfAngle);
            const Angle lat             = asin(satPos.get_z() / satR);
            const Angle lon             = atan2(satPos.get_y(), satPos.get_x());
            const auto nearby           = spatialIndex.get_nearby_ground_points(lat, lon, footprintRadius + 1.0 * deg);
            candidateSet.insert(nearby.begin(), nearby.end());
        }
        viewerCandidates[iViewer].assign(candidateSet.begin(), candidateSet.end());
    }

    // Build flat work-item list from candidate pairs
    struct PairResult {
        RiseSetArray platformAccess;
        std::vector<std::pair<std::size_t, RiseSetArray>> sensorAccesses; // (sensorIdx, access)
    };

    std::vector<std::pair<std::size_t, std::size_t>> workItems;
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        for (const std::size_t iGround : viewerCandidates[iViewer]) {
            workItems.emplace_back(iViewer, iGround);
        }
    }

    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(workItems.size(), "\tSat->Grid Access");

    // Parallel compute
    std::vector<PairResult> results(workItems.size());
    std::vector<std::size_t> indices(workItems.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par, indices.begin(), indices.end(), [&](std::size_t idx) {
        const auto& [iViewer, iGround] = workItems[idx];
        auto& viewer                   = viewers[iViewer];
        auto& groundPoint              = groundPoints[iGround];

        // Opt 3: fast ground-point occlusion (dot-product elevation check)
        const std::vector<AccessInfo> accessInfo = build_access_info(viewer->get_id(), groundPoint->get_id(), true);

        PairResult& result  = results[idx];
        std::size_t iSensor = 0;
        for (const auto& sensor : static_cast<SensorPlatform*>(viewer.get())->get_payloads()) {
            const FieldOfView* fov = sensor.get_parameters().get_fov();
            if (fov) {
                // Opt 1 + Opt 4: pre-computed boresight, dot-product FOV check
                const RiseSetArray sensorAccess =
                    find_sensor_accesses_precomputed(accessInfo, viewerBoresights[iViewer][iSensor], fov);
                if (sensorAccess.size() > 0) {
                    result.platformAccess |= sensorAccess;
                    result.sensorAccesses.emplace_back(iSensor, sensorAccess);
                }
            }
            ++iSensor;
        }
    });

    // ---- Sequential apply: write results to platform objects ----
    for (std::size_t idx = 0; idx < workItems.size(); ++idx) {
        const auto& [iViewer, iGround] = workItems[idx];
        auto& viewer                   = viewers[iViewer];
        auto& groundPoint              = groundPoints[iGround];
        PairResult& result             = results[idx];

        if (result.platformAccess.size() > 0) {
            const std::size_t viewerId = viewer->get_id();
            const std::size_t groundId = groundPoint->get_id();

            viewer->add_access(groundId, result.platformAccess);
            groundPoint->add_access(viewerId, result.platformAccess);
            allAccesses[viewerId, groundId] = result.platformAccess;

            auto& sensors = static_cast<SensorPlatform*>(viewer.get())->get_payloads();
            for (const auto& [iSensor, sensorAccess] : result.sensorAccesses) {
                sensors[iSensor].add_access(groundId, sensorAccess);
                groundPoint->add_access(sensors[iSensor].get_id(), sensorAccess);
            }
        }
        if (_printProgress) { progressBar(); }
    }

    return allAccesses;
}

std::vector<AccessInfo> AccessAnalyzer::build_access_info(const std::size_t& id1, const std::size_t& id2, const bool groundPointTarget) const
{
    std::vector<AccessInfo> accessInfo;
    accessInfo.reserve(_dates.size());

    if (groundPointTarget) {
        // Fast path for ground points: the position is fixed, so pre-compute the
        // squared magnitude once and use a dot-product elevation check at each
        // timestep instead of the expensive asin/acos in is_central_body_occulting.
        // Satellite is above the local horizon at groundPos iff
        //   dot(groundPos, satPos) >= dot(groundPos, groundPos)
        // which is equivalent to elevation angle >= 0.
        const auto& groundPos = _positionCache.get_position_by_id(id2, 0);
        const auto gpDotGp    = groundPos.dot(groundPos);
        for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
            const auto& satPos = _positionCache.get_position_by_id(id1, ii);
            AccessInfo info;
            info.time       = _dates[ii] - _startDate;
            info.radius1to2 = groundPos - satPos;
            info.isOcculted = (satPos.dot(groundPos) < gpDotGp);
            accessInfo.push_back(info);
        }
    }
    else {
        for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
            const auto& pos1 = _positionCache.get_position_by_id(id1, ii);
            const auto& pos2 = _positionCache.get_position_by_id(id2, ii);
            AccessInfo info;
            info.time       = _dates[ii] - _startDate;
            info.radius1to2 = pos2 - pos1;
            info.isOcculted = is_central_body_occulting(pos1, pos2, true);
            accessInfo.push_back(info);
        }
    }
    return accessInfo;
}

BoresightTable AccessAnalyzer::compute_sensor_boresights(std::shared_ptr<SensorPlatform> platform) const
{
    const std::size_t nTimesteps = _dates.size();
    const std::size_t nSensors   = platform->get_payloads().size();
    BoresightTable boresights(nSensors, std::vector<EciRadiusVec>(nTimesteps));

    std::size_t iSensor = 0;
    for (const auto& sensor : platform->get_payloads()) {
        if (sensor.get_parameters().get_fov()) {
            for (std::size_t iTime = 0; iTime < nTimesteps; ++iTime) {
                const auto& date     = _dates[iTime];
                const auto parentPos = platform->get_position(date);
                const auto parentVel = platform->get_velocity(date);
                const auto frame     = astro::frames::dynamic::ric.instantaneous(parentPos, parentVel);
                boresights[iSensor][iTime] = frame.rotate_out_of_this_frame(sensor.get_parameters().get_boresight(), date);
            }
        }
        ++iSensor;
    }
    return boresights;
}

RiseSetArray
    AccessAnalyzer::find_platform_to_platform_accesses(std::shared_ptr<SensorPlatform> platform1, std::shared_ptr<SensorPlatform> platform2, const bool twoWay) const
{
    // Build access info only for potential access windows
    const std::vector<AccessInfo> accessInfo = build_access_info(platform1->get_id(), platform2->get_id());

    // Determine access sensor by sensor
    RiseSetArray platformToPlatformAccesses;
    for (auto& sensor1 : platform1->get_payloads()) {
        for (auto& sensor2 : platform2->get_payloads()) {
            const RiseSetArray sensorAccess = find_sensor_accesses(accessInfo, sensor1, sensor2, twoWay);

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

RiseSetArray AccessAnalyzer::find_platform_to_ground_point_accesses(
    std::shared_ptr<SensorPlatform> platform,
    const std::shared_ptr<GroundPoint<astro::planets::Earth>> groundPoint
) const
{
    // Build access info
    const std::vector<AccessInfo> accessInfo = build_access_info(platform->get_id(), groundPoint->get_id());

    // Determine access sensor by sensor
    RiseSetArray platformToGroundAccesses;
    for (auto& sensor : platform->get_payloads()) {
        const RiseSetArray sensorAccess = find_sensor_accesses(accessInfo, sensor);

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
    AccessAnalyzer::find_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor1, const std::optional<Sensor> sensor2, const bool twoWay) const
{
    Time rise, set;
    bool insideAccessInterval = false;
    RiseSetArray access;
    const Time start = accessInfo.front().time;
    const Time end   = accessInfo.back().time;

    const bool hasSensor2 = sensor2.has_value();
    for (const auto& specificAccessInfo : accessInfo) {
        // Extract
        const Time& time = specificAccessInfo.time;
        const Date date  = _startDate + time;

        const EciRadiusVec& radius1to2 = specificAccessInfo.radius1to2.in_frame<earth::icrf>(date);
        const bool& isOcculted         = specificAccessInfo.isOcculted;

        // Check if they can see each other
        bool sensorsInView = false;
        if (isOcculted) { sensorsInView = false; }
        else {
            sensorsInView = sensor1.contains(radius1to2, date);
            if (hasSensor2) {
                if (twoWay) { sensorsInView = sensorsInView && sensor2->contains(-radius1to2, date); }
                else {
                    sensorsInView = sensorsInView || sensor2->contains(-radius1to2, date);
                }
            }
        }

        // Manage bookends
        if (time == start) {
            insideAccessInterval = sensorsInView;
            if (insideAccessInterval) // Consider the start time the initial rise
            {
                rise = start;
            }
            set = start; // catches a few errors
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
            if (rise >= set) {
                // Ignore for now rise == set
                // TODO: Make this an input option
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

RiseSetArray AccessAnalyzer::find_sensor_accesses_precomputed(
    const std::vector<AccessInfo>& accessInfo,
    const std::vector<EciRadiusVec>& boresightEci,
    const FieldOfView* fov
) const
{
    if (accessInfo.empty()) { return {}; }

    Time rise, set;
    bool insideAccessInterval = false;
    RiseSetArray access;
    const Time start = accessInfo.front().time;
    const Time end   = accessInfo.back().time;

    for (std::size_t iTime = 0; iTime < accessInfo.size(); ++iTime) {
        const auto& specific = accessInfo[iTime];
        const Time& time     = specific.time;
        const Date date      = _startDate + time;

        bool sensorsInView = false;
        if (!specific.isOcculted) {
            const EciRadiusVec radius1to2 = specific.radius1to2.in_frame<earth::icrf>(date);
            sensorsInView                 = fov->contains(boresightEci[iTime], radius1to2);
        }

        if (time == start) {
            insideAccessInterval = sensorsInView;
            if (insideAccessInterval) { rise = start; }
            set = start;
            continue;
        }
        else if (time == end) {
            if (insideAccessInterval && sensorsInView) {
                access.append(rise, end);
                continue;
            }
        }

        if (insideAccessInterval && !sensorsInView) {
            insideAccessInterval = false;
            if (rise >= set) { continue; }
            access.append(rise, set);
        }
        else if (insideAccessInterval && sensorsInView) {
            set = time;
        }
        else if (!insideAccessInterval && sensorsInView) {
            insideAccessInterval = true;
            rise                 = time;
            set                  = time;
        }
    }
    return access;
}

bool AccessAnalyzer::can_objects_ever_access_each_other(const std::size_t& id1, const std::size_t& id2, const bool atmosphereBlocks) const
{
    // in case a ground point with only one position is compared to a viewer with many positions
    for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
        if (!is_central_body_occulting(_positionCache.get_position_by_id(id1, ii), _positionCache.get_position_by_id(id2, ii), atmosphereBlocks)) {
            return true;
        }
    }
    return false;
}

bool AccessAnalyzer::is_central_body_occulting(const EcefRadiusVec& position1, const EcefRadiusVec& position2, const bool atmosphereBlocks) const
{
    // NOTE: Only checking one direction. Blocking 1->2 automatically means blocking 2->1
    // NOTE: Assumes spherical central body

    // Also make EciRadiusVec a class with utilities like magnitude, etc.
    const EcefRadiusVec nadir1 = -position1;
    const Distance nadir1Mag   = nadir1.norm();

    // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
    const EcefRadiusVec radius1to2 = position2 - position1;

    // Get edge angle of Earth
    const Distance atmosphereHeight =
        atmosphereBlocks ? astrea::astro::get_crash_radius<astro::planets::Earth>() : Distance::zero();
    const Distance radiusEarthMag = astrea::astro::get_equitorial_radius<astro::planets::Earth>() + atmosphereHeight;
    const Angle earthLimbAngle = asin(radiusEarthMag / nadir1Mag); // Assume this is good for all angles (circular Earth) - TODO: Fix

    // Get angle from boresight and sat to nadir
    const Angle satelliteNadirAngle = nadir1.offset_angle(radius1to2);

    // If nadir->object angle greater than Earth limb, Earth cannot block
    if (satelliteNadirAngle <= earthLimbAngle) {
        // Satellite is within Earth limb, check which is closer
        const Distance radius1to2Mag  = radius1to2.norm();
        const Distance earthLimbRange = nadir1Mag * cos(earthLimbAngle);

        // If outside farthest Earth limb distance - Earth must be blocking
        // the 1km is to avoid floating point errors
        if (radius1to2Mag > earthLimbRange + 1.0 * km) { return true; }
    }
    return false;
}


} // namespace trace
} // namespace astrea