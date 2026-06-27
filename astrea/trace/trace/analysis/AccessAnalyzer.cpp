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
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;


struct AccessInfo {
    Time time;                // Time of access
    EcefRadiusVec radius1to2; // Vector from the first object to the second object at the time of access
    bool isOcculted;          // Flag indicating if the access is occulted
};

/// Per-viewer result for one (viewer, ground-point) work item.
struct PairResult {
    RiseSetArray platformAccess;                                      ///< Union over all sensors
    std::vector<std::pair<std::size_t, RiseSetArray>> sensorAccesses; ///< (sensor_idx, access_windows)
};

namespace {

/// Earth central angle (rho) from the sub-satellite point to the edge of the sensor
/// footprint at elevation = 0, using the sine rule on the (Earth centre, satellite,
/// footprint-edge) triangle:  rho = arcsin(R_sat * sin(theta) / R_earth) - theta.
/// Returns pi/2 if the geometry is degenerate (sinArg >= 1).
Angle footprint_earth_central_angle(const Distance satR, const Angle halfConeAngle, const Distance rEarth)
{
    const Unitless sinArg = satR / rEarth * sin(halfConeAngle);
    if (sinArg >= 1.0 * mp_units::one) { return std::numbers::pi / 2.0 * rad; }
    return asin(sinArg) - halfConeAngle;
}

/// Maximum off-boresight half-angle across all sensors on a platform.
/// Returns 0 rad when no sensor has a valid FOV.
Angle max_sensor_half_angle(const std::shared_ptr<Viewer>& viewer)
{
    Angle maxAngle = Angle::zero();
    for (const auto& sensor : static_cast<SensorPlatform*>(viewer.get())->get_payloads()) {
        const FieldOfView* fov = sensor.get_parameters().get_fov();
        if (fov) { maxAngle = std::max(maxAngle, fov->max_half_angle()); }
    }
    return maxAngle;
}

/// Converts a flat (time, inView) visibility sequence into rise/set intervals.
/// Handles the bookend conditions at t=start and t=end.
RiseSetArray compute_rise_sets(const std::vector<std::pair<Time, bool>>& visibility)
{
    if (visibility.empty()) { return {}; }

    Time rise, set;
    bool insideAccess = false;
    RiseSetArray access;
    const Time start = visibility.front().first;
    const Time end   = visibility.back().first;

    for (const auto& [time, inView] : visibility) {
        if (time == start) {
            insideAccess = inView;
            if (insideAccess) { rise = start; }
            set = start;
            continue;
        }
        // At the final sample: close any open interval and stop.
        if (time == end && insideAccess && inView) {
            access.append(rise, end);
            continue;
        }

        if (insideAccess && !inView) {
            insideAccess = false;
            if (rise < set) { access.append(rise, set); } // skip zero-duration intervals
        }
        else if (insideAccess) {
            set = time;
        }
        else if (inView) {
            insideAccess = true;
            rise = set = time;
        }
    }
    return access;
}

} // anonymous namespace


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

    // Note: Parallel execution requires thread-safe access storage
    utilities::ProgressBar progressBar(nViewers * (nViewers - 1) / 2, "\tSat->Sat Access");
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
    if (_printProgress) { std::cout << std::endl; }

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
    if (_printProgress) { std::cout << std::endl; }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, Grid<astro::planets::Earth>& grid, const bool includeInternalAccesses)
{
    const std::size_t nViewers = constel.size();
    const std::size_t nGrounds = grid.size();

    _positionCache.clear();
    _positionCache.reserve(nViewers + nGrounds);

    ViewerRefVec viewers           = cache_viewers(constel);
    GroundPointRefVec groundPoints = cache_ground_points(grid);

    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel, false) : AccessArray();

    // Pre-compute ECI boresight per viewer/sensor/timestep.
    // Hoists RIC-frame construction out of the O(N_GP) inner loop.
    std::vector<BoresightTable> viewerBoresights(nViewers);
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        viewerBoresights[iViewer] = compute_sensor_boresights(viewers[iViewer]);
    }

    // Spatial culling: restrict (viewer, ground) work to pairs where the ground point
    // falls within the satellite's sensor footprint somewhere along its ground track.
    const SpatialIndex spatialIndex(groundPoints);
    const auto candidates = compute_candidate_ground_points(viewers, spatialIndex);

    // Flatten candidate pairs into a linear work list for parallel dispatch.
    std::vector<std::pair<std::size_t, std::size_t>> workItems;
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        for (const std::size_t iGround : candidates[iViewer]) {
            workItems.emplace_back(iViewer, iGround);
        }
    }

    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(workItems.size(), "\tSat->Grid Access");

    // Parallel access computation — each work item writes to a unique index, no locking needed.
    std::vector<PairResult> results(workItems.size());
    std::vector<std::size_t> indices(workItems.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::for_each(std::execution::par, indices.begin(), indices.end(), [&](std::size_t idx) {
        const auto& [iViewer, iGround] = workItems[idx];
        const auto accessInfo = build_ground_access_info(viewers[iViewer]->get_id(), groundPoints[iGround]->get_id());

        PairResult& result  = results[idx];
        std::size_t iSensor = 0;
        for (const auto& sensor : static_cast<SensorPlatform*>(viewers[iViewer].get())->get_payloads()) {
            const FieldOfView* fov = sensor.get_parameters().get_fov();
            if (fov) {
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

    // Sequential apply: write computed results to platform objects and the output map.
    for (std::size_t idx = 0; idx < workItems.size(); ++idx) {
        const auto& [iViewer, iGround] = workItems[idx];
        PairResult& result             = results[idx];

        if (result.platformAccess.size() > 0) {
            auto& viewer      = viewers[iViewer];
            auto& groundPoint = groundPoints[iGround];
            auto& sensors     = static_cast<SensorPlatform*>(viewer.get())->get_payloads();

            const std::size_t viewerId = viewer->get_id();
            const std::size_t groundId = groundPoint->get_id();

            viewer->add_access(groundId, result.platformAccess);
            groundPoint->add_access(viewerId, result.platformAccess);
            allAccesses[viewerId, groundId] = result.platformAccess;

            for (const auto& [iSensor, sensorAccess] : result.sensorAccesses) {
                sensors[iSensor].add_access(groundId, sensorAccess);
                groundPoint->add_access(sensors[iSensor].get_id(), sensorAccess);
            }
        }
        if (_printProgress) { progressBar(); }
    }

    return allAccesses;
}

std::vector<AccessInfo> AccessAnalyzer::build_access_info(const std::size_t& id1, const std::size_t& id2) const
{
    std::vector<AccessInfo> accessInfo;
    accessInfo.reserve(_dates.size());
    for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
        const auto& pos1 = _positionCache.get_position_by_id(id1, ii);
        const auto& pos2 = _positionCache.get_position_by_id(id2, ii);
        AccessInfo info;
        info.time       = _dates[ii] - _startDate;
        info.radius1to2 = pos2 - pos1;
        info.isOcculted = is_central_body_occulting(pos1, pos2, true);
        accessInfo.push_back(info);
    }
    return accessInfo;
}

std::vector<AccessInfo> AccessAnalyzer::build_ground_access_info(const std::size_t& satId, const std::size_t& gpId) const
{
    // Fast path for satellite-to-surface-point access: the ground position is fixed, so
    // pre-compute dot(gp, gp) once and check each timestep with the cheap elevation test
    //   dot(satPos, gpPos) >= dot(gpPos, gpPos)  ⟺  elevation >= 0°
    // This avoids the asin/acos calls inside is_central_body_occulting.
    const auto& groundPos = _positionCache.get_position_by_id(gpId, 0);
    const auto gpDotGp    = groundPos.dot(groundPos);

    std::vector<AccessInfo> accessInfo;
    accessInfo.reserve(_dates.size());
    for (std::size_t ii = 0; ii < _dates.size(); ++ii) {
        const auto& satPos = _positionCache.get_position_by_id(satId, ii);
        AccessInfo info;
        info.time       = _dates[ii] - _startDate;
        info.radius1to2 = groundPos - satPos;
        info.isOcculted = (satPos.dot(groundPos) < gpDotGp);
        accessInfo.push_back(info);
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

std::vector<std::vector<std::size_t>>
    AccessAnalyzer::compute_candidate_ground_points(const ViewerRefVec& viewers, const SpatialIndex& spatialIndex) const
{
    static const Distance rEqEarth = astrea::astro::get_equitorial_radius<astro::planets::Earth>();
    const std::size_t nViewers     = viewers.size();

    std::vector<std::vector<std::size_t>> candidates(nViewers);
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        const Angle maxHalfAngle = max_sensor_half_angle(viewers[iViewer]);
        if (maxHalfAngle <= 0.0 * deg) { continue; }

        std::unordered_set<std::size_t> candidateSet;
        const std::size_t viewerId = viewers[iViewer]->get_id();
        for (std::size_t iTime = 0; iTime < _dates.size(); ++iTime) {
            const auto& satPos    = _positionCache.get_position_by_id(viewerId, iTime);
            const Distance satR   = satPos.norm();
            const Angle footprint = footprint_earth_central_angle(satR, maxHalfAngle, rEqEarth);
            const Angle lat       = asin(satPos.get_z() / satR);
            const Angle lon       = atan2(satPos.get_y(), satPos.get_x());
            const auto nearby     = spatialIndex.get_nearby_ground_points(lat, lon, footprint + 1.0 * deg);
            candidateSet.insert(nearby.begin(), nearby.end());
        }
        candidates[iViewer].assign(candidateSet.begin(), candidateSet.end());
    }
    return candidates;
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
    if (accessInfo.empty()) { return {}; }
    const bool hasSensor2 = sensor2.has_value();

    std::vector<std::pair<Time, bool>> visibility;
    visibility.reserve(accessInfo.size());
    for (const auto& info : accessInfo) {
        const Date date          = _startDate + info.time;
        const EciRadiusVec r1to2 = info.radius1to2.in_frame<earth::icrf>(date);
        bool inView              = false;
        if (!info.isOcculted) {
            inView = sensor1.contains(r1to2, date);
            if (hasSensor2) {
                if (twoWay) { inView = inView && sensor2->contains(-r1to2, date); }
                else {
                    inView = inView || sensor2->contains(-r1to2, date);
                }
            }
        }
        visibility.emplace_back(info.time, inView);
    }
    return compute_rise_sets(visibility);
}

RiseSetArray AccessAnalyzer::find_sensor_accesses_precomputed(
    const std::vector<AccessInfo>& accessInfo,
    const std::vector<EciRadiusVec>& boresightEci,
    const FieldOfView* fov
) const
{
    if (accessInfo.empty()) { return {}; }

    std::vector<std::pair<Time, bool>> visibility;
    visibility.reserve(accessInfo.size());
    for (std::size_t iTime = 0; iTime < accessInfo.size(); ++iTime) {
        const auto& info = accessInfo[iTime];
        bool inView      = false;
        if (!info.isOcculted) {
            const Date date          = _startDate + info.time;
            const EciRadiusVec r1to2 = info.radius1to2.in_frame<earth::icrf>(date);
            inView                   = fov->contains(boresightEci[iTime], r1to2);
        }
        visibility.emplace_back(info.time, inView);
    }
    return compute_rise_sets(visibility);
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