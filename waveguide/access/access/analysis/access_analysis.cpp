#include <access/access.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <access/platforms/Sensor.hpp>


using namespace mp_units;
using namespace mp_units::si;

using astro::AstrodynamicsSystem;
using astro::Cartesian;
using astro::RadiusVector;
using astro::State;
using astro::Time;

namespace accesslib {

void find_accesses(ViewerConstellation& constel, const Time& resolution, const AstrodynamicsSystem& sys)
{
    // Get all sats
    std::vector<Viewer> viewers = constel.get_all_spacecraft();
    const std::size_t nSats     = viewers.size();

    // Create time array
    const auto states = viewers.front().get_states();
    TimeVector times  = create_time_vector(states, resolution); // TODO: Check all state histories for common time frame

    // Interpolate viewer state histories to specified times
    // These are stored internally in each viewer
    interpolate_states(viewers, times, sys);

    // For each sat
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
            }
        }
    }
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
    // Total sat to sat access
    RiseSetArray satAccess;

    // Determine access sensor by sensor
    for (auto& sensor1 : viewer1.get_sensors()) {
        for (auto& sensor2 : viewer2.get_sensors()) {

            // Calculate sensor1 -> sensor2 accesses
            RiseSetArray sensorAccess = find_sensor_to_sensor_accesses(viewer1, sensor1, viewer2, sensor2, times, sys, twoWay);

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

RiseSetArray find_sensor_to_sensor_accesses(
    const Viewer& viewer1,
    const Sensor& sensor1,
    const Viewer& viewer2,
    const Sensor& sensor2,
    const TimeVector& times,
    const astro::AstrodynamicsSystem& sys,
    const bool& twoWay
)
{
    Time rise, set;
    bool insideAccessInterval;
    RiseSetArray access;
    for (const auto& time : times) {
        // Get sat1 -> sat2 vector at current time
        const State& state1 = viewer1.get_closest_state(time); // closest state should be exact
        const State& state2 = viewer2.get_closest_state(time);

        // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
        const Cartesian& state1to2 = state2.elements.in<Cartesian>(sys) - state1.elements.in<Cartesian>(sys);
        const Cartesian& state2to1 = state1.elements.in<Cartesian>(sys) - state2.elements.in<Cartesian>(sys);

        const RadiusVector radius1to2 = state1to2.get_radius();
        const RadiusVector radius2to1 = state1to2.get_radius();

        // Check if they can see each other
        bool sensorsInView = false;
        if (twoWay) { sensorsInView = sensor1.contains(radius1to2) && sensor2.contains(radius2to1); }
        else {
            sensorsInView = sensor1.contains(radius1to2) || sensor2.contains(radius2to1);
        }

        // Manage bookends
        if (time == times.front()) {
            insideAccessInterval = sensorsInView;
            if (insideAccessInterval) // Consider the start time the initial rise
            {
                rise = times.front();
            }
            continue;
        }
        else if (time == times.back()) {
            if ((insideAccessInterval && sensorsInView)) { // Consider the final time the last set
                access.append(rise, times.back());
                continue;
            }
            // NOTE: this ignores cases where the last time is a rise time -> access analyzed for [0, T)
        }

        // Check for rise/set times
        if (insideAccessInterval && !sensorsInView) { // previous time had access, this time does not -> last time was a set
            insideAccessInterval = false;
            access.append(rise, set);
        }
        else if (insideAccessInterval && sensorsInView) { // previous time had access, and so does this one -> store set time and continue
            set = time;
        }
        else if (!insideAccessInterval && sensorsInView) { // previous time didn't have access, this time does -> this time is a rise
            insideAccessInterval = true;
            rise                 = time;
        }
    }
    return access;
}


} // namespace accesslib