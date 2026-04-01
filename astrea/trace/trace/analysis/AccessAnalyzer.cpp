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
#include <array>
#include <cmath>
#include <cstdint>
#include <execution>
#include <limits>
#include <optional>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <astro/frames/dynamic_frames.hpp>
#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>
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
#include <trace/platforms/vehicles/Viewer.hpp>
#include <trace/types/typedefs.hpp>

namespace astrea {

using namespace astro::frames;
using astro::AstrodynamicsSystem;
using astro::Cartesian;
using astro::CelestialBodyId;
using astro::Date;
using astro::Geodetic;
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

namespace {

class ChannelAccumulator {
  public:
    ChannelAccumulator(const std::size_t nChannels, const Time& start, const Time& end) :
        _channelAccesses(nChannels),
        _insideInterval(nChannels, 0u),
        _riseTimes(nChannels, 0.0 * s),
        _setTimes(nChannels, 0.0 * s),
        _start(start),
        _end(end)
    {
    }

    void record(const std::size_t channelIdx, const Time& time, const bool inView)
    {
        if (time == _start) {
            _insideInterval[channelIdx] = static_cast<uint8_t>(inView);
            if (inView) { _riseTimes[channelIdx] = _start; }
            _setTimes[channelIdx] = _start;
            return;
        }
        else if (time == _end) {
            if ((_insideInterval[channelIdx] != 0u) && inView) {
                _channelAccesses[channelIdx].append(_riseTimes[channelIdx], _end);
                _insideInterval[channelIdx] = 0u;
                return;
            }
            if ((_insideInterval[channelIdx] != 0u) && !inView) {
                _insideInterval[channelIdx] = 0u;
                if (_riseTimes[channelIdx] < _setTimes[channelIdx]) {
                    _channelAccesses[channelIdx].append(_riseTimes[channelIdx], _setTimes[channelIdx]);
                }
            }
            return;
        }

        if ((_insideInterval[channelIdx] != 0u) && !inView) {
            _insideInterval[channelIdx] = 0u;
            if (_riseTimes[channelIdx] < _setTimes[channelIdx]) {
                _channelAccesses[channelIdx].append(_riseTimes[channelIdx], _setTimes[channelIdx]);
            }
        }
        else if ((_insideInterval[channelIdx] != 0u) && inView) {
            _setTimes[channelIdx] = time;
        }
        else if ((_insideInterval[channelIdx] == 0u) && inView) {
            _insideInterval[channelIdx] = 1u;
            _riseTimes[channelIdx]      = time;
            _setTimes[channelIdx]       = time;
        }
    }

    void record_all_false(const Time& time)
    {
        for (std::size_t channelIdx = 0; channelIdx < _channelAccesses.size(); ++channelIdx) {
            record(channelIdx, time, false);
        }
    }

    void record_false_range(const std::size_t startIdx, const std::size_t endIdx, const Time& time)
    {
        for (std::size_t channelIdx = startIdx; channelIdx < endIdx; ++channelIdx) {
            record(channelIdx, time, false);
        }
    }

    const RiseSetArray& access(const std::size_t channelIdx) const { return _channelAccesses[channelIdx]; }

  private:
    std::vector<RiseSetArray> _channelAccesses;
    std::vector<uint8_t> _insideInterval;
    std::vector<Time> _riseTimes;
    std::vector<Time> _setTimes;
    Time _start;
    Time _end;
};

template <typename GroundRefVec>
Angle estimate_grid_spacing(const GroundRefVec& grounds)
{
    if (grounds.size() < 2) { return 1.0 * deg; }

    Angle minPositiveDelta = 360.0 * deg;
    for (std::size_t ii = 0; ii < grounds.size(); ++ii) {
        const Angle lat1 = grounds[ii]->get_latitude();
        const Angle lon1 = grounds[ii]->get_longitude();
        for (std::size_t jj = ii + 1; jj < grounds.size(); ++jj) {
            const Angle lat2 = grounds[jj]->get_latitude();
            const Angle lon2 = grounds[jj]->get_longitude();
            const Angle d    = sqrt((lat1 - lat2) * (lat1 - lat2) + (lon1 - lon2) * (lon1 - lon2));
            if ((d > 0.0 * deg) && (d < minPositiveDelta)) { minPositiveDelta = d; }
        }
    }

    if (minPositiveDelta <= 0.0 * deg) { return 1.0 * deg; }
    return minPositiveDelta;
}

template <typename GroundRefVec>
void build_ground_search_order(
    const GroundRefVec& grounds,
    const Angle& seedLat,
    const Angle& seedLon,
    std::vector<std::pair<Angle, std::size_t>>& groundOrder,
    std::vector<uint8_t>& visitedGround
)
{
    std::fill(visitedGround.begin(), visitedGround.end(), 0u);
    groundOrder.clear();
    if (grounds.empty()) { return; }

    for (std::size_t iGround = 0; iGround < grounds.size(); ++iGround) {

        // Angular distance from the seed point
        const Angle latDiff = abs(grounds[iGround]->get_latitude() - seedLat);
        const Angle lonDiff = abs(grounds[iGround]->get_longitude() - seedLon);
        const Angle dist    = sqrt(latDiff * latDiff + lonDiff * lonDiff);

        // Exclude anything on the opposite side of the earth
        if (latDiff > 90.0 * deg || lonDiff > 90.0 * deg) { continue; }

        groundOrder.emplace_back(dist, iGround);
    }

    std::sort(groundOrder.begin(), groundOrder.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
    });
}

std::optional<Geodetic>
    boresight_ground_intersection(const Viewer& viewer, const Sensor& sensor, const Date& date, const EcefRadiusVec& viewerPosition, const astro::CelestialBody* centralBody)
{
    const astro::frames::dynamic::ric ricFrame(&viewer);
    const auto boresightRic  = sensor.get_parameters().get_boresight();
    const auto boresightEci  = ricFrame.rotate_out_of_this_frame(boresightRic, date);
    const auto boresightEcef = boresightEci.in_frame<earth::earth_fixed>(date);

    const auto a = boresightEcef.dot(boresightEcef);
    if (a <= 0.0 * pow<2>(km)) { return std::nullopt; }

    const Distance radius = centralBody->get_equitorial_radius();
    const auto pDotD      = viewerPosition.dot(boresightEcef);
    const auto pDotP      = viewerPosition.dot(viewerPosition);
    const auto b          = 2.0 * pDotD;
    const auto c          = pDotP - radius * radius;

    const auto discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0 * pow<4>(km)) { return std::nullopt; }

    const auto sqrtDisc = sqrt(discriminant);
    const auto t1       = (-b - sqrtDisc) / (2.0 * a);
    const auto t2       = (-b + sqrtDisc) / (2.0 * a);

    Unitless t                   = t1;
    bool hasPositiveIntersection = false;
    if (t1 > 0.0 * one) {
        t                       = t1;
        hasPositiveIntersection = true;
    }
    if (t2 > 0.0 * one) {
        if (!hasPositiveIntersection || t2 < t) { t = t2; }
        hasPositiveIntersection = true;
    }
    if (!hasPositiveIntersection) { return std::nullopt; }

    const EcefRadiusVec intersection = viewerPosition + boresightEcef * t;
    return Geodetic(intersection, centralBody);
}

} // namespace


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
                    const auto rEcef = viewer.get_inertial_position(_dates[iTime]).in_frame<earth::earth_fixed>(_dates[iTime]);
                    _positionCache.set_position(platformIdx, iTime, rEcef);
                }
            }
        }
    }
    return viewers;
}

GroundStationRefVec AccessAnalyzer::cache_ground_points(GroundArchitecture& grounds)
{
    GroundStationRefVec groundStations;
    groundStations.reserve(grounds.size());
    for (auto& ground : grounds) {
        groundStations.push_back(std::make_shared<GroundStation>(ground));
        const std::size_t platformIdx = _positionCache.add_platform(ground.get_id(), 1);
        _positionCache.set_position(platformIdx, 0, ground.get_position());
    }
    return groundStations;
}

GroundPointRefVec AccessAnalyzer::cache_ground_points(Grid& grid)
{
    GroundPointRefVec groundPoints;
    groundPoints.reserve(grid.size());
    std::size_t gpIdx = 0;
    for (auto& groundPoint : grid) {
        groundPoints.push_back(std::make_shared<GroundPoint>(groundPoint));
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

    const std::size_t nPairs = (nViewers > 1) ? (nViewers * (nViewers - 1) / 2) : 0;
    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(nPairs, "\tSat->Sat Access");

    // Note: Parallel execution requires thread-safe access storage
    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
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

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const bool includeInternalAccesses, const bool twoWay)
{
    const std::size_t nViewers = constel.size();
    const std::size_t nGrounds = grounds.size();

    // Build position cache
    _positionCache.clear();
    _positionCache.reserve(nViewers + nGrounds);

    ViewerRefVec viewers               = cache_viewers(constel);
    GroundStationRefVec groundStations = cache_ground_points(grounds);

    // Internal accesses if requested
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel, false) : AccessArray();

    if (nViewers == 0 || nGrounds == 0) { return allAccesses; }

    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(nViewers, "\tSat->Ground Arch Access");

    const Time start = _dates.front() - _startDate;
    const Time end   = _dates.back() - _startDate;

    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        auto& viewer               = viewers[iViewer];
        const std::size_t viewerId = viewer->get_id();

        auto& viewerSensors        = static_cast<SensorPlatform&>(*viewer).get_payloads();
        const std::size_t nSensors = viewerSensors.size();

        if (nSensors == 0) {
            if (_printProgress) { progressBar(); }
            continue;
        }

        // Build per-ground channel layout.
        std::vector<uint8_t> groundHasSensors(nGrounds, 0u);
        std::vector<std::size_t> nGroundSensors(nGrounds, 0);
        std::vector<std::size_t> channelOffsets(nGrounds + 1, 0);
        for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
            const auto& groundSensors = static_cast<SensorPlatform&>(*groundStations[iGround]).get_payloads();
            const std::size_t nGs     = groundSensors.size();

            groundHasSensors[iGround] = static_cast<uint8_t>(nGs > 0);
            nGroundSensors[iGround]   = nGs;
            channelOffsets[iGround + 1] = channelOffsets[iGround] + (groundHasSensors[iGround] ? (nSensors * nGs) : nSensors);
        }
        const std::size_t nChannels = channelOffsets.back();
        ChannelAccumulator channels(nChannels, start, end);
        std::vector<uint8_t> visitedGround(nGrounds, 0u);

        // Loop through each time step and check access to each ground station
        for (std::size_t iTime = 0; iTime < _dates.size(); ++iTime) {
            const Date date = _dates[iTime];
            const Time time = date - _startDate;

            const EcefRadiusVec& viewerPosition = _positionCache.get_position_by_id(viewerId, iTime);

            for (std::size_t iSensor = 0; iSensor < nSensors; ++iSensor) {

                for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {

                    // Check visibility for this ground station
                    const std::size_t baseChannelIdx = channelOffsets[iGround];
                    const auto groundId              = groundStations[iGround]->get_id();
                    const auto& groundPosition       = _positionCache.get_position_by_id(groundId, 0);
                    const bool occulted              = is_central_body_occulting(viewerPosition, groundPosition, true);

                    // If the ground station has no sensors, we can record visibility with a single check. Otherwise, we
                    // may need to check each sensor on the ground station.
                    if (!groundHasSensors[iGround]) {
                        bool inView = false;
                        if (!occulted) {
                            const EciRadiusVec viewerToGround = (groundPosition - viewerPosition).in_frame<earth::icrf>(date);
                            inView = viewerSensors[iSensor].contains(viewerToGround, date);
                        }
                        channels.record(baseChannelIdx + iSensor, time, inView);
                    }
                    else {
                        auto& groundSensors = static_cast<SensorPlatform&>(*groundStations[iGround]).get_payloads();
                        const std::size_t startIdx = baseChannelIdx + iSensor * nGroundSensors[iGround];

                        if (occulted) {
                            channels.record_false_range(startIdx, startIdx + nGroundSensors[iGround], time);
                        }
                        else {
                            const EciRadiusVec viewerToGround = (groundPosition - viewerPosition).in_frame<earth::icrf>(date);
                            const bool viewerSeesGround = viewerSensors[iSensor].contains(viewerToGround, date);
                            for (std::size_t jSensor = 0; jSensor < nGroundSensors[iGround]; ++jSensor) {
                                const bool groundSeesViewer = groundSensors[jSensor].contains(-viewerToGround, date);

                                const bool inView = (twoWay) ? (viewerSeesGround && groundSeesViewer) :
                                                               (viewerSeesGround || groundSeesViewer);

                                channels.record(startIdx + jSensor, time, inView);
                            }
                        }
                    }

                    visitedGround[iGround] = 1u;
                }

                for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
                    if (visitedGround[iGround] != 0u) { continue; }

                    const std::size_t baseChannelIdx = channelOffsets[iGround];
                    if (!groundHasSensors[iGround]) { channels.record(baseChannelIdx + iSensor, time, false); }
                    else {
                        const std::size_t startIdx = baseChannelIdx + iSensor * nGroundSensors[iGround];
                        channels.record_false_range(startIdx, startIdx + nGroundSensors[iGround], time);
                    }
                }
            }
        }

        // Store accesses.
        for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
            RiseSetArray satAccess;

            auto& groundStation          = groundStations[iGround];
            const std::size_t groundId   = groundStation->get_id();
            const std::size_t baseOffset = channelOffsets[iGround];

            if (!groundHasSensors[iGround]) {
                for (std::size_t iSensor = 0; iSensor < nSensors; ++iSensor) {
                    const RiseSetArray& sensorAccess = channels.access(baseOffset + iSensor);
                    if (sensorAccess.size() > 0) {
                        satAccess |= sensorAccess;
                        viewerSensors[iSensor].add_access(groundId, sensorAccess);
                        groundStation->add_access(viewerSensors[iSensor].get_id(), sensorAccess);
                    }
                }

                if (satAccess.size() > 0) {
                    viewer->add_access(groundId, satAccess);
                    groundStation->add_access(viewerId, satAccess);
                    allAccesses[viewerId, groundId] = satAccess;
                }
            }
            else {
                auto& groundSensors = static_cast<SensorPlatform&>(*groundStation).get_payloads();
                for (std::size_t iSensor1 = 0; iSensor1 < nSensors; ++iSensor1) {
                    for (std::size_t jSensor = 0; jSensor < nGroundSensors[iGround]; ++jSensor) {
                        const std::size_t channelIdx     = baseOffset + iSensor1 * nGroundSensors[iGround] + jSensor;
                        const RiseSetArray& sensorAccess = channels.access(channelIdx);

                        if (sensorAccess.size() > 0) {
                            satAccess |= sensorAccess;
                            viewerSensors[iSensor1].add_access(groundSensors[jSensor].get_id(), sensorAccess);
                            groundSensors[jSensor].add_access(viewerSensors[iSensor1].get_id(), sensorAccess);
                        }
                    }
                }

                if (satAccess.size() > 0) {
                    viewer->add_access(groundId, satAccess);
                    groundStation->add_access(viewerId, satAccess);
                    allAccesses[viewerId, groundId] = satAccess;
                    allAccesses[groundId, viewerId] = satAccess;
                }
            }
        }

        if (_printProgress) { progressBar(); }
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, Grid& grid, const bool includeInternalAccesses)
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

    if (nViewers == 0 || nGrounds == 0) { return allAccesses; }

    const Angle gridSpacingEstimate = estimate_grid_spacing(groundPoints);

    if (_printProgress) { std::cout << std::endl; }
    utilities::ProgressBar progressBar(nViewers, "\tSat->Grid Access");

    const Time start = _dates.front() - _startDate;
    const Time end   = _dates.back() - _startDate;

    for (std::size_t iViewer = 0; iViewer < nViewers; ++iViewer) {
        auto& viewer                = viewers[iViewer];
        const std::size_t viewerId  = viewer->get_id();
        auto& viewerSensors         = static_cast<SensorPlatform&>(*viewer).get_payloads();
        const std::size_t nSensors  = viewerSensors.size();
        const std::size_t nChannels = nSensors * nGrounds;

        if (nSensors == 0) {
            if (_printProgress) { progressBar(); }
            continue;
        }

        ChannelAccumulator channels(nChannels, start, end);
        std::vector<std::pair<Angle, std::size_t>> groundOrder;
        groundOrder.reserve(nGrounds);
        std::vector<uint8_t> visited(nGrounds, 0u);

        for (std::size_t iTime = 0; iTime < _dates.size(); ++iTime) {
            const Date date = _dates[iTime];
            const Time time = date - _startDate;

            const EcefRadiusVec& viewerPosition = _positionCache.get_position_by_id(viewerId, iTime);

            for (std::size_t iSensor = 0; iSensor < nSensors; ++iSensor) {
                const std::size_t channelStart = iSensor * nGrounds;
                const std::size_t channelEnd   = channelStart + nGrounds;

                const auto boresightLla = boresight_ground_intersection(
                    *viewer, viewerSensors[iSensor], date, viewerPosition, _sys->get_central_body().get()
                );

                if (!boresightLla.has_value()) {
                    channels.record_false_range(channelStart, channelEnd, time);
                    std::cout << "Warning: Sensor " << viewerSensors[iSensor].get_id() << " on Viewer " << viewerId
                              << " has no valid boresight intersection at time " << date
                              << ". Marking all ground points as not visible for this sensor and time." << std::endl;
                    continue;
                }

                const Angle seedLat = boresightLla->get_latitude();
                const Angle seedLon = boresightLla->get_longitude();
                build_ground_search_order(groundPoints, seedLat, seedLon, groundOrder, visited);

                bool sawVisible     = false;
                bool binHadVisible  = false;
                std::size_t prevBin = std::numeric_limits<std::size_t>::max();

                for (const auto& [dist, iGround] : groundOrder) {
                    const std::size_t channelIdx = channelStart + iGround;
                    const double binDistance     = (dist / gridSpacingEstimate).numerical_value_in(one);
                    const std::size_t bin        = static_cast<std::size_t>(std::floor(std::max(0.0, binDistance)));

                    if (prevBin != std::numeric_limits<std::size_t>::max() && bin != prevBin) {
                        if (sawVisible && !binHadVisible) {
                            std::cout << "Warning: Viewer " << viewerId << " Sensor " << viewerSensors[iSensor].get_id()
                                      << " sees a ground point at distance "
                                      << dist << " but all closer points are not visible. This may indicate an issue with the sensor model or position data."
                                      << std::endl;
                            break;
                        }
                        binHadVisible = false;
                    }
                    prevBin = bin;

                    const auto groundId        = groundPoints[iGround]->get_id();
                    const auto& groundPosition = _positionCache.get_position_by_id(groundId, 0);
                    const bool occulted        = is_central_body_occulting(viewerPosition, groundPosition, false);
                    bool inView                = false;
                    if (!occulted) {
                        const EciRadiusVec viewerToGround = (groundPosition - viewerPosition).in_frame<earth::icrf>(date);
                        inView = viewerSensors[iSensor].contains(viewerToGround, date);
                    }

                    channels.record(channelIdx, time, inView);
                    visited[iGround] = 1u;

                    if (inView) {
                        sawVisible    = true;
                        binHadVisible = true;
                    }
                }

                for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
                    if (visited[iGround] == 0u) { channels.record(channelStart + iGround, time, false); }
                }
            }
        }

        // Store accesses
        for (std::size_t iGround = 0; iGround < nGrounds; ++iGround) {
            RiseSetArray satAccess;
            const auto& groundPoint         = groundPoints[iGround];
            const std::size_t groundPointId = groundPoint->get_id();

            for (std::size_t iSensor = 0; iSensor < nSensors; ++iSensor) {
                const std::size_t channelIdx       = iSensor * nGrounds + iGround;
                const RiseSetArray& sensorAccesses = channels.access(channelIdx);

                if (sensorAccesses.size() > 0) {
                    satAccess |= sensorAccesses;
                    viewerSensors[iSensor].add_access(groundPointId, sensorAccesses);
                    groundPoint->add_access(viewerSensors[iSensor].get_id(), sensorAccesses);
                }
            }

            if (satAccess.size() > 0) {
                viewer->add_access(groundPointId, satAccess);
                groundPoint->add_access(viewerId, satAccess);
                allAccesses[viewerId, groundPointId] = satAccess;
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

RiseSetArray
    AccessAnalyzer::find_platform_to_ground_point_accesses(std::shared_ptr<SensorPlatform> platform, const std::shared_ptr<GroundPoint> groundPoint) const
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
    const Distance atmosphereHeight = atmosphereBlocks ? _sys->get_central_body()->get_crash_radius() : 0.0 * km;
    const Distance radiusEarthMag   = _sys->get_central_body()->get_equitorial_radius() + atmosphereHeight;
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