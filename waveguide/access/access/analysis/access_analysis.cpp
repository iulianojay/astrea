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

std::vector<Viewer> find_accesses(ViewerConstellation& constel, const Time& resolution, const AstrodynamicsSystem& sys)
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

    return viewers; // TODO: this is dumb, please get sats by ref from constellation
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

        const Cartesian state1Cart = state1.elements.in<Cartesian>(sys);
        const Cartesian state2Cart = state2.elements.in<Cartesian>(sys);

        // TODO: Make this pointing generic, certainly not done at this level
        RadiusVector nadir1 = state1Cart.get_radius();
        RadiusVector nadir2 = state2Cart.get_radius();

        // TODO: Make subtraction operator for RadiusVector
        // Also make RadiusVector a class with utilities like magnitude, etc.
        for (std::size_t ii = 0; ii < 3; ++ii) {
            nadir1[ii] = -nadir1[ii];
            nadir2[ii] = -nadir2[ii];
        }

        const RadiusVector boresight1 = nadir1;
        const RadiusVector boresight2 = nadir2;

        // TODO: This subtraction will be duplicated many times. Look into doing elsewhere
        const Cartesian& state1to2 = state2Cart - state1Cart;
        const Cartesian& state2to1 = state1Cart - state2Cart;

        const RadiusVector radius1to2 = state1to2.get_radius();
        const RadiusVector radius2to1 = state1to2.get_radius();

        // Check if they can see each other
        bool sensorsInView = false;
        if (twoWay) { sensorsInView = sensor1.contains(nadir1, radius1to2) && sensor2.contains(nadir2, radius2to1); }
        else {
            sensorsInView = sensor1.contains(nadir1, radius1to2) || sensor2.contains(nadir2, radius2to1);
        }

        // Need to check if Earth is blocking
        // TODO: If this condition is ever hit, we never need to check these sensors at this time again.
        // Need a way to skip unnecessary calcs
        // NOTE: Only checking one direction. Blocking 1->2 automatically means blocking 2->1
        if (sensorsInView) {
            // Get edge angle of Earth
            static const Distance& radiusEarthMag =
                sys.get("Earth")->get_equitorial_radius() + 100 * km; // TODO: Generalize for any body?
            const Distance nadir1Mag = norm(nadir1);
            const Angle earthLimbAngle =
                atan(radiusEarthMag / nadir1Mag); // Assume this is good for all angles (circular Earth) - TODO: Fix

            // Get angle from boresight and sat to nadir
            const Angle boresightNadirAngle = calculate_angle_between_vectors(boresight1, nadir1);
            const Angle satelliteNadirAngle = calculate_angle_between_vectors(boresight1, radius1to2);

            // If nadir->satellite angle greater than Earth limb, Earth cannot block
            if (satelliteNadirAngle <= earthLimbAngle) {
                // Satellite is within Earth limb, check which is closer
                const Distance radius1to2Mag = norm(radius1to2);
                const Distance maxEarthLimb  = nadir1Mag / cos(earthLimbAngle);
                if (radius1to2Mag > maxEarthLimb) { // Outside farthest Earth limb distance - Earth must be blocking
                    sensorsInView = false;
                    continue;
                }
                else if (radius1to2Mag > nadir1Mag - radiusEarthMag) { // Outside closest nadir distance - Earth might be blocking
                    // Closer than earth limb, but farther than ground directly below
                    // There's no way I got these equations right
                    const auto A = 1.0 / (sin(satelliteNadirAngle) * sin(satelliteNadirAngle));
                    const auto B = -2.0 * nadir1Mag;
                    const auto C = radiusEarthMag * radiusEarthMag / (tan(satelliteNadirAngle) * tan(satelliteNadirAngle)) -
                                   nadir1Mag * nadir1Mag;
                    const Distance a = -B + sqrt(B * B - 4 * A * C) / (2 * A);
                    const Distance b = (nadir1Mag - a) * tan(satelliteNadirAngle);
                    const Distance d = sqrt((nadir1Mag - a) * (nadir1Mag - a) + b * b);

                    if (d < radius1to2Mag) // Satellite is farther than sat 1->2 distance - Earth is blocking
                    {
                        sensorsInView = false;
                        continue;
                    }
                }
            }
        }

        // Manage bookends
        if (time == times.front()) {
            insideAccessInterval = sensorsInView;
            if (insideAccessInterval) // Consider the start time the initial rise
            {
                rise = time;
            }
            continue;
        }
        else if (time == times.back()) {
            if (insideAccessInterval && sensorsInView) { // Consider the final time the last set
                access.append(rise, times.back());
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