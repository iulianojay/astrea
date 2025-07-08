#include <access/access.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <access/platforms/Sensor.hpp>


using namespace mp_units;
using namespace mp_units::angular;

using mp_units::si::unit_symbols::km;

using astro::Angle;
using astro::AstrodynamicsSystem;
using astro::Cartesian;
using astro::Distance;
using astro::RadiusVector;
using astro::State;
using astro::Time;

namespace accesslib {

AccessArray find_accesses(ViewerConstellation& constel, const Time& resolution, const AstrodynamicsSystem& sys)
{
    // Get all sats
    std::vector<Viewer> viewers = constel.get_all_spacecraft(); // TODO: this is dumb, please get sats by ref from constellation
    const std::size_t nSats = viewers.size();

    // Create time array
    const auto states = viewers.front().get_states();
    TimeVector times  = create_time_vector(states, resolution); // TODO: Check all state histories for common time frame

    // Interpolate viewer state histories to specified times
    // These are stored internally in each viewer
    interpolate_states(viewers, times, sys);

    // For each sat
    AccessArray allAccesses;
    for (std::size_t iViewer = 0; iViewer < nSats; ++iViewer) {
        Viewer& viewer1       = viewers[iViewer];
        const std::size_t id1 = viewer1.get_id();

        // For every other sat
        for (std::size_t jViewer = iViewer + 1; jViewer < nSats; ++jViewer) {
            Viewer& viewer2       = viewers[jViewer];
            const std::size_t id2 = viewer2.get_id();

            // Satellite-level access for viewer1 -> viewer2
            RiseSetArray satAccess = find_sat_to_sat_accesses(viewer1, viewer2, times, sys);

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

TimeVector create_time_vector(const StateVector& states, const Time& resolution)
{
    // Setup
    const Time& startTime = states.front().time;
    const Time& endTime   = states.back().time;

    // Fill
    Time time = startTime;
    TimeVector times;
    times.emplace_back(time);
    while (time < endTime) {
        if (time + resolution >= endTime) { time = endTime; }
        else {
            time += resolution;
        }
        times.emplace_back(time);
    }

    return times;
}

void interpolate_states(std::vector<Viewer>& viewers, const TimeVector& times, const AstrodynamicsSystem& sys)
{
    for (const auto& time : times) {
        for (auto& viewer : viewers) {
            viewer.get_state_at(time, sys);
        }
    }
}

RiseSetArray
    find_sat_to_sat_accesses(Viewer& viewer1, Viewer& viewer2, const TimeVector& times, const AstrodynamicsSystem& sys, const bool& twoWay)
{
    // Get all access info once to avoid unnecessary calcs
    std::vector<AccessInfo> accessInfo(times.size());
    std::size_t ii = 0;
    for (const auto& time : times) {
        // Get sat1 -> sat2 vector at current time
        accessInfo[ii].time       = time;
        accessInfo[ii].id1        = viewer1.get_id();
        accessInfo[ii].id2        = viewer2.get_id();
        accessInfo[ii].state1     = viewer1.get_closest_state(time).elements.in<Cartesian>(sys);
        accessInfo[ii].state2     = viewer2.get_closest_state(time).elements.in<Cartesian>(sys);
        accessInfo[ii].isOcculted = is_earth_occulting(accessInfo[ii].state1, accessInfo[ii].state2, sys);
        ++ii;
    }

    // Determine access sensor by sensor
    RiseSetArray satAccess;
    for (auto& sensor1 : viewer1.get_sensors()) {
        for (auto& sensor2 : viewer2.get_sensors()) {
            // Calculate sensor1 <-> sensor2 accesses
            RiseSetArray sensorAccess = find_sensor_to_sensor_accesses(accessInfo, sensor1, sensor2, twoWay);

            // Store
            if (sensorAccess.size() > 0) {
                satAccess = (satAccess | sensorAccess);
                sensor1.add_access(sensor2.get_id(), sensorAccess);
                sensor2.add_access(sensor1.get_id(), sensorAccess);
            }
        }
    }

    return satAccess;
}

bool is_earth_occulting(const Cartesian& state1, const Cartesian& state2, const AstrodynamicsSystem& sys)
{
    // NOTE: Only checking one direction. Blocking 1->2 automatically means blocking 2->1
    // NOTE: Assumes Earth-centered
    // NOTE: Assumes spherical Earth

    // TODO: Make subtraction operator for RadiusVector
    // Also make RadiusVector a class with utilities like magnitude, etc.
    RadiusVector nadir1 = state1.get_radius();
    for (std::size_t ii = 0; ii < 3; ++ii) {
        nadir1[ii] = -nadir1[ii];
    }
    const Distance nadir1Mag = norm(nadir1);

    // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
    const Cartesian& state1to2    = state2 - state1;
    const RadiusVector radius1to2 = state1to2.get_radius();

    // Get edge angle of Earth
    static const Distance& radiusEarthMag = sys.get("Earth")->get_equitorial_radius() + 100 * km; // TODO: Generalize for any body?
    const Angle earthLimbAngle = asin(radiusEarthMag / nadir1Mag); // Assume this is good for all angles (circular Earth) - TODO: Fix

    // Get angle from boresight and sat to nadir
    const Angle satelliteNadirAngle = calculate_angle_between_vectors(nadir1, radius1to2);

    // If nadir->satellite angle greater than Earth limb, Earth cannot block
    if (satelliteNadirAngle <= earthLimbAngle) {
        // Satellite is within Earth limb, check which is closer
        const Distance radius1to2Mag  = norm(radius1to2);
        const Distance earthLimbRange = nadir1Mag * cos(earthLimbAngle);

        // If outside farthest Earth limb distance - Earth must be blocking
        if (radius1to2Mag > earthLimbRange) { return true; }
    }
    return false;
}

RiseSetArray
    find_sensor_to_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor1, const Sensor& sensor2, const bool& twoWay)
{
    Time rise, set;
    bool insideAccessInterval;
    RiseSetArray access;
    const Time start = accessInfo.front().time;
    const Time end   = accessInfo.back().time;
    for (const auto& specificAccessInfo : accessInfo) {
        // Extract
        const Time& time        = specificAccessInfo.time;
        const Cartesian& state1 = specificAccessInfo.state1;
        const Cartesian& state2 = specificAccessInfo.state2;
        const bool& isOcculted  = specificAccessInfo.isOcculted;

        // TODO: Make this pointing generic, certainly not done at this level
        RadiusVector nadir1 = state1.get_radius();
        RadiusVector nadir2 = state2.get_radius();

        // TODO: Make subtraction operator for RadiusVector
        // Also make RadiusVector a class with utilities like magnitude, etc.
        for (std::size_t ii = 0; ii < 3; ++ii) {
            nadir1[ii] = -nadir1[ii];
            nadir2[ii] = -nadir2[ii];
        }

        const RadiusVector boresight1 = nadir1;
        const RadiusVector boresight2 = nadir2;

        // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
        const Cartesian& state1to2 = state2 - state1;
        const Cartesian& state2to1 = state1 - state2;

        const RadiusVector radius1to2 = state1to2.get_radius();
        const RadiusVector radius2to1 = state1to2.get_radius();

        // Check if they can see each other
        bool sensorsInView;
        if (isOcculted) { sensorsInView = false; }
        else if (twoWay) {
            sensorsInView = sensor1.contains(boresight1, radius1to2) && sensor2.contains(boresight2, radius2to1);
        }
        else {
            sensorsInView = sensor1.contains(boresight1, radius1to2) || sensor2.contains(boresight2, radius2to1);
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


} // namespace accesslib