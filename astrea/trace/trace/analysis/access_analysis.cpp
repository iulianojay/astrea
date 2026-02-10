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

#include <trace/analysis/access_analysis.hpp>

#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>
#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

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
using astro::RadiusVector;
using astro::State;
using astro::StateHistory;
using astro::VelocityVector;

namespace trace {

using namespace mp_units;
using namespace mp_units::angular;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;


struct AccessInfo {
    Time time;               // Time of access
    EciRadiusVec radius1to2; // Vector from the first object to the second object at the time of access
    std::size_t id1;         // ID of the first object
    std::size_t id2;         // ID of the second object
    bool isOcculted;         // Flag indicating if the access is occulted
};


AccessArray AccessAnalyzer::find_internal_accesses(ViewerConstellation& constel)
{
    // For each sat
    AccessArray allAccesses;
    std::cout << std::endl;
    utilities::ProgressBar progressBar(constel.size() * (constel.size() - 1) / 2, "\tSat->Sat Access");
    for (std::size_t iViewer = 0; iViewer < constel.size(); ++iViewer) {
        Viewer& viewer1       = constel[iViewer];
        const std::size_t id1 = viewer1.get_id();

        // For every other sat
        for (std::size_t jViewer = iViewer + 1; jViewer < constel.size(); ++jViewer) {
            Viewer& viewer2       = constel[jViewer];
            const std::size_t id2 = viewer2.get_id();

            // Satellite-level access for viewer1 -> viewer2
            RiseSetArray satAccess = find_platform_to_platform_accesses(&viewer1, &viewer2);

            // Store
            if (satAccess.size() > 0) {
                viewer1.add_access(id2, satAccess);
                viewer2.add_access(id1, satAccess);
                allAccesses[id1, id2] = satAccess; // TODO: Consider id2->id1 as well
            }
            progressBar();
        }
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const bool includeInternalAccesses)
{
    _positionHistory.clear();
    for (const auto& date : _dates) {
        for (auto& shell : constel.get_shells()) {
            for (auto& plane : shell.get_planes()) {
                for (Viewer& viewer : plane.get_all_spacecraft()) {
                    const std::size_t viewerId           = viewer.get_id();
                    _positionHistory[{ viewerId, date }] = viewer.get_inertial_position(date);
                }
            }
        }

        for (auto& ground : grounds) {
            const std::size_t groundId           = ground.get_id();
            _positionHistory[{ groundId, date }] = ground.get_inertial_position(date);
        }
    }

    // For each sat
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel) : AccessArray();

    std::cout << std::endl;
    utilities::ProgressBar progressBar(constel.size(), "\tSat->Ground Access");
    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (Viewer& viewer : plane.get_all_spacecraft()) {
                const std::size_t viewerId = viewer.get_id();

                // For every other sat
                for (auto& ground : grounds) {
                    const std::size_t groundId = ground.get_id();

                    // Satellite-level access for viewer1 -> viewer2
                    RiseSetArray satAccess = find_platform_to_platform_accesses(&viewer, &ground);

                    // Store
                    if (satAccess.size() > 0) {
                        viewer.add_access(groundId, satAccess);
                        ground.add_access(viewerId, satAccess);
                        allAccesses[viewerId, groundId] = satAccess; // TODO: Consider id2->id1 as well
                    }
                }
                progressBar();
            }
        }
    }

    return allAccesses;
}

AccessArray AccessAnalyzer::find_accesses(ViewerConstellation& constel, Grid& grid, const bool includeInternalAccesses)
{
    _positionHistory.clear();
    for (const auto& date : _dates) {
        for (auto& shell : constel.get_shells()) {
            for (auto& plane : shell.get_planes()) {
                for (Viewer& viewer : plane.get_all_spacecraft()) {
                    const std::size_t viewerId           = viewer.get_id();
                    _positionHistory[{ viewerId, date }] = viewer.get_inertial_position(date);
                }
            }
        }

        for (auto& ground : grid) {
            const std::size_t groundId           = ground.get_id();
            _positionHistory[{ groundId, date }] = ground.get_lla().get_position(date, ground.get_parent());
        }
    }

    // For each sat
    AccessArray allAccesses = includeInternalAccesses ? find_internal_accesses(constel) : AccessArray();

    std::cout << std::endl;
    utilities::ProgressBar progressBar(constel.size(), "\tSat->Grid Access");
    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (Viewer& viewer : plane.get_all_spacecraft()) {
                const std::size_t viewerId = viewer.get_id();

                // For every other sat
                for (auto& groundPoint : grid) {
                    const std::size_t groundId = groundPoint.get_id();

                    // Satellite-level access for viewer1 -> ground point
                    RiseSetArray satAccess = find_platform_to_ground_point_accesses(&viewer, groundPoint);

                    // Store
                    if (satAccess.size() > 0) {
                        viewer.add_access(groundId, satAccess);
                        groundPoint.add_access(viewerId, satAccess);
                        allAccesses[viewerId, groundId] = satAccess; // TODO: Consider id2->id1 as well
                    }
                }
                progressBar();
            }
        }
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

RiseSetArray AccessAnalyzer::find_platform_to_platform_accesses(SensorPlatform* platform1, SensorPlatform* platform2, const bool twoWay)
{
    // Get all access info once to avoid unnecessary calcs
    std::vector<AccessInfo> accessInfo(_dates.size());
    std::size_t ii   = 0;
    const Date epoch = _dates[0];
    for (const auto& date : _dates) {
        // Get ECI state of ground station
        const EciRadiusVec position1 = _positionHistory.at({ platform1->get_id(), date });
        const EciRadiusVec position2 = _positionHistory.at({ platform2->get_id(), date });

        // Get sat -> ground vector at current time
        accessInfo[ii].time       = date - epoch;
        accessInfo[ii].id1        = platform1->get_id();
        accessInfo[ii].id2        = platform2->get_id();
        accessInfo[ii].radius1to2 = position2 - position1;
        accessInfo[ii].isOcculted = is_earth_occulting(position1, position2);
        ++ii;
    }

    // Determine access sensor by sensor
    RiseSetArray access;
    for (auto& sensor1 : platform1->get_payloads()) {
        for (auto& sensor2 : platform2->get_payloads()) {
            RiseSetArray sensorAccess = find_sensor_to_sensor_accesses(accessInfo, sensor1, sensor2, twoWay);

            // Store
            if (sensorAccess.size() > 0) {
                access = (access | sensorAccess);
                sensor1.add_access(sensor2.get_id(), sensorAccess);
                sensor2.add_access(sensor1.get_id(), sensorAccess);
            }
        }
    }

    return access;
}

RiseSetArray AccessAnalyzer::find_platform_to_ground_point_accesses(astro::PayloadPlatform<Sensor>* platform, const GroundPoint& groundPoint)
{
    // Get all access info once to avoid unnecessary calcs
    std::vector<AccessInfo> accessInfo(_dates.size());
    std::size_t ii   = 0;
    const Date epoch = _startDate;
    for (const auto& date : _dates) {
        // Get ECI state of ground station
        const EciRadiusVec position1 = _positionHistory.at({ platform->get_id(), date });
        const EciRadiusVec position2 = _positionHistory.at({ groundPoint.get_id(), date });

        // Get sat -> ground vector at current time
        accessInfo[ii].time       = date - epoch;
        accessInfo[ii].id1        = platform->get_id();
        accessInfo[ii].id2        = groundPoint.get_id();
        accessInfo[ii].radius1to2 = position2 - position1;
        accessInfo[ii].isOcculted = is_earth_occulting(position1, position2);
        ++ii;
    }

    // Determine access sensor by sensor
    RiseSetArray access;
    for (auto& sensor : platform->get_payloads()) {
        const RiseSetArray sensorAccess = find_sensor_to_ground_point_accesses(accessInfo, sensor, groundPoint);

        // Store
        if (sensorAccess.size() > 0) {
            access = (access | sensorAccess);
            sensor.add_access(groundPoint.get_id(), sensorAccess);
        }
    }

    return access;
}

bool AccessAnalyzer::is_earth_occulting(const EciRadiusVec& position1, const EciRadiusVec& position2)
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
    static const Distance& radiusEarthMag = _sys->get_body(CelestialBodyId::EARTH)->get_equitorial_radius() + 100.0 * km; // TODO: Generalize for any body?
    const Angle earthLimbAngle = asin(radiusEarthMag / nadir1Mag); // Assume this is good for all angles (circular Earth) - TODO: Fix

    // Get angle from boresight and sat to nadir
    const Angle satelliteNadirAngle = nadir1.offset_angle(radius1to2);

    // If nadir->satellite angle greater than Earth limb, Earth cannot block
    if (satelliteNadirAngle <= earthLimbAngle) {
        // Satellite is within Earth limb, check which is closer
        const Distance radius1to2Mag  = radius1to2.norm();
        const Distance earthLimbRange = nadir1Mag * cos(earthLimbAngle);

        // If outside farthest Earth limb distance - Earth must be blocking
        if (radius1to2Mag > earthLimbRange) { return true; }
    }
    return false;
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

} // namespace trace
} // namespace astrea