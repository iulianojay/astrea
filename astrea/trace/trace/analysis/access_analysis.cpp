#include <trace/trace.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <astro/state/frames/frames.hpp>
#include <astro/utilities/conversions.hpp>
#include <utilities/ProgressBar.hpp>

#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/types/typedefs.hpp>


using namespace mp_units;
using namespace mp_units::angular;

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

namespace astrea {

using astro::AstrodynamicsSystem;
using astro::Cartesian;
using astro::Date;
using astro::ECEF;
using astro::ECI;
using astro::RadiusVector;
using astro::State;
using astro::StateHistory;
using astro::VelocityVector;

namespace trace {

AccessArray find_internal_accesses(ViewerConstellation& constel, const Time& resolution, const Date& epoch, const AstrodynamicsSystem& sys)
{
    // Create time array
    const auto& states    = constel[0].get_state_history();
    const Date& startDate = states.first().get_epoch();
    const Date& endDate   = states.last().get_epoch();

    TimeVector times = create_time_vector(0.0 * s, endDate - startDate, resolution); // TODO: Check all state histories for common time frame

    // For each sat
    AccessArray allAccesses;
    for (std::size_t iViewer = 0; iViewer < constel.size(); ++iViewer) {
        Viewer& viewer1       = constel[iViewer];
        const std::size_t id1 = viewer1.get_id();

        // For every other sat
        for (std::size_t jViewer = iViewer + 1; jViewer < constel.size(); ++jViewer) {
            Viewer& viewer2       = constel[jViewer];
            const std::size_t id2 = viewer2.get_id();

            // Satellite-level access for viewer1 -> viewer2
            RiseSetArray satAccess = find_platform_to_platform_accesses(&viewer1, &viewer2, times, sys, epoch);

            // Store
            if (satAccess.size() > 0) {
                viewer1.add_access(id2, satAccess);
                viewer2.add_access(id1, satAccess);
                allAccesses[id1, id2] = satAccess; // TODO: Consider id2->id1 as well
            }
        }
    }

    return allAccesses;
}

AccessArray find_accesses(ViewerConstellation& constel, GroundArchitecture& grounds, const Time& resolution, const Date& epoch, const AstrodynamicsSystem& sys)
{
    // TODO: Rework all this into a class

    // Create time array
    const auto& states    = constel[0].get_state_history();
    const Date& startDate = states.first().get_epoch();
    const Date& endDate   = states.last().get_epoch();

    TimeVector times = create_time_vector(0.0 * s, endDate - startDate, resolution); // TODO: Check all state histories for common time frame

    // For each sat
    // AccessArray allAccesses = find_accesses(constel, resolution, sys); // Do sat-sat first?
    AccessArray allAccesses;
    std::cout << std::endl;
    utilities::ProgressBar progressBar(constel.size(), "\tAccess");
    for (auto& shell : constel.get_shells()) {
        for (auto& plane : shell.get_planes()) {
            for (Viewer& viewer : plane.get_all_spacecraft()) {
                const std::size_t viewerId = viewer.get_id();

                // For every other sat
                for (auto& ground : grounds) {
                    const std::size_t groundId = ground.get_id();

                    // Satellite-level access for viewer1 -> viewer2
                    RiseSetArray satAccess = find_platform_to_platform_accesses(&viewer, &ground, times, sys, epoch);

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

TimeVector create_time_vector(const Time& start, const Time& end, const Time& resolution)
{
    // Fill
    Time time = start;
    TimeVector times;
    times.emplace_back(time);
    while (start + time < end) {
        if (start + time + resolution >= end) { time = end; }
        else {
            time += resolution;
        }
        times.emplace_back(time);
    }

    return times;
}

RiseSetArray find_platform_to_platform_accesses(
    SensorPlatform* platform1,
    SensorPlatform* platform2,
    const TimeVector& times,
    const AstrodynamicsSystem& sys,
    const Date& epoch,
    const bool& twoWay
)
{
    // Get all access info once to avoid unnecessary calcs
    std::vector<AccessInfo> accessInfo(times.size());
    std::size_t ii = 0;
    for (const auto& time : times) {
        // Get ECI state of ground station
        const Date date                   = epoch + time;
        const RadiusVector<ECI> position1 = platform1->get_inertial_position(date);
        const RadiusVector<ECI> position2 = platform2->get_inertial_position(date);

        // Get sat -> ground vector at current time
        accessInfo[ii].time       = time;
        accessInfo[ii].id1        = platform1->get_id();
        accessInfo[ii].id2        = platform2->get_id();
        accessInfo[ii].position1  = position1;
        accessInfo[ii].position2  = position2;
        accessInfo[ii].isOcculted = is_earth_occulting(position1, position2, sys);
        ++ii;
    }

    // Determine access sensor by sensor
    RiseSetArray access;
    for (auto& sensor1 : platform1->get_payloads()) {
        for (auto& sensor2 : platform2->get_payloads()) {
            RiseSetArray sensorAccess = find_sensor_to_sensor_accesses(accessInfo, sensor1, sensor2, twoWay, epoch);

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

bool is_earth_occulting(const RadiusVector<ECI>& position1, const RadiusVector<ECI>& position2, const AstrodynamicsSystem& sys)
{
    // NOTE: Only checking one direction. Blocking 1->2 automatically means blocking 2->1
    // NOTE: Assumes Earth-centered
    // NOTE: Assumes spherical Earth

    // Also make RadiusVector<ECI> a class with utilities like magnitude, etc.
    const RadiusVector<ECI> nadir1 = -position1;
    const Distance nadir1Mag       = nadir1.norm();

    // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
    const RadiusVector<ECI> radius1to2 = position2 - position1;

    // Get edge angle of Earth
    static const Distance& radiusEarthMag = sys.get("Earth")->get_equitorial_radius() + 100.0 * km; // TODO: Generalize for any body?
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
    find_sensor_to_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor1, const Sensor& sensor2, const bool& twoWay, const Date& epoch)
{
    Time rise, set;
    bool insideAccessInterval = false;
    RiseSetArray access;
    const Time start = accessInfo.front().time;
    const Time end   = accessInfo.back().time;
    for (const auto& specificAccessInfo : accessInfo) {
        // Extract
        const Time& time                   = specificAccessInfo.time;
        const RadiusVector<ECI>& position1 = specificAccessInfo.position1; // TODO: + attachment point?
        const RadiusVector<ECI>& position2 = specificAccessInfo.position2;
        const bool& isOcculted             = specificAccessInfo.isOcculted;

        // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
        const RadiusVector<ECI>& radius1to2 = position2 - position1;
        const RadiusVector<ECI>& radius2to1 = position1 - position2;

        // Check if they can see each other
        const Date date = epoch + time;
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

} // namespace trace
} // namespace astrea