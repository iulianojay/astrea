#include <access/access.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <access/platforms/Sensor.hpp>


using namespace mp_units;
using namespace mp_units::si;

using astro::AstrodynamicsSystem;
using astro::Cartesian;
using astro::Constellation;
using astro::RadiusVector;
using astro::State;
using astro::Time;

namespace accesslib {

void find_accesses(Constellation<Viewer>& constel, const Time& resolution, const AstrodynamicsSystem& sys)
{

    // Get all sats
    auto allSats            = constel.get_all_spacecraft();
    const std::size_t nSats = allSats.size();

    // Create time array
    std::vector<Time> times =
        create_time_vector(allSats[0].get_states(), resolution, sys); // TODO: Check all state histories for common time frame

    // Get and store interpolated states in cartesian to reduce overhead
    std::vector<std::vector<State>> interpStates = interpolate_states(allSats, times, sys);

    // For each sat
    for (std::size_t iSat = 0; iSat < nSats; ++iSat) {
        Viewer& sat1          = allSats[iSat];
        const std::size_t id1 = sat1.get_id();

        // For every other sat
        for (std::size_t jSat = iSat + 1; jSat < nSats; ++jSat) {
            Viewer& sat2          = allSats[jSat];
            const std::size_t id2 = sat2.get_id();

            // Satellite-level access for sat1 -> sat2
            RiseSetArray satAccess = find_sat_to_sat_accesses(iSat, jSat, sat1, sat2, times, interpStates, sys);

            // Store
            if (satAccess.size() > 0) {
                sat1.add_access(id2, satAccess);
                sat2.add_access(id1, satAccess);
            }
        }
    }
}

std::vector<Time> create_time_vector(const std::vector<State>& states, const Time& resolution, const AstrodynamicsSystem& sys)
{
    // Setup
    const std::size_t nSates = states.size();
    const Time& startTime    = states[0].time;
    const Time& endTime      = states[nSates - 1].time;

    // Fill
    std::vector<Time> times;

    int ii    = 0;
    Time time = startTime;
    while (time < endTime) {
        if (time + resolution > endTime) { times.emplace_back(endTime); }
        else {
            times.emplace_back(time);
        }
        time += ii * resolution;
        ++ii;
    }

    return times;
}

std::vector<std::vector<State>>
    interpolate_states(const std::vector<Viewer>& allSats, const std::vector<Time>& times, const AstrodynamicsSystem& sys)
{

    const std::size_t nTimes = times.size();
    const std::size_t nSats  = allSats.size();

    std::vector<std::vector<State>> interpStates;
    interpStates.resize(nTimes);

    for (std::size_t iTime = 0; iTime < nTimes; ++iTime) {

        const Time& time = times[iTime];
        interpStates[iTime].resize(nSats);

        for (std::size_t iSat = 0; iSat < nSats; ++iSat) {

            const Viewer& sat = allSats[iSat];
            const State state = sat.get_state_at(time, sys);

            const auto elements       = state.elements.in<Cartesian>(sys);
            interpStates[iTime][iSat] = State(time, elements);
        }
    }

    return interpStates;
}

RiseSetArray find_sat_to_sat_accesses(
    const std::size_t& iSat,
    const std::size_t& jSat,
    Viewer& sat1,
    Viewer& sat2,
    const std::vector<Time>& times,
    const std::vector<std::vector<State>>& states,
    const AstrodynamicsSystem& sys
)
{

    // Total sat to sat access
    RiseSetArray satAccess;

    // First determine access sensor by sensor
    for (auto& sensor1 : sat1.get_sensors()) {
        const std::size_t id1 = sensor1.get_id();

        for (auto& sensor2 : sat2.get_sensors()) {
            const std::size_t id2 = sensor1.get_id();

            RiseSetArray access = find_sensor_to_sensor_accesses(iSat, jSat, sensor1, sensor2, times, states, sys);

            // Store
            satAccess = (satAccess | access);
            if (access.size() > 0) { // TODO: Check 2-way access
                sensor1.add_access(id2, access);
                sensor2.add_access(id1, access);
            }
        }
    }

    return satAccess;
}


RiseSetArray find_sensor_to_sensor_accesses(
    const std::size_t& iSat,
    const std::size_t& jSat,
    const Sensor& sensor1,
    const Sensor& sensor2,
    const std::vector<Time>& times,
    const std::vector<std::vector<State>>& states,
    const AstrodynamicsSystem& sys
)
{

    RiseSetArray access;
    Time rise;
    bool hasAccess;
    for (std::size_t iTime = 0; iTime < states.size(); ++iTime) {

        // Get states
        const State& state1 = states[iTime][iSat];
        const State& state2 = states[iTime][jSat];

        const Cartesian& state1to2    = state2.elements.in<Cartesian>(sys) - state1.elements.in<Cartesian>(sys);
        const RadiusVector radius1to2 = state1to2.get_radius();

        // Manage bookends
        if (iTime == 0) {
            hasAccess = sensor1.contains(radius1to2);
            if (hasAccess) { rise = times[0]; }
            continue;
        }
        else if (iTime == states.size() - 1) {
            if ((hasAccess && sensor1.contains(radius1to2))) { access.append(rise, times[iTime]); }

            // NOTE: this ignores cases where the last time is a rise time -> access analyzed for [0, T)
        }

        // Check for rise/set times
        if (hasAccess && !sensor1.contains(radius1to2)) {
            hasAccess = false;

            access.append(rise, times[iTime]);
        }
        else if (!hasAccess && sensor1.contains(radius1to2)) {
            hasAccess = true;
            rise      = times[iTime];
        }
    }

    return access;
}

} // namespace accesslib